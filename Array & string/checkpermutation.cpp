#include<bits/stdc++.h>
using namespace std;

bool check(string s,string t){
    if(t.length()!=s.length()){
        return false;
    }
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    if(s.compare(t) == 0){
        return true;
    }
    return false;
}
int main(){
    cout << check("doge","god") << "\n";
    string r = "rohit";
    cout << r[3] << "\n";
    return 0;
}