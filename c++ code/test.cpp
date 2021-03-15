#include <iostream>
using namespace std;
class person
{
    char name[30];
    int age;

public:
    void getdata(void)
    {
        cout << "enter name" << endl;
        cin >> name;
        cout << "enter age" << endl;
        cin >> age;
    }
    void display(void)
    {
        cout << "name : " << name << endl;
        cout << "age : " << age << endl;
    }
};
/*void person ::getdata(void)
{
    cout << "enter name" << endl;
    cin >> name;
    cout << "enter age" << endl;
    cin >> age;
}
void person :: display(void)
{
    cout << "name : " << name << endl;
    cout <<"age :" << age << endl;
}
*/
int main()
{
    person p;
    p.getdata();
    p.display();
    return (0);
}
