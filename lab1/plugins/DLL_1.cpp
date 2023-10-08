#include <cmath>
#include <string>
using std::string;

extern "C"
{
	__declspec(dllexport) int op_priority = 3;
	__declspec(dllexport) char name = '^';
	__declspec(dllexport) double function(double a, double b) { if (a < 0 && b - (int)b != 0) { throw std::exception("You cannot raise a negative number to a fractional power!"); } return pow(a, b); }
	__declspec(dllexport) string name_type() { return "op"; }
}