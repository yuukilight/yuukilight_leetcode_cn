[toc]
# C++ 中 Stack 和 Queue 的基本操作
##  Stack
c++ 中的 stack 默认使用 deque 实现，也可以选择用 vector
deque 和 vector 都可以实现 $O(1)$ 的随机读取和 $O(1)$ 的尾部增删
deque 还可以实现 $O(1)$ 的头部增删
```c++
stack<int> s;       // 定义 stack, int 可以更换为其它数据类型
stack<int, vector<int>> // 也可以指定容器，默认为 deque

s.empty();         //如果栈为空则返回true, 否则返回false;
s.size();          //返回栈中元素的个数
s.top();           //返回栈顶元素, 但不删除该元素
s.pop();           //弹出栈顶元素, 但不返回其值
s.push();          //将元素压入栈顶
```




# 基础 Stack 和 Queue

EX: 232.Implement Queue using Stacks
主要学习 stack 和 queue 他们各自的特点
[leetcode_232](https://leetcode.cn/problems/implement-queue-using-stacks/)
```c++
class MyQueue {
private:
    stack<int> stack_push;
    stack<int> stack_pop;
public:
    MyQueue() {
    }
    
    void push(int x) {
        stack_push.push(x);
    }
    
    int pop() {
        push2pop();
        int result = stack_pop.top();
        stack_pop.pop();
        return result;
    }
    
    int peek() {
        push2pop();
        return stack_pop.top();
    }
    
    bool empty() {
        push2pop();
        return stack_pop.empty();
    }

    void push2pop(){
        // 没有出队元素的时候 才会重新将元素载入
        if(stack_pop.empty()){
        while(!stack_push.empty()){
            stack_pop.push(stack_push.top());
            stack_push.pop();
            }
        }
    }
};
```

EX: 155.Min Stack
利用 stack 的特性在进行相关操作的同时 存储一些额外的信息
[leetcode_155](https://leetcode.cn/problems/min-stack/)
```c++
class MinStack {
public:
    MinStack() {

    }
    void push(int val) {
        my_stack.push(val);
        // 只有当最小栈为空或压栈的值小于等于栈顶时才压入最小栈
        // 因为可能有多个相同的最小值，pop 操作不方便，所以等于时也会压栈
        if(min_stack.empty()||val<=min_stack.top()){
            min_stack.push(val);
        }
    }
    
    void pop() {
        // 当栈顶和最小栈的栈顶相同时同时出栈
        if(my_stack.top()==min_stack.top()){
            min_stack.pop();
        }
        my_stack.pop();
    }
    
    int top() {
        return my_stack.top();
    }
    
    int getMin() {
        return min_stack.top();
    }
private:
    stack<int> my_stack;
    stack<int> min_stack;
};
/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
```

EX: 20.Valid Parentheses
利用 stack 的特征进行对的匹配（例如括号）
[leetcode_20](https://leetcode.cn/problems/valid-parentheses/submissions/)
```c++
class Solution {
public:
    bool isValid(string s) {
        // 定义一个 stack 存储括号
        stack<char> parsed;
        for(const char &c:s){
            // 当元素为左括号的时候压栈
            if(c=='('||c=='['||c=='{'){
                parsed.push(c);
            }
            // 否则判断是否有与之配对的括号，没有的话即为无效括号字符串
            else{
                if(parsed.empty()) return false;
                char parsed_top = parsed.top();
                if((parsed_top == '['&& c==']')||
                    (parsed_top == '{'&& c=='}')||
                    (parsed_top == '('&& c==')')){
                        parsed.pop();
                    }
                else return false;
            }
        }
        // 遍历完所有的 字符后应该为空，否则无效
        return parsed.empty();
    }
};
```

# 单调栈
EX: 739.Daily Temperatures
利用 stack 来维护一直有序的数据可以很轻易的找到下一个更大或者更小值称为 NGE （Next Greater Element） 问题
[leetcode_739](https://leetcode.cn/problems/daily-temperatures/)
```c++
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        // 初始值为0 
        vector<int> result(n);
        // 可以指定 stack 的容器， 默认为 deque
        stack<int, vector<int>> sort_stack;
        for(int i=0;i<n;++i){
            // 只要栈不为空就一直检测下去
            while(!sort_stack.empty()){
                int pre_index = sort_stack.top();
                // 出现更大就就将结果写入 result
                if(temperatures[i]>temperatures[pre_index]){
                    result[pre_index]=i-sort_stack.top();
                    sort_stack.pop();
                }
                // 否则退出循环进行 入栈操作
                // 维持栈的递减的
                else{
                    break;
                }
            }
        sort_stack.push(i);
        }
        return result;
    }
```