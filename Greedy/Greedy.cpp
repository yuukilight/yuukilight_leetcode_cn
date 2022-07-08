#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


class Solution {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        // 分别对饼干大小和小孩饥饿度进行排序
        // 每次都先满足饥饿度低并且尽可能使用更小的饼干
        sort(g.begin(),g.end());
        sort(s.begin(),s.end());
        int child=0, cookie=0;
        // 当还存在小孩没有喂饱 且 还有饼干就继续循环
        while(child<g.size()&&cookie<s.size()){
            // 饼干大小 大于 饥饿度即可增加吃饱小孩的数目
            if(s[cookie]>=g[child]){
                ++child;
            }
            // 饼干要么满足要求喂食，要么不满足都会指向下一个饼干
            ++cookie;
        }
        return child;
        
    }

    int candy(vector<int>& ratings) {
        int n = ratings.size();
        if(n<2) return n;
        vector<int> candies (n, 1);
        // compare with left
        for(int i=1; i<n ;++i){
            if(ratings[i]>ratings[i-1]){
                // 如果比左边的评价高，得到的糖果数目更多，所以 +1
                candies[i]=candies[i-1]+1;
            }
        }
        // compare with right
        for(int i=n-2; i>=0 ;--i){
            if(ratings[i]>ratings[i+1]){
                // 如果比右边的评价高，因为当前的糖果数目是满足比左边评价高的
                // 所以不能低于当前值，取 当前值 和 右边糖果+1 的最大值
                candies[i]=max(candies[i+1]+1,candies[i]);
            }
        }
        // accumulate 进行累加计算
        return accumulate(candies.begin(), candies.end(), 0);
    }

    // leetcode 435
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.empty()) return 0;
        // 划分成区间后，区间的结尾一定是依次递增的，所以先按区间的结尾排序
        // 使用引用型数据类型更节省时间
        sort(intervals.begin(),intervals.end(),
                [](vector<int> &a, vector<int> &b){return b[1]>a[1];});
        // 依次将区间的头于当前结尾对比，不重合则保留
        int total=0, prev=intervals[0][1];
        for(int i=1;i<intervals.size();++i){
            if(intervals[i][0]<prev){
                // 不满足则删去，并累加计数
                ++total;
            }
            else{
                prev = intervals[i][1];
            }
        }
        return total;
    }
};





int main(){
    Solution a;
    vector<int> g = {1,2,3,2,2,4,3,4,4,6,796,9,4,5,1,5};
    vector<int> s = {1,1,1,2,3,3,5};
    int r = a.findContentChildren(g,s);
    cout<<r;
}

