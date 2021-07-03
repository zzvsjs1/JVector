#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <chrono>

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
	my_class2() = default;
	my_class2(T c, T* d) : a(c), b(d) {}

private:
	T a;
	T* b;
};

int main()
{
#ifdef _WIN32
	constexpr auto UTF_8 = 65001;
	SetConsoleOutputCP(UTF_8);
#endif // WIN32

	//JVector<string> g;
	vector<string> gg;

	auto t1 = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 10000000; i++)
	{
		//g.emplace(g.cend(), "haha");
		gg.emplace(gg.cend(), "haha");
	}
	auto t2 = std::chrono::high_resolution_clock::now();
	
	std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
	auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	std::chrono::duration<long, std::micro> int_usec = int_ms;

	std::cout << "This vector took " << fp_ms.count() << " ms, "
		<< "or " << int_ms.count() << " whole milliseconds "
		<< "(which is " << int_usec.count() << " whole microseconds)" << std::endl;

	//cout << g.capacity() << " " << gg.capacity();

	return 0;
}