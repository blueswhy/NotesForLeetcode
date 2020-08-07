// 列举常见的排序算法
#include<algorithm>
#include<stdio.h>
#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;


struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){ }
};

class Solution_sortMethod{
    public:
    // Merged Sorted Array
    // 归并排序基础， 合并两个有序序列， 在第二章链表有类似算法
    // 合并结果到A中
    // 时间复杂度O(m + n), 空间复杂度O(1)
    void merge(vector<int> &A, int m, vector<int> &B, int n){
        int ia = m - 1, ib = n - 1, icur = m + n - 1;
        while(ia >= 0 && ib >= 0){
            A[icur--] = A[ia] >= B[ib] ? A[ia--] : B[ib--];
        }
        while(ib >= 0){
            A[icur--] = B[ib--];
        }
    }
    // 对于有序链表进行Merge操作，链表是无法进行随机存取的
    // 时间复杂度O(n1 + n2)， 空间复杂度 O(1)
    ListNode *mergeTwoSortedLists(ListNode *list1, ListNode *list2){
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        ListNode dummy(-1);                      // 头结点
        ListNode *p = &dummy;
        for (; list1 != nullptr && list2 !=nullptr; p = p->next){
            if (list1->val > list2->val){
                p->next = list2;
                list2 = list2->next;
            }
            else{
                p->next = list1;
                list1 = list1->next;
            }
        }
        p->next = list1 != nullptr ? list1 : list2;
        return dummy.next;
    }

    // Merged K Sorted Lists
    ListNode *mergeKLists(vector<ListNode *> &lists){
        if (lists.size() == 0) return nullptr;
        ListNode *p = lists[0];
        for (int i = 1; i < lists.size(); i++){
            p = mergeTwoSortedLists(p, lists[i]);
        }
        return p;
    }
    // Insertion Sort List
    // 时间复杂度O(n*n), 空间复杂度O(1)
    ListNode *insertionSortList(ListNode *head){
        ListNode dummy(INT_MIN);
        for (ListNode *cur = head; cur != nullptr;){
            auto pos = findInsertPos(&dummy, cur->val);
            ListNode *tmp = cur->next;                    // 逐次进行排序
            cur->next = pos->next;
            pos->next = cur;
            cur = tmp;
        }
        return dummy.next;
    }

    // 归并排序， 适用于单向链表
    // 如果是双向链表, 可以使用快排
    // 时间复杂度O(nlog n)， 空间复杂度O(1)
    ListNode *sortListUsingMerge(ListNode *head){
        if (head == nullptr || head->next == nullptr) return head;

        ListNode *fast = head, *slow = head;
        while (fast->next !=NULL && fast->next->next != NULL){
            fast = fast->next->next;
            slow = slow->next;       // 结束后slow指向中间节点
        }
        // 断开
        fast = slow;
        slow = slow->next;
        fast->next = NULL;

        ListNode *l1 = sortListUsingMerge(head);
        ListNode *l2 = sortListUsingMerge(slow);
        return mergeTwoSortedLists(l1, l2);
    }
    // First Missing Positive
    // 桶排序找出第一个缺少的连续正整数
    // 每当A[i] != i + 1时，将A[i]和 A[A[i] - 1]交换， 直到无法交换为止

    int firstMissingPositive(vector<int> &nums){
        bucketSort(nums);
        for (int i = 0; i < nums.size(); i++){
            if (nums[i] != (i + 1)){
                return i + 1;
            }
            return nums.size() + 1;
        }
    }

    // sort colors
    // 荷兰国旗问题， 有红白蓝三种颜色的球， 算法目标是将这三种求按颜色顺序正确地排列
    // 三向切分快排的一种变种，将数组分为三个区间：等于红色，等于白色，等于蓝色
    // 颜色对应于0，1，2

    // count数组方法，时间复杂度O(n), 空间复杂度O(1)
    void sortColorsUsingCount (vector<int> &A){
        int counts[3] = {0};
        for (int i = 0; i <= A.size(); i++){
            counts[A[i]]++;
        }
        for (int i = 0, idx = 0; i < 3; i++){
            for (int j = 0; j < counts[i]; j++){
                A[idx++] = i;
            }
        }
    }

    // 双指针方法， 时间复杂度O(n), 空间复杂度O(1)
    void sortColorsUsingTwoPointers(vector<int> &A){
        int red = 0, blue = A.size() - 1;

        for (int i = 0; i < blue + 1; ){
            if (A[i] == 0){
                swap(A[i++], A[red++]);
            }
            else if (A[i] == 2){
                swap(A[i], A[blue--]);
            }
            else{
                i++;
            }
        }
    }

    // 快排设置partition的方法
    void sortColorsUsingQuickSort(vector<int> &nums){
        partition(partition(nums.begin(), nums.end(), bind1st(equal_to<int>(), 0)), \
                nums.end(), bind1st(equal_to<int>(), 1));
    }
    // Top K Frequent Elements
    // 这里的K个数，本算法按照数字个数来进行
    // 如果强调前K个频率，将前K个桶都加入即可。
    vector<int> getTopKFrequent(const vector<int> &nums, int k){
        if (k <= 0) return vector<int>{0};
        const int size = nums.size();
        unordered_map<int, int> count;
        for (auto iElem = nums.begin(); iElem != nums.end(); iElem++){
            count[*iElem]++;                       // 统计频率
        }
        vector<int> bucket[size + 1];            // 设置桶，下标表示数字频率，0次-size+1次
        for (const auto &cMem:count){
            bucket[cMem.second].push_back(cMem.first);
        }

        vector<int> ret;
        
        for (int i = size, pushNum = 0; i >= 0; i--){
            if (!bucket[i].empty()){
                for (auto iElem = bucket[i].begin(); \
                    iElem != bucket[i].end(); iElem++){
                    ret.push_back(*iElem);
                    pushNum++;
                    if (pushNum == k) break;
                }
            }
            if (pushNum == k) break;
        }
        
        return ret;

    }
    private:
    ListNode *findInsertPos (ListNode *head, int x){
        ListNode *pre = nullptr;
        for (ListNode *cur = head; cur != nullptr && \
            cur->val <= x; cur = cur->next, pre = cur)
            ;
        return pre;
    }

    // 按照桶排序 3, 4,-1, 1 --> 1, -1, 3, 4
    static void bucketSort (vector<int> A){
        const int n = A.size();
        for (int i = 0; i < n; i++){
            while (A[i] != i + 1){
                if (A[i] <= 0 || A[i] > n || A[i] == A[A[i] - 1]){
                    break;   // 无法实现交换或者交换终止
                }
                swap(A[i], A[A[i] - 1]);
            }
        }
    }
    // 桶排序[l, h]区间, 这里映射到[0, 1)区间，区间映射可以在求桶编号的时候考虑
    // 空间换时间
    void bucketSortForFloat(float A[], int left, int right){
        const int size = right - left + 1;
        vector<float> bucket[size];            // 有size个数据，即分配size个桶
        for (int i = left; i <= right; i++){
            int bi = size*A[i];              // 向下取整
            bucket[bi].push_back(A[i]);
        }
        for (int i = 0; i<size; i++){
            sort(bucket[i].begin(), bucket[i].end());     // 桶内排序用快排
        }
        int idx = left;
        // 遍历桶
        for (int i = 0; i < size; i++){
            for (int j = 0; j<bucket[i].size(); j++){
                A[idx++] = bucket[i][j];
            }
        }
    }
    
    // 快排的思想
    // 一般用数组的第一个数作为key/partition, 将数组分为两部分, 大于该key的放在其右边， 小于的放在其左边
    // 分块方法是使用边里交换的方法， 两边夹逼， 直到两个指针相等
    // 可以直接借助该partition算法找到数组中第k大的数字
    void quickSort(int arr[], int low, int high){
        if (high <= low) return;
        int i = low, j = high + 1, key = arr[low];
        while(true){
            while (arr[++i] < key){
                if (i == high){
                    break;
                }
            }
            while (arr[--j] > key){
                if (j == low){
                    break;
                }
            }
            if (i >= j) break; // 结束条件
            swap(arr[i], arr[j]);
        }
        swap(arr[low], arr[j]);  // j可能越界到i处， 因此j指向元素一定小于key=arr[low]

        quickSort(arr, low, j - 1);
        quickSort(arr, j + 1, high);
    }
};      