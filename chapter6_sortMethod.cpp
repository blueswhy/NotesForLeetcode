#include "chapter6_sortMethod.h"

int main(){
    Solution_sortMethod s_sort;
    vector<int> nums{1, 2, 1, 2, 2, 3, 4, 5, 5};
    int topKNum = 2;
    vector<int> ret;
    ret = s_sort.getTopKFrequent(nums, topKNum);
    cout << " The top K frequent elements: ";
    for (int iElem:ret){
        cout << iElem << ", ";
    }
    cout << endl;
    system("pause");
    return 0;
}