#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Solution_greedy{
    public:
    // Jump Game
    // 阶梯跳跃问题
    // 贪心算法，时间复杂度O(n), 空间复杂度O(1)

    bool canJumpUsingGreedy(const vector<int> &nums){
        int reach = 1;      // 最终比较的是nums.size(), 把台阶下标上移一格
        for (int i = 0; i < reach && reach < nums.size(); ++i){
            reach = max(reach, i + 1 + nums[i]); 
        }
        return reach >= nums.size();
    }

    // 动态规划解决上述问题
    // 时间复杂度O(n), 空间复杂度O(1)
    bool canJumpUsingDP(const vector<int> &nums){
        vector<int> f(nums.size(), 0);   // 走到nums[i]时剩余的最大步数
        // f[0] = 0;
        for (int i = 1; i < nums.size(); ++i){
            f[i] = max(f[i - 1], nums[i - 1]) - 1;
            if (f[i] < 0) return false;
        }
        return f[nums.size() - 1] >= 0;
    }

    // Jump Game II
    // 找到能跳到终点所用的最小转折路径
    // 时间复杂度O(n), 空间复杂度O(1)
    int jumpUsingGreedy(const vector<int> &nums){
        int step = 0;
        int left = 0;            // 用[left, right]来表示当前覆盖区间
        int right = 0; 
        if (nums.size() == 1) return 0;
        while (left <= right){
            ++step;
            const int prev_right = right;
            for (int i = left; i <= prev_right; ++i){
                int new_right = i + nums[i];
                if (new_right >= nums.size() - 1) return step;
                if (new_right > right) right = new_right;
            }
            left = prev_right + 1;
        }
        return 0;
    }

    // Best Time to Buy and Sell Stock
    // 股票抛售时机问题--一次购买一股
    // 找到价格最低和最高的一天，做到低进高出，而且低的天数在高之前
    int maxProfitOneShare(vector<int> &prices){
        if (prices.size() < 2) return 0;
        int profit = 0;
        int cur_min = prices[0];
        for (int i = 1; i < prices.size(); i++){
            profit = max(profit, prices[i] - cur_min);
            cur_min = min(cur_min, prices[i]);
        }
        return profit;
    }
    // 允许多次抛售一股, 但手中最多持有一股
    int maxProfitMoreShare(vector<int> &prices){
        int sum = 0;
        for (int i = 1; i < prices.size(); ++i){
            int diff = prices[i] - prices[i - 1];
            if (diff < 0) sum += diff;
        }
        return sum;
    }

    // Longest Substring Without Repeating Characters
    // 找到给定字符串中，无重复字符的子字符串的最大长度
    // 时间复杂度O(n), 空间复杂度O(1)
    int lengthOfLongestSubstring(string s){
        const int ASCII_MAX = 255;    // 包含所有ASCII字符
        int last[ASCII_MAX];          // 记录字符a上一次在字符串中的位置
        int start = 0;
        fill(last, last + ASCII_MAX, -1);  // 初始化
        int max_len = 0;
        for (int i = 0; i < s.size(); i++){
            if (last[s[i]] >= start){         // 遇到了两次, 不过这里的max_len只有在遇到重复字符才开始赋值
                max_len = max(i - start, max_len);
                start = last[s[i]] + 1;
            }
            last[s[i]] = i;
        }
        return max((int)s.size() - start, max_len);
    }

    // Container With Most Water
    // 木桶选择问题
    // 找到水平面上能装水最多的两块木板的位置
    int maxArea(vector<int> &height){
        int start = 0;
        int end = height.size() - 1;
        int ret = INT_MIN;
        while (start < end){
            int area = min(height[end], height[start]) * (end - start);
            ret = max(ret, area);
            if (height[start] <= height[end]){
                start++;                          // 保留当前最高的木板
            }
            else {
                end--;
            }
        }
        return ret;
    }
    // Non-overlapping Intervals
    // 不重叠的区间个数
    // 改动一下可以解决刺破气球类问题
    // 首先根据区间末尾对区间数组进行排序, 然后根据区间末尾元素判断重叠区间的个数
    static bool cmpInterval(pair<int, int> interval1, pair<int, int> interval2){
        return interval1.second < interval2.second;
    }
    int getOverlapIntervalNums(const vector<pair<int, int>> &intervals){
        int count = 1;                  // 区间队列中不重叠的个数
        if (intervals.empty()) return 0;
        sort(intervals.begin(), intervals.end(), cmpInterval);
        int prevEnd = intervals[0].second;
        for (int i = 1; i < intervals.size(); i++){
            if (intervals[i].first < prevEnd){
                continue;
            }
            prevEnd = intervals[i].second;
            count++;
        }
        return intervals.size() - count;
    }
    // Partition Labels
    // 顺序聚类
    vector<int> getPartitionLables(const string s){
        vector<int> lastIndexOfChar(26, -1);         // 记录每一个字母对应的下标
        for (int i = 0; i < s.size(); i++){
            lastIndexOfChar[s[i] - 'a'] = i;
        }
        vector<int> ret;
        int firstIndex = 0;
        while (firstIndex < s.size()){
            int lastIndex = firstIndex;
            for (int i = firstIndex; i < s.size() && i <= lastIndex; i++){
                int index = lastIndexOfChar[s[i] - 'a'];
                if (index > lastIndex){
                    lastIndex = index;
                }
            }
            ret.push_back(lastIndex - firstIndex + 1);
            firstIndex = lastIndex + 1;
        }
        return ret;
    }
    // Non-decreasing Array
    // 判断一个数组是否可以通过修改一个数成为非递减数组
    bool cheakPossibilityToNonDecrease(vector<int> nums){
        int cnt = 0;
        for (int i = 1; i < nums.size(); i++){
            if (nums[i] > nums[i - 1]){
                continue;
            }
            cnt++;
            if (i >= 2 && nums[i - 2] > nums[i]){
                nums[i] = nums[i - 1];
            }
            else{
                nums[i - 1] = nums[i];
            }
            if (cnt > 1) return false;
        }
        return true;
    }
};