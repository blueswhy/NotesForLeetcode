## Read Me For Leetcode

记录每一章代码的小结。在部分参考文献中，举证了一些复杂度较大的算法来进行比较，阐述算法改进的过程和基本算法思想。在算法章节，对于复杂度较高的穷搜算法，本文及代码部分不作列举。

* 本文及代码部分都是对于Leetcode上经典文章的总结，代码部分也是直接移用文章代码。
* 代码分章节处理，每一章的代码放在一个头文件中。根据功能，分在不同的solution类下。搜索指定题目按照本目录搜章节指定位置。
* 在对应cpp文件中简单验证了头文件中的部分代码。

### 基本数据结构

#### 第二章 线性表

使用线性数据结构进行增删改等编辑操作和排序功能，当需要排序实现数据查找时，借助C++中的unordered_map或者unordered_set实现hash查找。

##### 数组

* 基础题目：移除重复项，循环排序数组，remove Element(In Place)，Rotate Image，Plus One，Climbing Stairs，Set Matrix Zeros，Candy
* 位运算：Single Number I&II，
* 经典题目：双数组k-th元素，Longest Consecutive Sequence，Two-Sum（3-Sum, k-Sum)，**next-permuation**，Gray Code，Gas Station
* 进阶题目：康托编码，Valid Sudoku，Trapping Rain Water

##### 单链表

很多题目要求In place，使用了很多小技巧。

* 基础题目：Add Two Numbers，Partition List，Remove Duplicates from sorted List I & II，Swap Nodes In pairs，In色rsection of Two Linked Lists
* 进阶题目：Reverse Nodes in K Group，DeepCopy，Reorder List，
* 技巧题目：Reverse Linked List II，Rotate List，Remove Nth Node from End of List，Linked List Cycle I&II，**LRU Cache**.

#### 第三章 字符串

本部分不讨论使用regex和regex_match等正则表达式实现字符串的比较和匹配。

* 基础题目：isPalindrome，String to Integer，Add Binary，Longest Common Prefix，Count and Say，anagrams，Simplify Path，Length of  Last Word.
* 经典题目：KMP，Longest Palindmic Subarray，Integer to Roman.
* 进阶题目：Wildcard Matching，Valid Number.

#### 第四章 栈与队列

在后续的DFS和BFS中，可以看出来FIFO的队列用于广度遍历（层级遍历）中，而FILO的栈用于需要到达叶子节点的深度遍历中。这部分的具体题目也可以放到后续讲。

* 栈：Valid Parenthese，Longest Valid Parenthese ,Largest Rectangle in Histogram，Evaluate Reverse Polish Notation。

#### 第五章 树

本部分仅仅考虑二叉树，依次为遍历、构建、BST，递归。

* 二叉树的遍历：Preorder，Inorder，Postorder(这三种基本遍历提供Morris遍历方式，使用Inplace遍历一棵树)；LevelOrder，Zigzag Level Order，Recover BST，Sysmmetric Tree，Balanced Binary Tree，Flatten Binary Tree to Linked List，Populating Next Right Poointers in Each Node II.
* 二叉树的构建： Preorder and Inorder，Inorder and Postorder.
* 二叉查找树：Unique BST I&II，Validate BST，Convert Sorted Array to BST，Convert Sorted List to BST.
* 二叉树的递归：Minumum/Maximum Depth of Binary Tree，Path Sum I&II，Binary Tree Max PathSum，Populating Next Right Pointer in Each Node，Sum root to leaf Numbers.

#### 第十四章 图

介绍两种图的结构，一种按照指针扩展，指针可以代表一个连通图。另外一种，按照顶点个数，边连接关系来表示图的邻接关系，实际上指代的是稀疏邻接矩阵。

* 基本问题：Clone Graph（涉及到图数据结构，和图的两种遍历方式）。
* 经典问题：二分图，拓扑排序、并查集(这里的图都用邻接数组来表示)。

### 常用搜索算法

#### 第六章 排序

**快排**

用于求解kth Element问题。一般用数组的第一个数，作为key/partition，大于该key的放在右边，小于该key的放在左边。时间复杂度O(NlogN)，空间复杂度O(1)。

**堆排序**

堆排序是选择排序的一种，属于不稳定排序。直接用于排序时间复杂度为O(nlogn)，空间复杂度为O(1)。

堆的数据结构一般建立在**完全二叉树**上，如果每个父节点的值都大于或者等于其左右孩子节点的值，称为大顶堆；如果每个父节点的值都小于等于其左右孩子节点的值，称为小顶堆。如果将堆的二叉树结构写成一个数组，按照广度优先遍历原则进行排列，即同一层的节点放在前面。

堆排序的**基本思想**——将排序序列构造成一个大顶堆（升序使用大顶堆，降序使用小顶堆），则序列的最大值为堆顶的根节点。将其与末尾元素交换，然后将剩余n-1个元素重新构造为一个堆，这样就依次得到n个元素的次小值。最终得到一个有序序列。具体步骤如下：

* S1: 构建初始堆。将无序数组按层级二叉树划分，从最后一个非叶子节点（A.size()/2 - 1）开始进行堆排序调整。注意，按二叉树level遍历，一个父节点i的子节点下标一定是（2\*i和2\*i + 1)。交换过程中，先保证上层顶堆最大，在顶堆元素交换后，再自上而下保证子树也满足最大堆排序。
* S2: 将堆顶元素和末尾元素交换，最大元素沉底。
* S3: 去掉最大元素调整子树范围，重新调整堆，反复执行调整和交换，直到范围中仅仅包含三个元素，此时直接调整即可。

**桶排序**

假设数据在[min, max]之间均匀分布，将区间分为n等分，这n个区间便被称作n个桶。将数据加入对应的桶中，由于桶之间有大小关系，可以按桶的顺序将桶中排好的数字依次输出。平均时间复杂度O(n)，空间复杂度O(n*m)(不过使用vector来自动分配，可以减少很多不必要空间的使用）。

**题目**

* 基础：Merge Sorted Array/Linked Lists，Insertion Sort List，First Missing Positive.
* 经典：归并排序链表，荷兰国旗问题，Top K Frequent Elements，QuickSort.

#### 第七章 二分查找

* 基础题目： Search Range In Sorted Array, Search Insert Position
* 进阶题目： Search Target In Matrix

#### 第八章 穷举

#### 第九章 BFS

* ”词语接龙“和围棋类这两个问题，阐述了使用广度优先遍历建立模型进行最短路径长度求解和最短路径搜索的算法过程。
* 模型转化：perfect squares.

##### :point_right:适用场景

* **输入数据**: 无需特征。
* **状态转换图**: 树或者DAG图（Directed Acyclic Graph)--无权图。
* **输出**: 最短路径及相关参数。

##### :point_right:**算法思想**

* 如果是求**最短路径长度**，使用单队列时，状态量里有路径长度。使用双队列时，使用一个全局变量记录当前层数；
* 如果需要列举最短路径或者动作序列，使用一棵树来存储BFS过程中的路径。

##### :point_right:**状态量**

需要存储必要的数据，使得完整提供扩展到下一状态的所有信息。找准相邻层数之间转换的状态联系量。扩展状态，一般使用双向队列，利用其FIFO的特性，在同一层的节点遍历完毕后，才开始遍历后加入的被扩展节点。

##### :point_right:**Visited**

* 如果是一棵树，则无需判重，因为不会出现回路，但是如果是一个DAG，则需要判重。
* 如果是求最短路径长度，只需要让状态节点不重复出现即可，因此遍历过直接放入visited数组保证不出现回路即可。
* 如果列举所有最短路径，在DAG中，允许两个父节点指向同一个子节点，因此实现时，要“延迟”节点加入到visited集合的时间，等同一层全部访问结束，再将该层节点全部加入到visited数组中。

##### :point_right:**模板**

BFS需要一个队列用来扩展，一个hashset用于判重，一棵树用于存储整棵树。

* 队列可以使用单队列或者双队列形式。单队列需要定义包含level的状态结构体；
* hashset，如果有完美哈希方案，则用布尔数组来表示，如果没有直接用STL中的set或者unorder_set。
* 存储树，如果用STL可以用unordered_map<state_t, state_t>father来表示为一棵树。如果能预估状态总数的上限，则可以用数组即树的双亲表示法来表示，效率更高也需要更多细节实现代码。

#### 第十章 DFS

##### :point_right:题目简介

* 基础穷搜题目：Word Search，Generate Parenthese.
* 进阶剪枝题目：Palindrome Partition, Unique Path,  Restore IP Addr, Combination Sum，Pacific Atlantic Water，
* 经典题目： Sodoku Solver， N-Queens.

##### :point_right:**适用场景**

* **输入数据**：递归数据结构（单链表、二叉树、集合）最适用。
* **状态转换图**：树或者图。
* **求解目标**：必须走到最深（以树为例，必须走到叶子节点）才能得到一个解时，适合用深搜。

##### :point_right:建模要点

深搜有三类经典问题：可行解的总数，求一个可行解，求所有可行解。

* 后两类问题需要路径存储，但是DFS在搜索过程中始终只有一条路径，因此用一个数组就足够存储了。
* 深搜的状态变量，是通过添加函数参数或者设置全局变量的方式记录状态变化。在扩展状态的时候，如果是显示的二叉树或图等，直接根据题意向叶子节点合理（剪枝）推进即可。如果是隐式图，需要想清楚状态相关的变量。
* 终止条件：一般深搜都是靠递归函数，利用函数栈实现到叶子节点返回。
* 收敛条件：找到一个合法解的时刻。由于深搜是到叶子节点才能得到解，因此很多题目中终止条件和收敛条件合二为一。但这两者不完全相同。在正向搜索（尾递归）时，指的是是否达到目标状态；在逆向搜索中，处理父状态时需要提前知道子状态的情况，递归语句不在最后。
* 加速方法有两种剪枝和缓存。剪枝即在未到达叶子节点时，通过题目设置的约束条件直接return空值或者设置continue，跳过该错误路径；缓存则需要状态转换图是DAG，存在重叠子问题的情况下，使用数组或者Hashmap进行加速（实际上相当于用空间换取时间，可参考Unique Path II的备忘录法）：

##### :point_right:深搜&回溯&递归

* 回溯法=深搜+剪枝。
* 备忘录=深搜+缓存，Memorization。当可以使用记忆化搜索方法时，也一定可以使用动态规划，在不使用程序栈的情况下实现所有情况的遍历。
* 为了代码的简洁性，使用递归的方式来实现深搜。深搜是逻辑意义上的算法，需要借助栈的方式来扩展，递归恰恰提供了这种函数栈，递归是一种物理意义上的实现，和迭代是对应的。**但是深搜不一定用递归，但递归一定是深搜。**

### 常用算法思想

#### 第十一章 分治法

分治法的基本思想是以空间来换取时间，相当于将总任务并行化为若干个子任务，前提是这个总任务是可并行化，各任务之间不满足串行逻辑。

* 经典问题：二分法解决pow(x, n)和sqrt(x)
* 技巧问题：Different Ways tp Add Parentheses

#### 第十二章 贪心法

当单个子问题可以决定父问题时，可以使用贪心法。动态规划中，单个子问题达到影响父问题的地步即可，不需要决定父问题。，保证每次操作都是局部最优的，并且最后得到的结果是全局最优的。

* 基础问题：木板选择、股票交易。
* 技巧问题：Jump Game I&II、最长子字符串问题，Non-overlapping Intervals，Partition Labels.

#### 第十三章 动态规划

递归和动态规划都将原问题拆分成若干子问题然后求解，但**动态规划保存了子问题的解，避免重复计算**。动态规划首先要找到状态方程，然后根据状态方程设置全局状态数组，建立状态转移关系。而且对于二维遍历不需要找解对应路径情况而言，可以利用前后之间的关系，将二维状态数组转换为一维滚动数组，降低空间复杂度。如果涉及到路径的遍历，使用DFS相关算法即可。

* 基础问题：Triangle, Maximum Subarray, Palindrome Partitioning II， Word Break.
* 滚动数组：Interleaving  String，Minimum Path Sum,  Edit Distance, 0-1背包.
* 技巧题目：Best Time to Buy and Sell Stock III, Decode Ways.
* 三维动规：Scramble String.
* 路径遍历：Word Break II.

#### 数学知识

**素数**

* 每一个整数都可以分解为素数的乘积，质因子分解。
* 整除： $x = 2^{m_0} * 3^{m_1} * 5^{m_2} *\dotsb$ , $y = 2^{n_0} * 3^{n_1} * 5^{n_2} * \dotsb , if \space y \bmod x = 0,$ , $then \space \forall i, m_i \leq n_i.$
* $\gcd(x, y) = 2^{\min(m_0, n_0)}*3^{\min(m_1, n_1)}*5^{\min(m_2, n_2)}*\dotsb$, $lcm(x, y) = 2^{\max(m_0, n_0)}*3^{\max(m_1, n_1)}*5^{\max(m_2, n_2)}*\dotsb$.

**进制转换**

和十进制类似，使用整除和余数这两种运算即可得到各位。

**阶乘**$N!$

* 统计阶乘中尾部0的个数——统计阶乘序列中5的个数即可：$\sum_{i = 1}^\infty N/5^i$。如果是统计其中最低位1的位置，等效于统计有多少个2，$\sum_{i = 1}^\infty N/2^i$.

**字符串加减法**

和进制类似，从低位开始，记住设置进位变量carry，然后根据进制进行加减即可，遇到乘除问题也可以以十进制来推广。

**多数投票问题**

如果能保证数组中存在数目超过n/2的元素时，先排序，然后找到最中间的数即可。

* Boyer-Moore Majority Vote Algorithm，时间复杂度O(N)，空间复杂度O(1)。基本思想为：要查找的元素个数一定比剩下的元素个数都多。首先设置初值为头元素，然后使用一个cnt变量进行计数，如果找到相等元素，cnt++，否则cnt--。等到cnt = 0，将当前元素赋值给目标元素，最终得到goal。为了保证主元素的存在性，第二次轮询数组，找出goal的个数，如果确实大于n/2，则证明找到，否则不存在这种元素。
* 将n/2改成n/3时，思路也是如此。记录两个值，依次轮询，找到两个数num1和num2，对应两个计数变量cnt1和cnt2。

**位运算**

* 0s表示一串0，1s表示一串1，因此可以以此结合位运算符进行相应运算。$x^{0s} = x,x^{1s} = \tilde x, x^x = 0, x \& 0s = 0, x\|1s = x$
* 利用异或运算可以去除数组中出现偶数次的数。
* 利用位与运算可以实现掩码操作，取对应位的码。
* $n\&{n-1}$表示去除n的二进制表示中最低的非零位。
* $n\&-n$表示n的二级制表示中最低的那一位，$-n \rightarrow \tilde n + 1$，和上述结果相同。
* \>>表示算术右移，相当于除法，\<<表示算术左移，相当于乘法。

### 细节实现题目

**Trie**树

* 又称为单词查找树或者键树，是哈希树的一种变种。一般用于统计和大量字符串的排序。优点是，最大限度减少无谓字符串的比较，查询效率高于哈希表。缺点是内存消耗非常大，内存的优化在建树的过程中。
* 核心思想是空间换取时间，利用字符串的公共前缀来降低查询时间的开销从而达到提高效率的目的。
* 和BST不同的是，trie树中，每个节点并不是存储一个元素，而是将要查找的关键词看作一个字符序列，根据构成关键词字符的先后顺序构造用于检索的树结构。字符存储在每条边中。
* trie树中每一层的节点数是$26^{level}$级别的，为了节省空间，用动态链表或者数组来模拟，空间使用控制在单词数*单词长度以内。
* 建立和查询操作在trie树中，是可以同时进行的。
* 热门应用和相关题目：字符串检索、词频统计，字符串的最长公共前缀（LCA和RMQ)，字典排序。

**Reverse Integer**

十进制整数的逆序输出，需要考虑负数的情况和溢出($2^{31}-1$)。

**Palindrome Number**

在in place的要求下判断整数是否是一个回文序列。

**Insert Interval**

给出若干非重叠区间，插入一个新区间使得数字范围加入后，得到的区间仍然满足非重叠约束。如果不能直接插入，即进行相应的区间合并。

可以用本题合并的思路用于Merge Interval中，直接遍历每一个子区间插入到原区间数组中即可。

**Multiply Strings**

高精度乘法。将字符转化为一个int，形成一个int数组。最后用string作为输出。相应地，也高精度除法。

**Substring with Concatenation of All Words**

给出一个字符数组和一个字符串，找出这个字符串中所有可能的组合在字符串中的位置。组合出来的词语必须是连续的。为了方便，所有字符数组的长度是相同的。

**Pascal's Triangle I & II**

生成给定行数的Pascal三角二维数组。Pascal数组可以认为是二项式系数组合。

**Spiral Matrix I & II**

返回一个矩阵按照螺旋形遍历的结果。设置四个边角量作为每次沿着外围螺旋遍历的界限，随着每次一次环的遍历结束都会带来界限的收缩。当收缩到界限越界时，跳出循环，返回结果。

**ZigZag Conversion**

介绍一种利用变长数组对字符串存储变形，然后改变读取顺序，实现字符串的Zigzag编码。设$(i,j)$对应Zigzag矩阵中的元素坐标，则每一层垂直元素的坐标$(i, j)\rightarrow(j+1)/ n \times2(n-1) + i$, 而斜线元素坐标$(i, j)\rightarrow[(j+1)/ n+1] \times2(n-1) - i$.

**Text Justification**

格式化输出。给出一个词语字符串数组，要求按顺序输出字符串，词语之间至少有一个空格。每一行输出的字符串的长度要等于L，不足的使用空格补全，首词语左对齐。

**MaxPoints on a Line**

给定一组2D平面的一组点，然后给出共线的点的最多的个数。经典算法是Hough变换。将2D坐标点映射到$(\rho,\theta)$坐标中，$\rho$表示原点到直线的距离，$\theta$表示相应垂线段与x轴之间的夹角。只有对应的$(\rho,\theta)$相同，这些点才在同一条直线上。

本题中不考虑过多的点，直接按斜率划线暴力枚举，按点来扩展n-1条线，记录其余点在这条线上的个数，然后找到最多的那条线。

### 代码书写规范

### 参考文献

* LeetCode题解，灵魂机器 (soulmachine@gmail.com)，  https://github.com/soulmachine/leetcode 

* Leetcode题解，https://github.com/CyC2018/CS-Notes 
* huihut，https://github.com/huihut/interview

