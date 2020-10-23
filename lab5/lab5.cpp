/*								*/
/* 		Dekompozycja LU	    	*/
/*								*/

#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;

double A[4][4] = {
	{ 1.L, 		20.L, 		-30.L, 		-4.L },
	{ 4.L, 		20.L, 		-6.L, 		50.L },
	{ 9.L, 		-18.L, 		12.L, 		-11.L },
	{ 16.L, 	-15.L, 		14.L, 		130.L }
};

double b[4] = {
	0.L, 
	114.L, 
	-5.L, 
	177.L
};

int order[4][2];

double L[4][4], U[4][4];
double x[4], y[4];

void decompose(){
	{
		cout << endl << "[A]:" << endl;

		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < 4; ++j){
				cout << setw(10) << A[i][j];
			}

			cout << endl << endl;
		}
	}

	int orderI = 0;

	for (int j = 0; j < 4; ++j){
		double max = 0;
		
		for (int i = j; i < 4; ++i){
			if (fabs(A[i][j]) > fabs(A[j][j])){
				swap(A[i], A[j]);
				order[orderI][0] = i;
				order[orderI][1] = j;
				++orderI;
			}
		}
	}

	{
		cout << endl << "[A]:" << endl;

		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < 4; ++j){
				cout << setw(10) << A[i][j];
			}

			cout << endl << endl;
		}
	}

	for(int j = 0; j < 4; ++j){
		for(int i = 0; i < 4; ++i){
			if(i <= j){ // Top right corner
				U[i][j] = A[i][j];
				
				for(int k = 0; k < i; ++k){
					U[i][j] -= L[i][k] * U[k][j];
				}

				L[i][j] = i == j ? 1 : 0;
			} else { // Bottom left corner
				L[i][j] = A[i][j];
				
				for(int k = 0; k < j; ++k){
					L[i][j] -= L[i][k] * U[k][j];
				}

				L[i][j] /= U[j][j];
				U[i][j] = 0;
			}
		}
	}

	{ // Print matrix L
		cout << "[L]:" << endl;

		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < 4; ++j){
				cout << setw(10) << L[i][j];
			}

			cout << endl;
		}
	}

	{ // Print matrix U
		cout << endl << "[U]:" << endl;

		for(int i = 0; i < 4; ++i){
			for(int j = 0; j < 4; ++j){
				cout << setw(10) << U[i][j];
			}

			cout << endl;
		}
	}
}

void calculate(){
	{
		cout << endl << "[b]:" << endl;
		
		for(int i = 0; i < 4; ++i){
			cout << setw(10) << b[i];
		}

		cout << endl;
	}

	for (int i = 0; i < 4; ++i){
		std::swap(b[order[i][0]], b[order[i][1]]);
	}

	{
		cout << endl << "[b]:" << endl;
		
		for(int i = 0; i < 4; ++i){
			cout << setw(10) << b[i];
		}

		cout << endl;
	}

	for(int i = 0; i < 4; ++i){ // Ly = b, stąd wyliczamy y
		y[i] = b[i];

		for(int j = 0; j < i; ++j){
			y[i] -= L[i][j] * y[j];
		}
	}

	
	{ // Print vector y
		cout << endl << "[y]:" << endl;
		
		for(int i = 0; i < 4; ++i){
			cout << setw(10) << y[i];
		}

		cout << endl;
	}

	for(int i = 3; i >= 0; --i){ // Ux = y, stąd wyliczamy x
		x[i] = y[i];

		for(int j = i + 1; j < 4; ++j){
			x[i] -= U[i][j] * x[j];
		}

		x[i] /= U[i][i];
	}

	{ // Print vector x
		cout << endl << "[x]:" << endl;
			
		for(int i = 0; i < 4; ++i){
			cout << setw(10) << x[i];
		}

		cout << endl;
	}
}

int main(){
	decompose(); // Matrix A decomposition
	calculate(); // Calculations using vector b 

	cout << endl;
}