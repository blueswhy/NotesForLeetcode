#include<stdio.h>
#include<iostream>
#include<iomanip>
#include<vector>
#include<algorithm>
#include<unordered_map>

using namespace std;

struct TrieNode{
    int nCount;        // 记录该字符前缀出现的次数
    unordered_map<char, TrieNode> children;   // 表示路径字符和相应子节点
    TrieNode(){
        nCount = 1;
        children = unordered_map<char, TrieNode>();
    }
};
struct Interval{
    int start;
    int end;
    Interval(): start(0), end(0) { }
    Interval(int s, int e): start(s), end(e) { }
};
class Solution_project{
    public:
    // 字典树的插入和查找
    void insertTrie(TrieNode node,  const string word){
        const int size = word.length();
        for (int i = 0; i < size; i++){
            char cElem = word[i];
            if (!(node.children.find(cElem) == node.children.end())){
                node.children[cElem].nCount++;                    // 在树节点中找到了相应路径，在各节点中+1
            }
            else{
                node.children.insert({cElem, TrieNode()});        // 如果没有在该节点处插入边为cElem的节点
            }
            node = node.children[cElem];
        }
    }
    int searchTrie(TrieNode node, const string word){
        for (int i = 0; i < word.length(); i++){
            char cElem = word[i];
            if (node.children.find(cElem) == node.children.end()){
                return 0;
            }
            node = node.children[cElem];
        }
        return node.nCount;
    }
    // Reverse Integer
    int getReverseNum(int x){
        long long r = 0;
        long long t = x;
        t = t > 0 ? t : -t;    // 取绝对值
        for (; t; t /= 10){
            r = r * 10 + t % 10;  // 逆序--取余放高位
        }
        bool sign = x > 0 ? false : true;
        if ( r > 2147483647 || (sign && r > 2147483648)){
            return 0;
        }
        else{
            return sign ? -r : r;
        }
    }
    // Palindrome Number
    //  时间复杂度O(1), 空间复杂度O(1)
    bool isPalindromeInteger(int x){
        if (x < 0) return false;
        int div = 1;
        while (x / div >= 10) div *= 10;     // 找到最高位
        while (x > 0){
            int quot = x / div;
            int rem = x % 10;
            if (quot != rem) return false;
            x = (x % div) / 10;
            div /= 100;
        }
        return true;
    }
    // Insert Interval
    // 时间复杂度O(n), 空间复杂度O(1)
    // Merge Interval
    // 时间复杂度O(n1 + n2 +...),空间复杂度O(1)
    vector<Interval> insertInterval(vector<Interval> &intervals, Interval newInterval){
        vector<Interval> :: iterator iter = intervals.begin();
        while (iter != intervals.end()){
            if (newInterval.end < iter->start){
                intervals.insert(iter, newInterval);
                return intervals;
            }
            else if (newInterval.start > iter->end){
                iter++;
                continue;
            }
            else{
                newInterval.start = min(newInterval.start, iter->start);
                newInterval.end = max(newInterval.end, iter->end);
                iter = intervals.erase(iter);
            }
        }
        intervals.insert(intervals.end(), newInterval);  // 跳出while循环后重合子空间没有插入
        return intervals;

    }
    // Multiply Strings
    // 时间复杂度O(n*m/81), 空间复杂度O((n + m)/9)
    // 一个数组元素对应9个十进制位，即数组是亿进制的，而10^18 < 2^63 - 1
    string multiply(string num1, string num2){
        BigInt iNum1 = make_bigInt(num1);
        BigInt iNum2 = make_bigInt(num2);
        BigInt iRet = multiply(iNum1, iNum2);
        return toString(iRet);
    }
    // Substring with Concatenation of  All Words
    // 时间复杂度O(n*m), 空间复杂度O(m)
    vector<int> findSubstring(string s, vector<string> &dict){
        size_t wordLength = dict.front().length();
        size_t catLength = wordLength*dict.size();
        vector<int> ret;

        if (s.length() < catLength) return ret;
        unordered_map<string, int> wordCount;
        for (auto const& word : dict) ++wordCount[word];  // 统计词频
        for (auto  i = begin(s); i <= prev(end(s), catLength); ++i){  // 遍历结束点在离end处前一个总词长的位置
            unordered_map<string, int> unused(wordCount);
            for (auto j = i; j != next(i, catLength); j += wordLength){ // 遍历的步长为词长, 每隔
                auto pos = unused.find(string(j, next(j, wordLength)));
                if (pos == unused.end() || pos->second == 0) break;
                if (--pos->second == 0) unused.erase(pos); 
            }
            if (unused.size() == 0) ret.push_back(distance(begin(s), i));
        }
    }
    // Pascal's Triangle
    // 从右边到左边，时间复杂度O(n^2)，空间复杂度O(n)
    vector<vector<int>> genPascalTriangle(int numRows){
        vector<vector<int>> ret;
        vector<int> array;         // 滚动数组
        for (int i = 1; i <= numRows; i++){
            for (int j = i - 2; j > 0; j--){
                array[j] = array[j - 1] + array[j];
            }
            array.push_back(1);
            ret.push_back(array);
        }
        return ret;
    }
    // 仅仅返回第k行的数组结果
    vector<int> getPascalRow(int rowIndex){
        vector<int> array;
        for (int i = 1; i <= rowIndex; i++){
            for (int j = i - 2; j > 0; j--){
                array[j] = array[j - 1] + array[j];
            }
            array.push_back(1);
        }
        return array;
    }
    // Spiral Matrix
    // 时间复杂度O(n^2)， 空间复杂度O(1)
    vector<int> spiralOrder(vector<vector<int>> &matrix){
        vector<int> ret;
        if (matrix.empty()) return ret;
        int beginX = 0, endX = matrix[0].size() - 1;   // 这里的X按一行走
        int beginY = 0, endY = matrix.size() - 1;      // 这里的Y按一列走
        while(true){
            for (int j = beginX; j <= endX; ++j){
                ret.push_back(matrix[beginY][j]);
            }
            if (++beginY > endY) break;
            for (int i = beginY; i <= endY; ++i){
                ret.push_back(matrix[i][endX]);
            }
            if (beginX > --endX) break;
            for (int j = endX; j >= beginX; j--){
                ret.push_back(matrix[endY][j]);
            }
            if (endY-- < beginY) break;
            for (int i = endY; i >= beginY; i--){
                ret.push_back(matrix[i][beginX]);
            }
            if (++beginX > endX) break;
        }
        return ret;
    }
    // 给定一个数字n，将1到n^2按照螺旋顺序填入一个二维数组中
    // 由于是方阵，比上一题要简单
    vector<vector<int>> genSpiralMatrix(int n){
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int begin = 0, end =  n - 1;
        int num = 1;
        while (begin < end){
            for (int j = begin; j < end; j++) matrix[begin][j] = num++;
            for (int i = begin; i < end; i++) matrix[i][end] = num++;
            for (int j = end; j > begin; j--) matrix[end][j] = num++;
            for (int i = end; i > begin; i--) matrix[i][begin] = num++;
            begin++;
            end--;
        }
        if (begin == end) matrix[begin][begin] = num; // n是一个奇数时
        return matrix;
    }
    // Zigzag Conversion
    // 时间复杂度O(n)，空间复杂度O(1)
    string convertZigzag(string s, int nRows){
        if (nRows <= 1 || s.size() <= 1) return s;
        string ret;
        // 这里的j表示处在zigzag串中的第几个垂直列
        for (int i = 0; i < nRows; i++){
            for (int j = 0, index = i; index < s.size();\
                    j++, index = 2*(nRows - 1)*j + i){
                ret.append(1, s[index]);   // 垂直元素
                if (i == 0 || i == nRows - 1) continue;  // 该行没有斜线元素
                if (index + (nRows - i - 1) *2 < s.size()){
                    ret.append(1, s[index + (nRows - i - 1)*2]);  // 斜线元素和前面同行元素之间的关系
                }
            }
        }
        return ret;
    }
    // Divide Two Integers
    // 在不使用乘除和取模的情况下，进行除法运算。
    // 可以使用减法和移位运算
    // 时间复杂度O(log n), 空间复杂度O(1)
    int divideUsingMinus(int dividend, int divisor){
        long long a = dividend >= 0 ? dividend : -(long long)dividend;
        long long b = divisor >= 0 ? divisor : -(long long) divisor;
        // 使用long long 防止dividend = INT_MIN的情况
        long long ret = 0;
        while(a >= b){
            long long c = b;
            for (int i = 0; a >= c; ++i, c <<= 1){
                a -= c;
                ret += 1 << i;
            }
        }
        return (dividend^divisor >> 31) ? (-ret): ret; // 移位运算判断正负
    }
    //  Text Justification
    // 时间复杂度O(n), 空间复杂度O(1)
    vector<string> fullJustify(vector<string> &words, int L){
        vector<string> ret;
        const int n = words.size();
        int begin = 0, len = 0;  // 本行的第一个词语， 本行当前的字符串个数
        for (int i = 0; i < n; i++){
            if (len + words[i].size() + (i - begin) > L){
                ret.push_back(connectedWords(words, begin, i - 1, len, L, false));
                begin = i;
                len = 0;
            }
            len += words[i].size();
        }
        ret.push_back(connectedWords(words, begin, n - 1, len, L, true));
        return ret;
    }
    // Max Points on a Line
    // 时间复杂度O(n^2)，空间复杂度O(n)
    int maxPoints(vector<pair<int, int>> &points){
        if (points.size() < 3) return points.size();
        int ret = 0;
        unordered_map<double, int> slope_count; // 斜率计算，对于每个点而言进行扩展
        for (int i = 0; i < points.size() - 1; i++){
            slope_count.clear();       // 初始化，对于每个点而言重新赋值
            int samePointNum  =  0;   // 和i重合的点
            int point_max = 1;        // 和i共线的点
            for (int j = i + 1; j < points.size(); j++){
                double slope;
                if (points[i].first == points[j].first){
                    slope = std::numeric_limits<double>::infinity();   // 垂直斜率置为无穷大
                    if (points[i].second == points[j].second){
                        ++ samePointNum;
                        continue;
                    }
                }
                else{
                    slope = 1.0*(points[i].second - points[j].second)/ \
                            (points[i].first - points[i].first);
                }
                int count = 0;
                if (slope_count.find(slope) != slope_count.end()){
                    count = ++slope_count[slope];
                }
                else{
                    count = 2;
                    slope_count[slope] = 2;
                }
                if (point_max < count) point_max = count;
            }
            ret = max(ret, point_max + samePointNum);       // 每次计算算上相同点和共线点
        }
        return ret;
    }
    private:
    typedef pair<int, int> Point;
    typedef long long int64_t;
    const static int BIGINT_RADIX = 1000000000;
    const static int RADIX_LEN = 9;
    typedef vector<int64_t> BigInt;
    BigInt make_bigInt(string s){
        vector<int64_t> ret;
        ret.reserve(s.size()/RADIX_LEN + 1);
        for (int i = s.size(); i > 0; i -= RADIX_LEN){
            int tmp = 0;
            const int low = max(i - RADIX_LEN, 0);
            for (int j = low; j < i; j++){
                tmp = tmp*10 +s[j] - '0';
            }
            ret.push_back(tmp);       // 高位到低位存储在ret中
        }
        return ret;
    }
    // 流控制函数
    // setw: 需要填充多少字符，默认填充的字符为空格
    // setfill： 设置setw的默认字符
    // setbase: 将输出数据转换为n进制
    // setprecision: 控制输出流显示浮点数的数字个数， C++默认显示后6位
    string toString(BigInt &intRet){
        stringstream ret;
        bool started = false;  // 跳出前置0
        for (auto i = intRet.rbegin(); i != intRet.rend(); i++){
            if (started){
                ret << setw(RADIX_LEN) << setfill('0') << *i; // 如果低位不到的位置用0补齐
            }
            else{
                ret << *i;
                started = true;
            }
        }
        if (!started) {
            return "0";
        }
        else{
            return ret.str();
        }
    }
    // 执行大整数乘法
    static BigInt multiply(const BigInt &x, const BigInt &y){
        BigInt z(x.size() + y.size(), 0);
        for (size_t i = 0; i < y.size(); i++){
            for (size_t j = 0; j < x.size(); j++){
                z[i + j] = x[j] * y[i];
                if (z[i + j] >= BIGINT_RADIX){
                    z[i + j + 1] += z[i + j] / BIGINT_RADIX;
                    z[i + j] %= BIGINT_RADIX; 
                }
            }
        }
        while (z.back() == 0) z.pop_back(); // 如果没有进位，去掉高位多余的0
        return z;
    }
    // 字符串格式化输出
    string connectedWords(vector<string> &words, int begin, int end, \
            int len, int L, bool is_last){
        string s;
        int n = end - begin + 1;
        for (int i = 0; i < n; ++i){
            s += words[begin + i];
            addSpaces(s, i, n - 1, L - len, is_last);
        }
        if (s.size() < L) s.append(L - s.size(), ' ');
        return s;
    }
    void addSpaces(string &s, int i, int n, int L, bool is_last){
        // L表示去除有用字符串后L剩余的空格总数
        if (n < 1 || i > n - 1) return;
        int spaces = is_last ? 1 : (L/n + (i < (L%n) ? 1 : 0));
        s.append(spaces, ' ');
    }
    
};