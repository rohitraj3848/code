#include <iostream>
using namespace std;

class item
{
    int number;
    float cost;
    public :
        void getdata(int a, float b);
        void putdata(void)
        {
             cout << "number : " << number << endl;
             cout << "cost : "<< cost << "\n";
        }
};

void item :: getdata(int a, float b)
{
    number = a;
    cost = b;
}


void swap(int a, int b, int c=11)
{
    cout << a+b+c << endl;
}
int main()
{
    item x;
    x.getdata(10,299.93);
    x.putdata();

    item y;
    y.getdata(500, 45.53);
    y.putdata();

    return 0;
}