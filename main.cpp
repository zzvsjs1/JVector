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

template <typename Ty>
void print_arr(const Ty &t)
{
	for (const auto &e : t)
		cout << e << " ";

	cout << endl;
}

template <typename Ty>
void print_2darr(const Ty &t)
{
	for (const auto &e : t)
	{
		for (const auto &e2 : e)
		{
			cout << e2 << " ";
		}
		
		cout << endl;
	}

	cout << endl;
}


class my_class
{
public:
	my_class() = default;
	my_class(int g) : a(g) {}


private:
	int a;
};

template <class T>
class my_class2
{
public:
	my_class2(T g) : a(g) {}


private:
	T a;
};


int main()
{
#ifdef _WIN32
	constexpr auto UTF_8 = 65001;
	SetConsoleOutputCP(UTF_8);
#endif // WIN32

	/*
	vector svector = { 10, 5, 12, 6, 4, 2, 0 };
	vector svector2 = { 10, 5, 12, 6, 4, 2, 0 };

	JVector jvector = { 10, 5, 12, 6, 4, 2, 0 };
	JVector<string> jvector2 = { "d", "a", "b"};
	*/
	
	//JVector<my_class2<int>> w(5);

	//vector<my_class2<int>> ww(5);
	
	return 0;
}