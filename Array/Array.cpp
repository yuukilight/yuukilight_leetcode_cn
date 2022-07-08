#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
/*
EX：448.Find All Numbers Disappeared in an Array
*/
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        vector<int> result;
        // 遍历整个数组，出现的数字可以对应成一个索引
        for(const int &num: nums){
            int val = abs(num)-1;
            if(nums[val]>0){
                // 因为原数组所有数都大于0，所以可以用负数来标记，并且不影响数值绝对值
                nums[val] = -nums[val];
            }
        }
        // 遍历数组结束后，原数组中仍然为正就表示没有出现过，对应的位置索引加 1 就是没有出现过的值
        for(int i=0;i<nums.size();i++){
            if(nums[i]>0){
                result.push_back(i+1);
            }
        }
        return result;
    }
/*
EX：48.Rotate Image
*/
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size()-1;    // n 为矩阵最大索引
        for(int i=0;i<=n/2;++i){
            for(int j=i;j<n-i;++j){  // 从外圈向内圈计算
            // i 和 n-i 代表着边界
                int temp = matrix[i][j];
                matrix[i][j]= matrix[n-j][i];matrix[j][n-i];
                matrix[n-j][i]=matrix[n-i][n-j];
                matrix[n-i][n-j]=matrix[j][n-i];
                matrix[j][n-i]=temp;
            }
        }
    }

/*
EX：240.Search a 2D Matrix II
*/
    // 因为按行和列都是有规律可循的，并且属于同一套规律（递增和递减属于同一套）
    // 行和列的访问顺序可以自己设定（前往后或者后往前）
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // 利用这种规律 获得二维数据的尺寸后可以 Z 形访问来搜索
        int row = matrix.size();
        int column = matrix[0].size();
        // 本题行列都是递增所以可以在左下角或右上角开始 Z 形
        int i=0,j=column-1;
        while(i < row && j>=0){
            if(matrix[i][j]>target){
                --j;
                continue;
            }
            else if(matrix[i][j]<target){
                ++i;
                continue;
            }
            else if(matrix[i][j]==target){
                return true;
            }
        }
        return false;
    }

/*
EX：769.Max Chunks To Make Sorted
*/
    // 从最终结果倒推，最终的结果索引是等于对应的值的
    // 索引是递增的，所以只要当前最大值等于索引就可以增加一个划分 chunk
    int maxChunksToSorted(vector<int>& arr) {
        if(arr.size()<2){
            return arr.size();
        }
        // 初始化值
        int max_val=0, count=0;
        // 循环整个数组后即可得到结果
        for(int i=0; i<arr.size();++i){
            max_val = max(max_val, arr[i]);
            if(max_val == i){
                ++count;
            }
        }
        return count;
    }

};