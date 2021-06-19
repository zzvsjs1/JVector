#include <iostream>
#include <vector>

#include "JVector.h"

#ifdef _WIN32
#ifdef _MSC_VER
#include <Windows.h>
#endif // _MSC_VER
#endif // WIN32

using namespace JSTD;
using std::vector;
using std::cin;
using std::cout;
using std::endl;
using std::string;

int main()
{
#ifdef _WIN32
	constexpr auto UTF_8 = 65001;
	SetConsoleOutputCP(UTF_8);
#endif // WIN32

	vector<int> svector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector<int> jvector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector<int> a(0, 50);
	vector<int> vector2(0, 50);

	cout << a.size() << a.capacity() << endl;
	cout << vector2.size() << vector2.capacity();

	for (auto e : a)
		cout << e << " ";

	cout << endl;

	for (auto a = jvector.crbegin(); a != jvector.rend(); a++)
		cout << *a << " ";

	cout << endl;

	return 0;
}