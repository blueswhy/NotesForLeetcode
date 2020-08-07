#include "chapter13_dynamicProgramming.h"

int main(){
    Solution_dp s_dp;

    vector<vector<char>> matrix(4, vector<char>(4, '0'));
    for (int i = 1; i < 4; i++){
        matrix[i][2] = '1';
    }
    for (int j = 1; j < 4; j ++){
        matrix[1][j] = '1';
    }

    int ret_rectArea = s_dp.maxRectangle(matrix);
    cout << "The max rectangle area is " << ret_rectArea << endl;

    string s1{"aabcc"}, s2{"dbbca"};
    string s3{"aadbbcbcac"};
    bool ret_interleaving = s_dp.isInterleave(s1, s2, s3);
    if (ret_interleaving) {
        cout << "s1 and s2 are interleaved." << endl;
    }
    else{
        cout << "s1 and s2 are  not interleaved." << endl;
    }

    string sCode1{"12341023"};
    cout << "Code1 " << sCode1 << " has " << s_dp.getNumDecoding(sCode1) << " ways to be decoded." << endl;
    system("pause");
    return 0;
}