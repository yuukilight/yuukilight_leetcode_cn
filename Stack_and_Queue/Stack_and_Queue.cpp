#include <iostream>
#include <vector>
#include <stack>

using namespace std;

/*
EX: 232.Implement Queue using Stacks
*/
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
/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

/*
EX: 155.Min Stack
*/
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


/*
EX: 20.Valid Parentheses
*/
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

/*
EX: 739.Daily Temperatures
*/
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
};

