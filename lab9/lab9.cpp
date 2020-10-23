/*								*/
/* 		RR zwyczajne 2 rzędu		*/
/*								*/

#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits.h>

using namespace std;

#define end 	0.78539816339L
#define h 	1e-3

int matrixSize = 1 + end / h;
double squarehMin1 = 1.L / (h * h);
double oneThird = 1.L / 3.L;

/* Variables for Thomas algorithm */
double *L = new double[matrixSize - 1];
double *D = new double[matrixSize];
double *U = new double[matrixSize - 1];
double *b = new double[matrixSize];
double *y = new double[matrixSize];
double *n = new double[matrixSize];
double *r = new double[matrixSize];

double x(int i){ // Returns i-th x
	return i * h;
}

double analytic(double x){
	return (2.L * x * cos(2.L * x) + 2.L * sin(2.L * x) - log(2.L) * sin(2.L * x) - 2.L * log(cos(x)) * sin(2.L * x)) / 4.L;
}

void fillMatrix(bool numerow){
	D[0] = 1.L;
	U[0] = 0.L;
	L[matrixSize - 2] = 0.L;
	D[matrixSize - 1] = 1.L;
	
	b[0] = analytic(x(0));
	b[matrixSize - 1] = analytic(x(matrixSize - 1));

	for (int i = 1; i < matrixSize - 1; ++i){
		if (numerow == true){
			L[i - 1] = squarehMin1 + (1.L/12.L) * 4.L;
			D[i] = -2.L * (squarehMin1 - (5.L/12.L) * 4.L);
			U[i] = squarehMin1 + (1.L/12.L) * 4.L;
			b[i] = - (1.L / 12.L) * tan(x(i - 1)) - (10.L / 12.L) * tan(x(i)) - (1.L / 12.L) * tan(x(i + 1));
		} else{
			L[i - 1] = squarehMin1;
			D[i] = -2.L * squarehMin1 + 4.L;
			U[i] = squarehMin1;
			b[i] = -tan(x(i));
		}
	}
}

void calculateA(){
	n[0] = D[0];
	
	for (int i = 1; i < matrixSize; ++i){
		n[i] = D[i] - (L[i - 1] * U[i - 1]) / n[i - 1];
	}
}

void calculateB(){
	r[0] = b[0];

	for (int i = 1; i < matrixSize; ++i){
		r[i] = b[i] - (L[i - 1] * r[i - 1]) / n[i - 1];
	}

	y[matrixSize - 1] = r[matrixSize - 1] / n[matrixSize - 1];

	for (int i = matrixSize - 2; i >= 0; --i){
		y[i] = (r[i] - U[i] * y[i + 1]) / n[i];
	}
}

void printY(){
	double maxErr = 0.L;
	// cout << setw(10) << "x" << setw(30) << "y(i)" << setw(30) << "yi" << setw(30) << "Blad" << endl;
	
	for(int i = 0; i < matrixSize; ++i){
		double err = abs(analytic(x(i)) - y[i]);
		if(err > maxErr){
			maxErr = err;
		}

		// if(i % int(0.05 / h) == 0 || i == matrixSize - 1){
		// 	cout.precision(3);
		// 	cout << setw(10) << defaultfloat << x(i);
		// 	cout.precision(17);
		// 	cout << setw(30) << scientific << analytic(x(i)) << setw(30) << y[i] << setw(30) << err << endl;
		// }
	}

	cout.precision(17);
	cout << "Maksymalny błąd: " << scientific << maxErr << endl;
}

int main(){
	cout << "Z dyskretyzacją Numerowa:" << endl;
	fillMatrix(true);
	calculateA();
	calculateB();
	printY();

	cout << endl << "Bez dyskretyzacji Numerowa:" << endl;
	fillMatrix(false);
	calculateA();
	calculateB();
	printY();
	// {
	// 	cout << endl << "matrix:" << endl;

	// 	for(int i = 0; i < matrixSize; ++i){
	// 		for(int j = 0; j < matrixSize; ++j){
	// 			if(i == j){
	// 				cout << setw(10) << D[i];
	// 			} else if(j == i - 1){
	// 				cout << setw(10) << L[i - 1];
	// 			} else if(j == i + 1){
	// 				cout << setw(10) << U[i];
	// 			} else{
	// 				cout << setw(10) << 0;
	// 			}
	// 		}

	// 		cout << endl << endl;
	// 	}
	// }
}