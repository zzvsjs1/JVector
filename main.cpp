#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <Windows.h>
#include <memory>

#include "JVector.h"

#ifdef _WIN32
#ifdef _MSC_VER
#include <Windows.h>
# elif (__GNUC__) && (__MINGW32__)
#include <windows.h>
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
	static int i;
	int a;
	my_class() = default;
	my_class(int g) : a(g) {}
	auto r() { return ++a; }
	~my_class() { cout << "delete me " << i++ << " times." << endl; }
};
int my_class::i = 0;

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

	JVector<int> k(10);

	k = { 1, 2, 3, 4, 5 , 6, 7, 8, 9, 10 , 11};

	print_arr(k);

	/*
	const auto t1 = std::chrono::high_resolution_clock::now();
	for (size_t i = 0; i < 10000000; i++)
	{
		g.emplace(g.cend(), 5);
		//gg.emplace(gg.cend(), 5);
	}
	const auto t2 = std::chrono::high_resolution_clock::now();

	std::chrono::duration<double, std::milli> fp_ms = t2 - t1;
	const auto int_ms = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
	const std::chrono::duration<long, std::micro> int_usec = int_ms;

	cout << "This vector took " << fp_ms.count() << " ms, "
		<< "or " << int_ms.count() << " whole milliseconds "
		<< "(which is " << int_usec.count() << " whole microseconds)" << endl;
	*/
	
	return 0;
}