#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

#define a 0.L
#define b 0.5L
#define dt 1e-8

double square(double x){
	return x * x;
}

double f(double tk, double yk){
	return ((10.L * square(tk) + 20.L) / (square(tk) + 1)) * (yk - 1.L);
}

double secant(double (*func)(double, double, double), double& tk, double& yk) { 
	double x1 = a;
	double x2 = b;
	double xm, result; 
	
	if ((*func)(tk, yk, x1) * (*func)(tk, yk, x2) < 0){ 
		for (int ic = 0; ic < 100; ++ic) { // Arbitralne ograniczenie na liczbę iteracji 
			result = (x1 * (*func)(tk, yk, x2) - x2 * (*func)(tk, yk, x1)) / ((*func)(tk, yk, x2) - (*func)(tk, yk, x1)); 

			x1 = x2;
			x2 = result;

			xm = (x1 * (*func)(tk, yk, x2) - x2 * (*func)(tk, yk, x1)) / ((*func)(tk, yk, x2) - (*func)(tk, yk, x1));

			if (fabs(result - xm) <= dt && fabs((*func)(tk, yk, result)) <= dt){ 
				break; // Kryterium wiarygodności Xn jako przybliżenia pierwiastka i kryterium dokładności wyznaczenia Xn
			}
		}
	}

	return result;
}

int main(){
	double yk[] = { 0.L, 0.L, 0.L };
	int c = 0;

	cout << setw(10) << "t" << setw(30) << "BME" << setw(30) << "PME" << setw(30) << "PMT" << endl;
	cout << "====================================================================================================" << endl;

	for (double tk = a; tk <= b; tk += dt, c++){
		if(c % int(0.025 / dt) == 0){
			cout.precision(3);
			cout << defaultfloat << setw(10) << tk;
			cout.precision(17);
			cout << scientific << setw(30) << yk[0] << setw(30) << yk[1] << setw(30) << yk[2] << endl;
		}

		yk[0] -= f(tk, yk[0]) * dt;
		yk[1] = secant([](double tk, double yk, double yk1) { return (yk1 - yk) / dt + f(tk + dt, yk1); }, tk, yk[1]);
		yk[2] = secant([](double tk, double yk, double yk1) { return (yk1 - yk) / dt + (f(tk, yk) + f(tk + dt, yk1)) / 2.0; }, tk, yk[2]);
	}
}
