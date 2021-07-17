#include <iostream>
using namespace std;

int main()
{
    int number[] = { 2, 3 ,4,5 ,8};
    int n = sizeof(number) / sizeof(number[0]);
    cout << n << endl;
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