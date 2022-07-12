#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <map>

using namespace std;

/**
 * 
 * Definition for a binary tree node.
 **/
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


class Solution {
public:
    // EP001: 1. Two Sum
    vector<int> twoSum(vector<int>& nums, int target) {
        // 因为答案唯一，所以可以使用 hash 表来存放索引
        unordered_map<int, int> indices;
        // 将对应索引存入 hash 表
        for(int i=0;i<nums.size();++i){
            indices[nums[i]]=i;
        }
        // 查找 hash 表中是否存在 target-nums[i]
        for(int i=0;i<nums.size();++i){
            int left = target-nums[i];
            // 如果存在并且不等于自身，即得到答案，返回即可
            if(indices.count(left)&&indices[left]!=i){
                return {i, indices[left]};
            }
        }
        return{};
    }

    // EP002: 657. Robot Return to Origin
    bool judgeCircle(string moves) {
        int x=0, y=0;
        // 如果访问元素不存在会返回 0
        map<char, int> dx{{'L',-1},{'R',1}},dy{{'U',1},{'D',-1}};
        for(const char &move:moves){
            x+=dx[move];
            y+=dy[move];
        }
        // 当 x 与 y 均为 0 时会转圈
        return x==0&&y==0;
    }

    // EP003: 461. Hamming Distance
    int hammingDistance(int x, int y) {
        int ans=0;
        // 异或运算
        int t=x^y;
        while(t>0){
            ans+=t&1;
            // 右移一位
            t>>=1 ;
        }
        return ans;
    }

    // EP004: 455. Assign Cookies
    // turn to Greedy

    // EP005: 404. Sum of Left Leaves
    int sumOfLeftLeaves(TreeNode* root) {
        if(!root) return 0;
        int sum=0;
        // 如果左结点存在 并且为叶子结点 则返回对应的值；
        if(root->left && !root->left->left && !root->left->right){
            sum +=  root->left->val;
        }
        // 如果不满足 则递归 自己的孩子
        return sum + sumOfLeftLeaves(root->left)+sumOfLeftLeaves(root->right);
    }
};