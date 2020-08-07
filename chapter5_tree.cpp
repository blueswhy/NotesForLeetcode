#include "chapter5_tree.h"

int main(){
    // 建立二叉树时，用-1表示空节点
    // 因为在头文件中的建立节点根据值查找实现，因此序列不能有重复
    vector<int> treePreorderList = {1, 2, 3, 4, 5, -1, 6, 7, 8};
    vector<int> treeInorderList = {3, 2, 4, 1, -1, 5, 7, 6, 8};

    TreeNode *treeRoot1;
    Solution_treeConstructor s_treeConst1;

    treeRoot1 = s_treeConst1.buildTreeUsingPreInorder(treePreorderList, treeInorderList);

    Solution_treeTraversing s_treeTraver1;
    vector<int> treePreorderRet = s_treeTraver1.preorderTraveralUsingMorris(treeRoot1);
    vector<int> treeInorderRet = s_treeTraver1.inorderTraversalUsingStack(treeRoot1);
    vector<int> treePostorderRet = s_treeTraver1.postorderTraversalUsingStack(treeRoot1);

    cout << "Result of Preorder traversing: "<< endl;
    for (auto iBegin = treePreorderRet.begin(), iEnd = treePreorderRet.end(); iBegin != iEnd; iBegin++){
        cout << *iBegin << ", ";
    }
    cout << endl;
    cout << "Result of Inorder traversing: " << endl;
    for (auto iBegin = treeInorderRet.begin(), iEnd = treeInorderRet.end(); iBegin != iEnd; iBegin++){
        cout << *iBegin << ", ";
    }
    cout << endl;
    cout << "Result of Postorder traversing: "  << endl;
    for (auto iBegin = treePostorderRet.begin(), iEnd = treePostorderRet.end(); iBegin != iEnd; iBegin++){
        cout << *iBegin << ", ";
    }
    cout << endl;

    // 验证平衡二叉树BST的构建
    vector<int> sortedArray1 = {1, 3, 5, 8, 10, 13, 18};
    Solution_treeBinarySearch s_treeBT;
    TreeNode *retSAToBST = s_treeBT.sortedArrayToBST(sortedArray1);
    cout << "The reesult of sorted array to binary search tree using postorder traversing: " << endl;
    vector<int> retSAToBST_postorderList = s_treeTraver1.postorderTraversalUsingStack(retSAToBST);
    for (auto iBegin = retSAToBST_postorderList.begin(), iEnd = retSAToBST_postorderList.end();
        iBegin != iEnd;
        iBegin++){
        cout << *iBegin << ", ";
    }
    cout << endl;
    system("pause");
    return 0;
}