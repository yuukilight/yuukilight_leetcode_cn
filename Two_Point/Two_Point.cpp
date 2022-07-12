#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
/*
EX：76. Minimum Window Substring
*/
    string minWindow(string s, string t) {
        auto m=s.size(), n=t.size();
        vector<int> char_count(58,0);
        vector<bool> flag(58,false);

        for(auto &c:t){
            flag[c-'A']=true;
            ++char_count[c-'A'];
        }

        // 使用两个指针 形成一个窗口来框住字符串
        // 右指针移动来使窗口更大满足要求，满足要求后移动左指针来缩小窗口
        int cnt=0, l=0, min_l=0, min_size=m+1;
        for(int r=0;r<m;++r){
            if(flag[s[r-'A']]){
                if(char_count[r-'A']-->0) ++cnt;
            }

            while(cnt==n){
                if(r-l+1<min_size){
                    min_size=r-l+1;
                    min_l=l;
                }
                if(flag[s[l]-'A']&&++char_count[s[l++]-'A']>0) --cnt;
            }
        }
        return min_size>m? "":s.substr(min_l, min_size);
    }



/*
EX：167. Two Sum II - Input Array Is Sorted
*/
    vector<int> twoSum(vector<int>& numbers, int target) {
        // the numbers is oreded, so could use two point search
        int l_point=0, r_point=numbers.size()-1;
        while (r_point>l_point)
        {
            if(numbers[l_point]+numbers[r_point]==target) break;
            if(numbers[l_point]+numbers[r_point]>target) --r_point;
            else ++l_point;
        }
        return vector<int>{l_point+1, r_point+1};
    }

/*
EX：88. Merge Sorted Array
*/
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        // pos 指向需要插入元素的位置
        int pos = m-- + n-- -1;
        // 优先插入尾端，因为尾端是空的，不用考虑移动和被覆盖的问题
        while(m>=0&&n>=0){
            if(nums1[m]>nums2[n]) nums1[pos--]=nums1[m--];
            else nums1[pos--]=nums2[n--];
        }
        while(n>=0){
            nums1[pos--]=nums2[n--];
        }
    }

/*
EX：142. Linked List Cycle II
*/
    ListNode *detectCycle(ListNode *head) {
        // 首先判断 走一步和 走两步 后的地址是否存在
        // 以免访问不到，如果不存在直接返回 null 没有环路
        if(!head||!(head->next)) return NULL;
        ListNode *slow=head->next, *quick=head->next->next;
        while(quick!=slow){
            // 同样先判断后续的路径是否存在，再开始移动
            if(!quick||!quick->next) return NULL;
            slow=slow->next;
            quick=quick->next->next;
        }
        quick=head;
        while(quick!=slow){
            quick=quick->next;
            slow=slow->next;
        }
        return quick;
    }
};

