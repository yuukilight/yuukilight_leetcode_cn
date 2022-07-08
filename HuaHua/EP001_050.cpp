#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_map>

using namespace std;

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
};