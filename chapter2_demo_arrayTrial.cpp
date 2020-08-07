#include "chapter2_array_removeAndSort.h"
// #include <vector>

// vector<int> Solution_s5::twoSum(vector<int> &nums, int target);
int main(){
    // Solution_s5 t_s5;
    // vector<int> QueryA{5, 3, 6, 9, 0, 4, 2};
    // int target = 9;
    // vector<int> ret = t_s5.twoSum(QueryA, target);

    // for (auto iRet = ret.begin(); iRet != ret.end(); iRet++)
    //     cout << *iRet << endl;
    
    Solution_trappingRainWater t_trap;
    vector<int> trapArray{1, 2, 3, 4, 3, 2, 1};
    int trapRet;
    trapRet = t_trap.trap3(trapArray);
    cout << trapRet << endl;
    system("pause");
    return 0;
}