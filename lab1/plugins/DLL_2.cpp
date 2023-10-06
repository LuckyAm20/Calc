#include <cmath>
#include <string>
using std::string;

extern "C"
{
	__declspec(dllexport) string name() { return "sqrt"; }
	__declspec(dllexport) double function(double a) { if (a < 0) { throw std::exception("Нельзя извлечь корень квадратный!"); } return sqrt(a); }
	__declspec(dllexport) string name_type() { return "func"; }
}