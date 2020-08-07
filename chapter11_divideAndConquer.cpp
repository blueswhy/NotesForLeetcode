#include "chapter11_divideAndConquer.h"

int main(){
    Solution_divideAndConquer s_divCon;
    string testExp{"5-3*4-1+2"};
    vector<int> ret = s_divCon.getDiffWaysToCompute(testExp);
    cout << "All the possible results of the expression by adding parenthese: ";
    for (auto iElem:ret){
        cout << iElem << ", ";
    }
    cout << endl;
    system("pause");
    return 0;
}