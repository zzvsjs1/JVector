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

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(UTF_8);
#endif // WIN32


	vector<int> std_vector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector<int> j_vector = { 10, 5, 12, 6, 4, 2, 0 };

	return 0;
}