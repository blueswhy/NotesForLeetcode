// 穷搜法--暴力枚举法
#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<numeric>
#include<vector>
#include<set>
#include<string>

using namespace std;

class Solution_enumeration{
    public:
    // Subsets, 给出一个数组的所有子集
    // 迭代增量构造法
    // 时间复杂度O(2^n), 空间复杂度O(1)
    vector<vector<int>> subsetsListing(vector<int> &S){
        sort(S.begin(), S.end());
        vector<vector<int>> ret(1);
        for (auto elem : S){
            ret.reserve(ret.size() * 2);
            auto half = ret.begin() + ret.size();
            copy(ret.begin(), half, back_inserter(ret));
            for_each(half, ret.end(), [&elem](decltype (ret[0]) &e){
                e.push_back(elem);
            });       
        }
        return ret;
    }
    // 二进制法实现，该子集共有2^n种。也可以看作是位向量法。
    // 相当于对于集合进行次序编码, 根据编码结果填充相应元素
    vector<vector<int>> subsetsListingUsingBin(vector<int> &S){
        sort(S.begin(), S.end());
        vector<vector<int>> ret;
        const size_t n = S.size();
        vector<int> v;
        for (size_t i = 0; i < 1 << n; i++){
            for (size_t j = 0; j < n; j++){
                if (i & 1 << j) v.push_back(S[j]);
            }
            ret.push_back(v);
            v.clear();
        }
        return ret;
    }
    // Subset II
    // 考虑原集合包含重复元素
    // 同样采用增量构造法和二进制法实现
    // 对于相同的元素在填充的过程中， 采取跳过的形式
    vector<vector<int>> subsetsWithDup(vector<int> &S){
        sort(S.begin(), S.end());
        vector<vector<int>> ret(1);

        size_t prevSize = 0;       // 记录被扩充的大小
        for (size_t i = 0; i < S.size(); ++i){
            const size_t size = ret.size();
            for (size_t j = 0; j <size; ++j){
                if (i == 0 || S[i] != S[i - 1] || j >= prevSize){
                    ret.push_back(ret[j]);
                    ret.back().push_back(S[i]);
                }
            }
            prevSize = size;
        }
        return ret;
    }
    vector<vector<int>> subsetsWithDupUsingBin(vector<int> &S){
        sort(S.begin(), S.end());
        set<vector<int>> ret;    // 使用set来去重
        const size_t n = S.size();
        vector<int> v;
        for (size_t i = 0; i < 1 << n; ++i){
            for (size_t j = 0; j < n; ++j){
                if (i & 1 << j){
                    v.push_back(S[j]);
                }
            }
            ret.insert(v);
            v.clear();
        }
        // 去除重合集合
        vector<vector<int>> realRet;
        copy(ret.begin(), ret.end(), back_inserter(realRet));
        return realRet;
    }
    // Permutations I & II
    // 都使用next_permutation即可
    vector<vector<int>> permute(vector<int> &num){
        vector<vector<int>> ret;
        sort(num.begin(), num.end());  // 从非递减序列开始
        do{
            ret.push_back(num);
        }while(next_permutation(num.begin(), num.end()));
        return ret;
    }
    // Combinations
    // 实现从[0, 1, 2, ..., n]序列中取出k个数的所有组合列举
    // 时间复杂度O((n - k)!)， 空间复杂度O(n)
    // 设置select变量，将排列问题降为组合问题
    vector<vector<int>> combineUsingIteration(int n, int k){
        vector<int> values(n);
        iota(values.begin(), values.end(), 1);    // 初始化为 v_k = k;
        vector<bool> select(n, false);
        fill_n(select.begin(), k, true);

        vector<vector<int>> ret;
        do{
            vector<int> temp(k);
            for (int i = 0, idx = 0; i < n; ++i){
                if (select[i]){
                    temp[idx++] = values[i];
                }
            }
            ret.push_back(temp);
        }while (prev_permutation(select.begin(), select.end()));
        // 利用排列函数作为Cn_k的计算终止条件
        return ret;
    }
    // Letter Combinations of a Phone Number
    // 拨号字母组合问题
    // 时间复杂度O(n^3)，空间复杂度O(1)

    // 拨号字母组合问题中，1代表空字符清零 0是空格
    const vector<string> keyboard{" ", "", "abc", "def", \
            "ghi", "jkl", "mno", "pqrs", "tuv", "wyxz" };
    vector<string> letterCombinations(const string &digits){
        if (digits.empty()) return vector<string>();
        vector<string> ret(1, "");       // 1*sz1*sz2*...*szN      
        for (auto d : digits){
            const size_t n = ret.size();
            const size_t m = keyboard[d - '0'].size();
            ret.resize(n * m);
            for (size_t i = 0; i < m; ++i){
                copy(ret.begin(), ret.begin() + n, ret.begin() + n * i);
            }
            for (size_t i = 0; i < m; ++i){
                auto begin = ret.begin();
                for_each(begin + n*i, begin + n * (i + 1), [&](string &s){
                    s += keyboard[d - '0'][i];
                });
            }
        }
        return ret;
    }
    private:
    
    // next_permutation的基本思想
    // S1: 从右到左找到第一个不满足递增方向的地方，记作pivot;
    // S2: 从右到左找到第一个比pivot大的地方（S1成立时， 必有），记作change;
    // S3: 交换change和pivot的数值；
    // S4: reverse所有处于pivot右边的序列
    template<typename BidiIt> 
    bool next_permutation(BidiIt first, BidiIt last){
        const auto rfirst = reverse_iterator<BidiIt>(last);
        const auto rlast = reverse_iterator<BidiIt>(first);
        auto pivot = next(rfirst);
        while (pivot != rlast && *pivot >= *prev(pivot)){
            ++pivot;
        }
        if (pivot == rlast){
            reverse(rfirst, rlast);
            return false;
        }
        auto change = find_if(rfirst, pivot, bind1st(less<int> (), *pivot));
        swap(*change, *pivot);
        reverse(rfirst, pivot);  // 注意这里rfirst和pivot的实际位置，而不是反向迭代器的逻辑位置
        return true;
    }
};
