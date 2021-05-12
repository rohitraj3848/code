#include<stdio.h>
#include<iostream>
#include<string>
using namespace std;

bool solution(string s){
    if(s.length()>26){
        return false;
    }
    bool b[26]={false};
    for(int i=0;i<s.length();i++){
        int val=s[i];
        if(val>=65 && val<=90){
            if(b[(val+32)%97]){
                return false;
            }
        }
        else{
            if(b[val%97]){
                return false;
            }
        }
        if(val>=65 && val <=90){
            b[(val+32)%97]=true;
        }
        else{
            b[val%97]=true;
        }
    }
    return true;
}

int main(){
    string s;
    cout << "please enter the string:" << "\n";
    cin >> s;
    cout << solution(s)<< "\n";

}