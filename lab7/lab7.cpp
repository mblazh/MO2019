/*								*/
/* 		Uklady rownan	    	*/
/*								*/

#include <iostream>
#include <iomanip>
#include <math.h>
#include "lab7.hpp"

using namespace std;

#define MAX_ITERATIONS 50
#define TOLX 1e-8L
#define TOLF 1e-8L
#define N 4

double A[4][4] = {
	{ 100.L, 	1.L, 	-2.L, 	3.L 		},
	{ 4.L, 		300.L, 	-5.L, 	6.L 	},
	{ 7.L, 		-8.L, 	400.L, 	9.L 	},
	{ -10.L, 	11.L, 	-12.L, 	200.L 	}
};

double b[4] = { 395.L, 603.L, -415.L, -606.L };

double residuum(double *x){
	double Ax[4];

	for (int i = 0; i < 4; ++i){
		Ax[i] = 0;

		for (int j = 0; j < 4; ++j){
			Ax[i] += A[i][j] * x[j];
		}
	}

	double residuum = 0;

	for (int i = 0; i < 4; ++i){
		double resi = fabs(b[i] - Ax[i]);
		if(resi > residuum){
			residuum = resi;
		}
	}

	return residuum;
}

void Jacobi(){
	double x[4] = { 1.L, 1.L, 1.L, 1.L };
	double M[4][4];
	double c[4];
	double Mx[4];
	double LplusU[4][4];
	double Dmin1[4][4];

	for (int i = 0; i < 4; ++i){ // Obliczanie L+U i D^-1
		for (int j = 0; j < 4; ++j){
			if (i == j){
				LplusU[i][j] = 0;
				Dmin1[i][j] = 1.L / A[i][j];
			} else{
				LplusU[i][j] = A[i][j];
				Dmin1[i][j] = 0;
			}
		}
	}
	
	for(int i = 0; i < 4; ++i){ // Obliczanie M
		for(int j = 0; j < 4; ++j){
			M[i][j] = 0;

			for(int k = 0; k < 4; ++k){
				M[i][j] -= Dmin1[i][k] * LplusU[k][j];
			}
		}
	}

	for (int i = 0; i < 4; ++i){ // Obliczanie c
		c[i] = 0;

		for (int j = 0; j < 4; ++j){
			c[i] += Dmin1[i][j] * b[j];
		}
	}

	double oldx[4] = { 1.L, 1.L, 1.L, 1.L };

	for (int n = 0; n < MAX_ITERATIONS; ++n){
		for (int i = 0; i < 4; ++i){  // Mnożenie M przez x
			Mx[i] = 0;

			for (int j = 0; j < 4; ++j){
				Mx[i] += M[i][j] * x[j];
			}
		}

		for (int i = 0; i < 4; ++i){ // Iteracja
			x[i] = Mx[i] + c[i];
		}

		for(int i = 0; i < 4; ++i){ // Wynik
			cout << setw(20) << x[i];
		}

		double res = residuum(x);

		cout 
			<< setw(20) << (fabs(x[0] - oldx[0]) + fabs(x[1] - oldx[1]) + fabs(x[2] - oldx[2]) + fabs(x[3] - oldx[3])) / 4
			<< setw(20) << res << endl;

		if (fabs(x[0] - oldx[0]) < TOLX && fabs(x[1] - oldx[1]) < TOLX && fabs(x[2] - oldx[2]) < TOLX && fabs(x[3] - oldx[3]) < TOLX){
			if (res < TOLF){
				break;
			}
		}

		for (int i = 0; i < 4; ++i){
			oldx[i] = x[i];
		}
	}
}

void GaussSeidel(){
	double x[4] = { 1.L, 1.L, 1.L, 1.L };
	double UplusD[4][4];
	double minL[4][4];
	double minLx[4];
	double minLxplusb[4];

	for (int i = 0; i < 4; ++i){ // Obliczanie U + D i -L
		for (int j = 0; j < 4; ++j){
			if (i <= j){
				UplusD[i][j] = A[i][j];
				minL[i][j] = 0;
			} else{
				UplusD[i][j] = 0;
				minL[i][j] = -A[i][j];
			}
		}
	}

	double oldx[4] = { 1.L, 1.L, 1.L, 1.L };

	for (int n = 0; n < MAX_ITERATIONS; ++n){
		for (int i = 0; i < 4; ++i){  // Mnożenie -L przez x
			minLx[i] = 0;

			for (int j = 0; j < 4; ++j){
				minLx[i] += minL[i][j] * x[j];
			}
		}

		for (int i = 0; i < 4; ++i){
			minLxplusb[i] = minLx[i] + b[i];
		}

		for(int i = 3; i >= 0; --i){ // Podstawienie wsteczne
			x[i] = minLxplusb[i];

			for(int j = i + 1; j < 4; ++j){
				x[i] -= UplusD[i][j] * x[j];
			}

			x[i] /= UplusD[i][i];
		}

		for(int i = 0; i < 4; ++i){ // Wynik
			cout << setw(20) << x[i];
		}

		double res = residuum(x);

		cout 
			<< setw(20) << (fabs(x[0] - oldx[0]) + fabs(x[1] - oldx[1]) + fabs(x[2] - oldx[2]) + fabs(x[3] - oldx[3])) / 4
			<< setw(20) << res << endl;

		if (fabs(x[0] - oldx[0]) < TOLX && fabs(x[1] - oldx[1]) < TOLX && fabs(x[2] - oldx[2]) < TOLX && fabs(x[3] - oldx[3]) < TOLX){
			if (res < TOLF){
				break;
			}
		}

		for (int i = 0; i < 4; ++i){
			oldx[i] = x[i];
		}
	}
}

void SOR(double** A, double* b, double* x){
	double omega = 0.5;
	double y[N + 1];
	double sum;
	double diagonal;

	for (int k = 0; k < MAX_ITERATIONS; k++) {
		for (int i = 1; i <= N; ++i){
			y[i] = x[i];
		}
		
		for (int i = 1; i <= N; ++i) {
			sum = b[i];
			diagonal = A[i][i];
			
			for (int j = 1; j <= i-1; ++j) {
				sum -= A[i][j] * x[j];
			}

			for (int j = i+1; j <= N; ++j) {
				sum -= A[i][j] * x[j];
			}
			
			x[i] = sum / diagonal;
			x[i] = omega * x[i] + (1.0 - omega) * y[i];
		}
		
		for(int i = 1; i <= N; ++i){ // Wynik
			cout << setw(20) << x[i];
		}

		double estimator = max(subtractArrays(x, y));
		cout << setw(20) << estimator;

		double residuum = calculateResiduum(A, b, x);
		cout << setw(20) << residuum << endl;

		if (estimator < TOLX && residuum < TOLF) {
			return;
		}
	}
}

int main(){
	cout 
		<< setw(20) << "x[0]"
		<< setw(20) << "x[1]"
		<< setw(20) << "x[2]"
		<< setw(20) << "x[3]"
		<< setw(20) << "estymator bledu"
		<< setw(20) << "residuum"
		<< endl;
		
	cout << "Metoda Jacobi:" << endl;
	Jacobi();

	cout << endl << "Metoda Gaussa-Seidela:" << endl;
	GaussSeidel();

	cout << "Metoda SOR:" << endl;
	SORWrapper(SOR);
}