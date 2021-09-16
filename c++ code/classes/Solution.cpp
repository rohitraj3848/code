#include <string>
#include <iostream>
#include<stack>
#include <vector>
#include <set>
using namespace std;
//daily temperatures
//find days after which a warmer day come
struct ListNode {
      int val;
      ListNode* next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    
    vector<int> dailyTemperatures(vector<int>& temperatures) {

        int n=temperatures.size();
        vector<int> ans;
        ans.assign(n,0);
        stack<int> s;
        for(int i=n-1;i>=0;--i){
            while(!s.empty() && temperatures[i]>=temperatures[s.top()]){
                s.pop();
            }
            ans[i]=s.empty()? 0 : s.top()-i;
            s.push(i);
        }
        return ans;
    }
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* sum = new ListNode(0);
        ListNode* head=sum;
        if(l1==nullptr){
            return l2;
        }
        if(l2==nullptr){
            return l1;
        }
        int add=0;
        int carry=0;
        int data=0;
        while(l1!=nullptr || l2!=nullptr){
            add=l1->val+l2->val+carry;
            carry=add/10;
            data=add%10;
            sum->next=new ListNode(data);
            sum=sum->next;
            l1=l1->next;
            l2=l2->next;
            
        }
        while(l1!=nullptr){
            add=l1->val+carry;
            carry=add/10;
            data=add%10;
            sum->next=new ListNode(data);
            sum=sum->next;
            l1=l1->next;
        }
        while(l2!=nullptr){
            add=l2->val+carry;
            carry=add/10;
            data=add%10;
            sum->next=new ListNode(data);
            sum=sum->next;
            l2=l2->next;
        }
        if(carry==1 ){
            sum->next=new ListNode(carry);
        }
        
        return head->next;
    }
    //longest non-repeating substring
    int lengthOfLongestSubstring(string s) {
        int n=s.size();
        int res=0;
        for(int i=0;i<n;i++){
             vector<bool> visited(256);
            for(int j=i;j<n;j++){
                if(visited[s[j]]==true){
                    break;
                }
                else{
                    res=max(res,j-i+1);
                    visited[s[j]]=true;
                }
            }
            visited[s[i]]=false;
        }
       return res;

    }
    
};



int main()
{   /*vector<int> temperatures{73, 74, 75, 71, 69, 72, 76, 73};
    Solution s;
    vector<int> out=s.dailyTemperatures(temperatures);
    for(auto it=out.begin(); it!=out.end();it++){
        cout << *it << " ";
    }*/
    ListNode* l1=new ListNode(2);
    l1->next=new ListNode(4);
    l1->next->next=new ListNode(3);
    ListNode* l2=new ListNode(5);
    l2->next=new ListNode(6);
    l2->next->next=new ListNode(4);
    Solution s1;
    ListNode* result=s1.addTwoNumbers(l1,l2);
    while(result!=nullptr){
        cout << result->val << " ";
        result=result->next;
    }
    cout << endl;

}
