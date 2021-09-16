#include <string>
#include <iostream>
#include<stack>
#include <vector>
#include <set>
#include "linked_list"

struct ListNode{
    int val;
    ListNode* next;
    ListNode() : val(0) , next(nullptr){}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};