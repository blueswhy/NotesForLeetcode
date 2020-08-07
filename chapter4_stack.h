// 栈

#include<stdio.h>
#include<stack>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution_stack{
    public:
    // Valid Parenthese
    // 当一个字符串仅仅包括三种括号时，判断这些括号组合是否正确

    bool isValid(string const &s){
        // 存储正确的括号格式和对应关系
        string left = "([{";
        string right = ")]}";
        stack<char> stk;

        for (auto c : s){
            // c是否被包含在left字符串中
            if (left.find(c) != string::npos){
                stk.push(c);
            }
            else{
                if (stk.empty() || stk.top() != left[right.find(c)]){
                    return false;
                }
                else{
                    stk.pop();
                }
            }
        }
        return stk.empty();
    }

    // Longest Valid Parentheses
    // 上述题目的进阶版，需要找到字符串中最长的合法括号使用字段

    // 简单一些，这些字符串中仅仅包含小括号()
    // 其实如果不是的话，也可以通过replace直接将{[]}等括号替换掉，或者直接遍历替换
    int longestValidParentheses(const string &s){
        int max_len = 0, last = -1;
        stack<int> lefts; // 记录没有被匹配的左括弧的位置
        for (int i = 0; i < s.size(); ++i){
            if (s[i] == '('){
                lefts.push(i);
            }
            else {
                if (lefts.empty()){
                    last = i;     // 记录最接近的右括弧的位置
                }
                else {
                    lefts.pop(); // find a valid pair
                    if (lefts.empty()){
                        max_len = max(max_len, i - last);
                    }
                    else {
                        // 对于 ((())这样的情况记录最接近的左括弧的位置
                        max_len = max(max_len, i - lefts.top());
                    }
                }
            }
        }
        return max_len;
    }

    // 直方图中最大的长方形面积
    // 这个和第二章中的蓄水池(trap)问题类似，用栈来解决。
    // 左边的大于右边的，则以左边为高的矩形块已经只有这一个了
    // 左边小于等于右边的，可以放到非递减序列中
    int largestRectArea(vector<int> &height){
        stack<int> s;
        height.push_back(0);   // 计算最后一个元素的最大面积
        int ret = 0;
        for (int i = 0; i < height.size(); ){
            if (s.empty() || height[i] > height[s.top()]){
                s.push(i++);
            }
            else {
                int tmp = s.top();
                s.pop();
                ret = max (ret, height[tmp]*(s.empty() ? i : i - s.top() - 1));
            }
        }
        return ret;
    }

    // 计算逆序波兰表达式，实际上即为 后缀表达式
    // 入栈，遇到计算符号出栈两个数字，计算相应值，再入栈，直到string遍历结束

    int evalPostfixExpression(vector<string> &tokens){
        stack<string> s;
        auto token = tokens.back();
        bool opFlag = true;
        for (auto token : tokens){
            if (!is_operator(token)){
                s.push(token);
            }
            else {
                int y = stoi(s.top());
                s.pop();
                int x = stoi(s.top());
                s.pop();
                switch(token[0]) {
                    case '+': x += y; break;
                    case '-': x -= y; break;
                    case '*': x *= y; break;
                    case '/': x /= y; break;
                    default : opFlag = false;
                }
                if (opFlag){
                    s.push(to_string(x));
                }
                else
                {
                    s.push(to_string(x));
                    s.push(to_string(y));
                    opFlag = true;
                }
                
                
            }
        }
        return stoi(s.top());         // 只是计算合法的后缀表达式，没有判断表达式是否合法
    }

    private:
    bool is_operator(const string &op){
        return op.size() == 1 && string("+-*/ ").find(op) != string::npos;
    }


};
