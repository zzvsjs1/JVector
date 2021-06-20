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

enum Gender
{
	GMale,
	GFemale,
	GUnknown,
};

class Charactor
{
public:
	std::string m_Name;
	unsigned int m_Age;
	Gender m_Gender;
	float m_Height;		// in cm
	float m_Weight;		// in kg
};

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

	cout << svector.max_size();

	cout << endl;

	return 0;
}