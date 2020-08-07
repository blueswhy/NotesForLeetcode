// 二叉树
// 分为遍历，构建，查找，递归四部分

#include<stdio.h>
#include<algorithm>
#include<iostream>
#include<vector>
#include<iterator>
#include<stack>
#include<queue>
#include<functional>


using namespace std;

// 树节点的定义
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr){ }
};
struct TreeLinkNode{
    int val;
    TreeLinkNode *left;
    TreeLinkNode *right;
    TreeLinkNode *next;
    TreeLinkNode(int x): val(x), left(nullptr), right(nullptr), next(nullptr){ }
};

struct ListNode{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr){ }
};

// 二叉树的遍历，可以分为先序遍历、后序遍历和中序遍历
// 遍历可以借助栈或者递归的方法， 但是此时使用的空间不由个人控制, 空间复杂度正比于树节点的个数
// 如果要达到常数空间复杂度, 直接在原树上进行处理, Morris遍历
class Solution_treeTraversing{
    public:
    // 借助栈的方式实现先序遍历 root-left-right
    vector<int> preorderTraversalUsingStack(TreeNode *root){
        vector<int> ret;                // 存放节点值，用以输出
        stack<const TreeNode *> s;      // 用来存放树节点，以规定root-left-right的遍历顺序
        if (root != nullptr) s.push(root);
        while (!s.empty()){
            const TreeNode *p = s.top();
            s.pop();
            ret.push_back(p->val);
            if (!p->right) s.push(p->right);
            if (!p->left) s.push(p->left);
        }
        return ret;
    }
    // 使用Morris遍历方式, 记录每次的根节点
    vector<int> preorderTraveralUsingMorris (TreeNode *root){
        vector <int> ret;
        TreeNode *cur = root, *prev = nullptr;

        while (cur != nullptr){
            if (cur->left == nullptr){
                ret.push_back(cur->val);
                prev = cur;
                cur = cur->right;      // 建立线索后可以直接
            }
            else
            {
                // 寻找前驱， 即找到最终结束的位置, 从而返回
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur){
                    node = node->right;
                }
                // 逐步建立线索, 相当于遍历链表化
                if (node->right == nullptr){
                    ret.push_back(cur->val);  // 这部分关乎输出的顺序
                    node->right = cur;
                    prev = cur;
                    cur = cur->left;
                }
                else {
                    node->right = nullptr;  // 已经线索化， 则删除线索
                    cur = cur->right;
                }
            }
            
        }
        return ret;
    }

    // 实现中序遍历: left-root-right
    vector <int> inorderTraversalUsingStack (TreeNode *root){
        vector <int> ret;
        stack <const TreeNode *> s;
        const TreeNode *p = root;
        while (!s.empty() ||p != nullptr){
            if (p != nullptr) {
                s.push(p);
                p = p->left;
            }
            else
            {
                p = s.top();
                s.pop();
                ret.push_back(p->val);
                p = p->right;
            }
            
        }
        return ret;
    }

    vector <int> inorderTraversalUsingMorris(TreeNode *root){
        vector <int> ret;
        TreeNode *cur = root, *prev = nullptr;
        while (cur != nullptr){
            if (cur->left == nullptr){
                ret.push_back(cur->val);
                prev = cur;
                cur = cur->right;
            }
            else{
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur){
                    node = node->right;
                }
                if (node->right == nullptr){
                    node->right = cur;
                    cur = cur->left;
                }
                else
                {
                    ret.push_back(cur->val);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            }
        }
        return ret;
    }
    // 后序遍历 left-right-root
    vector <int> postorderTraversalUsingStack(TreeNode *root){
        vector<int> ret;
        stack<const TreeNode *>s;
        const TreeNode *p = root, *q = nullptr; // 分别指向正在访问的节点和刚刚访问的节点
        do{
            // 先顺着左边这条线push其节点
            while (p != nullptr){
                s.push(p);
                p = p->left;            
            }
            q = nullptr;
            while (!s.empty()){
                p = s.top();
                s.pop();
                // 右节点不存在或者已经被访问， 则访问
                if (p ->right == q){
                    ret.push_back(p->val);
                    q = p;
                }
                else{
                    s.push(p);
                    // 当前节点右节点序列未被完全访问, 二次进栈
                    p = p->right;
                    break;
                }
            }
        } while(!s.empty());
        return ret;
    }

    // 使用Morris实现后序遍历, 不过验证过程中有一定问题
    vector<int> postorderTraversalUsingMorris(TreeNode *root){
        vector<int> ret;
        TreeNode dummy(-1);
        TreeNode *cur, *prev = nullptr;
        // 函数模板化， 需要调用functional头文件
        std::function <void (const TreeNode *)> visit = \
        [&ret] (const TreeNode *node){
            ret.push_back(node->val);
        };

        dummy.left = root;
        cur = &dummy;
        while (cur != nullptr){
            if (cur->left == nullptr){
                prev = cur;
                cur = cur->right;
            }
            else
            {
                TreeNode *node = cur->left;
                while (node->right != nullptr && node->right != cur){
                    node = node->right;
                }
                if (node->right == nullptr){
                    node->right = cur;
                    prev = cur;
                    cur = cur->left;
                }
                else
                {
                    visit_reversePath(cur->left, prev, visit);
                    prev->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
                
            }
            return ret;
            
        }
    }
    // Level Order Travelsal
    // 广度优先遍历， 先将离root近的节点遍历完毕，再遍历其余的
    // 设置一个队列，进行FIFO即可
    // 时间复杂度为O(n), 空间复杂度为O(n)
    vector<vector<int>> levelOrderUsingRecursion(TreeNode *root){
        vector<vector<int>> ret;
        levelOrderTraversal(root, 1, ret);
        return ret;
    }

    vector<vector<int>> levelOrderUsingIteration(TreeNode *root){
        vector<vector<int>> ret;
        queue<TreeNode *> current, next;  // 符合先进新出规则
        if (root == nullptr){
            return ret;
        }
        else{
            current.push(root);
        }

        while (!current.empty()){
            vector <int> curLevel;
            while (!current.empty()){
                TreeNode *node = current.front();
                current.pop();
                curLevel.push_back(node->val);
                if (node->left != nullptr) next.push(node->left);
                if (node->right != nullptr) next.push(node->right);
            }
            ret.push_back(curLevel);
            swap(next, current);
        }
        // reverse(ret.begin(), ret.end());   // 如果是层数越大的在上面， 用个reverse即可
        return ret;
    }
    // 广度优先遍历
    // 二叉树Zigzag层序遍历，使用一个bool数组记录左右顺序，每一层结束即翻转
    vector<vector<int>> zigzagLevelOrderUsingIteration(TreeNode *root){
        vector<vector<int>> ret;
        queue<TreeNode*> current, next;
        bool left_to_right = true;

        if (root == nullptr){
            return ret;
        }
        else{
            current.push(root);
        }
        while (!current.empty()){
            vector<int> curLevel;
            while (!current.empty()){
                TreeNode *node = current.front();
                current.pop();
                curLevel.push_back(node->val);
                if (node->left != nullptr) next.push(node->left);
                if (node->right != nullptr) next.push(node->right);
            }
            if (!left_to_right) reverse(curLevel.begin(), curLevel.end());
            ret.push_back(curLevel);
            left_to_right = !left_to_right;
            swap(next, current);
        }
        return ret;
    }
    // Recover Binary Search Tree
    // 一个二叉搜索树中有两个元素错误的交换了，恢复该树, 并且不改变其原有结构
    // 使用Morris中序遍历直接在原树结构上进行寻找， 不需要用到栈, 空间复杂度为常数项
    // 时间复杂度为O(n), 空间复杂度为O(1)
    void recoverBSTreeUsingMorris(TreeNode *root){
        pair<TreeNode*, TreeNode*> broken;
        TreeNode *prev = nullptr;
        TreeNode *cur = root;
        while (cur != nullptr){
            if (cur->left == nullptr){
                detect(broken, prev, cur);
                prev = cur;
                cur = cur->right;
            }
            else
            {
                auto node = cur->left;
                while (node->right != nullptr && node->right != cur){
                    node = node->right;
                }

                if (node->right == nullptr){
                    node->right = cur;
                    cur = cur->left;
                }
                else
                {
                    detect(broken, prev, cur);
                    node->right = nullptr;
                    prev = cur;
                    cur = cur->right;
                }
            
            }
        }
        swap(broken.first->val, broken.second->val);
            
    }

    // 判断两个树是否为同一棵树
    // 可以更改为对称树判判断, 直接比较根节点处的左子树和右子树即可。
    // 时间复杂度O(n)， 空间复杂度O(log n)
    bool isSameTree(TreeNode *p, TreeNode *q){
        stack<TreeNode*> s;
        s.push(p);
        s.push(q);

        while (!s.empty()){
            p = s.top(); s.pop();
            q = s.top(); s.pop();

            if (!p && !q) continue;
            if (!p || !q) return false;
            if (p->val != q->val) return false;

            s.push(p->left);
            s.push(q->left);

            s.push(p->right);
            s.push(q->right);
        }
        return true;
    }
    // 平衡二叉树的判断, 一棵平衡二叉树左右子树的深度差距不超过1
    bool isBalanced(TreeNode *root){
        return balancedHeight (root) >= 0;
    }

    // Flatten Bianary Tree to Linked List
    // 二叉树到链表， 按相应遍历顺序构建链表即可。题目是先序遍历要求。
    // 时间复杂度O(n), 空间复杂度O(log n)
    void flattenPreorder(TreeNode *root){
        if (root == nullptr) return;

        stack<TreeNode *> s;
        s.push(root);

        while (!s.empty()){
            auto p = s.top();
            s.pop();
            if(p->right){
                s.push(p->right);
            }
            if (p->left){
                s.push(p->left);
            }

            p->left = nullptr;
            if (!s.empty()){
                p->right = s.top();
            }
        }
    }
    // Populating Next Right Pointers in Each Node
    // 将处于同一层的节点构建为一个链表
    // 时间复杂度O(n), 空间复杂度O(1)
    void connectLevelNodes(TreeLinkNode *root){
        while (root){
            TreeLinkNode *next = nullptr; // 使用next来进行层级过度
            TreeLinkNode *prev = nullptr; // 处于同一层的上一节点, 使用prev来连接同一层
            for (; root; root = root->next){
                if (!next) next = root->left ? root->left : root->right; // 只记录该层第一个非叶子节点的最左边的子节点
                if (root->left){
                    if (prev) prev->next = root->left;
                    prev = root->left;
                }
                if (root->right){
                    if(prev) prev->next = root->right;
                    prev  = root->right;
                }
            }
            root = next;     // 到达下一层
        }
    }
    
    private:
    static void reversePath(TreeNode *from, TreeNode *to){
        TreeNode *x = from, *y = from->right, *z;
        if (from == to) return;
        while (x != to){
            z = y->right;
            y->right = x;
            x = y;
            y = z;
        }
    }
    static void visit_reversePath(TreeNode *from, TreeNode *to,\
                                std::function<void(const TreeNode *)> & visit){
        TreeNode *p = to;
        reversePath(from , to);

        while(true){
            visit(p);
            if (p = from){
                break;
            }
            p = p->right;
        }

        reversePath(to, from);
    }
    
    void levelOrderTraversal(TreeNode *root, size_t level, vector<vector<int>> & ret){
        if (!root) return;
        if (level > ret.size()){
            ret.push_back(vector<int>());    // 如果输入等级大于当前等级数目, 导入一个vector列表来记录当前层节点
        }
        ret[level - 1].push_back(root->val);
        levelOrderTraversal(root->left, level + 1, ret);
        levelOrderTraversal(root->right, level + 1, ret);
    }

    // 检测pair是否broken
    void detect(pair<TreeNode *, TreeNode *> &broken, TreeNode *prev, TreeNode *cur){
        if (prev != nullptr && prev->val > cur->val){
            if (broken.first == nullptr){
                broken.first = prev;
            }
            broken.second = cur;
        }
    }

    int balancedHeight(TreeNode *root){
        if (root == nullptr) return 0;
        int left = balancedHeight(root->left);
        int right = balancedHeight(root->right);

        if (left < 0 || right < 0 || abs(left - right) > 1) return -1; // 剪枝

        return max(left, right) + 1;
    }
    
};

class Solution_treeConstructor{
    public:
    // 根据先序和中序遍历结果来构建一棵树
    // 基本思想，根据先序和中序序列来确定当前根节点，左子树区间，右子树区间
    // 然后根据递归逐次得到树。
    // 递归结束条件为，先序序列或者中序序列只有一个节点，返回nullptr。
    // 递归， 时间复杂度O(n), 空间复杂度O(log n)
    TreeNode *buildTreeUsingPreInorder(vector<int>& preorder, vector<int> &inorder){
        return buildTreeUsingPreInorder(begin(preorder), end(preorder), \
                begin(inorder), end(inorder));
    }
    template<typename InputIterator>

    TreeNode *buildTreeUsingPreInorder(InputIterator pre_first, InputIterator pre_last,\
            InputIterator in_first, InputIterator in_last){
        if (pre_first == pre_last) return nullptr;
        if (in_first == in_last) return nullptr;
        auto root = new TreeNode(*pre_first);
        auto inRootPos = find(in_first, in_last, *pre_first); // 找到当前根节点在中序遍历中的位置，分左右子树
        auto leftSize = distance(in_first, inRootPos);
        root->left = buildTreeUsingPreInorder(next(pre_first), next(pre_first, leftSize + 1), \
                in_first, next(in_first, leftSize));     // 这里的+1 , 表示左子树最后一个元素后的元素作为结束元素
        root->right = buildTreeUsingPreInorder(next(pre_first, leftSize + 1), pre_last, \
                next(inRootPos), in_last);
        return root;
    }
    // 使用后序和中序遍历结果建立二叉树
    // 后序遍历 是 左子树-右子树-根节点
    TreeNode *buildTreeUsingInPostorder(vector<int> &inorder, vector<int> &postorder){
        return buildTreeUsingInPostorder(begin(inorder), end(inorder), \
                begin(postorder), end(postorder));
    }
    template<typename BidiIt>
    TreeNode *buildTreeUsingInPostorder(BidiIt in_first, BidiIt in_last, \
            BidiIt post_first, BidiIt post_last){
        if (in_first == in_last) return nullptr;
        if (post_first == post_last) return nullptr;
        const auto val = *prev(post_last); // 注意一个容器的end指向最后一个元素后的迭代器
        TreeNode *root = new TreeNode(val);

        auto in_root_pos = find(in_first, in_last, val);
        auto left_size = distance(in_first, in_root_pos);
        auto post_left_last = next(post_first, left_size);

        root->left = buildTreeUsingInPostorder(in_first, in_root_pos, \
                post_first, post_left_last);
        root->right = buildTreeUsingInPostorder(next(in_root_pos), in_last, \
                post_left_last, prev(post_last));

        return root;
    }
};

// 二叉查找树
// 对于每一个根节点k而言，左子树里所有的元素都小于k，右子树里所有元素都大于k。
class Solution_treeBinarySearch{
    public:
    // 二叉查找树的个数：记录[1, 2, ..., n]这n个值的BST的数目
    // 考虑BST的唯一性建立原则：以i为根节点的数，其左子树序列为[1,.., i-1], 右子树为[i+1,...,n]
    // 递推公式为 f(n) = Sum_k=1~n [f(k - 1) * f(n - k)]

    // 动态规划问题
    // 时间复杂度O(n^2)， 空间复杂度O(n)
    int numTree(int n){
        vector<int> f(n + 1, 0);
        f[0] = 1;
        f[1] = 1;
        for (int i = 2; i <=n; ++i){
            for (int k = 1; k <=i; k++){
                f[i] += f[k - 1] * f[i -k];
            }
        }
        return f[n];
    }

    // 顺着上一题的思想， 列举所有记录[1, 2, ..., n]的BST
    // 基本思想即按照上述计算来递归得到所有情况
    
    vector<TreeNode *> generateBinarySearchTree(int n){
        return genBST(1, n);
    }

    // 判断一棵树是否为二叉查找树
    bool usValidBST(TreeNode *root){
        return isValidBST(root, INT_MIN, INT_MAX);
    }
    // 使用二分法将一个顺序序列，转换为平衡二叉查找树
    // 自顶向下的设计方法
    // 时间复杂度O(n), 空间复杂度O(log n)
    TreeNode *sortedArrayToBST(vector<int> &num){
        return sortedArrayToBST(num.begin(), num.end());
    }
    template<typename  RandomAccessIterator>
    TreeNode *sortedArrayToBST(RandomAccessIterator first, 
        RandomAccessIterator last){
        const auto length = distance(first, last);

        if (length <= 0) return nullptr;
        auto mid = first + length / 2;
        TreeNode *root = new TreeNode(*mid);
        root->left = sortedArrayToBST(first, mid);
        root->right = sortedArrayToBST(mid + 1, last);

        return root;
    }
    // 在上述题目作一个修改, Convert Sorted List to Binary Search Tree
    // 链表不能随机访问, 只支持顺序访问
    // 使用一种自底向上的方法， 即按先序遍历的思想, left-root-right来建立BST
    // 时间复杂度O(n), 空间复杂度O(log n)
    TreeNode *sortedListToBST(ListNode *head){
        int len = 0;
        ListNode *p = head;
        while (p){
            len++;
            p = p->next;
        }
        return sortedListToBST(head, 0, len - 1);
    }


    private:
    vector<TreeNode *> genBST(int start, int end){
        vector<TreeNode *> subTree;
        if (start > end){
            subTree.push_back(nullptr);  // 空节点, 递归终止条件
            return subTree;
        }
        for (int k = start; k <= end; k++){
            vector<TreeNode*> leftSubTree = genBST(start, k - 1);
            vector<TreeNode*> rightSubTree = genBST(k + 1, end);  // 按顺序两个依次存放
            for (auto i : leftSubTree){
                for (auto j :rightSubTree){
                    TreeNode *node = new TreeNode(k);
                    node->left = i;
                    node->right = j;
                    subTree.push_back(node);
                }
            }
        }
        return subTree;
    }

    bool isValidBST(TreeNode *root, int lower, int upper){
        if (root == nullptr) return true;
        return root->val > lower && root->val < upper\
                && isValidBST(root->left, lower, root->val)
                && isValidBST(root->right, root->val, upper);
    }

    TreeNode *sortedListToBST(ListNode *&list, int start, int end){
        // 注意这里对list的标注， 表明在函数在递归的过程中，list的位置时前进的
        if (start > end) return nullptr;    // 链表中只有两个元素时， 左节点是nullptr
        int mid = start + (end - start)/2;  // 用mid来记录list移动的距离
        TreeNode *leftChild = sortedListToBST(list, start, mid - 1);
        TreeNode *parent = new TreeNode(list->val);
        parent->left = leftChild;
        list = list->next;
        parent->right = sortedListToBST(list, mid + 1, end);
        return parent;
    }
};
// 二叉树的递归, 考察递归思维能力
class Solution_treeRecursion{
    public:
    // 找到二叉树最小的深度
    // 时间复杂度O(n), 空间复杂度O(log n)
    int minDepth(const TreeNode *root){
        return minDepth(root, false);
    }

    // 相应地，返回二叉树最大深度
    int maxDepth(TreeNode *root){
        if (root == nullptr) return 0;
        return max(maxDepth(root->left), maxDepth(root->right)) + 1;
    }

    // Path Sum
    // 判断是否有一条root-to-leaf路径使得该路径上的元素和为sum
    // 题目中没有对二叉树进行限定，只能穷举搜索
    // 时间复杂度O(n)，空间复杂度O(log n)
    bool hasPathSum(TreeNode *root, int sum){
        if (root == nullptr) return false;
        if (root->left == nullptr && root->right == nullptr)
            return sum == root->val;
        return hasPathSum(root->left, sum - root->val) \
        || hasPathSum(root->right, sum - root->val);
    }

    // Path Sum Two
    // 在上述题目的基础上，找到所有满足sum的路径
    // 时间复杂度O(n), 空间复杂度O(log n)
    vector<vector<int>> findPathSum(TreeNode *root, int sum){
        vector<vector<int>> ret;
        vector<int> cur;
        findPathSum(root, sum, cur, ret);
        return ret;
    }

    // Binary Tree Maximum Path Sum
    // 本题目中的path是树中的任意节点范围， 不再限制于root-to-leaf
    // 因此需要使用dfs方法来遍历
    int maxPathSum(TreeNode *root){
        int max_sum = INT_MIN;
        dfsFindMaxSum(root, max_sum);
        return max_sum;
    }
    // Sum root to leaf Numbers
    // 从叶子节点处为各位, 向根节点处升位, 作和
    // 根据描述即为深度优先遍历

    private:
    static int minDepth(const TreeNode *root, bool hasbrother){
        if (!root) return hasbrother ? INT_MAX : 0;
        return 1 + min(minDepth(root->left, root->right != NULL), \
                minDepth(root->right, root->left != NULL));
    }
    void findPathSum(TreeNode *root, int gap, vector<int> &cur, vector<vector<int>> &ret){
        if (root == nullptr) return;
        cur.push_back(root->val);
        // 找到叶子节点之后开始进行判断和路径存储
        if (root->left == nullptr && root->right == nullptr){
            if (gap == root->val)
                ret.push_back(cur);
        }
        findPathSum(root->left, gap - root->val, cur, ret);
        findPathSum(root->right, gap - root->val, cur, ret);
        cur.pop_back();        // 当该节点的左右路径都找到之后, 可以pop出来
    }
    int dfsFindMaxSum(const TreeNode*root, int &max_sum){
        if (root == nullptr) return 0;
        int l = dfsFindMaxSum(root->left, max_sum);
        int r = dfsFindMaxSum(root->right, max_sum);
        int sum = root->val;
        if ( l > 0) sum += l;
        if ( r > 0) sum += r;
        max_sum = max(max_sum, sum);
        return max(r, l)>0 ? max(r, l) + root->val : root->val;
    }
    // 和上面一个算法相比，本方法的空间复杂度高为O(log n)
    // 而且只适合于完全二叉树, 或者说按深度优先遍历规则生成的二叉树
    void connectLevelNodesUsingRecursion(TreeLinkNode *root, TreeLinkNode *sibling){
        if (root == nullptr){
            return;
        }
        else{
            root->next = sibling;
        }
        connectLevelNodesUsingRecursion(root->left, root->right);
        if (sibling){
            connectLevelNodesUsingRecursion(root->right, sibling->left);
        }
        else{
            connectLevelNodesUsingRecursion(root->right, nullptr);
        }
    }
};