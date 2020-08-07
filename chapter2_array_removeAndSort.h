// 下面的函数都是考虑数组算法，因此使用下标来访问各数据

#include <stdio.h>
#include <iostream>
#include <string.h>
#include <math.h>
#include <vector>
#include <iterator>
#include <stack>
#include <algorithm>
#include <numeric>
#include <unordered_map>

using namespace std;
// unique 函数, 返回去除重复项后的数组长度
class Solution1{
public:
    int removeDuplicates(vector<int>& nums){
        if(nums.empty()) return 0;
        int uniqueIndex = 0;
        for (int i = 1; i < nums.size(); i++){
            if(nums[uniqueIndex] != nums[i])
                nums[++uniqueIndex] = nums[i];
        }
        return uniqueIndex + 1;
    }
};

class Solution2{
public:
    int removeDuplicates(vector<int> &nums){
        return distance(nums.begin(), unique(nums.begin(), nums.end()));
    }
};

class Solution3{
    public:
        int removeDuplicates(vector<int> &nums){
            return distance(nums.begin(), removeDuplicates(nums.begin(), nums.end(), nums.begin()));
        }
        
        template<typename Init, typename OutIt>
        OutIt removeDuplicates(Init first, Init last, OutIt output){
            while(first != last){
                *output = *first;
                first = upper_bound(first, last, *first);
                output++;
            }
            return output;
        }
};

// 允许有多个重复，重复参数用n来表示，n=2即为允许有两个重复数
class Solution1_N{
    public:
    int removeDuplicatesN(vector<int>& nums, int n){
        if(nums.size()<=n) return nums.size();
        int uniqueIndex = n;
        for (int i = n; i < nums.size(); i++){
            if(nums[uniqueIndex - n] != nums[i])
                nums[uniqueIndex++] = nums[i];              // 注意++放在后面，和刚刚不同，是执行赋值操作后，再进行下标移动
        }
        return uniqueIndex + 1;
    }
};
// 方法二， 只针对n=2的情况，扩展性较差
class Solution2_N{
    public:
    int removeDuplicatesN(vector<int>& nums){
        const int sizeNums = nums.size();
        int uniqueIndex = 0;
        for (int i = 0; i<sizeNums; i++){
            if (i > 0 && i < sizeNums - 1 && nums[i] == nums[i - 1] && nums[i] == nums[i + 1])
                continue;
            else
                nums[uniqueIndex++] = nums[i];
        }
        return uniqueIndex + 1;
    }
};

// 在一个Rotated顺序阵列中进行搜索
// 基于二分查找设计算法， 时间复杂度O(log n)， 空间复杂度O(1)
class Solution_s1{
    public:
    int searchRotatedSortedArray(const vector<int> &nums, int target){
        int first = 0, last = nums.size();
        while (first != last){
            int mid = first + (last - first) / 2;
            if (nums[mid] == target)
                return mid;
            if (nums[first] <= nums[mid]){
                if (nums[first] <= target && target < nums[mid])
                    last = nums[mid];
                else
                    first = mid + 1;    
            }
            else
            {
                if (nums[mid] < target && target <= nums[last - 1])
                    first = mid + 1;
                else
                    last = mid;
            }
            
        }
        return -1;                   // not found
    }
}; 

// 在一个Rotated Sorted Array中允许有重复元素，则其递增序列的假设不再成立。
// 也就是以判断条件而言 n[first] <= n[mid] 不能反映[first, mid]这一段区间元素递增，还可能是都相等, 需区别看待

class Solution_s2{
    public:
    int searchRotatedSortedArrayWithDulplicates(const vector<int> &nums, int target){
        int first = 0, last = nums.size();
        while (first!=last){
            int mid = (first + last)/2;
            if (nums[first] < nums[mid]){
                if (nums[first] <= target && target < nums[mid])
                    last = mid;
                else
                    first = mid + 1;
            }
            else{
                if (nums[first] > nums[mid])
                {
                    if (target > nums[mid] && target <= nums[last-1])
                        first = mid + 1;
                    else
                        last = mid;
                }
                else
                {
                    first++;
                }
            }
        }
        return -1;
    }
};

// 给定两个顺序数组，找出两者所有元素中第k大的元素。
// 时间复杂度应该为O(log(m+n))，即相当于二分法来求整体数组的时间。
// 基于归并排序的思想设计算法，其复杂度是O(m+n)的。
// 利用两个数组的有序性，结合指针对数组进行“删除"操作
// 当查找的是两个数组的中值时， 对于偶数位数组，中位数是中间两个数的均值
class Solution_s3{
    public:
    double findMedianInTwoSortedArrays(const vector<int> &A, const vector<int> &B){
        const int m = A.size();
        const int n = B.size();
        int total = m + n;
        if (total & 0x1)
            return find_kth(A.begin(), m, B.begin(), n, total/2 + 1);
        else
            return (find_kth(A.begin(), m, B.begin(), n, total/2) + find_kth\
            (A.begin(), m, B.begin(), n, total/2 + 1))/2.0;
    }
    private:
    static int find_kth(std::vector<int>::const_iterator A, int m, \
                std:: vector<int>:: const_iterator B, int n, int k){
                    if (m > n) return find_kth(B, n, A, m, k);
                    if (m == 0) return *(B + k - 1);
                    if (k == 1) return min(*A, *B);
                    // divide k into two parts
                    int ia = min(k/2, m), ib = k - ia;
                    if (*(A + ia - 1) < *(B + ib - 1))
                        return find_kth( A + ia, m - ia, B, n, k - ia);
                    else if (*(A + ia - 1) > *(B + ib - 1))
                        return find_kth ( A, m, B + ib, n - ib, k - ib);
                    else
                        return A[ia - 1];
                }

};
// 对于一个无序的数组要求，找到其中最长的连续序列,并返回其长度。
// 如果对时间复杂度没有要求，可以先对数组进行排序，然后返回若干个连续块的长度, 比较返回。复杂度为O(nlog n)。
// 现在要求在O(n)的复杂度下完成该算法。
// 使用Hash表的方式记录每个元素是否使用，对于每个元素，以该元素为中心，向左右扩张，直到不连续为止，记录下最长的长度。
// 该算法中如果有重复元素，是不计入连续数组中的。
class Soultion_s4_Hash{
    public:
    int longestConsecutive(const vector<int> &nums){
        unordered_map<int, bool> used;
        for (auto i : nums) used[i] = false;
        int longest = 0;
        for (auto i : nums){
            if(used[i]) continue;         // 在查找过程中，被使用后即不再进行
            int length = 1;               // 每次找到一个可查找点，初始化长度值
            used[i] = true;
            for (int j = i + 1; used.find(j) != used.end(); ++j){
                used[j] = true;
                ++length;
            }
            for (int j = i - 1; used.find(j) != used.end(); --j){
                used[j] = true;
                ++length;
            }

            longest = max(longest, length);
        }
        return longest;
    }
};

// 聚类的方法, 用字典来存储聚类数组的两端, 用长度来聚类，而unorder允许重复set
class Solution_s4_Clumster{
    public:
    int longestConsecutive(vector<int> &nums){
        unordered_map<int, int> map;
        int size = nums.size();
        int length = 1;
        for (int i = 0; i < size; i++){
            if (map.find(nums[i]) != map.end()) continue;        // 如果有记录，即被标记，跳过
            map[nums[i]] = 1;                                    // 找到了，初始化长度为1
            if (map.find(nums[i] - 1) != map.end()){
                length = max(length, mergeCluster(map, nums[i] -1, nums[i]));
            }
            if (map.find(nums[i] + 1) != map.end())
                length = max(length, mergeCluster(map, nums[i], nums[i] + 1));
        }
        return size == 0 ? 0 : length;
    }
    private:
    int mergeCluster(unordered_map<int, int> &map, int left, int right){
        int upper = right + map[right] - 1;        // 记录两端的位置， 上端
        int lower = left - map[left] + 1;          // 下端位置
        int length = upper - lower + 1;
        map[upper] = length;
        map[lower] = length;
        return length;
    }
};

// 给定一组整数数组，找到其中两个数，使得其相加得到目标值
// 输出为Array中两个数的位置，而且 index1 必须小于 index2 。
// 程序输出是非0开始的，即下标按顺序来，不是按C++下标规定。找到即可。

// 方法1： hash表，存储每个对应的下标，复杂度为O(n)。使用方法1思想。

// 方法2： 先排序，然后左右夹逼。排序O(nlogn), 夹逼O(n)。不过由于需要返回下标，在排序过程中需要记录
// 原始序列和当前序列的映射关系，即排序后原始index变化。

class Solution_s5{
    public:
    vector<int> twoSum(vector<int> &nums, int target){
        unordered_map<int, int> mapping;
        vector<int> result;
        for (int i = 0; i < nums.size(); i++)    // 初始化
            mapping[nums[i]] = i; 
        for (int i = 0; i < nums.size(); i++){
            const int gap = target - nums[i];
            if (mapping.find(gap) != mapping.end() && mapping[gap] > i){
                result.push_back (i + 1);
                result.push_back (mapping[gap] + 1);
                break;                                 // 找到一个即返回，如果是多个可以将break返回
            }
        }
        return result;                     // 如果返回空数组，即没有找到
    }
};
// 上述题目的变种， 三元组问题。找出其中满足a + b + c = 0 的所有元组。
// 要求a, b, c满足递增关系，返回的三元组中不包含重复元素。
// 先排序，然后左右夹逼， 复杂度O(n^2), 也可以推广到k-sum， 先排序， 然后作k-2次循环，在
// 最内层循环左右夹逼，时间复杂度为O(max{nlogn, n^(k-1)}。
class Solution_s5_nSum{
    public:
    vector<vector<int>> threeSum(vector<int> &nums){
        vector<vector<int>> ret;
        if (nums.size() < 3) return ret;      // 如果少于3个数，直接返回空值
        sort(nums.begin(), nums.end());
        const int target = 0;

        auto last = nums.end();
        for (auto i = nums.begin(); i < last - 2; i++){
            auto j = i + 1;
            if (i > nums.begin() && *i == *(i-1)) continue;
            auto k = last - 1;
            while (j < k){
                if (*i + *j + *k < target){
                    ++j;
                    while(*j == *(j-1) && j < k) ++j;   //重复元素向前挪动
                }
                else if (*i + *j + *k > target){
                    --k;
                    while (*k == *(k+1) && k > j) --k;
                }
                else
                {
                    ret.push_back({*i, *j, *k});
                    ++j;                                // 以i为出发点，继续夹逼符合条件的（j, k)元组
                    --k;
                    while(*j == *(j-1) && *k == *(k+1) && j<k) ++j;
                }
                
            }

        }
        return ret;
    }
    // 上述问题的再次变种，找到数组中最接近于target的三元组
    // perv函数： 获取一个距离离指定迭代器n个元素的迭代器，使用的迭代器只能是双向迭代器或者随机访问迭代器，n可以取正数或者负数指示方向
    int threeSumClosest(vector<int> &nums, int target){
        int ret = 0;
        int min_gap = INT_MAX;         // 初始值极大
        sort(nums.begin(), nums.end());
        for (auto a = nums.begin(); a != prev(nums.end(), 2); ++a){
            auto b = next(a);
            auto c = prev(nums.end());   // 两边夹逼
            while (b < c){
                const int sum = *a + *b + *c;
                const int gap = abs(target - sum);
                if (gap < min_gap){
                    ret = sum;
                    min_gap = gap;
                }
                if (sum < target) ++b;
                else if (sum > target) --c;
                else
                    return 0;
                
            }
        }
        return ret;
    }
    // 4Sum: 先用一个hashmap来缓存两个数的和，最终复杂度为O(n^3), 定下两项后夹逼
    vector<vector<int>> fourSumExhausting(vector<int> &nums, int target){
        vector<vector<int>> ret;
        if (nums.size()<4) return ret;
        sort (nums.begin(), nums.end());
        auto last = nums.end();
        for (auto a = nums.begin(); a < prev(last, 3); a++){
            for (auto b = next(a); b < prev(last, 2); b++){
                auto c = next(b);
                auto d = prev(last);
                while (c<d){
                    if (*a + *b + *c + *d < target){
                        c++;
                    }else if (*a + *b + *c + *d > target){
                        d--;
                    }
                    else {
                        ret.push_back({*a, *b, *c, *d});
                        ++c;
                        --d;
                    }
                }
            }
        }
        sort(ret.begin(), ret.end());
        ret.erase(unique(ret.begin(), ret.end()), ret.end());     // 清除多余元素
        return ret;
    }
    // 使用hashMap作为缓存提高效率， 时间复杂度平均O(n^2)空间复杂度O(n^2)
    vector<vector<int>> fourSumHashMap(vector<int> &nums, int target){
        vector<vector<int>> ret;
        if (nums.size() < 4) return ret;
        sort (nums.begin(), nums.end());

        unordered_map<int, vector<pair<int, int>>> cache;
        for (size_t a = 0; a < nums.size(); ++a){
            for (size_t b = a + 1; b < nums.size(); ++b){
                cache[nums[a] + nums[b]].push_back(pair<int, int>(a, b));
            }
        }
        for (int c = 0; c < nums.size(); ++c){
            for (size_t d = c + 1; d < nums.size(); ++d){
                const int key = target - nums[c] - nums[d];   // 找到需要的值
                if (cache.find(key) == cache.end()) continue;
                const auto &vec = cache[key];                 // 找到匹配的值
                for (size_t k = 0; k < vec.size(); ++k){
                    if (c <= vec[k].second) continue;  // 防止重叠，因为不是按四层循环来的
                    ret.push_back({nums[vec[k].first], nums[vec[k].second, nums[c], nums[d]] });
                }
            }
        }
        sort(ret.begin(), ret.end());
        ret.erase(unique(ret.begin(), ret.end()), ret.end());
        return ret;
    }
};

// 删除指定元素，但是删除后各元素的相对顺序不变
class Solution_r1{
    public:
    int removeElement(vector<int> &nums, int target){
        int reLength = 0;
        for (auto i = 0; i < nums.size(); i++){
            if(nums[i] == target) continue;
            nums[reLength++] = nums[i];
        }
        return reLength;
    }

    int removeElementUsingRemove(vector<int> &nums, int target){
        return distance(nums.begin(), remove(nums.begin(), nums.end(), target));
    }
};

// 下一种排列方式，Next Permutation,对于当前的排列（非递减序列）给出不同的排列方式
// 在STL中有这种库函数
class Solution_permutation{
    public:
    void nextPermutation(vector<int> &nums){
        next_permutation(nums.begin(), nums.end());
    }
    template<typename BidiIt>      // 使用模板来实现参数多态化
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
        // 从右边向左边扫描，找到第一个
        auto change = find_if(rfirst, pivot, bind1st(less<int> (), *pivot));
        swap(*change, *pivot);
        reverse(rfirst, pivot);
        return true;
    }
    // 输入n和k, 输出根据next_permutation法则定义下的第k个排列
    // 直接使用暴力枚举方法可以解决问题，但比较浪费。
    // 利用康托编码的思路，依据k找到n个元素的对应位置。余数和整除推导出位置。
    string getPermutation(int n, int k){
        string s(n, '0');            // 初始化输出序列
        for (int i = 0; i < n; ++i)
            s[i] += i + 1;
        string ret;
        return kth_permutation(s, k);
    }
    private:
    int factorial(int n){
        int ret = 1;
        for (int i = 1; i <= n; ++i)
            ret *= i;
        return ret;
        }
    template<typename Sequence>
    Sequence kth_permutation(const Sequence &seq, int k){
        const int n = seq.size();
        Sequence S(seq);
        Sequence ret;
        int base = factorial(n - 1);
        --k;                  // 康托编码从0开始, 对输入下标有一定要求
        for (int i = n - 1; i > 0; k %=base, base /= i, --i){
            auto a = next(S.begin(), k / base);
            ret.push_back(*a);
            S.erase(a);       // 入栈后从剩下的里面用
        }
        ret.push_back(S[0]);
        return ret;
    }
};

// // 判断一个9*9的数独网格是否合法
// // 每一行每一列没有重复项， 每个小格子里也没有重复项
// // 数独网格数据存储在二维字符数组中， 如果空着， 其元素为'.'

// // 重复项的判断使用used数组，如果用过表示重复，返回false

class Solution_sudoku{
    public:
    bool isValidSudoku(const vector<vector<char>> &board){
        bool used[9];
        for (int i  = 0; i < 9; ++i){
            fill(used, used + 9, false);           // fill函数重新初始化
            for (int j = 0; j < 9; ++j)
                if (!check(board[i][j], used))     // 检查第i行
                return false;
            fill(used, used + 9, false);         

            for (int j = 0; j < 9; ++j)
                if(!check(board[j][i], used))     // 检查第i列
                return false;
        }
        for (int r = 0; r < 3; ++r){
            for (int c = 0; c < 3; ++c){
                fill (used, used + 9, false);
                for (int i = r * 3; i < r*3 + 3; ++i)
                    for (int j = c*3; j < c*3 + 3; ++j)
                        if (!check(board[i][j], used))
                        return false;
            }
        }
        return true;

    }
    bool check (char ch, bool used[9]){
        if (ch == '.') return true;
        if (used[ch - '1']) return false;   // 由于是ch字符，转换成int类型直接利用ASCII码映射到0-8
        return used[ch - '1'] = true;       // 非零即真
    }
    
};

// 填方格返回蓄水能力，给定n个非负整数，每个整数的数字的单位为1方格，摆在同一条水平轴上，返回其蓄水能力
// 分析
// 对于每个竹子，找到其左右两边最高的柱子，该柱子能容纳的面积为min(mmax_left, max_right) - height.

class Solution_trappingRainWater{
    public:
    // 方法1， 时间复杂度O(n), 空间复杂度O(n)
    int trap1 (const vector<int> &Height){
        const int n = Height.size();
        int *max_left = new int[n]();         // 直接按vector来
        int *max_right = new int[n]();
        for (int i = 1; i < n; i ++){
            max_left[i] = max(max_left[i - 1], Height[i - 1]);
            max_right[n - i - 1] = max(max_right[n - i], Height[n - i]);
        }
        int sum = 0;
        for (int i = 0; i < n; i++){
            int horiHeight = min(max_left[i], max_right[i]);
            if (horiHeight > Height[i]){
                sum += horiHeight - Height[i];        // 如果本身的块太高，只能做堤坝，无法蓄水
            }
        }
        delete[] max_left;
        delete[] max_right;
        return sum;
    }
    // 方法2，时间复杂度O(n), 空间复杂度O(1)
    // 找到最高的点，从而分两部分处理，只需要找左边的支柱peak和右边的支柱top即可
    int trap2(const vector<int> &Height){
        const int n = Height.size();
        int max = 0;
        for (int i = 0; i < n; i++)
            if (Height[i] > Height[max]) max = i;  // 找到最高的柱子，将数组分成两部分
        int water = 0;
        for (int i = 0, peak = 0; i < max; i++){  // max 左边的处理， peak = 0表示最左边的不蓄水
            if (Height[i] > peak) peak = Height[i];
            else
            {
                water += peak - Height[i];
            }
        }
        for (int i = n - 1, top = 0; i > max; i--){
            if (Height[i] > top) top = Height[i];
            else
                water += top - Height[i];
        }
        return water;
    }

    // 方法3，用一个栈辅助，小于栈顶的元素压入，大于等于栈顶就把栈里所有小于或者等于当前值的元素全部出栈处理掉
    int trap3(const vector<int> &Height){
        const int n = Height.size();
        stack<pair<int, int>> s;
        int water = 0;
        // 将栈中比当前元素矮或者等高的全部处理掉, 因此栈中存放的元素都是非递增的
        for (int i = 0; i < n; ++i){
            int height = 0;
            while (!s.empty()){
                int bar = s.top().first;
                int pos = s.top().second;
                water += (min(bar, Height[i]) - height) * (i - pos - 1);
                height = bar;

                if (Height[i] < bar) break;
                else s.pop();
            }
            s.push(make_pair(Height[i], i));
        }
        return water;
    }
};
// 下面介绍一些小方法

class Solution_smallTricks{
    public:
    // 顺时针旋转一幅n*n的图像90度, 坐标映射，in_place执行
    // 根据旋转坐标变换(x1， y1) -> (y1, -x1 + n - 1) 
    // 方法1： 先沿着副对角线对折，然后沿着水平中线对折
    void rotate1(vector<vector<int>>&img){
        const int n = img.size();
        for (int i = 0; i < n; ++i){
            for (int j = 0; j < n - i; ++j){
                swap(img[i][j], img[n - 1 - j][n - 1 - i]);
            }
        }
        for (int i = 0; i < n/2; ++i){
            for (int j = 0; j < n; ++j){
                swap(img[i][j], img[n - 1 - i][j]);
            }
        }
    }
    // 方法2: 先沿着水平中线对折，然后再沿着主对角线对折
    void rotate2(vector<vector<int>> &img){
        const int n = img.size();
        for (int i = 0; i < n/2 ; i++){
            for (int j = 0; j < n; j++){
                swap(img[i][j], img[n - 1 - i][j]);
            }
        }
        for (int i = 0; i < n ; i++){
            for (int j = 0; j < n - i; j++){
                swap(img[i][j], img[j][i]);
            }
        }
    }

    // Plus One， 高精度十进制加法， 这里没有涉及到小数，如果有小数的话，将小数点位置记住即可
    vector<int> plusOne(vector<int> &digits){
        add(digits, 1);
        return digits;
    }
    // 爬梯子，每次可以爬1或2层台阶，问爬到n层共有多少中方法。
    // 是一种斐波那契数列，f(n) = f(n - 1) + f(n - 2), f(1) = 1, f(2) = 2;
    // 可以用迭代法，或者直接计算公式 f(n-1) = 1/sqrt(5)*(((1+sqrt(5))/2)^n - ((1-sqrt(5))/2)^n)
    int getFibonaciiNum1(int n){
        int prev = 0;  // 记录f(n - 2)
        int cur = 1;   // 记录f(n - 1)
        for (int i = 1; i <= n; ++i){
            int tmp = cur;
            cur += prev;
            prev = tmp;
        }
        return cur;
    }
    int getFibonaciiNum2(int n){
        const double s = sqrt(5);
        return floor((pow((1 + s)/2.0,  n + 1) - pow((1 - s)/2.0, n + 1))/s + 0.5);
    }

    // 求格雷码 g0 = b0， gi = bi 异或 bi-1, 注意0指的是最高位
    // 相邻的码之间的汉明距离为1
    vector<int> getGrayCode1(int n){
        vector<int> ret;
        const size_t size = 1 << n; // 算术移位
        ret.reserve(size);          // 重新分配空间
        for (size_t i = 0; i < size; i++){
            ret.push_back(binary_to_gray(i));
        }
        return ret;
    }
    vector<int> getGrayCode2(int n){
        vector<int> ret;
        ret.reserve(1<<n);
        ret.push_back(0);
        for (int i = 0; i < n; i++){
            const int highest_bit = 1 << i;
            for (int j = ret.size() - 1; j >= 0; j--){
                ret.push_back(highest_bit | ret[j]);      // 反序遍历
            }
        }
        return ret;
    }
    // in place操作，给一个m*n的矩阵，如果一个元素为0,则其所在行和列都为0
    // 用一个flag矩阵很容易标记0的位置，依靠遍历的想法来变成0，但是目前需要in place操作
    // 另外一种方法是用O(m+n)行列两个数组来记录，不过也没有达到O(1)的空间要求
    void setZeros(vector<vector<int>> &matrix){
        const size_t m = matrix.size();     // 行数
        const size_t n = matrix[0].size();  // 列数
        bool row_hasZero = false;
        bool col_hasZero = false;
        // 判断第一行和第一列中的元素是否含有0
        for (size_t i = 0; i < n; i++){
            if (matrix[0][i] == 0){
                row_hasZero = true;
                break;
            }
        }
        for (size_t i = 0; i < m; i++){
            if (matrix[i][0] == 0){
                col_hasZero = true;
                break;
            }
        }
        // 用第一行和第一列来存储0所在的行和列， 而第一行或者第一列是否全0, 上一步已经记录
        for (size_t i = 1; i < m; i++){
            for(size_t j = 1; j < n; j++){
                if (matrix[i][j] == 0){
                    matrix[0][j] = 0;
                    matrix[i][0] = 0;
                }
            }
        }
        // 也可以用fill函数填充行， 列元素用二次循环做
        for (size_t i = 1; i < m; i++){
            for (size_t j = 1; j < n; j++){
                if (matrix[i][0] == 0 || matrix [0][j] == 0)
                    matrix[i][j] = 0;
            }
        }
        if (row_hasZero){
            fill (&matrix[0][0], &matrix[0][0] + n, 0);
        }
        if (col_hasZero){
            for (size_t i = 0; i < m; i++){
                matrix[i][0] = 0;
            }
        }
    }
    // gasStation：已知N个加油站在一个环形车道上。每个站的油量为gas[i](假设汽车可以全部加满)，
    // 汽车从油站i到油站i+1，所花费的油量为cost[i]。
    // 初始条件，无油量汽车在一个未知的站点，要求选取一个合适的站点使得汽车能走完一圈。否则返回-1。
    // 结果必须唯一。
    // 思路：设置两个变量，sum判断当前指针的有效性，total判断整个数组是否有解。
    int canCompleteCircuit(vector<int> &gas, vector<int> &cost){
        int total = 0;       // 初始值相当于初始油量
        int j = -1;
        for (int i = 0, sum = 0; i < gas.size(); i++){
            sum += gas[i] - cost[i];
            total += gas[i] - cost[i];
            if (sum < 0){
                j = i;                      // 换一个起点，起点为j + 1
                sum = 0;
            }
        }
        return total >= 0? j + 1 : -1;
    }
    // 分糖果：N个孩子，各自的优先级为rate[i].
    // 要求： 每个孩子至少有一个糖果，高优先级的孩子得到的糖果必须必低优先级的多
    // 问至少要准备多少糖果。
    // 类似于树的生成，只要知道层数和每层的节点个数，即可返回所有糖果。
    int candy1(vector<int> &ratings){
        const int n = ratings.size();
        vector<int> increment(n);
        for (int i = 1, inc = 1; i < n; i++){
            if (ratings[i] > ratings[i - 1]){
                increment[i] = max(inc++, increment[i]); // 注意++的方式
            }
            else
            {
                inc = 1;
            }
        }
        for (int i = n - 2, inc = 1; i >= 0; i--){
            if (ratings[i] > ratings[i + 1]){
                increment[i] = max(inc++, increment[i]);
            }
            else
            {
                inc = 1;
            }
        }

        return accumulate(&increment[0], &increment[0] + n, n);  // 初始值为n
    }
    // 使用备忘录方法
    int candy2(const vector<int> &ratings){
        vector<int> f(ratings.size());
        int sum = 0;
        for (int i = 0; i < ratings.size(); ++i){
            sum += candySolve(ratings, f, i);
            return sum;
        }
    }
    // 找到数组中的唯一不重复元素（该元素是存在的），使用线性时间复杂度，尽量少的空间。
    // 如果是偶数，使用位异或运算即可。
    int singleNumEvenTimes(vector<int> &nums, int mode){
        int x = 0;
        if (mode == 1){
            for (auto i:nums){
                x ^= i;
            }
        }
        else
        {
            x = accumulate(nums.begin(), nums.end(), 0, bit_xor<int>());
        }
        
        return x;
    }
    // 如果是奇数（特指3次），同样使用位运算。
    int singleNumThreeTimes(vector<int> &nums){
        const int W = sizeof(int) * 8;
        int count[W];    // bit数组
        for (int i = 0; i < nums.size(); i++){
            for (int j = 0; j < W; j++){
                count[j] += (nums[i] >> j) & 1;  // 取其位数
                count[j] %= 3;
            }
        }
        int  ret = 0;
        for (int i = 0; i < W; i++){
            ret += (count[i] << i);
        }
        return ret;
    }
    private:
    void add(vector<int> &digits, int digit){
        int c = digit; // 从被加数开始，表示进位
        // 反序遍历， 从低位开始
        for (auto it = digits.rbegin(); it != digits.rend(); ++it){
            *it += c;
            c = *it/10;
            *it %= 10;
        }
        if (c > 0) digits.insert(digits.begin(), 1);
    }
    static unsigned int binary_to_gray(unsigned int n){
        return n ^ (n >> 1);   // 直接用公式法， n 异或 n/2
    }    
    int candySolve(const vector<int> &ratings, vector<int> &f, int i){
        if (f[i] == 0){
            f[i] = 1;
            if (i > 0 && ratings[i] > ratings[i - 1]){
                f[i] = max(f[i], candySolve(ratings, f, i - 1) + 1);
            }
            if (i < ratings.size() - 1 && ratings[i] > ratings[i + 1]){
                f[i] = max(f[i], candySolve(ratings, f, i + 1) + 1);
            }
        }
    }
};