// Depth First Search
// 深度优先遍历
// 对于递归数据结构比如单链表，二叉树，集合等用DFS是十分合适的。
// 适用情况：必须要走到最深即叶子节点才能得到一个解。

#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>

using namespace std;

class Solution_depthFirstSearch{
    public:
    // Palindrome Partitioning
    // 回文序列分割，给出一段字符串，返回其中所有的回文序列
    // 一个长度为n的字符串，有n-1个地方可以作分割点，分割点处可以选择断开也可以选择不断开
    // 时间复杂度O(2^n), 空间复杂度O(n)
    vector<vector<string>> partitionUsingDFS(string s){
        vector<vector<string>> ret;
        vector<string> path;
        dfsPalindrome(s, path, ret, 0, 1);
        return ret;
    }
    // 使用动态规划来解决该问题
    // 算法思想
    // S1: 初始化p矩阵来记录子序列的回文序列及间隔
    // S2: 利用p矩阵逐层来组建回文序列，利用最终长度为n这个性质来逐层建立
    // 时间复杂度O(2^n), 空间复杂度O(1)
    
    vector<vector<string>> partitionUsingDP(string s){
        const int n = s.size();
        bool p[n][n]; // 记录s[i, j]是否为回文序列, 只使用上半区间
        fill_n(&p[0][0], n*n, false); // 初始化
        for (int i = n - 1; i >= 0; --i){
            for (int j = i; j < n; ++j){
                p[i][j] = s[i] == s[j] && ((j - i) < 2)||p[i + 1][j - 1];
            }
        }
        vector<vector<string>> sub_palins[n]; // s[0, i]部分的子回文序列
        for (int i = n - 1; i >= 0; --i){
            for (int j = i; j < n; ++j){
                if (p[i][j]){
                    const string palindrome = s.substr(i, j - i + 1);
                    if (j + 1 < n){
                        for (auto v : sub_palins[j + 1]){
                            v.insert(v.begin(), palindrome);
                            sub_palins[i].push_back(v);
                        }
                    }
                    else{
                        sub_palins[i].push_back(vector<string> {palindrome});
                    }
                }
            }
        }
        return sub_palins[0];
    }
    // Unique Paths
    // 棋盘路径问题
    // 不过直接用数学思想可以直接得出答案
    // (0, 0)->(m-1, n-1)中一定会走m + n - 2步，其中一定要选(m - 1)步向下的
    // 因此最终有C(m + n - 2)_(m - 1)种选法
    // 如果直接使用DFS，对于大集合可能会超时。使用备忘录法用空间来换时间。
    // 动态规划，滚动数组。该算法很精妙。
    // f[i][j] = f[i - 1][j] + f[i][j - 1]
    // 时间复杂度O(n ^ 2), 空间复杂度O(n)
    int uniquePaths(int m, int n){
        vector<int> f(n, 0);        // 初始化为n个0
        f[0] = 1;
        for (int i = 0; i < m; i++){
            for (int j = 1; j < n; j++){
                f[j] = f[j] + f[j - 1];  // 左边的表示f[i][j], 而右边的一词为 f[i - 1][j], f[i][j - 1];
            }    
        }
        return f[n - 1];
    }

    // Unique Path With Obstacles
    // 在该矩阵中加入障碍，路径中有障碍的不计入总数
    // 这里介绍备忘录法：深搜 + 缓存
    // 时间复杂度O(n^2)， 空间复杂度O(n^2)
    int uniquePathsWithObstaclesUsingMem(const vector<vector<int>> &obstacleGrid){
        const int m = obstacleGrid.size();
        const int n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) return 0;
        f = vector<vector<int>> (m, vector<int>(n, 0));    // 初始化
        f[0][0] = obstacleGrid[0][0] ? 0 : 1;
        return dfsObstacleGrid(obstacleGrid, m - 1, n - 1);
    }
    // 动态规划，滚动数组
    // 时间复杂度O(n^2), 空间复杂度O(n)
    int uniquePathWithObstaclesUsingDP(const vector<vector<int>> &obstacleGrid){
        const int m = obstacleGrid.size();
        const int n = obstacleGrid[0].size();
        if (obstacleGrid[0][0] || obstacleGrid[m - 1][n - 1]) return 0;
        vector<int> f(n, 0);
        f[0] = 1;                       // 上述已经有条件排除初始位置有障碍的情况，初始位置有一条路径
        for (int i = 0; i < m; i++){
            f[0] = f[0] == 0 ? 0 : (obstacleGrid[i][0] ? 0 : 1);
            for (int j = 1; j < n; j ++){
                f[j] = obstacleGrid[i][j] ? 0 : (f[j] + f[j - 1]);
            }
        }
        return f[n - 1];
    }
    // N-Queens
    // 经典的N皇后问题：在8*8的棋盘中，摆放8个皇后使得彼此不会被吃掉。
    // 深搜 + 剪枝
    // 时间复杂度O(n!)，空间复杂度O(n)
    vector<vector<string>> solveNQueens(int n){
        this->columns = vector<bool>(n, false);                // 已经放置的皇后所占列
        this->main_diag = vector<bool>(2 * n - 1, false);      // 占据的主对角线
        this->anti_diag = vector<bool>(2 * n - 1, false);      // 占据的副对角线

        vector<vector<string>> ret;
        vector<int> C(n, -1);                                  // C[i]表示第i行皇后所在的列编号
        dfsNQueens(C, ret, 0);                                 // 从第0行开始
        return ret;

    }

    // 简化上述N皇后问题， 找出解的个数即可，不需要知道具体排布。
    // 设置一个全局计数器即可。
    int totalNQueens (int n){
        this->count = 0;
        this->columns = vector<bool>(n, false);
        this->main_diag = vector<bool>(2 * n - 1, false);
        this->anti_diag = vector<bool>(2 * n - 1, false);
        vector<int> C(n, 0);
        dfsTotalNQueens(C, 0);
        return this->count;

    }
    // Restore IP Addr
    // 给定数字字符串，分割得到对应合法IP地址
    // 时间复杂度O(n^4), 空间复杂度O(n)
    vector<string> restoreIpAddr(const string &s){
        vector<string> ret;
        vector<string> ip;
        dfsIpAddr(s, ip, ret, 0);
        return ret;
    }

    // Combination Sum
    // 给出非负整数数组C和一个目标数T, 找到C中所有加和得的和
    // 每个数字可以多用几次
    // 时间复杂度O(n!), 空间复杂度O(n)
    vector<vector<int>> combinationSum(vector<int> &nums, int target){
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        vector<int> path;
        dfsCombineSum(nums, path, ret, target, 0);
        return ret;
    }

    // Sudoku Solver
    // 解决数独问题
    // 认为是一个字符串数组，空白的地方设置为"."
    // 时间复杂度O(9^4), 空间复杂度O(1)
    bool solveSudoku(vector<vector<char>> &board){
        for (int  i = 0; i < 9; i++){
            for (int j = 0; j < 9; j++){
                if (board[i][j] == '.'){
                    for (int k = 0; k < 9; ++k){
                        board[i][j] = '1' + k;
                        if (isValidSudoku(board, i, j) && solveSudoku(board)){
                            return true;
                        }
                        board[i][j] = '.';
                    }
                    return false;
                }
            }
        }
    }
    // Pacific Atlantic Water Flow
    // 同时达到海洋的位置， 海洋表示为在靠两侧边界处
    // 从两个顶点出发，反向找到能达到这两个顶点的所有位置放到bool数组里
    // 然后再遍历同时满足这两个条件的位置
    // 这里使用动态数组来解决该问题
    // 这个方法是严格按照递减路径进行的，如果仅仅按照地势高低进行地点选取，用dfs而且结果和本算法不同
    vector<pair<int, int>> getPacificAltanticFlow(const vector<vector<int>> &heightMtx){
        const int m = heightMtx.size();
        const int n = heightMtx[0].size();
        bool reachPacific[m][n];
        bool reachAltantic[m][n];
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                reachPacific[i][j] = false;
                reachAltantic[i][j] = false;
            }
        }
        
        // 边界初始化bool数组
        for (int i = 0; i < m; i++){
            reachPacific[i][0] = true;
            reachAltantic[m - 1 - i][n - 1] = true;
        }
        for (int j = 1; j < n; j++){
            reachPacific[0][j] = true;
            reachAltantic[m - 1][n - 1 - j] = true;
        }
        // 内部初始化bool数组
        for (int i = 1; i < m; i++){
            for  (int j = 1; j < n; j++){
                if ((reachPacific[i - 1][j] && heightMtx[i][j] >= heightMtx[i - 1][j]) \
                    || (reachPacific[i][j - 1] && heightMtx[i][j] >= heightMtx[i][j - 1])){
                    reachPacific[i][j] = true;
                }
                if ((reachAltantic[m - 1 - i][n - j] && heightMtx[m - 1 - i][n - 1 - j] >= \
                        heightMtx[m - 1 - i][n - j]) || (reachAltantic[m - i][n - 1 - j] && \
                        heightMtx[m - 1 - i][n - 1 - j] >= heightMtx[m - i][n - 1 - j])){
                    reachAltantic[m - 1 - i][n - 1 - j] = true;
                }
            }
        }
        
        // 遍历结果
        vector<pair<int, int>> ret;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (reachAltantic[i][j] && reachPacific[i][j]){
                    ret.push_back(pair<int, int>(i, j));
                }
            }
        }
        return ret;
    }
    // dfs_flow
    vector<pair<int, int>> reachPacificAtlantic(vector<vector<int>> &heightMtx){
        const int m = heightMtx.size();
        const int n = heightMtx[0].size();
        vector<vector<bool>>reachPacific(m, vector<bool>(n, false));
        vector<vector<bool>>reachAltantic(n, vector<bool>(n, false));

        
        for (int i = 0; i < m; i++){
            dfsPacificAltantic(i, 0, reachPacific, heightMtx);
            dfsPacificAltantic(i, n - 1, reachAltantic, heightMtx);
        }
        for (int j = 0; j < n; j++){
            dfsPacificAltantic(0, j, reachPacific, heightMtx);
            dfsPacificAltantic(m - 1, j, reachAltantic, heightMtx);
        }
        vector<pair<int, int>> ret;
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (reachPacific[i][j] && reachAltantic[i][j]){
                    ret.push_back(pair<int, int>(i, j));
                }
            }
        }
        return ret;
    }
    private:
    vector<vector<int>> f;         // 用作缓存

    // 用作N皇后问题的剪枝变量
    vector<bool> columns;
    vector<bool> main_diag;
    vector<bool> anti_diag;
    int count;

    // @param[in] prev   前面一个隔板
    // @param[in] start  当前隔板
    void dfsPalindrome(string &s, vector<string> &path, \
            vector<vector<string>> &ret, size_t prev, size_t start){
        if (start == s.size()){
            if (isPalindrome(s, prev, start - 1)){
                path.push_back(s.substr(prev, start - prev));
                ret.push_back(path);
                path.pop_back();
            }
            return;
        }
        dfsPalindrome(s, path, ret, prev, start + 1);
        if (isPalindrome(s, prev, start - 1)){
            path.push_back(s.substr(prev, start - prev));
            dfsPalindrome(s, path, ret, start, start + 1);
            path.pop_back();
        }
    }
    // 判断是否为回文序列
    bool isPalindrome(const string &s, int start, int end){
        while (start < end && s[start] == s[end]){
            start++;
            end--;
        }
        return start >= end;  // 越过中间的字母
    }

    // obstacleGrid
    int dfsObstacleGrid(const vector<vector<int>> &obstacleGrid, \
            int x, int y){
        if (x < 0 || y < 0) return 0;

        if (obstacleGrid[x][y]) return 0;        // 遇到障碍，此路不通
        if (x == 0 and y == 0) return f[0][0];   // 回到起点, 递归终止条件
        if (f[x][y] > 0){
            return f[x][y];
        }
        else{
            return f[x][y] = dfsObstacleGrid(obstacleGrid, x - 1, y) + \
                dfsObstacleGrid(obstacleGrid, x, y - 1);
        }
    }
    // NQueens
    void dfsNQueens(vector<int> &C, vector<vector<string>> &ret, int row){
        const int N = C.size();
        if (row == N){
            vector<string> solution;
            for (int i = 0; i < N; ++i){
                string s(N, '.');
                for (int j = 0; j < N; ++j){
                    if (j == C[j]) s[j] = 'Q'; // 根据C给出的可行解的列编号， 放置Q的位置
                }
                solution.push_back(s);
            }
            ret.push_back(solution);
            return;
        }

        for (int j = 0; j < N; ++j){
            const bool ok = !columns[j] && !main_diag[row - j + N - 1] && \
                    !anti_diag[row + j];
            if (!ok) continue;    // 剪枝操作
            // 符合要求，开始扩展
            C[row] = j;
            columns[j] = main_diag[row - j + N -1] = anti_diag[row + j] = true;
            dfsNQueens(C, ret, row + 1);
            // 继续找其余列的可能，重置为false
            columns[j] = main_diag[row - j + N - 1] = anti_diag[row + j] = false;
        }
    }

    // NQueens II
    void dfsTotalNQueens(vector<int> &C, int row){
        const int N = C.size();
        if (row == N){
            ++this->count;
            return;
        }

        for (int j = 0; j < N; ++j){
            const bool ok = !columns[j] && \
                    !main_diag[row - j + N - 1] && !anti_diag[row + j];
            if (!ok) continue;
            C[row] = j;
            columns[j] = main_diag[row - j + N - 1] = anti_diag[row + j] = true;
            dfsTotalNQueens(C, row + 1);
            columns[j] = main_diag[row - j + N - 1] = anti_diag[row + j] = false;
        }
    }

    // dfs IP Addr
    void dfsIpAddr(string s, vector<string>& ip, vector<string> &ret, size_t start){
        if (ip.size() == 4 && start == s.size()){
            ret.push_back(ip[0] + '.' + ip[1] + '.' + ip[2] + '.' + ip[3]);
            return;
        }
        // 剪枝，分的不合理
        if (s.size() - start > (4 - ip.size()) * 3) return;
        if (s.size() - start < (4 - ip.size())) return;
        int num = 0;
        // 每次移动三个数字， 进行dfs
        for (size_t i = start; i < start + 3; i++){
            num = num*10 + (s[i] - '0');
            if (num < 0 || num > 255) continue;
            ip.push_back(s.substr(start, i - start + 1));
            dfsIpAddr(s, ip, ret, i + 1);
            ip.pop_back();
            if (num == 0) break;
        }
    }
    // Combination Sum
    void dfsCombineSum(vector<int> &nums, vector<int> &path, \
            vector<vector<int>> &ret, int gap, int start){
        if (gap == 0){
            ret.push_back(path);
            return;
        }
        // int prev = -1;                           // 如果有不重复Combine的原则，使用prev来指示在该path中，该数字已经被使用过即可
        for (size_t i = start; i < nums.size(); i++){
            if (gap < nums[i]) return;
            // if (prev == nums[i]) continue;
            path.push_back(nums[i]);
            // prev = nums[i];
            // dfsCombineSum(nums, path, ret, gap - nums[i], i + 1); // 注意不重复Combine下是前进的
            dfsCombineSum(nums, path, ret, gap - nums[i], i);
            path.pop_back();
        }
    }

    // 递归生成括号的组合方式
    vector<string> generateParenthesis(int n){
        if (n == 0) return vector<string>(1, "");
        if (n == 1) return vector<string>(1, "()");
        vector<string> ret;
        for (int i = 0; i < n; ++i){
            for (auto inner :generateParenthesis(i)){
                for (auto outer:generateParenthesis(n - 1 - i)){
                    ret.push_back("(" + inner + ")" + outer);       // 状态的连接关键
                }
            }
        }
        return ret;
    }

    bool isValidSudoku(const vector<vector<char>> &board, int x, int y){
        // 行检查
        for (int i = 0; i < 9; ++i){
            if (i != x && board[i][y] == board[x][y]){
                return false;
            }
        }
        // 列检查
        for (int j = 0; j < 9; j++){
            if (j != y && board[x][j] == board[x][y]){
                return false;
            }
        }

        // 格子检查
        for (int i = 3*(x/3); i < 3*(x/3) + 3; i++){
            for (int j = 3*(y/3); j < 3*(y/3) + 3; j++){
                if ( i != x && j != y && board[i][j] == board[x][y]){
                    return false;
                }
            }
        }

        return true;
    }
    // Word Search
    // 在2D字典中，给定一个词，看是否能通过2D字典连接得到
    // 时间复杂度O(n^2*m^2), 空间复杂度O(n^2)
    bool exsitWordSearch(const vector<vector<char>> &board, const string &word){
        const int m = board.size();
        const int n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (dfsWordSearch(board, word, 0, i, j, visited)){
                    return true;
                }
            }
        }
        return false;
    }

    bool dfsWordSearch(const vector<vector<char>> &board, const string &word, \
            int index, int x, int y, vector<vector<bool>> &visited){

        // 终止条件
        if (index == word.size()) return true;

        // 剪枝
        if (x < 0 || y < 0 || x >= board.size() || y >= board[0].size()) return false;
        if (visited[x][y]) return false;
        if (word[index] != board[x][y]) return false;
        visited[x][y] = true;
        // 四个方向开始搜索
        bool ret = dfsWordSearch(board, word, index + 1, x - 1, y, visited)\
        || dfsWordSearch(board, word, index + 1, x + 1, y, visited) \
        || dfsWordSearch(board, word, index + 1, x , y - 1 , visited) \
        || dfsWordSearch(board, word, index + 1, x, y + 1, visited);
        visited[x][y] = false;
        return ret;
    }
    // Friend Circles
    // 给定一个无向图邻接矩阵，判断其中有多少个环(可以说是可达链路)
    int findCircleNum(const vector<vector<int>> M){
        const int n = M.size();
        int circleNum = 0;
        vector<bool> hasVisited(n, false);
        for (int i = 0; i < n; i++){
            if (!hasVisited[i]){
                dfsFriend(M, i, hasVisited);
                circleNum++;
            }
        }
        return circleNum;
    }
    private:
    vector<pair<int, int>> direction{{0, - 1}, {0, 1}, {1, 0}, {-1, 0}};
    // 
    void dfsFriend(const vector<vector<int>> &M, int i, vector<bool> &hasVisited){
        const int n = M.size();
        hasVisited[i] = true;
        for (int k = 0; k < n; k++){
            if (M[i][k] == 1 && !hasVisited[k]){
                dfsFriend(M, k, hasVisited);
            }
        }

    }
    // 
    void dfsPacificAltantic(int i, int j, vector<vector<bool>> canReach, \
            const vector<vector<int>> &heightMtx){
        const int m = canReach.size();
        const int n = canReach[0].size();
        if (canReach[i][j]){
            return;
        }
        canReach[i][j] = true;
        for (auto dir : direction){
            int nextI = dir.first + i;
            int nextJ = dir.second + j;
            if (nextI < 0 || nextI >= m || nextJ < 0 || nextJ >= n || \
            heightMtx[i][j] > heightMtx[nextI][nextJ]){
                continue;
            }
            dfsPacificAltantic(nextI, nextJ, canReach, heightMtx);
        }
    }
};