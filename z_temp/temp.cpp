#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;


// Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:

/*
EX：76. Minimum Window Substring
*/
    string minWindow(string s, string t) {
        int m=s.size(), n=t.size();
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
            if(flag[s[r]-'A']){
                if(char_count[s[r]-'A']-- > 0) ++cnt;
            }

            while(cnt==n){
                if(r-l+1<min_size){
                    min_size=r-l+1;
                    min_l=l;
                }
                if(flag[s[l]-'A']&&++char_count[s[l]-'A']>0) --cnt;
                ++l;
            }
        }
        return min_size>m? "":s.substr(min_l, min_size);
    }

    bool canChange(string start, string target) {
        int len=start.size();
        // 设置双指针，因为还要判断位置所以不能用 stack
        int sta=0, tar=0;
        // start 同序的 'L' 需要在target的 'L' 的右侧，同理 'R' 在左侧
        while(sta<len){
            if(start[sta]=='_'){
                ++sta;
                continue;
            }
            else{
                while(tar<len){
                    if(target[tar]=='_'){
                        ++tar;
                        continue;
                    }
                    else break;
                }
                // 没有找到符号 || 或者符号不等
                if(tar==len||target[tar]!=start[sta]) return false;

                if(start[sta]=='L'&&sta<tar) return false;

                if(start[sta]=='R'&&sta>tar) return false;

                ++sta;
                ++tar;
            }
        }
        while(tar<len){
            if(target[tar]!='_') return false;
            ++tar;
        }
        return true;
    }


    // Minimum Amount of Time to Fill Cups
    int fillCups(vector<int>& amount) {
        // 首先进行排序
        sort(amount.begin(),amount.end());
        int x = amount[0]+amount[1];
        if(amount[2]>=x)
            return amount[2];
        x-=int((x-amount[2])/2);
        return x;
    }

    long long minSumSquareDiff(vector<int>& nums1, vector<int>& nums2, int k1, int k2) {
        for(vector<int>::size_type i=0;i<nums1.size();++i){
            nums1[i]=abs(nums1[i]-nums2[i]);
        }
        sort(nums1.begin(),nums1.end());
        int k =k1+k2;
        vector<int>::size_type flag = nums1.size();
        --flag;
        int result=0;
        while(k>0){
            
        }
        for(vector<int>::size_type i=0;i<nums1.size();++i){
            result+=nums1[i]*nums1[i];
        }
        return result;
    }

    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(),buses.end());
        sort(passengers.begin(),passengers.end());
        int final_bus = buses.size()-1;
        vector<int>::size_type passenger=0;
        for(vector<int>::size_type i=0;i<buses.size()-1;++i){
            int count=0;
            // passenger==passengers.size() 代表乘客都已经上车了
            if(passenger==passengers.size()) break;
            while(count<capacity&&passengers[passenger]<=buses[i]){
                ++count;
                ++passenger;
                if(passenger==passengers.size()) break;
            }
        }
        if(passenger==passengers.size()) return buses[final_bus];
        // 需要找到一个小于等于 buses[final_bus] 的数
        // 找到最后一辆车乘坐了 capacity - 1 人的情况
        int count=0;
        while(count<capacity-1&&passengers[passenger]<=buses[final_bus]){
            ++count;
            ++passenger;
            if(passenger==passengers.size()) break;
        }
        int temp = buses[final_bus];
        if(count == capacity - 1)
        // 1. 乘坐了  capacity - 1 人 (还要考虑同时问题 稍后完成 compare with passengers[passenger-1])
            temp = min(buses[final_bus], passengers[passenger]-1);
        // // 2. 数组中的乘客坐完了  (还要考虑同时问题 稍后完成 compare with passengers[passenger-1])
        // int temp = buses[final_bus];
        // // 3. 乘客没坐完 但是 后续的迟到了 (还要考虑同时问题 稍后完成 compare with passengers[passenger-1])
        // int temp = buses[final_bus];

        int flag = passenger-1;
        while(temp==passengers[flag]){
            --temp;
            --flag;
        }
        return temp;
    }

    bool evaluateTree(TreeNode* root) {
        if(root->val==0)
            return false;
        if(root->val==1)
            return true;
        if(root->val==2){
            return evaluateTree(root->left)||evaluateTree(root->right);
        }
        if(root->val==3){
            return evaluateTree(root->left)&&evaluateTree(root->right);
        }
    }


    string decodeMessage(string key, string &message) {
        vector<char> decode_table(26);
        int count=0;
        int n=message.size();
        for(const char &c: key){
            if(c!=' '&&decode_table[c-'a']==0){
                decode_table[c-'a']=count+97;
                if(++count==26) break;
            }
        }
        for(int i=0;i<n;++i){
            if(message[i]!=' '){
                message[i]=decode_table[message[i]-'a'];
            }
        }
        return message;
    }

    vector<vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    vector<vector<int>> matrix(m, vector<int>(n, -1));
    int row=0,column=0;
    while(head){
        int i=row,j=column;
        for(;j<n-column;++j){
            matrix[i][j]=head->val;
            head = head->next;
            if(head==NULL) return matrix;
        }
        for(--j,++i;i<m-row;++i){
            matrix[i][j]=head->val;
            head = head->next;
            if(head==NULL) return matrix;
        }
        for(--i,--j;j>=column;--j){
            matrix[i][j]=head->val;
            head = head->next;
            if(head==NULL) return matrix;
        }
        for(++j,--i;i>row;--i){
            matrix[i][j]=head->val;
            head = head->next;
            if(head==NULL) return matrix;
        }
        ++row,++column;
        
    }
    return matrix;
    }
};


class SmallestInfiniteSet {
public:
    vector<int> removed_num;
    int neg_count;
    SmallestInfiniteSet() {
        neg_count=0;
        removed_num.clear();
    }
    int popSmallest() {
        int smallest=0;
        if(neg_count){
            for(int & i:removed_num){
                if(i<0){
                    i=-i;
                    --neg_count;
                    return i;
                }
            }
        }
        else{
            removed_num.emplace_back(removed_num.size()+1);
            return removed_num.size();
        }
        return smallest;
    }
    
    void addBack(vector<int>::size_type num) {
        if(num>removed_num.size()) return;
        else{
            if(removed_num[num-1]>0){
                ++neg_count;
                removed_num[num-1]=-removed_num[num-1];
            }
        }
    }
};