[toc]
## C++ 中数组的基本操作
在 c++ 中主要使用 vector 来进行数组操作，vector 是一种顺序存储的动态数组，起特定和常用操作如下：
vector 可以实现 $O(1)$ 的随机读取和 $O(1)$ 的尾部增删, 其余大部分算法的时间复杂度都会大于 $O(n)$
- 基础使用
```c++
// int 可以更换为其它数据类型，a 为数组名称
vector<int> a();
vector<int> a(n);       // 创建的数组容量为n, 默认数值为0
vector<int> a(n, t);    // 创建的数组容量为n, 数值为t

a.push_back(x);     // 在尾部增加元素 x
a.emplace_back(x);

a.pop_back();       // 删除向量中最后一个元素

a.begin();          // 返回向量头指针，指向第一个元素
a.end();            // 返回向量尾指针，指向向量最后一个元素的下一个位置

a.front();          // 返回首元素的引用
a.back();           // 返回尾元素的引用

a.empty();          // 判断向量是否为空，若为空，则向量中无元素

a.size();           // 返回向量中元素的个数
```

1. 创建数组
```c++
vector():创建一个空vector
vector(int nSize):创建一个vector,元素个数为nSize
vector(int nSize,const t& t):创建一个vector，元素个数为nSize,且值均为t
vector(const vector&);   //复制构造函数
vector(begin,end);       //复制[begin,end)区间内另一个数组的元素到vector中
```
2. 增加函数
```c++
emplace() // 插入单个元素时使用 emplace 更佳
void push_back(const T& x):向量尾部增加一个元素X
iterator insert(iterator it,const T& x):向量中迭代器指向元素前增加一个元素x
iterator insert(iterator it,int n,const T& x):向量中迭代器指向元素前增加n个相同的元素x
iterator insert(iterator it,const_iterator first,const_iterator last):向量中迭代器指向元素前插入另一个相同类型向量的[first,last)间的数据
```
3. 删除函数
```c++
iterator erase(iterator it):删除向量中迭代器指向元素
iterator erase(iterator first,iterator last):删除向量中[first,last)中元素
void pop_back():删除向量中最后一个元素
void clear():清空向量中所有元素
```
4. 遍历函数
```c++
reference at(int pos):返回pos位置元素的引用
reference front():返回首元素的引用
reference back():返回尾元素的引用
iterator begin():返回向量头指针，指向第一个元素
iterator end():返回向量尾指针，指向向量最后一个元素的下一个位置
reverse_iterator rbegin():反向迭代器，指向最后一个元素
reverse_iterator rend():反向迭代器，指向第一个元素之前的位置
```
5. 判断函数
```c++
bool empty() const:判断向量是否为空，若为空，则向量中无元素
```
6. 大小函数
```c++
int size() const:返回向量中元素的个数
int capacity() const:返回当前向量所能容纳的最大元素值
int max_size() const:返回最大可允许的vector元素数量值
```
7. 其他函数
```c++
void swap(vector&):交换两个同类型向量的数据
void assign(int n,const T& x):设置向量中前n个元素的值为x
void assign(const_iterator first,const_iterator last):向量中[first,last)中元素设置成当前向量元素
```
8. 补充
```c++
// 创建二维数组 m*n 值为 -1
vector<vector<int>> matrix(m, vector<int>(n, -1));
```


## 灵活利用输入的数组本身来节省时间空间
EX：448.Find All Numbers Disappeared in an Array
[leetcode_448](https://leetcode.cn/problems/find-all-numbers-disappeared-in-an-array/)
```c++
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
```

## 二维数组的原地操作 （in-place）
EX：48.Rotate Image
[letcode_48](https://leetcode.cn/problems/rotate-image/)
```c++
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
```
## 二维数组间的顺序关系（z 形搜索）
EX：240.Search a 2D Matrix II
[leetcode_240](https://leetcode.cn/problems/search-a-2d-matrix-ii/)
```cpp
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
```

## 数组内分块处理
EX：769.Max Chunks To Make Sorted
[leetcode_768](https://leetcode.cn/problems/max-chunks-to-make-sorted/)
```c++
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
```