// 分治法
#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#include<vector>

using namespace std;

class Solution_divideAndConquer{
    public:
    // 二分法解决x^n, 认为n是一个正整数
    // 时间复杂度O(log n), 空间复杂度O(1)
    double myPow(double x, int n){
        if ( n < 0) return 1.0/ power(x, -n);
        else return power(x, n);
    }

    // 二分法解决Sqrt(x)
    // 返回一个和sqrt(x)接近的整数
    // 时间复杂度O(log n), 空间复杂度O(1)
    int mySqrt(int x){
        int left = 1, right = x/2;
        int last_mid;
        if (x < 2) return x;
        const int mid = left + (right - left)/2;
        while (left <= right){
            if ( x / mid > mid){    // 防止溢出
                left = mid + 1;
                last_mid = mid;
            }
            else if (x / mid < mid){
                right = mid - 1;
            }
            else {
                return mid;
            }
        }
        return last_mid;
    }
    // Different Ways to Add Parentheses
    // 输出给一个合法算式加括号后所有可能的结果
    // 实际上可以以贪心算法来生成 中缀表达式 对应的所有可能的二叉树，然后执行得到结果
    vector<int> getDiffWaysToCompute(string exp){
        vector<int> ret;
        if(exp.empty()) return vector<int>(0);
        for (int i = 0; i < exp.size(); i++){
            char cElem = exp[i];
            if (cElem == '+' || cElem == '-' || cElem == '*' || cElem == '/'){
                vector<int> left = getDiffWaysToCompute(exp.substr(0, i));
                vector<int> right = getDiffWaysToCompute(exp.substr(i + 1, exp.size() - i - 1));
                for (int lMem : left){
                    for (int rMem : right){
                        switch(cElem) {
                            case '+':
                            ret.push_back(lMem + rMem);
                            break;
                            case '-':
                            ret.push_back(lMem - rMem);
                            break;
                            case '*':
                            ret.push_back(lMem * rMem);
                            break;
                            default: 
                            ret.push_back(lMem / rMem);   // 如果考虑整数域，最好不考虑除法
                            break;
                        }
                    }
                }
                
            }
        }
        if (ret.empty()){
            ret.push_back(stoi(exp));     // 碰到单个数字即返回其值
        }
        sort(ret.begin(), ret.end());
        auto retRemoveDuplicates = unique(ret.begin(), ret.end());
        ret.erase(retRemoveDuplicates, ret.end());
        return ret;
    }
    private:
    double power(double x, int n){
        if (n == 0) return 1;
        double v = power(x, n/2);
        if (n % 2 == 0) return v*v;
        else
        {
            return v*v*x;
        }
    }
};