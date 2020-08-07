#include "chapter8_enumeration.h"

int main(){
    Solution_enumeration s_enum1;
    vector<int> testNums{1, 2, 3, 4};
    vector<vector<int>> testRet;

    testRet = s_enum1.permute(testNums);
    for (auto i = 0; i < testRet.size(); i++){
        auto ivRet = testRet[i];
        cout << "The " << i + 1 << "th permutation: ";
        for (auto iElem = ivRet.begin(); iElem < ivRet.end(); iElem++){
            cout << *iElem << ", ";
        }
        cout << endl;
    }

    const string dialNum("322");
    vector<string> retWord = s_enum1.letterCombinations(dialNum);
    if (retWord.empty()){
        cout << "Word Clear!" << endl;
    }  
    cout << "The word combinations of " << dialNum << " is , " << endl;
    for (auto sElem = retWord.begin(); sElem < retWord.end(); sElem++){
        cout << *sElem << ", ";
    }
    cout << endl;
    system("pause");
    return 0;
}