#include "chapter4_stack.h"

int main(){
    string s = "(()))(";
    Solution_stack testStk;
    int lenValid = testStk.longestValidParentheses(s);
    cout << "Longest Valid Parentheses of "<< s << " is :" << lenValid << endl;

    vector<string> exp1{"4", "13", "5", "/", " ", "+"};
    cout << "The result of Postfix Expression is : " << testStk.evalPostfixExpression(exp1) << endl;
    system("pause");
    return 0;
}
