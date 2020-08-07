#include<stdio.h>
#include<algorithm>
#include<vector>
#include<queue>
#include<stack>
#include<unordered_map>
#include<iostream>

using namespace std;

// 无向图的数据结构
struct UndirectedGraphNode{
    int label;
    vector<UndirectedGraphNode *> neighbors;
    UndirectedGraphNode(int x) : label(x){};
};

class Solution_graph{
    public:
    // Clone Graph
    // 根据给定图来复制信息
    // 可以用DFS，也可以用BFS实现
    // 时间复杂度O(n), 空间复杂度O(n)
    // DFS
    UndirectedGraphNode *cloneGraphUsingDFS(const UndirectedGraphNode *node){
        if (node == nullptr) return nullptr;
        // 字典：原始节点-被复制节点
        unordered_map <const UndirectedGraphNode *, \
                UndirectedGraphNode *> copied;
        cloneUsingDFS(node, copied);
        return copied[node];
    }
    // BFS
    UndirectedGraphNode * cloneGraphUsingBFS(const UndirectedGraphNode * node){
        if (node == nullptr) return nullptr;
        unordered_map <const UndirectedGraphNode *,
                UndirectedGraphNode *> copied;
        queue<const UndirectedGraphNode *> q;
        q.push(node);
        copied[node] = new UndirectedGraphNode(node->label);
        while (!q.empty()){
            const UndirectedGraphNode *cur = q.front();
            q.pop();
            for (auto nbr:cur->neighbors){
                if (copied.find(nbr) != copied.end()){
                    copied[cur]->neighbors.push_back(copied[nbr]);
                }
                else{
                    UndirectedGraphNode *new_node = \
                            new UndirectedGraphNode(nbr->label);
                    copied[cur]->neighbors.push_back(new_node);
                    q.push(nbr);
                }
            }
        }
        return copied[node];
    }

    // 这里的图按照邻接关系看记作有向图
    
    // 判断是否为二分图
    // 实际上是对图的集聚系数作限制，图中不能出现三元组
    bool isBipartite(vector<vector<int>> graph){
        const size_t n = graph.size();        // 记作图的节点个数
        vector<int> colors(n, -1);            // 初始化
        for (int i = 0; i < n; i++){
            if (colors[i] == -1 && !isBipartiteNode(i, 0, colors, graph)){
                return false;
            }
        }
        return true;
    }
    // 拓扑排序： 具有先序关系的任务规划中
    // 使用DFS实现拓扑排序，使用一个栈存储后序遍历结果，这个栈的逆序结果即为拓扑排序。

    // 约束关系矩阵preCourses--(CourseNum, [])课程个数， 双约束关系
    // 课程按编号代替, 比如[3, 2],[3, 1]表示学习第3门课程必须先学习1, 2这两门课程
    vector<int> getOrder(const int courseNum, vector<vector<int>> preCoureses){
        vector<vector<int>> graphic(courseNum, vector<int>(0));                      // 对应课程的约束关系
        for (auto courseRestict : preCoureses){
            graphic[courseRestict[0]].push_back(courseRestict[1]);
        }
        vector<int> postOrder;                                // 可以直接以vector变量push_back即可
        vector<bool> globalMarked(courseNum, false);
        vector<bool> localMarked(courseNum, false);

        for (int i = 0; i < courseNum; i++){
            if (hasCycle(globalMarked, localMarked, graphic, i , postOrder)){
                return vector<int>(0);
            }
        }
        
        // reverse(postOrder.begin(), postOrder.end());
        return postOrder;
        
    }
    // 并查集
    // 动态的连通两个点，快速判断两个点是否连通。
    // 只需要根据边确定前置点，如果遇到一条边中的两个点有相同的前置点，该边即为冗余边。
    // 代码就不再写了，遍历边数组即可。
    private:
    static UndirectedGraphNode* cloneUsingDFS(const UndirectedGraphNode *node, \
            unordered_map <const UndirectedGraphNode *, UndirectedGraphNode *> &copied){
        if (copied.find(node) != copied.end()) return copied[node];
        UndirectedGraphNode *new_node = new UndirectedGraphNode(node->label);
        copied[node] = new_node;
        for (auto nbr: node->neighbors){
            new_node ->neighbors.push_back(cloneUsingDFS(nbr, copied));
        }
        return new_node;
    }
    //
    bool isBipartiteNode(int curNode, int curColor, \
            vector<int> &colors, vector<vector<int>>graph){
        if (colors[curColor] != -1){
            return colors[curNode] == curColor;     // 结束判断条件，赋值后要符合条件
        }
        colors[curColor] = curColor;
        // 只有所有邻居都和自己相反，才会返回true
        for (int nextNode : graph[curNode]){
            if (!isBipartiteNode(nextNode, 1 - curColor, colors, graph)){
                return false;                       
            }
        }
        return true;
    }
    // 判断图是否有环
    bool hasCycle(vector<bool> &globalMarked, vector<bool> &localMarked, \
                vector<vector<int>> graphic, int curNode, vector<int> &postOrder){
        if (localMarked[curNode]) return true;          // 再次遇到该节点
        if (globalMarked[curNode]) return false;         

        globalMarked[curNode] = true;
        localMarked[curNode] = true;
        for (int nextNode : graphic[curNode]){
            if (hasCycle(globalMarked, localMarked, graphic, nextNode, postOrder)){
                return true;
            }
        }
        localMarked[curNode] = false;
        postOrder.push_back(curNode);
        return false;
    }
};