[toc]
# 指针基本操作
- 指针常量
```c++
int x;          // 定义一个变量，可以被修改
// 定义一个指针 p1 指向这个变量的地址，指向的地址和地址的值都可以修改
int * p1=&x;
// 定义一个指针 p2 指向这个变量的地址， 地址指向的值不能修改(const int)
const int * p2 = &x;
// 定义一个指针 p3 指向这个变量的地址，指向的地址不能修改(* const)
int * const p3 = &x;
// 定义一个指针 p3 指向这个变量的地址，指向的地址和地址的值均不能修改
const int * const p4 = &x;
```

- 指针函数与函数指针
指针函数是返回 指针的函数 是一个函数
函数指针是 指向一个函数的指针 是指针
```c++
// addition 是一个指针函数，是一个返回类型是指针的函数
int * addition(int a, int b){
    int * sum = new int(a+b);
    return sum
}

int subtraction(int a, int b){
    return a-b;
}

// operation 是一个调用了函数指针的函数
int operation(int x, int y, int (*func)(int, int)){
    return (*func)(x,y);
}

// minus 是函数指针，指向函数的指针
int (*minus)(int, int) = subtraction;

int *m=addition(1,2);               // *m=3
int n = operation(3, *m, minus);    // n = 3-3
```

# 有序队列使用双指针搜索
EX: 167. Two Sum II - Input Array Is Sorted
本题可以利用数组是递增的特定，设置头尾指针，根据与目标值对比的结果来选择移动那个指针（本题移动头指针是增大结果，移动尾指针是减小结果）
[leetcode_167](https://leetcode.cn/problems/two-sum-ii-input-array-is-sorted/)
```c++
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
```

# 归并有序数组
EX：88. Merge Sorted Array
使用双指针，来遍历两个有序数组来选择合适的元素插入合并后的数组，以维持数组有序
[leetcode_88](https://leetcode.cn/problems/merge-sorted-array/)
```c++
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
```

# 快慢指针
EX：142. Linked List Cycle II
Floyd 判圈法 是判断回路是否存在的经典算法 时间复杂度 O(nlogn), 空间复杂度O(1)
简单证明：
1. 当存在回路时，两个指针必定会相遇：肯定会在回路中相遇，当两个指针同时存在于回路当中时，就是一个追赶问题，每一次移动会追上一步。
2. 当在回路中相遇时，将一个指针指向开头，并同时每次只移动一次，相遇的结点就是回路的路口：首先，在回路中相遇的结点，以同速移动时，一定在回路中处处相遇；然后，相遇的结点可以视为从起点出发移动了 n 次和 2*n 次。一个指针回到开头后，再以每次移动一次移动 n 次必定会在相同的地方相遇，那么第一次相遇的结点就是回路的路口。
[leetcode_142]
```c++
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
```

# 滑动窗口
两个指针指向同一个数组，移动方向相同，并且两个指针不会相交，两个指针包围的区域即为滑动窗口，常用于区间搜索。
EX：76. Minimum Window Substring
```c++
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
```