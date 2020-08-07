#include "chapter2_list.h"

int main(){
    Solution_basicList tList;
    forward_list<int> l1{3, 7, 9};
    forward_list<int> l2{1, 6, 4, 3};
    forward_list<int> ret;
    ret = tList.addTwoNums(l1, l2);
    for (auto i = ret.begin(); i != ret.end(); i++){
        cout << *i << ", ";
    } 
    cout << endl;
    
    ListNode testList(0);
    vector<int> a{1, 2, 3, 3, 6};
    size_t aSize = a.size();
    ListNode *head = &testList;
    ListNode *cur = head;
    for (size_t i = 0; i < aSize; i++){
        cur->next = new ListNode(a[i]);
        cur = cur->next;
    }
    // 测试过，不能直接删除输入链表的头指针
    ListNode *newHead = tList.removeKthFromEnd(head->next, 5);
    cout << " deleteDuplicates" << endl;
    for (cur = newHead; cur != nullptr; cur = cur->next){
        cout << cur->val << ", ";
    }
    cout << endl;
    
    system("pause");
    return 0;
}