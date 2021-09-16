#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

bool compare_function(int i, int j)
{
   return i > j;    // return 1 if i>j else 0
}
bool compare_string(string i, string j)
{ 
  return (i.size() < j.size()); 
}

int main()
{
    int arr[5] = {1,5,8,4,2};
    
    sort(arr , arr+5);    // sorts arr[0] to arr[4] in ascending order
    /* now the arr is 1,2,4,5,8  */
    
    vector<int> v1;
    
    v1.push_back(8);
    v1.push_back(4);
    v1.push_back(5);
    v1.push_back(1);
    
    /* now the vector v1 is 8,4,5,1 */
    vector<int>::iterator i, j;
    
    i = v1.begin();   // i now points to beginning of the vector v1
    j = v1.end();     // j now points to end of the vector v1
    
    sort(i,j);      //sort(v1.begin() , v1.end() ) can also be used
    /* now the vector v1 is 1,4,5,8 */
    int a[5] = {1,5,8,4,2}; 
    cout<<is_sorted(a, a+5);
    
    /* use of compare_function */
    int a2[] = { 4,3,6,5,6,8,4,3,6 };
    int count_5 = count(a2, a2+9, 3);
    partial_sort(a, a+4, a+9);
    cout<<equal(v1.begin(), v1.end(), v2.begin()+2 );
    sort(a2,a2+9,compare_function);  // sorts a2 in descending order 
    /* here we have used compare_function which uses operator(>), 
    that result into sorting in descending order */
    int inputs[] = {7,8,4,1,6,5,9,4};
    vector<int> v(inputs, inputs+8);
    
    cout << binary_search(v.begin() , v.end() , 7 );
    int input1[] = {1,1,1,2,2,2,3,3,6,7,7,7,7,7,8,9};
    vector v(input1, input1+16);
               
    pair< vector<int>::iterator, vector<int>::iterator > sub_range;
    /* defining the pair of two iterators to an integer vector */
    
    
    sub_range = equal_range (v.begin(), v.end(), 2);
    /* now sub_range.first points to 4th element in the vector v and 
     sub_range.second points to 7th element , 
     note that sub_range.secong points to the element 
     which is next to the element in the subrange  */ 
    
    sub_range = equal_range (v.begin(), v.end(), 20, compare_function);
    /* sub_range.first points to first element in the vector v , 
    as it satisfy the condition exerted by compare_function , <= , 
     sub_range.second points to 7th element in the vector . */
    cout << binary_search(v.begin() , v.end() , 217);
    /* compare_function is also used to sort non-numeric elements such as*/
    
    string s[]={"a" , "abc", "ab" , "abcde"};
    
    sort(s,s+4,compare_string);
    /* now s is "a","ab","abc","abcde"  */
}