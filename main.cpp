#include <iostream>
#include <vector>

#include "JVector.h"

constexpr auto UTF_8 = 65001;

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
	SetConsoleOutputCP(UTF_8);
#endif // WIN32

	vector<int> svector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector<int> jvector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector<int> a;
	vector<int> vector2;

	cout << jvector[0] << endl;
	jvector.erase(jvector.begin());
	cout << jvector[0] << endl;

	//for (const auto e : jvector)
	//	cout << e << endl;
	
	return 0;
}