// 动态规划
#include<stdio.h>
#include<algorithm>
#include<vector>
#include<unordered_set>
#include<iostream>

using namespace std;

class Solution_dp{
    public:
    // Triangle
    // 金字塔找最短路径问题
    // 自下而上找最优解
    // 时间复杂度O(n^2), 空间复杂度O(1)
    int minTotal(vector<vector<int>> &triangle){
        for (int i = triangle.size() - 2; i >= 0; --i){
            for (int j = 0; j < i + 1; ++j){
                triangle[i][j] += min(triangle[i + 1][j], \
                    triangle[i + 1][j + 1]);
            }
        }
        return triangle[0][0];
    }

    // Maximum Subarray
    // 最大连续子序列和
    // 当遇到数组里的整数时，有两种选择，加入之前的Subarray或者另外建立一个Subarray

    // DP, 时间复杂度O(n), 空间复杂度O(1)
    int maxSubArray(const vector<int> &nums){
        int ret = INT_MIN, f = 0;
        for (int i = 0; i < nums.size(); ++i){
            f = max(f + nums[i], nums[i]);
            ret = max(ret, f);
        }
        return ret;
    }
    // Palindrome Partitioning II
    // 找到将字符串拆分成若干回文序列的最短cut

    // 时间复杂度O(n^2), 空间复杂度O(n^2)
    int minCut(const string &s){
        const int n = s.size();
        int f[n + 1];
        bool p[n][n];
        fill_n(&p[0][0], n*n, false);
        for (int i = 0; i <= n; i++){
            f[i] = n - 1 - i;             // 设置f[n] = -1
        }
        // 反向扫描
        for (int i = n - 1; i >= 0; i--){
            for (int j = i; j < n; j++){
                if (s[j] == s[i] && (j - i < 2 || p[i + 1][j - 1])){
                    p[i][j] = true;
                    f[i] = min(f[i], f[j + 1] + 1);
                }
            }
        }
        return f[0];
    }
    // Maximal Rectangle
    // 给定一个二值图，设置全为1的为有效阴影部分，找出有效阴影中的最大矩形及其面积。
    // 时间复杂度O(n^2), 空间复杂度O(n)

    int maxRectangle(vector<vector<char>> &matrix){
        if (matrix.empty()) return 0;
        const int m = matrix.size();
        const int n = matrix[0].size();
        vector<int> H(n, 0);      // 记录高
        vector<int> L(n, 0);      // 当前连续1的最左坐标
        vector<int> R(n, n);      // 当前连续1的最右坐标

        int ret = 0;
        for (int i = 0; i < m; i++){
            int left = 0, right = n;
            for (int j = 0; j < n; j++){
                if (matrix[i][j] == '1'){
                    ++H[j];
                    L[j] = max(L[j], left);
                }
                else{
                    left = j + 1;
                    H[j] = 0; L[j] = 0; R[j] = n;
                }
            }

            for (int j = n - 1; j >= 0; j--){
                if (matrix[i][j] == '1'){
                    R[j] = min(R[j], right);
                    ret = max(ret, H[j]*(R[j] - L[j]));
                }
                else{
                    right = j;
                }
            }

        }
        return ret;
        
    }
    // Best time to buy and Sell Stock III
    // 允许一天内两次交易
    // P = f[0--i] + f[i -- n - 1]
    int maxProfit (vector<int> &prices){
        if (prices.size() < 2) return 0;
        const int n = prices.size();
        vector<int> f(n, 0);
        vector<int> g(n, 0);

        for (int i = 1, valley = prices[0]; i < n; ++i){
            valley = min(valley, prices[i]);
            f[i] = max(f[i - 1], prices[i] - valley);
        }

        for (int i = n - 2, peak = prices[n - 1]; i >= 0; --i){
            peak = max(peak, prices[i]);
            g[i] = max(g[i], peak - prices[i]);
        }
        int max_profit = 0;
        for (int i = 0; i < n; ++i){
            max_profit = max(max_profit, f[i] + g[i]);
        }
        return max_profit;

    }

    // Interleaving String
    // 验证字符串s3 是否可以根据 s1和s2交错得到
    // 实际上是一种DFS，可以以DP+2D的方式进行递归遍历，中间遇到不合理的路径进行剪枝
    // DP + 滚动数组---比较难理解，可以先将以2D数组推导，然后再根据前后性质
    // 观察得到一维滚动数组的构造
    // 二维数组f[i][j] 表示 s1[0, i] 和 s2[0, j] 匹配s3[0, i + j]
    // 按照最后一个字符匹配的字符串分两种情况从而得到下面的状态转移方程
    // f[i][j] = (f[i][j-1] && s2[j - 1] == s3[i + j - 1]) || (f[i - 1][j] && s1[i - 1] == s3[i + j - 1])
    // 将s1这个维度作为隐藏条件得到下面的滚动数组f[j]
    // 时间复杂度O(n^2), 空间复杂度O(n)

    // 以这个思路提供 求两个字符串的最长重合串
    // dp[i][j] = dp [i - 1][j - 1] + 1, s1[i] == s2[j]
    // dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]), s1[i] <> s2[j]
    bool isInterleave(const string &s1, const string &s2, const string &s3){
        if (s1.length() + s2.length() != s3.length()){
            return false;
        }
        if (s1.length() < s2.length()){
            return isInterleave(s2, s1, s3);
        }
        vector<bool> f(s2.length() + 1, true);
        for (size_t i = 1; i <= s2.length(); ++i){
            f[i] = s2[i - 1] == s3[i - 1] && f[i - 1]; // f[0]决定字符串的开头， 后面按照滚动字符串来处理
        }


        for (size_t i = 1; i <= s1.length(); ++i){
            f[0] = s1[i - 1] == s3[i - 1] && f[0];
            for (size_t j = 1; j <= s2.length(); ++j){
                f[j] = (s1[i - 1] == s3[i + j - 1] && f[j]) ||\
                        (s2[j - 1] == s3[i + j - 1] && f[j - 1]);  
            }
        }
        return f[s2.length()];
    }

    // Scramble String
    // 判断两个字符串是否来自于同一个二叉字母树
    // 3D DP
    // f[n][i][j] 表示 长度为n, 起点为s1[i]和起点为s2[j]的字符串是否互为scramble
    // 状态转移方程为 f[n][i][j] = (f[k][i][j] && f[n - k][i + k][j + k]) || 
    //                            (f[k][i][j + n - k] && f[n - k][i + k][j])
    // DP, 时间复杂度O(n^3), 空间复杂度O(n^3)
    bool isScarmbleUsingDP(const string &s1, const string &s2){
        const int N = s1.size();
        if (N != s2.size()) return false;
        bool f[N + 1][N][N];
        fill_n(&f[0][0][0], (N + 1)*N*N, false);
        for (int i = 0; i < N ; i++){
            for (int j = 0; j < N; j++){
                f[1][i][j] = s1[i] == s2[j];
            }
        }
        for (int n = 1; n <= N; ++n){
            for (int i = 0; i + n <= N; ++i){
                for (int j = 0; j + n <= N; ++j){
                    for (int k = 1; k < n; ++k){
                        if (f[k][i][j] && f[n - k][i + k][j + k] || \
                            f[k][i][j + n - k] && f[n - k][i + k][j]){
                            f[n][i][j] = true;
                            break;
                        }
                    }
                }
            }
        }
        return f[N][0][0];
    }

    // Minimum Path Sum
    // 一个格子数组里都是非负整数，求两个边角点的最短距离
    // 二维动态规划-> 滚动数组
    // f[i][j] = min(f[i][j - 1], f[i - 1][j])
    // 时间复杂度O(n^2), 空间复杂度O(n)

    int minPathSumUsingDP(vector<vector<int>> &grid){
        const size_t m = grid.size();
        const size_t n = grid[0].size();
        int f[n] = {0};                                // (0, 0)到(i, j)的最短路径长度, 滚动数组

        // 边界第一行预赋值
        f[0] = grid[0][0]; 
        for (size_t j = 1; j < n; j++){
            f[j] = f[j - 1] + grid[0][j];
        }

        for (size_t i = 1; i < m; i++){
            f[0] = f[0] + grid[i][0];                 // 边界第一列赋值
            for (size_t j = 1; j < n; j++){
                f[j] = min(f[j], f[j - 1]) + grid[i][j];
            }
        }
        return f[n - 1];
    }

    // Edit Distance
    // 给定两个词，找到二者的最小编辑距离
    // 编辑的方式有三种：替换、添加、删除
    // 替换：f[i][j] = f[i - 1][j - 1] + 1
    // 添加：f[i][j] = f[i][j - 1] + 1;
    // 删除：f[i][j] = f[i - 1][j] + 1;
    // 长度为n的数组，共有n + 1个隔板

    // DP + 滚动数组
    // 时间复杂度O(m*n), 空间复杂度O(n)
    int getEditDistance(const string &s1, const string &s2){
        const size_t m = s1.size();
        const size_t n = s2.size();

        int f[n + 1];
        int upper_left = 0;                       // 用一个变量记录f[i - 1][j - 1]，防止一维数组被更新
        for (size_t j = 0; j <= n; j++){
            f[j] = j;                             // 初始化, 表示一直添加
        }
        for (size_t i = 1; i <= m; i++){
            upper_left = f[0];
            f[0] = i;
            for (size_t j = 1; j <= n; j++){
                int upper = f[j];
                if (s1[i] == s2[j]){
                    f[j] = f[j - 1];
                }
                else{
                    f[j] = 1 + min(upper_left, min(f[j], f[j - 1]));
                }
                upper_left = upper;
            }
        }
        return f[n];
    }

    // Decode Ways
    // 将A-Z的字母用进行数字对应1-26，由于没有分割会出现多种译码方式, 问有多少中译码
    // 迭代进行，f[n] = f[n - 1] + f[n - 2]       -->cur是当前加入一个数字后能扩展的译码方式
    int getNumDecoding(const string &s){
        if (s.empty() || s[0] == '0') return 0;

        int prev = 0;
        int cur = 1;
        for (size_t i = 1; i <= s.size(); ++i){
            if (s[i - 1] == '0') cur = 0;
            if (i < 2 || !(s[i - 2] == '1' ||\
                (s[i - 2] == '2' && s[i - 1] <= '6'))){
                prev = 0;
            }

            int tmp = cur;
            cur = cur + prev;
            prev = tmp;
        }
        return cur;
    }
    // Word Break
    // f[i] = any_of (f[j] && s[j + 1, i] --dict) 分词状态转移方程
    // 时间复杂度O(n^2), 空间复杂度O(n)
    bool wordBreak(string s, unordered_set<string> &dict){
        vector<bool> f(s.size() + 1, false);
        f[0] = true;
        for (int i = 1; i <= s.size(); ++i){
            for (int j = i - 1; j >= 0; --j){
                if (f[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                    f[i] = true;
                    break;
                }
            }
        }
        return f[s.size()];
    }
    // Word Break II
    // 分词，并找出所有靠dict分词的结果
    // 利用prev数组搭建关系，然后根据该关系反向找到所有词语，组成结果
    // 时间复杂度O(n ^ 2), 空间复杂度O(n ^ 2)
    vector<string> getBrokenWords(string s, unordered_set<string> &dict){
        vector<bool> f(s.length() + 1, false);
        vector<vector<bool>> prev(s.length() + 1, vector<bool>(s.length()));
        f[0] = true;
        for (size_t i = 1; i <= s.length(); ++i){
            for (int j = i - 1; j >= 0; --j){
                if (f[j] && dict.find(s.substr(j, i - j)) != dict.end()){
                    f[i] = true;
                    prev[i][j] = true;
                }
            }
        }
        vector<string> ret;
        vector<string> path;
        gen_path(s, prev, s.length(), path, ret);
        return ret;
    }
    // 0-1背包问题
    // 有一个容量为N的背包，要用这个背包装下物品使得总价值最大。
    // 物品有两个属性，体积w和价值v。
    // 设置一个前i个商品放入背包后，体积不超过j的二维数组dp[i][j]
    // 第i个商品可以选择放入，也可以选择不放入，具体和其下标j有关
    // 状态转移方程为：
    // dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + v);
    // 滚动数组，时间复杂度O(N*W),空间复杂度O(W + 1)
    int knapsack(const int W, const int N, vector<int> weights, vector<int> values){
        int dp[W + 1] = {0};                             // 滚动数组, 初始化全0
        for (int i = 0; i < N; i++){
            int w = weights[i], v = values[i];
            for (int j = W; j >= 1; j--){
                if (j >= w){
                    dp[j] = max(dp[j], dp[j - w] + v);
                }
            }
        }
        return dp[W];
    }

    private:
    void gen_path(const string &s, const vector<vector<bool>> &prev, \
            int cur, vector<string> &path, vector<string> &ret){
        if (cur == 0){
            string tmp;
            for (auto iter =  path.crbegin(); iter != path.crend(); ++iter){
                tmp += *iter + " ";
            }
            tmp.erase(tmp.end() - 1);   // 去除最后一个多于的空格
            ret.push_back(tmp);
        }
        for (size_t i = 0; i < s.size(); ++i){
            if (prev[cur][i]){
                path.push_back(s.substr(i, cur - i));
                gen_path(s, prev, i, path, ret);
                path.pop_back();
            }
        }
    }
};
