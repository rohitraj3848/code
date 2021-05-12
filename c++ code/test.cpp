#include <iostream>
using namespace std;

int main()
{
    int n, capacity,i;
   cin >> n >> capacity;
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << key << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         cout << key << value;
      }
   }
   return 0;
}
/*
    8 4

    set 4 2

    set 2 7

    get 2

    set 1 8

    set 5 9

    set 6 15

    get 4

    get 5
*/