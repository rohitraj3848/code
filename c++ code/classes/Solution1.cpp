#include <string>
#include <iostream>
#include<stack>
#include <vector>
#include <set>
#include <queue>
using namespace std;

class Solution{
public:
    int maxArea(vector<int>& height) {
        int l = 0;
        int r = height.size()-1;
        int area = 0;
     
        while (l < r)
        {
            // Calculating the max area
            area = max(area, min(height[l],height[r]) * (r - l));                
            if (height[l] < height[r])
                l += 1;   
            else
                r -= 1;
        }
        return area;
    }
    //phone pad all letter combination given key combination
    vector<string> letterCombinations(string digits) {
        string table[10] = { "0",   "1",   "abc",  "def", "ghi","jkl", "mno", "pqrs", "tuv", "wxyz" };
        int arr[digits.length()]={0};
        for(int i=0;i<digits.length();i++){
            arr[i] = arr[i] * 10 + (digits[i] - 48);
        }
        int n=digits.size();
        vector<string> list;
        queue<string> q;
        q.push("");
        while(!q.empty()){
            string s = q.front();
            q.pop();
 
            // If complete word is generated
            // push it in the list
            if (s.length() == n)
                list.push_back(s);
            else
    
                // Try all possible letters for current digit
                // in number[]
                for (auto letter : table[arr[s.length()]])
                    q.push(s + letter);
        }
        return list;
    }


};
int main(){
    Solution s;
    string digits="23";
    vector<string> result=s.letterCombinations(digits);
    for(int i=0;i<result.size();i++){
        cout << result[i] << " ";
    }
    cout << endl;

}