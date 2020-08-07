// 广度优先搜索, Breadth First Search
// 搜索中分为广搜和深搜, 广度搜索又分为普通广搜和双向广搜
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
#include<queue>
#include<unordered_map>
#include<algorithm>

using namespace std;


struct state_t{
    string word;
    int level;
    state_t(){ word = ""; level = 0; }
    state_t(const string&word, int level){
        this->word = word;
        this->level = level;
    }
    bool operator==(const state_t &other) const{
        return this->word == other.word;
    }
};

namespace std{
    template<> struct hash<state_t>{
        public:
        size_t operator()(const state_t& s) const{
            return str_hash(s.word);
        }
        private:
        std::hash<std::string> str_hash;
    };
}

class Solution_BFS{
    
    public:
    // WordLadder
    // 给定两个词和一个字典，找到词语变化的最短路径
    // 路径中相邻词只变化一个字母, 词都是等长的，都是由小写字母组成的。
    // 单队列搜索，时间复杂度O(n), 空间复杂度O(n)
    int ladderLengthUsingOneQueue(const string &start, const string &end,
            const unordered_set<string> &dict){
        queue<state_t> q;
        unordered_set<state_t> visited; // 收集已经被使用过的词

        auto state_is_valid = [&](const state_t &s){
            return dict.find(s.word) != dict.end() || s.word == end;
        };
        // 最终到达end这个单词
        auto state_is_target = [&](const state_t &s){return s.word == end;};
        auto state_extend = [&](const state_t &s){
            unordered_set<state_t> ret;
            for (size_t i = 0; i < s.word.size(); ++i){
                state_t new_state(s.word, s.level + 1);
                for (char c = 'a'; c <= 'z'; c++){
                    if (c == new_state.word[i]) continue; // 防止同字母替换
                    swap(c, new_state.word[i]);  // 换一个单词， 搜索是否在visited字典中
                    if (state_is_valid(new_state) && \
                        visited.find(new_state) == visited.end()){
                        ret.insert(new_state);
                    }
                    swap(c, new_state.word[i]); // 恢复该单词
                }
            }
            return ret; // 返回所有与s只相差一个字母的词语，该词语必须合法（在end和dict中），没有被visited过
        };

        state_t start_state(start, 0);
        q.push(start_state);
        visited.insert(start_state);
        while(!q.empty()){
            const auto state = q.front();
            q.pop();
            if (state_is_target(state)){
                return state.level + 1;
            }
            const auto& new_states = state_extend(state);
            for (const auto& new_state: new_states){
                q.push(new_state);
                visited.insert(new_state);
            }
        }
        return 0;
    }
    // 双队列解决上述问题
    // 双队列不需要使用结构体来记录level
    // 时间复杂度O(n), 空间复杂度O(n)
    int ladderLengthUsingTwoQueues(const string& start, const string &end, \
        const unordered_set<string> &dict){
        queue<string> current, next; // 类似于第八章的树， 记录当前层和下一层
        unordered_set<string> visited;

        int level = -1;
        auto state_is_valid = [&](const string &s){
            return s == end || dict.find(s) != dict.end();
        };
        auto state_is_target = [&](const string &s){
            return s == end;
        };
        auto state_extend = [&](const string &s){
            unordered_set<string> ret;
            for (size_t i = 0; i < s.size(); ++i){
                string new_word(s);
                for (char c = 'a'; c <= 'z'; c++){
                    if (c == s[i]) continue;
                    swap(c, new_word[i]);
                    if (state_is_valid(new_word) && \
                        visited.find(new_word) == visited.end()){
                        ret.insert(new_word);
                    } 
                    swap(c, new_word[i]);
                }
            }
            return ret;
        };

        current.push(start);
        visited.insert(start);
        while (!current.empty()){
            ++level;
            while(!current.empty()){
                const auto state = current.front();
                current.pop();
                if(state_is_target(state)){
                    return level + 1;
                }
                const auto &new_states = state_extend(state);
                for (const auto &new_state : new_states){
                    next.push(new_state);
                    visited.insert(new_state);
                }
            }
            swap(next, current); // 实现逐层寻找
        }
        return 0;
    }
    // Word Ladder II
    // 在前面一个问题的基础上, 加一个条件， 找出所有符合最小长度的wordList
    // 为了简单，这里只列举双队列的方法。
    // 这道题可以看作是图的广搜
    // 时间复杂度O(n), 空间复杂度O(n)
    vector<vector<string>> findLaddersUsingTwoQueues(const string& start, \
    const string &end, const unordered_set<string> &dict){
        unordered_set<string> current, next;
        unordered_set<string> visited;
        unordered_map<string, vector<string>> father; // DAG图

        int level = -1;
        auto state_is_valid = [&](const string &s){
            return s == end || dict.find(s) != dict.end();
        };
        auto state_is_target = [&](const string &s){
            return s == end;
        };
        auto state_extend = [&](const string &s){
            unordered_set<string> ret;
            for (size_t i = 0; i < s.size(); ++i){
                string new_word(s);
                for (char c = 'a'; c <= 'z'; ++c){
                    if (c == new_word[i]) continue;
                    swap(c, new_word[i]);
                    if (state_is_valid(new_word) && \
                        visited.find(new_word) == visited.end()){
                        ret.insert(new_word);
                    }
                    swap(c, new_word[i]);
                }
            }
            return ret;
        };
        vector<vector<string>> ret;
        current.insert(start);
        while (!current.empty()){
            ++level;
            if (!ret.empty() && level + 1 > ret[0].size()) break;

            // 1. 延迟加入visited，允许两个父节点指向同一个子节点
            // 2. current 全部加入visted， 防止本层前一个节点扩展节点时，
            //    指向本层后面尚未处理的节点，而这条路径必然不是最短的
            for (const auto& state : current){
                visited.insert(state);
            }
            for (const auto &state : current){
                if (state_is_target(state)){
                    vector<string> path;
                    gen_path(father, path, start, state, ret);
                    continue;
                }

                const auto new_states = state_extend(state);
                for (const auto& new_state : new_states){
                    next.insert(new_state);
                    father[new_state].push_back(state);
                }
            }
            current.clear();   // 这里current是扫描完毕一层后统一清除的
            swap(current, next);
        }
        return ret;
    }
    // Surrounded Regions
    // 类似于围棋
    // 广搜，从上下左右四个边界从里走，凡是能碰到的O, 都是和边界接壤的，应该被保留
    void solve(vector<vector<char>> &board){
        if (board.empty()) return;
        const int m = board.size();
        const int n = board[0].size();
        // 从四个边界开始寻找‘0’并进行扩展, 注意不要重复
        for (int j = 0; j < n ; j++){
            bfsChessboard(board, 0, j);
            bfsChessboard(board, m - 1, j);
        }
        for (int i = 1; i < m - 1; i++){
            bfsChessboard(board, i, 0);
            bfsChessboard(board, i, n - 1);
        }
        for (int i = 0; i < m; i++){
            for (int j = 0; j < n; j++){
                if (board[i][j] == '0'){
                    board[i][j] = 'X';
                }
                else if(board[i][j] == '+'){
                    board[i][j] = '0';
                }
            }
        }
    }

    // Perfect Squares
    // 找到组成target所需的最少的平方数个数
    int getNumSquares(int target){
        vector<int> squareList = genSquares(target);
        queue<int> retDecompose;
        vector<bool> marked(target + 1, false);  // 防止重复剪枝使用
        retDecompose.push(target);
        marked[target] = true;
        int level = 0;
        while (!retDecompose.empty()){
            int size = retDecompose.size();
            level++;
            while (size-- > 0){
                int cur = retDecompose.front();
                retDecompose.pop();
                for (int iElem:squareList){
                    int next = cur - iElem;
                    if (next < 0) break;
                    if (next == 0) return level;
                    if (marked[next]) continue;
                    marked[next] = true;
                    retDecompose.push(cur - iElem);
                }
            }
        }
        return target;                                             // 如果最终都没有找到，使用n个1组成
    }
    private:
    // 反向生成路径
    // @param[in] father 存放了所有路径的树
    // @param[in] start  起点
    // @param[in] word   终点
    // @return           从起点到终点的所有路径
    void gen_path(unordered_map<string, vector<string>>&father, \
            vector<string> &path, const string &start, const string &word, \
            vector<vector<string>> &ret){
        path.push_back(word);
        if (word == start){
            if (!ret.empty()){
                if (path.size() < ret[0].size()){
                    ret.clear();
                    ret.push_back(path);   // 最短路径节点可能不同，但是长度是一样的
                }
                else if(path.size() == ret[0].size()){
                    ret.push_back(path);
                }
                else{
                    throw std::logic_error("not possible to get here for DAG");
                }
            }
            else{
                reverse(ret.back().begin(), ret.back().end());
            }
        }
        else{
            for (const auto &f: father[word]){
                gen_path(father, path, start, f, ret);
            }
        }
        path.pop_back();
    }

    void bfsChessboard(vector<vector<char>> &board, int i, int j){
        typedef pair<int, int> state_t;
        queue<state_t> q;
        const int m = board.size();
        const int n = board[0].size();
        auto state_is_valid = [&](const state_t &s){
            const int x = s.first;
            const int y = s.second;
            // 越界或者为X的地方返回false
            if( x < 0 || x >= m || y < 0 || y >= 0 || board[x][y] != '0'){
                return false;
            }
            return true;
        };
        auto state_extend = [&](const state_t &s){
            vector<state_t> ret;
            const int x = s.first;
            const int y = s.second;
            const state_t new_states[4] = {{x - 1, y}, {x + 1, y}, \
                    {x, y - 1}, {x, y + 1}};
            for (int k = 0; k < 4; ++k){
                if (state_is_valid(new_states[i])){
                    // '+'表示标记和去重两种功能
                    board[new_states[k].first][new_states[k].second] = '+';
                    ret.push_back(new_states[k]);
                }
            }
            return ret;
        };
        state_t start = {i, j}; // 这里的start一定是从边界开始的
        if (state_is_valid(start)){
            board[i][j] = '+';
            q.push(start);
        }
        while (!q.empty())
        {
            auto cur = q.front();
            q.pop();
            auto new_states = state_extend(cur);
            for (auto s : new_states){
                q.push(s);
            }
        }
        
    }
    // 生成所有小于target的平方数集合
    vector<int> genSquares(int target){
        vector<int> ret;
        int square = 1;
        int diff = 3;
        while (square <= target){
            ret.push_back(square);
            square += diff;
            diff += 2;             // 注意迭代公式 (n + 1)^2 - n^2 = 2*n - 1
        }
        return ret;
    }
    
    
};

