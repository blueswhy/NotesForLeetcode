// Leecode 2.2部分单链表
// 在教程中使用的是自定义的单链表，不过C++库中提供了可以直接使用的单链表forward_list

#include<stdio.h>
#include<iostream>
#include<forward_list>
#include<list>
#include<iterator>
#include<vector>
#include<unordered_map>

using namespace std;

// 自定义单链表
// 部分链表要求头节点存放容器大小，这里没需要，直接置为-1
struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){ }
};


class Solution_basicList{
    public:
    // 十进制相加，但是数据存储按照单链表反序存放, 按照以下算法返回值是按正常顺序存放的。
    // forward_list 和ListNode比起来限制更多，无法在遍历的过程中进行插入操作（会改变原有链表的end()值）
    // 后续使用自定义链表解题
    forward_list<int> addTwoNums(const forward_list<int> &l1, const forward_list<int> &l2){
        forward_list<int> ret;
        int carry = 0;   // 表示进位
        // auto r = ret.begin();
        for (auto i = l1.begin(), j = l2.begin(); i != l1.end() || \
        j != l2.end(); ){
            const int ai = (i == l1.end()) ? 0: (*i++);
            const int bj = (j == l2.end()) ? 0: (*j++);
            ret.push_front((ai + bj + carry) % 10);
            carry = (ai + bj + carry) / 10;
        }
        if (carry > 0){
            ret.push_front(1);
        }
        return ret;
    }
    // 对于给定链表，指定（m, n）将m和n之间的所有元素反序
    // 小trick: 靠后的元素前移，相当于一种递归操作
    ListNode *reverseBetween(ListNode *head, int m, int n){
        ListNode dummy(-1);   // 头节点
        dummy.next = head;    // 指向所要操作的数组
        ListNode *prev = &dummy;
        for (int i = 0; i < m - 1; ++i){
            prev = prev->next;            // 保留前面的m - 1个节点
        }
        ListNode* const head2 = prev;
        prev = head2->next;               // 第m个节点
        ListNode *cur = prev->next;
        for (int i = m; i < n; ++i){
            prev->next = cur->next;
            cur->next = head2->next;
            head2->next = cur;
            cur = prev->next;
        }
        return dummy.next;  
    }
    // Partition List
    // 给定一个单链表L和值x, 使得链表中的值按照partition x 分成两部分，各部分内部数据相对位置不变
    ListNode *partition(ListNode *head, int x){
        ListNode left_dummy(-1);
        ListNode right_dummy(-1);
        auto left_cur = &left_dummy;
        auto right_cur = &right_dummy;

        for (ListNode *cur = head; cur != nullptr; cur = cur->next){
            if(cur->val < x){
                left_cur->next = cur;
                left_cur = cur;
            }
            else
            {
                right_cur->next = cur;
                right_cur = cur;
            }
        }
        left_cur->next = right_dummy.next;
        right_cur->next = nullptr;
        return left_dummy.next;
    }
    // 对于一个排序后的链表去除重复元素，和数组处理方法类似，移动到非重复元素后，直接改变链路
    // 这里没有删除节点
    // 如果需要删除节点，即一个一个遍历cur，判断cur是否重复，若重复则删除
    ListNode *deleteDuplicates(ListNode *head){
        if(!head) return head;   // 如果是一个链表， 返回空指针
        
        ListNode *prev = head, *cur = head->next;
        for (; cur != nullptr; cur = cur->next){
            if (prev->val != cur->val){
                prev->next = cur;
                prev = prev->next;
            }
        }
        if (prev->next && !cur){
            prev->next = cur;
        }
        return head;
    }
    // 给定一个链表，删除其中所有含有重复元素的节点
    ListNode *deleteDuplicates2(ListNode *head){
        if (!head) return head;
        ListNode dummy(INT_MIN);        // 头节点, 这里设置头节点是因为可能开头直接被删除，需要有一个固定节点作为头
        dummy.next = head;
        ListNode *prev = &dummy, *cur = head;
        while (cur){
            bool dulplicated = false;
            while (cur->next && cur->val == cur->next->val){
                dulplicated = true;
                ListNode *temp = cur;
                cur = cur->next;
                delete temp;
            }
            if (dulplicated){
                ListNode *temp = cur;
                cur = cur->next;
                delete temp;
                continue;                // Warn: 删除掉最后一个元素后， 继续判断下一个元素是否重复
            }
            prev->next = cur;
            prev = prev->next;
            cur = cur->next;
        }
        prev->next = cur;
        return dummy.next;
    }
    // 循环移位k位， k可能大于len, 因此移位先处理为 k%len
    ListNode *rotateRight(ListNode *head, int k){
        if (!head) return head;
        int len = 1;
        ListNode *p = head;
        while (p->next){
            len++;
            p = p->next;   // 遍历过以后记录尾部节点的位置
        }
        k = len - k % len;
        p->next = head;        // 首尾相连
        for (int step = 0; step < k; step++){
            p = p->next;
        }
        head = p->next;
        p->next = nullptr;      // 找到首尾节点，断开环
        return head;
    }
    // 删除距离尾部节点第k个节点
    // 设置两个指针，让p先走n步，然后p和q一起走，直到p到尾部元素（非Null)，则q指向被删除节点前一个位置，然后删除即可
    // 因为头部指针可能被删除，需要建立一个新的头节点
    ListNode *removeKthFromEnd(ListNode *head, int k){
        if (!head) return head;
        ListNode dummy(-1);
        dummy.next = head;
        ListNode *p = &dummy, *q = &dummy; 
        for (int i = 0; i < k && p; i++){
            p = p->next;
        }
        if (!p) return nullptr;          // 输入k超过长度，则直接返回空
        while (p->next)
        {
            p = p->next;
            q = q->next;
        }
        ListNode *tmp = q->next;
        q->next = tmp->next;
        delete tmp;
        return dummy.next;
    }
    // 以头节点为初始节点，对相邻的每一对节点进行交换，不允许直接交换节点内部的值
    ListNode *swapPairs(ListNode *head){
        if( !head || !head->next) return head;
        ListNode dummy(-1);
        dummy.next = head;
        // 是奇数个，则用next直接控制结束
        for (ListNode *prev = &dummy, *cur = prev->next, *next = cur->next;\
                next;\
                prev = cur, cur = cur->next, next = cur ? cur->next: nullptr){
            prev->next = next;
            cur->next = next->next;
            next->next = cur;
        }
        return dummy.next;
    }
    // 上述交换问题的升级版本，给定k, 使得链表中每k个元素作为一个子链表进行逆序处理
    ListNode *reverseKGroup(ListNode *head, int k){
        if(!head || !head->next) return head;
        ListNode *next_group = head;
        for (int i = 0; i < k; i++){
            if (next_group){
                next_group = next_group->next;
            }
            else{
                return head;
            }
        }
        // 剩余的元素返回其头部元素指针
        ListNode *new_next_group = reverseKGroup(next_group, k);
        ListNode *prev = nullptr, *cur = head;
        while(cur != next_group){
            ListNode *next = cur->next;
            cur->next = prev ? prev :new_next_group;  // prev为真，则选取prev否则指向后面的子链表头部
            prev = cur;
            cur = next;
        }
        return prev;

    }
    ListNode *reverseKGroupIter(ListNode *head, int k){
        if (!head || !head->next || k < 2) return head;
        ListNode dummy(-1);
        dummy.next = head;

        for (ListNode *prev = &dummy, *end = head; end; end = prev->next){
            for (int i = 1; i < k && end ; i++){
                end = end->next;
            }
            if (end == nullptr) break;
            prev = reversePart(prev, prev->next, end);
        }
        return dummy.next;
    }
    // 复制带有随机指针的链表，深度复制
    // 需要定义RandomListNode 特殊链表，存放随机指针节点
    // 给出两个链表，找到其相交点的位置
    ListNode *getIntersectionNode(ListNode *head1, ListNode *head2){
        ListNode *p = head1, *q = head2;
        while (p != q ){
            if (p->next == nullptr && q->next == nullptr){
                p = p->next;
                q = q->next;                
                break;
            }
            else{
                if (p->next == nullptr){
                    p = head2;
                }
                if (q->next == nullptr){
                    q = head1;
                }
            }
            p = p->next;
            q = q->next;
        }
        return p;             // 如果不存在，则两个节点同时到末尾，返回空指针
    }
    // 给出一个链表，证明是否有环
    // 空间复杂度为O(1)的方法，设置两个指针，快指针一次走2步， 慢指针一次走1步，如果能相遇，则说明有环
    // 该方法也可以用来找数组里的相同值位置（只有一个环的情况下）
    bool hasCycle(ListNode *head){
        ListNode *fast = head, *slow = head;
        while(fast && fast->next){
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) return true;
        }
        return false;
    }
    // 找到上述环的地方
    // 设环入口为x, 相遇点距环入口a， 而 fast 比 slow 指针多走了n圈
    // 最终可以推导得到 x = (n - 1)r + (L - x - a);
    // 可以在相遇点 x + a 处固定之前的slow指针， 然后再在初始位置设置一个fast2 或者 slow2
    // 最终相遇点变成 x 位置， 最简单的是 n = 1的验证
    ListNode *detectCycle(ListNode *head){
        ListNode *fast = head, *slow = head;
        while (fast && fast->next)
        {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow){
                ListNode *slow2 = head;
                while (slow2 != slow){
                    slow2 = slow2->next;
                    slow = slow->next;
                }
                return slow;
            }
        }
        return nullptr;
    }
    // ReorderList
    // 对于链表重新排序，使得相邻的节点和为n(如果下标以0开始n结束，n+1个节点)
    // in place
    // 由于链表的单向性，先找到中间节点，断开，然后将后半截单链表逆序，合并两个单链表
    void reorderList(ListNode *head){
        if(!head || !head->next) return;
        ListNode *slow = head, *fast = head, *prev = nullptr;
        // 分成两段，slow作为第二段的头部，fast作为第二段的尾部实现逆序
        while(fast && fast->next){
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = nullptr;
        slow = reverseList(slow);
        ListNode *cur = head;
        while (cur->next){
            ListNode *tmp = cur->next;
            cur->next = slow;
            slow = slow->next;
            cur->next->next = tmp;
            cur = tmp;
        }
        cur->next = slow;       // 连上最终后半List多余的部分
    }
    
    private:
    // 在[begin, end]区间内反转，返回反转后的末尾节点
    ListNode *reversePart(ListNode *prev, ListNode *begin, ListNode *end){
        ListNode *end_next = end->next;
        for (ListNode *p = begin, *cur = p->next, *next = cur->next;\
            cur != end_next;\
            p = cur, cur = next, next = next ? next->next : nullptr){
                cur->next = p;
        }
        begin->next = end->next;
        prev->next = end;
        return begin;
    }
    ListNode *reverseList(ListNode *head){
        if (!head||!head->next) return head;
        ListNode *prev = head;
        for (ListNode *cur = head->next, *next = cur->next; 
                cur;
                prev = cur, cur = next, next = next? next->next : nullptr){
            cur->next  = prev;
        }
        head->next = nullptr;
        return prev;
    }
    
    
};
// 设计一个复合LRUCache(最近最少使用, 防止cache固定单元被频繁使用)的数据结构。功能函数是get 和 set。
// 为了保证查找、插入和删除的高性能，使用双向链表和哈希表。
// 哈希表可以保存每个节点的地址，保证在O(1)时间内查找节点
// 双向链表插入和删除效率高，单向链表插入和删除时，还要查找节点的前驱结点。

// 靠近链表头部的节点表示最近刚被访问，尾部节点表示最近访问较少
// 访问节点时，如果节点存在，把该节点交换到链表头部，同时更新hash表中该节点的地址。
// 插入节点时，如果cache的size达到了上限capacity，则删除尾部节点。
// 时间复杂度为O(log n)， 空间复杂度为O(n)


class LRUCache{
    private:
    struct CacheNode{
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v){}
    };
    list<CacheNode> cacheList;  // 一个双向链表
    unordered_map<int, list<CacheNode>::iterator> cacheMap;
    int capacity;

    public:
    LRUCache (int capacity){
    this->capacity = capacity;
    }
    // 但是按照本算法进行，在插入元素或者查找元素后，仅仅更新了头部key的地址，其余元素怎么办？
    int get(int key){
        if (cacheMap.find(key) == cacheMap.end()) return -1;
        // 移动函数，将被查找元素放到链表头部，并且更新map中该节点的地址
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        cacheMap[key] = cacheList.begin();
        return cacheMap[key]->value;
    }

    void set(int key, int value){
        if (cacheMap.find(key) == cacheMap.end()){
            // 超出LRUCache存储能力，将最后的存放地址删除
            if (cacheList.size() == capacity){
                cacheMap.erase(cacheList.back().key);
                cacheList.pop_back();
            }
            cacheList.push_front(CacheNode(key, value));
            cacheMap[key] = cacheList.begin();
        }
        else{
            // 更新各节点的地址值
            cacheMap[key]->value = value;
            cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
            cacheMap[key] = cacheList.begin();
        }
    }
};