#include <iostream>
#include <math.h>
#include <iomanip>

#define MAX_ITERATIONS 30
#define LOW -0.3L
#define HIGH 0.6L
#define TOLX 1e-8L
#define TOLF 1e-8L

double f1(double x) {
	double tmp = sin(x / 4.L);
	return tmp * tmp - x;
}

double f2(double x) {
	return tan(2.L * x) - x - 1.L;
}

double f1Deriv(double x) {
	return sin(x / 4.L) * cos(x / 4.L) / 2.L - 1.L;
}

double f2Deriv(double x) {
	double tmp = cos(2.L * x);
	return 2.L / (tmp * tmp) - 1.L;
}

double picard(double (*func)(double), double (*funcD)(double)) {
	double result = HIGH;

	for (int ic = 0; ic < MAX_ITERATIONS; ++ic) { // Arbitralne ograniczenie na liczbę iteracji
		if (fabs((*func)(result)) <= TOLX && ic < MAX_ITERATIONS - 1){ // Kryterium dokładności wyznaczenia Xn
			return result;
		}

		if (fabs((*func)(result) + result) <= TOLF){ // Kryterium wiarygodności Xn jako przybliżenia pierwiastka
			return result;
		}

		std::cout << "\t\t" << std::setw(15) << ic << std::setw(15) << result << std::setw(15) << fabs((*func)(result)) << std::setw(15) << fabs((*func)(result) + result) << std::endl;

		result = fabs((*func)(result) + result);
	}

	if (fabs((*funcD)(result)) > 1){
		std::cout << "\t\t\tMetoda jest rozbiezna!" << std::endl;
	}

	return result;	
}

double bisection(double (*func)(double)) {
	double a = LOW; 
	double b = HIGH;

	if ((*func)(a) * (*func)(b) >= 0){ // Bład. Metodę nie można stosować
		return 999; 
	}

	double result = a;
	for (int ic = 0; ic < MAX_ITERATIONS; ++ic) { // Arbitralne ograniczenie na liczbę iteracji 
		result = (a + b) / 2.L;

		if (fabs((b - a) / 2.L) <= TOLX){ // Kryterium dokładności wyznaczenia Xn
			break;
		}

		if (fabs((*func)(result)) <= TOLF){ // Kryterium wiarygodności Xn jako przybliżenia pierwiastka
			break;
		}
		
		std::cout << "\t\t" << std::setw(15) << ic << std::setw(15) << result << std::setw(15) << fabs((b - a) / 2.L) << std::setw(15) << fabs((*func)(result)) << std::endl;

		if ((*func)(result) * (*func)(a) < 0){
			b = result;
		} else{
			a = result;
		}
	}

	return result; 
}

double newton(double (*func)(double), double (*derivFunc)(double)) {
	double result = HIGH;
	double prev = LOW;
	double h = (*func)(result) / (*derivFunc)(result); 
	
	for (int ic = 0; ic < MAX_ITERATIONS; ++ic) { // Arbitralne ograniczenie na liczbę iteracji 
		if (fabs(result - prev) <= TOLX){ // Kryterium dokładności wyznaczenia Xn
			break;
		}

		if (fabs((*func)(result)) <= TOLF){ // Kryterium wiarygodności Xn jako przybliżenia pierwiastka
			break;
		}

		h = (*func)(result) / (*derivFunc)(result); 

		std::cout << "\t\t" << std::setw(15) << ic << std::setw(15) << result << std::setw(15) << fabs(result - LOW) << std::setw(15) << fabs((*func)(result)) << std::endl;

		prev = result;
		result = result - h;
	}

	return result;
}

double secant(double (*func)(double)) { 
	double x1 = LOW;
	double x2 = HIGH;
	double xm, result; 
	
	if ((*func)(x1) * (*func)(x2) < 0){ 
		for (int ic = 0; ic < MAX_ITERATIONS; ++ic) { // Arbitralne ograniczenie na liczbę iteracji 
			result = (x1 * (*func)(x2) - x2 * (*func)(x1)) / ((*func)(x2) - (*func)(x1)); 

			x1 = x2;
			x2 = result;

			xm = (x1 * (*func)(x2) - x2 * (*func)(x1)) / ((*func)(x2) - (*func)(x1));

			std::cout << "\t\t" << std::setw(15) << ic << std::setw(15) << result << std::setw(15) << fabs(result - xm) << std::setw(15) << fabs((*func)(result)) << std::endl;

			if (fabs(result - xm) <= TOLX){ // Kryterium dokładności wyznaczenia Xn
				break;
			}

			if (fabs((*func)(result)) <= TOLF){ // Kryterium wiarygodności Xn jako przybliżenia pierwiastka
				break;
			}
		}
	}

	return result;
}

void printHeader(){
	using namespace std;
	cout << "\t\t" << setw(15) << "iteracja" << setw(15) << "wynik" << setw(15) << "estymator" << setw(15) << "reziduum" << endl;
}

int main(){
	using namespace std;

	cout << "Metoda Picarda:\n\tObliczenia dla f1:\n"; 
	picard(f1, f2Deriv);
	printHeader();
	cout << "\n\tObliczenia dla f2:\n";
	picard(f2, f2Deriv);
	printHeader();

	cout << "\nMetoda bisekcji:\n\tObliczenia dla f1:\n"; 
	bisection(f1);
	printHeader();
	cout << "\n\tObliczenia dla f2:\n";
	bisection(f2);
	printHeader();
	
	cout << "\nMetoda Newtona:\n\tObliczenia dla f1:\n"; 
	newton(f1, f1Deriv);
	printHeader();
	cout << endl << "\tObliczenia dla f2:\n";
	newton(f2, f2Deriv);
	printHeader();

	cout << "\nMetoda siecznych:\n\tObliczenia dla f1:\n"; 
	secant(f1);
	printHeader();
	cout << "\n\tObliczenia dla f2:\n";
	secant(f2);
	printHeader();
	
	cout << endl;

	return 0;
}