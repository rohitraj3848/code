/* #include <iostream>
#include <string>
#include <map>

using namespace std;
int main()
{

	map<int, string> Students;

	Students.insert(pair<int, string>(200, "Alice"));
	Students.insert(pair<int, string>(201, "John"));
	cout << "Map size is: " << Students.size() << endl;
	cout << endl
		 << "Default map Order is: " << endl;
	for (map<int, string>::iterator it = Students.begin(); it != Students.end(); ++it)
	{
		cout << (*it).first << ": " << (*it).second << endl;
	}
} */

/* #include <map>
#include <iostream>

using namespace std;

int main() {

	map<int, int> m{ {1,3} , {2,4} , {3,5} };
	m.insert({ 1, 8 });
	m.insert({ 5, 6 });
	
	
	cout << "Key\tElement\n";
	for (auto itr = m.begin(); itr != m.end(); itr++) {
		cout << itr->first << '\t' << itr->second << '\n';
	}
	return 0;
} */
/* #include <iostream>
#include <string>
#include <map> 
using namespace std;
int main() {
	map<int, string> Students;
	Students.insert(pair<int, string>(200, "Alice"));
	Students.insert(pair<int, string>(201, "John"));
	map<int, string>::iterator it = Students.find(201);
	if (it != Students.end()) {
		cout << endl << "Key 201 has the value: => "<< Students.find(201)->second << '\n';
	}
} */
#include <iostream>
#include <string>
#include <map>

using namespace std;
int main()
{

	map<string, int> my_map;

	my_map.insert(make_pair("cow", 1));

	my_map.insert(make_pair("cat", 2));

	my_map["lion"] = 3;

	map<string, int>::iterator it = my_map.find("cat");

	my_map.erase(it);

	for (map<string, int>::iterator it = my_map.begin(); it != my_map.end(); ++it)

		cout << (*it).first << ": " << (*it).second << endl;

	return 0;
}
/**/
/**/