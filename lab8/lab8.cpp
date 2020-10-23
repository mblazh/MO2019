/*								*/
/* 	   Przybliżenia różnicowe	*/
/*								*/

#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define PI 3.14159265359L

template <typename T>
T f(T x){
	return cos(x / T(2.L));
}

template <typename T>
T df(T x){
	return -sin(x / T(2.L)) * T(0.5L);
}

template <typename T>
T d2f(T x){
	return -cos(x / T(2.L)) * T(0.25L);
}

template <typename T>
T fd2(T x, T h){ // Różnica progresywna dwupunktowa
	return (f(x + h) - f(x)) / h;
}

template <typename T>
T fd3(T x, T h){ // Różnica progresywna trzypunktowa
	return ( -1.5L * f(x) + 2.L * f(x + h) - 0.5L * f(x + 2.L * h) ) / h;
}

template <typename T>  // Różnica centralna dla pierwszej pochodnej
T cd(T x, T h){
	return (f(x + h) - f(x - h)) / (T(2.L) * h);
}

template <typename T>
T bd2(T x, T h){ // Różnica wsteczna dwupunktowa
	return (f(x) - f(x - h)) / h;
}

template <typename T>
T bd3(T x, T h){ // Różnica wsteczna trzypunktowa
	return ( 1.5L * f(x) - 2.L * f(x - h) + 0.5L * f(x - 2.L * h) ) / h;
}

template <typename T>
T c2d(T x, T h){ // Różnica centralna dla drugiej pochodnej
	return ( f(x - h) - 2.L * f(x) + f(x + h) ) / (h * h);
}

template <typename T>
T f2d(T x, T h){ // Różnica progresywna dla drugiej pochodnej
	return ( f(x) - 2.L * f(x + h) + f(x + 2.L * h) ) / (h * h);
}

template <typename T>
T b2d(T x, T h){ // Różnica wsteczna dla drugiej pochodnej
	return ( f(x - 2.L * h) - 2.L * f(x - h) + f(x) ) / (h * h);
}

template <typename T>
void calculate(T points[3], T &h){
	cout.precision(3);
	cout << setw(15) << defaultfloat << h;
	cout.precision(10);
	cout << scientific
		<< setw(20) << fabs(fd2(points[0], h) - df(points[0]))
		<< setw(20) << fabs(fd3(points[0], h) - df(points[0]))
		<< setw(20) << fabs(cd(points[1], h) - df(points[1]))
		<< setw(20) << fabs(bd2(points[2], h) - df(points[2]))
		<< setw(20) << fabs(bd3(points[2], h) - df(points[2]))
		<< setw(20) << fabs(f2d(points[0], h) - d2f(points[0]))
		<< setw(20) << fabs(c2d(points[1], h) - d2f(points[1]))
		<< setw(20) << fabs(b2d(points[2], h) - d2f(points[2]))
		<< endl;
}

void printHeader(){
	cout
		<< setw(15) << "h" 
		<< setw(20) << "f'(0) [2p]"
		<< setw(20) << "f'(0) [3p]"
		<< setw(20) << "f'(pi/2)"
		<< setw(20) << "f'(pi) [2p]"
		<< setw(20) << "f'(pi) [3p]"
		<< setw(20) << "f''(0)"
		<< setw(20) << "f''(pi/2)"
		<< setw(20) << "f''(pi)"
		<< endl;
}

int main(){
	double dPoints[3] = { 0.L, PI / 2.L, PI };
	float fPoints[3] = { 0.L, PI / 2.L, PI };

	printHeader();
	for (double h = 1; h > 1e-16; h /= 4){
		calculate(dPoints, h);
	}

	cout << endl;
	printHeader();
	for (float h = 1; h > 1e-8; h /= 4){
		calculate(fPoints, h);
	}
}