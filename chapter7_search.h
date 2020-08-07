#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

class Solution_search{
    public:
    // 在一个有序序列中查找一个数，返回其范围下标
    // 使用二分法即可， O(logn) 空间复杂度O(1)
    vector<int> searchRangeUsingSTL(vector<int> &nums, int target){
        // 使用lower_bound和upper_bound函数来实现对target的二分查找
        // lower返回数值第一个出现的位置
        // upper返回第一个大于待查找数值出现的位置
        const int l = distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
        const int u = distance(nums.begin(), prev(upper_bound(nums.begin(), nums.end(), target)));
        if (nums[l] != target){
            return vector<int> {-1, -1};
        }
        else{
            return vector<int> {l, u};
        }
    }

    // Search Insert Position
    // 对于一个有序序列，找一个target。找到了，则返回位置，没有找到，则返回可以插入的位置
    // 实际上就是lower_bound
    int searchInsert(vector<int> &nums, int target){
        return distance(nums.begin(), lower_bound(nums.begin(), nums.end(), target));
    }

    // 搜索一个2D矩阵
    // 在C++中，矩阵实际上指的是多维数组。因此，其矩阵元素地址中是按行存储的。

    // 在一个有序化2D矩阵中，进行二分搜索。
    // 有序2D矩阵，即将2D矩阵向量化后是一个有序数组。
    bool searchMatrix(const vector<vector<int>> &mat, int target){
        if (mat.empty()) return false;
        const size_t m = mat.size();    // m行
        const size_t n  = mat.front().size(); // n列
        int first = 0;
        int last = m * n;
        while (first < last){
            int mid = first + (last - first)/2;
            int value = mat[mid/n][mid%n];
            if (value == target){
                return true;
            }
            else if (value < target){
                first = mid + 1;
            }
            else{
                last = mid;
            }
        }
        return false;
    }

    private:
    // 如果要求自己实现lower和upper函数
    template<typename ForwardIterator, typename T>
    ForwardIterator lower_bound(ForwardIterator first, ForwardIterator \
            last, T target){
        while(first != last){
            auto mid = next(first, distance(first, last)/2);
            if(target > *mid){
                first = ++mid;
            }
            else if(target < *mid){
                last = mid;
            }
            else{
                first = mid;
                break;
            }
        }
        return first;
    }
    template<typename ForwardIterator, typename T>
    ForwardIterator upper_bound(ForwardIterator first, ForwardIterator \
            last, T target){
        while(first != last){
            auto mid = next(first, distance(first, last)/2);
            if(target >= *mid){
                first = ++mid;     // 此处不同
            }
            else if(target < *mid){
                last = mid;
            }
        }
        return first;
    }
};