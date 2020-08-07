#include "chapter10_DFS.h"

int main(){
    Solution_depthFirstSearch s_dfs;
    vector<vector<int>> obstacleGrid(4, vector<int>(4, 0));
    obstacleGrid[2][1] = 1;
    obstacleGrid[0][3] = 1;
    int ret_dfsObstacleGrid = s_dfs.uniquePathsWithObstaclesUsingMem(obstacleGrid);

    cout << "The valid paths of obstacleGrid : " << ret_dfsObstacleGrid << endl;

    vector<int> nums{2, 3, 1, 9, 8, 6};
    int target = 17;
    vector<vector<int>> ret_combineSum = s_dfs.combinationSum(nums, target);         // 可重复选择
    int index = 1;
    for (auto vRet : ret_combineSum){
        cout << "The " << index << "th combination from nums to target " << target << " is: ";
        for (auto iRet = vRet.begin(); iRet < vRet.end(); iRet++){
            cout << *iRet << ", ";
        }
        cout << endl;
        index++;
    }
    
    vector<vector<int>> heightMtx{{1, 2, 2, 3, 5}, {3, 2, 3, 4 ,4}, \
        {2, 4, 5, 3, 1}, {6, 7, 1, 4, 5}, {5, 1, 1, 2, 4}};
    vector<pair<int, int>> retPAFlow;
    retPAFlow = s_dfs.getPacificAltanticFlow(heightMtx);
    cout << "All the positions which can reach pacific and atlantic :" << endl;
    for (auto pElem : retPAFlow){
        cout << "(" << pElem.first << ", " << pElem.second << "), ";
    }
    cout << endl;
    
    system("pause");
    return 0;
    

}