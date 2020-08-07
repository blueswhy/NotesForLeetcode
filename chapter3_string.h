// 字符串
// C++ 常见字符串分割方法
// 借助strtok实现, char *strtok(char *str, const char *delim);
// 借助正则化表达式实现 std::regex re(pattern);, pattern是一个字符串，
//                    std::regex_match(tmp, re); 借助match函数实现匹配
// 还有一些regex_search、regex_replace函数，用法和python中的字符串处理正则化类似
#include<stdio.h>
#include<string.h>
#include<iostream>
#include<sstream>
#include<algorithm>
#include<vector>
#include<regex>
#include<unordered_map>
using namespace std;

class Solution_string{
    public:
    // 判断一个字符串的合法性：只包含字母数字和特殊符号，构成回文序列
    // 利用夹逼即可
    // 如果允许删除一个字符判断，直接在不符合条件的情况下，加上删除该字符(可能是左边，也可能是右边)的约束
    bool isPalindrome(string s){
        // transform函数将前两个参数所限制的字符串，根据第四个参数变化，存放到第三个参数中
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        auto left = s.begin(), right = prev(s.end());
        while (left < right){
            // alnum检查是否为字母或者数字
            if(!::isalnum(*left)) ++left;
            else if (!::isalnum(*right)) --right;
            else if (*left != *right) return false;
            else
            {
                left++, right--;
            }
            
            return true;
        }
    }
    // needle in haystack：string1中是否包含小字符串string2
    // 暴力解法，直接遍历O(N*M)，BruteForce解法
    int bruteForce(const string &haystack, const string &needle){
        if (needle.empty()) return 0;

        const int N = haystack.size() - needle.size() + 1;
        for (int i = 0; i < N; i++){
            int j = i;
            int k = 0;
            while (j < haystack.size() && k < needle.size() && haystack[j] == needle[k]){
                j++;
                k++;
            }
            if (k == needle.size()) return i;
        }
        return -1;
    }
    // 快速算法，有KMP算法， Boyer-Moore算法和Rabin-Karp算法。
    // 这里简述Rabin-Karp的思想，将m个小字符串的比较变为相应hash值的比较
    // 而且在移动窗口的情况下，相邻窗口的字符串的hash值是相关的，相应地减少计算次数而减少比较次数
    

    // atoi: String To Integer
    // 字符串输入转换
    // 可以考虑使用正则表达式 regex
    // 考虑不规则输入，无效格式，溢出数据
    int myAtoi(const string &str){
        int num = 0;
        int sign = 1;
        const int n = str.length();
        int i = 0;

        while (str[i] == ' ' && i < n) i++;

        if (str[i] == '+'){
            i++;
        }
        else if (str[i] == '-'){
            sign = -1;
            i++;
        }
        for (; i < n ; i++){
            // 碰到不合法字符，直接跳出结算
            if (str[i] < '0' || str[i] > '9') break;
            // 如果溢出看符号，正号直接截断输出最大值，负号输出为0
            if (num > INT_MAX/10 || (num = INT_MAX / 10 && (str[i] - '0') > INT_MAX % 10)){
                return sign = -1 ? INT_MIN : INT_MAX;
            }
            num = num*10 + str[i] - '0';
        }
        return num*sign;
    }
    // 给两个二进制数的字符串，返回相应结果
    string addBinary(string a, string b){
        string ret;
        const size_t n = a.size() > b.size() ? a.size() : b.size();
        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        int carry = 0;
        for (size_t i = 0; i < n; i++){
            const int ai = i < a.size() ?  a[i] - '0' : 0;
            const int bi = i < b.size() ?  b[i] - '0' : 0;
            const int val = (ai + bi + carry) % 2;
            carry = (ai + bi + carry) / 2;
            ret.insert(ret.begin(), val + '0');
        }
        if (carry) ret.insert(ret.begin(), '1');
        return ret;
    }
    // 经典题目，找到字符串中的最长回文串, 并返回
    // 动态规划的方法，复杂度较高，O(n*n) 和 O(n*n)
    string longestPalindmicDP(const string &s){
        const int n = s.size();
        // 使用vector数组由于其动态结构，会导致空间和时间的浪费
        bool f[n][n];
        fill_n(&f[0][0], n*n, false);
        size_t max_len = 1, start = 0;

        for (size_t i = 0; i < n; i++){
            f[i][i] = true;
            // 基于C++中二维数组按行存储，最后改成i,j的格式，Cache中会连续一些
            for (size_t j = 0; j < i; j++){
                f[j][i] = (s[j] == s[i]) && (i - j < 2 || f[j + 1][i - 1]);
                if (f[j][i] && max_len < i - j + 1){
                    max_len = i - j + 1;
                    start = j;
                }
            }
            return s.substr(start, max_len);
        }

    }
    // Manacher's Algorithm解决上述问题
    // 不过这种方法中要求原始字符串s中没有扩充符号, 扩充后字符串长度一定是奇数
    string longestPalindromeManacher(string s){
        string T = preProcess(s);
        const int n = T.length();
        // 以T[i]为中心，向两侧扩张的长度
        // T[i]是用哨兵符号^和$以及#扩充后的字符串
        // 最终P[i]是源字符串回文串的长度
        int P[n];
        int C = 0, R = 0; // C表示当前中心位置
        for (int i = 1; i < n - 1; i++){
            int i_mirror = 2 * C - i;
            P[i] = (R > i) ? min (R - i, P[i_mirror]) : 0; // 关键， 找最长不需要每一个地方为中心的回文序列都正确
            while (T[i + 1 + P[i]] == T[i - 1 - P[i]]){
                P[i]++;
            }

            if (i + P[i] > R){
                C = i;
                R = i + P[i];
            }

        }
        int max_len = 0;
        int center_index = 0;
        for (int i = 0; i < n - 1; i++){
            if (P[i] > max_len){
                max_len = P[i];
                center_index = i;
            }
        }
        return s.substr((center_index - 1 -max_len)/2, max_len);
    }
    // 自己实现正则化匹配函数
    // Regular Expression Matching
    // 带有通配符 * 和 ？
    // s是目标字符串， p是匹配字符串
    // 对于*的处理： p每当遇到一个*, 保留当前*的坐标和s的坐标，然后s从前向后扫描，如果不成功，s++重新扫描
    // p遇到？,直接s和p向前进一步即可
    bool isMatch(const char *s, const char *p){
        bool star = false;
        const char *str, *ptr;
        for (str = s, ptr = p; *str != '\0'; str++, ptr++){
            switch (*ptr){
                case '?':
                break;
                case '*':
                star = true;      // star用来记录通配符*,在后续跳过
                s = str, p = ptr; // s跳到str位置处开始扫描
                while(*p == '*') p++;
                if(*p == '\0') return true;
                str = s - 1;
                ptr = p - 1;    // 指向靠近非*元素最近的一个*
                break;
                default:
                if (*str != *ptr){
                    if (!star) return false;
                    s++;
                    str = s - 1;
                    ptr = p - 1;  // 保持留在p处
                }
            }
        }
        while (*ptr == '*') ptr++;
        return (*ptr == '\0');
    }
    // longset Common Prefix
    // 返回一个字符数组里 最长的前缀
    string longestCommonPrefix(vector<string> &strs){
        if (strs.empty()) return "";
        int right_most = strs[0].size() - 1; // 最大匹配长度

        for (size_t i = 1; i < strs[0].size(); i++){
            for (int j = 0; j <= right_most; j++){
                if (strs[i][j] != strs[0][j]){
                    right_most = j - 1;
                }
            }
        }
        return strs[0].substr(0, right_most + 1);
    }
    // Valid Number
    // 判断输入字符串是否为一个合法的数字
    // 使用regex 直接匹配 "-?\\d+\\.\\d+||-?\\d+",小数或者整数即可

    // strtod 将str所指向的字符串转换为一个浮点数，endptr指向转换中最后一个数字字符后的字符指针
    // 不为空，则说明str不是单纯的数字字符串。使用时需要头文件<stdlib.h>
    bool isValidNum(const string &s){
        enum InputType{
            INVALID,      // 0
            SPACE,        // 1
            SIGN,         // 2
            DIGIT,        // 3
            DOT,          // 4
            EXPONENT,     // 5
            NUM_INPUTS    // 6, 计数作用
        };
        // 状态转移表 9*6
        const int transitionTable[][NUM_INPUTS] = {
            -1, 0, 3, 1, 2, -1,           // 0
            -1, 8, -1, 1, 4, 5,           // 1
            -1, -1, -1, 4, -1, -1,        // 2
            -1, -1, -1, 1, 2, -1,         // 3
            -1, 8, -1, 4, -1, 5,          // 4
            -1, -1, 6,  7, -1, -1,        // 5
            -1, -1, -1, 7, -1, -1,        // 6
            -1, 8, -1, 7, -1, -1,         // 7
            -1, 8, -1, -1, -1, -1,        // 8
        };

        int state = 0;
        for (auto ch : s){
            InputType inputType = INVALID;
            if (isspace(ch)) inputType = SPACE;
            else if (ch == '+'|| ch == '-') inputType = SIGN;
            else if (isdigit(ch)) inputType = DIGIT;
            else if (ch == '.') inputType = DOT;
            else if (ch == 'e' || ch == 'E') inputType = EXPONENT;

            state = transitionTable[state][inputType];
            if (state == -1) return false;
        }
        return state == 1 || state == 4 || state == 7 || state == 8;
    }
    // 罗马数字转换
    // 类似于十进制，不过编码方式不同
    string intToRoman(int num){
        const int radix[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
        const string symbol[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", \
                                    "IX", "V", "IV", "I"};
        string roman;
        for (size_t i = 0; num > 0; ++i){
            int count = num / radix[i];
            num %= radix[i];
            for (; count > 0; --count){
                roman += symbol[i];
            }
        }
        return roman;
    }
    
    // 将罗马数字转换为整型变量有些麻烦，因为涉及到VI, II, IV等数字的分段，除非在写的时候就以空格隔开
    // 前面一个比后面一个大，使用减法 IV = V - I = 5 - 1 = 4, 否则是加法 VI = 5 + 1 = 6.
    int romanToInt(const string &s){
        int ret = 0;
        for (size_t i = 0; i < s.size(); i++){
            // 前面的比后面的小，减两次
            if (i > 0 && romanMap(s[i] > romanMap(s[i - 1]))){
                ret += (romanMap(s[i]) - 2 * romanMap((s[i - 1])));
            }
            else{
                ret += romanMap(s[i]);
            }
        }
        return ret;
    }
    // count and say
    // 对给定数字int，数数,形成一个序列
    // 1, 11, 21, 1211, 111221,...
    string countAndSay(int n){
        string s("1");
        while (--n){
            s = getNext(s);
        }
        return s;
    }

    // 单词聚类--Anagrams, 将组成单词的字母按照字母表排列后完全相同的单词归为一类
    vector<string> anagrams(vector<string> &strs){
        unordered_map<string, vector<string>> group;
        for (const auto &s: strs){
            string key = s;
            sort(key.begin(), key.end());
            group[key].push_back(s);
        }

        vector<string> ret;
        for (auto it = group.cbegin(); it != group.cend(); it++){
            if (it->second.size() > 1){
                ret.insert(ret.end(), it->second.begin(), it->second.end());
            }
        }

        return ret;
    }
    // Simplify Path
    // 在Unix-style下的路径简化
    // 用栈来实现
    string simplifyPath(const string &path){
        vector<string> dirs;
        for (auto i = path.begin(); i != path.end();){
            ++i;
            auto j = find(i, path.end(), '/');
            auto dir = string(i, j);

            // 当有连续的'///'时，dir为空
            if (!dir.empty() && dir != "."){
                if (dir == ".."){
                    if (!dirs.empty()){
                        dirs.pop_back();
                    }
                }
                else
                {
                    dirs.push_back(dir);    
                }
                
            }
            i = j;
        }
        stringstream out;
        if (dirs.empty()){
            out << "/";
        }
        else{
            for (auto dir :dirs){
                out << '/' << dir;
            }
        }
        return out.str();
    }
    // 返回一个字符串中最后一个单词的长度， 单词中不能包括空格和其他字符
    int lengthOfLastWord(const string &s){
        auto first = find_if(s.rbegin(), s.rend(), ::isalpha);
        auto last = find_if_not(s.rbegin(), s.rend(), ::isalpha);
        return distance(first, last);
    }
    private:
    // KMP算法则是直观的观察needle字符串本身的性质，来实现窗口的快速移动
    // 返回小字符串的next数组
    // next数组的值含义：j位处前的最大重复子串的长度
    static void compute_prefix(const char *pattern, int next[]){
        int i;
        int j = -1;
        const int m = strlen(pattern);
        next[0] = -1;
        for (i = 1; i < m; i++){
            while (j > -1 && pattern[j + 1] != pattern[i]) j = next[j];
            if (pattern[i] == pattern[j + 1]) j++;
            next[i] = j;
        }
    }
    // kmp算法
    // 消除主串指针的不必要回溯，提起信息进行加速匹配
    static int kmp(const char *text, const char *pattern){
        int i;
        int j = -1;
        const int n = strlen(text);
        const int m = strlen(pattern);
        if (n == 0 && m == 0) return 0;
        if (m == 0) return 0;
        // 申请空间后记得删除，new对应delete, malloc对应free
        int *next = (int*) malloc(sizeof(int) * m);
        compute_prefix(pattern, next);
        // 注意到其中i作为主串的下标时一直往前走的
        // 而子串pattern的下标视next数组来回退，相当于对text数组进行大区域滑动
        for (i = 0; i < n; i++){
            while (j > -1 && pattern[j + 1] != text[i]) j = next[j];
            if(text[i] == pattern[j + 1]) j++;
            if (j = m - 1){
                free(next);
                return i - j;
            }
        }
        free(next);
        return -1;
    }
    // 用于最长回文串的预处理中， Manacher's algorithm
    string preProcess(const string &s){
        int n = s.length();
        if (n == 0) return "^$";
        string ret = "^";
        for (int i = 0; i < n; i++){
            ret += "#" + s.substr(i, 1);
        }
        ret += "#$";
        return ret;
    }
    int romanMap(const char c){
        switch (c){
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            case 'D': return 500;
            case 'M': return 1000;
            default: return 0;     // 空格或其余无效字符
        }
    }

    string getNext(const string &s){
        stringstream ss;
        // find_if函数：前两个参数指定范围， 最后一个参数lambda表达式表示待找对象
        // 找到返回相应迭代器，否则返回该序列的结束迭代器
        // bind1st, 将一个二元函数的参数设定为定值，这样二元函数可以转化为一元函数来使用
        for (auto i = s.begin(); i != s.end(); ){
            auto j = find_if(i, s.end(), bind1st(not_equal_to<char>(), *i));
            ss << distance(i, j) << *i;
            i = j;
        }
        return ss.str();
    }

    // 用于在一句话中找到某一单词(这句话可以也只能作删除字符操作)
    bool findValid(const string &s, const string &target){
        size_t i, j = 0;
        while (i < s.size() && j < target.size()){
            if (s[i] == target[j]) j++;
            i++;
        }
        return j == target.size();       // 最终都会到达空字符
    }
};