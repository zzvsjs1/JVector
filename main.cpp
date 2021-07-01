#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

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

	vector svector = { 10, 5, 12, 6, 4, 2, 0 };
	vector svector2 = { 10, 5, 12, 6, 4, 2, 0 };
	JVector jvector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector jvector2 = { 10, 5, 12, 6, 4, 2 };
	JVector a(0, 50);
	vector vector2(0, 50);

	for (const auto &jvector1 : jvector)
	{
		cout << jvector1 << " ";
	}

	cout << endl;

	std::sort(jvector.begin(), jvector.end());
	
	for (const auto &jvector1 : jvector)
	{
		cout << jvector1 << " ";
	}

	cout << endl;

	//if (svector == svector2)
	//	cout << "Equal!" << endl;

	//if (jvector > jvector2)
		//cout << "Greater!" << endl;

	//JVector<string> g;
	//g.emplace(0, "5");
	
	return 0;
}