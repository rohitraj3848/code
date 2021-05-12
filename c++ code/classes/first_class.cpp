#include <string>
#include <iostream>
using namespace std;
class Foo
{
public:
    Foo() : counter_(0), str_(NULL) {}
    Foo(int c, string *p) : counter_(c), str_(p) {}
    void print(){
        cout << counter_ << "  " << *str_ << endl;
    }
private:
    int counter_;
    string *str_;
};
int main()
{
    string s = "bar";
    Foo f(2, &s);
    f.print();

}
