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

int main()
{
#ifdef _WIN32
	SetConsoleOutputCP(UTF_8);
#endif // WIN32





	return 0;
}