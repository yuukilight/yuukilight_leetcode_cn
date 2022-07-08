#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
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


