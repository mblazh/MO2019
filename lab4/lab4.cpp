#include <iostream>
#include <iomanip>
#include <math.h>

#define MAX_ITERATIONS 10
#define TOLX 1e-8L
#define TOLF 1e-8L

typedef double (*functions) (double *);

// Funkcje
double f0(double x[3]) { return x[0] * x[0] + x[1] * x[1] + x[2] * x[2] - 2; }
double f1(double x[3]) { return x[0] * x[0] + x[1] * x[1] - 1; }
double f2(double x[3]) { return x[0] * x[0] - x[1]; }
functions f[3] = { f0, f1, f2 };

// Pochodne
double df00(double x[3]) { return 2.L * x[0]; }
double df01(double x[3]) { return 2.L * x[1]; }
double df02(double x[3]) { return 2.L * x[2]; }

double df10(double x[3]) { return 2.L * x[0]; }
double df11(double x[3]) { return 2.L * x[1]; }
double df12(double x[3]) { return 0.L; }

double df20(double x[3]) { return 2.L * x[0]; }
double df21(double x[3]) { return -1.L; }
double df22(double x[3]) { return 0.L; }

functions df[3][3] = {
	{ df00, df01, df02 },
	{ df10, df11, df12 },
	{ df20, df21, df22 }
};

double x[3] = { 2.L, 2.L, 2.L };
double lastx[3] = { 0.L, 0.L, 0.L };

int main(){
	using namespace std;

	cout << setw(15) << "x" << setw(15) << "estymator x" 
			<< setw(15) << "reziduum x"
			<< setw(15) << "y" << setw(15) << "estymator y"
			<< setw(15) << "reziduum y" 
			<< setw(15) << "z" << setw(15) << "estymator z" 
			<< setw(15) << "reziduum z" << endl
			<< "====================================================================================================================================" << endl
			<< setw(15) << x[0] << setw(30) << x[1] << setw(30) << x[2] << endl;

	for (int ic = 0; ic < MAX_ITERATIONS; ++ic) { // Arbitralne ograniczenie na liczbę iteracji
		double fx[3];

		for (int i = 0; i < 3; i++) {
			fx[i] = f[i](x);
		}

		double dfx[3][3];

		for (int i = 0; i < 3; ++i){
			for (int j = 0; j < 3; ++j){
				dfx[i][j] = df[i][j](x);
			}
		}

		double d[3];
		double max;
		int k, index;
		k = 0;

		// Eliminacja Gaussa
		while (k < 3) {
			// Poszukiwanie rzędu z maksymalnym dfx[i][k]
			max = abs(dfx[k][k]);
			index = k;

			for (int i = k + 1; i < 3; i++) {
				if (abs(dfx[i][k]) > max){
					max = abs(dfx[i][k]);
					index = i;
				}
			}

			if (max < TOLX) break;

			for (int j = 0; j < 3; j++) {
				double temp = dfx[k][j];
				dfx[k][j] = dfx[index][j];
				dfx[index][j] = temp;
			}

			double temp = fx[k];
			fx[k] = fx[index];
			fx[index] = temp;

			for (int i = k; i < 3; i++) { // Od równan i-tych odejmujemy równanie pierwsze pomnożone przez a[i][1]/a[1][1] 
				double temp = dfx[i][k];

				if (abs(temp) < TOLX){ // Dla zerowego koeficjenta
					continue;
				}

				for (int j = 0; j < 3; j++){
					dfx[i][j] = dfx[i][j] / temp;
				}
				
				fx[i] = fx[i] / temp;
				
				if (i == k){ // Nie robimy odejmowania od samego siebie
					continue;
				}
				
				for (int j = 0; j < 3; j++){
					dfx[i][j] = dfx[i][j] - dfx[k][j];
				}

				fx[i] = fx[i] - fx[k];
			}

			k++;
		}

		// Podstawienie wsteczne
		for (k = 3 - 1; k >= 0; k--){
			d[k] = fx[k];

			for (int i = 0; i < k; i++){
				fx[i] = fx[i] - dfx[i][k] * d[k];
			}
		}

		// End eliminacja Gaussa

		for (int i = 0; i < 3; ++i){
			lastx[i] = x[i];
			x[i] = x[i] - d[i];
		}

		cout << setw(15) << x[0] << setw(15) << fabs(x[0] - lastx[0]) << setw(15) << fabs(fx[0]) 
			<< setw(15) << x[1] << setw(15) << fabs(x[1] - lastx[1]) << setw(15) << fabs(fx[1])
			<< setw(15) << x[2] << setw(15) << fabs(x[2] - lastx[2]) << setw(15) << fabs(fx[2]) << endl;

		if(fabs(x[0] - lastx[0]) <= TOLX && fabs(x[1] - lastx[1]) <= TOLX && fabs(x[2] - lastx[2]) <= TOLX){ // Kryterium dokładności wyznaczenia Xn
			if (fabs(fx[0]) <= TOLF && fabs(fx[1]) <= TOLF && fabs(fx[2]) <= TOLF){ // Kryterium wiarygodności Xn jako przybliżenia pierwiastka
				break;
			}
		}
	}

	return 0;
}
