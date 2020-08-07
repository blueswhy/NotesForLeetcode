#include"chapter14_graph.h"

int main(){
    Solution_graph s_g;
    const int courseNum = 4;
    vector<vector<int>> preCourses{{3, 1}, {3, 2}, {1, 0}, {2, 0}, {1, 2}};
    vector<int> retOrder = s_g.getOrder(courseNum, preCourses);
    cout<< "The correct order of courses : ";
    for (auto iBeg = retOrder.begin(); iBeg != retOrder.end(); iBeg++){
        cout << *iBeg << ", ";
    }
    cout << endl;
    system("pause");
    return 0;
}
