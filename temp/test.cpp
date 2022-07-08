#include "temp.h"
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <string>

using namespace std;

int main(){
    Solution a;
    string key = "the quick brown fox jumps over the lazy dog fasf fasf";
    string message = "vkbs bs t suepuv";
    string result = a.decodeMessage(key, message);

    cout<<result<<endl;
}
