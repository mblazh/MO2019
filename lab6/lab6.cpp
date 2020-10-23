/*								*/
/* 		Algorytm Thomasa		*/
/*								*/

#include <iostream>
#include <math.h>
#include <iomanip>

using namespace std;

double L[5] = { 3.L / 4.L, 	7.L / 8.L, 	11.L / 12.L, 	15.L / 16.L, 	19.L / 20.L};
double D[6] = { 30.L, 		20.L, 		10.L, 			10.L, 			20.L, 			30.L};
double U[5] = { 2.L / 3.L, 	5.L / 6.L, 	9.L / 10.L, 	13.L / 14.L, 	17.L / 18.L};

double b[6] = {94.L / 3.L, 173.L / 4.L, 581.L / 20.L, -815.L / 28.L, -6301.L / 144.L, -319.L / 10.L};
double x[6], n[6], r[6];

void calculateA(){
	n[0] = D[0];
	
	for (int i = 1; i < 6; ++i){
		n[i] = D[i] - (L[i - 1] * U[i - 1]) / n[i - 1];
	}
}

void calculateB(){
	r[0] = b[0];

	for (int i = 1; i < 6; ++i){
		r[i] = b[i] - (L[i - 1] * r[i - 1]) / n[i - 1];
	}

	x[5] = r[5] / n[5];

	for (int i = 4; i >= 0; --i){
		x[i] = (r[i] - U[i] * x[i + 1]) / n[i];
	}
}

int main(){
	{
		cout << endl << "matrix:" << endl;

		for(int i = 0; i < 6; ++i){
			for(int j = 0; j < 6; ++j){
				if(i == j){
					cout << setw(15) << D[i];
				} else if(j == i - 1){
					cout << setw(15) << L[j];
				} else if(i == j - 1){
					cout << setw(15) << U[i];
				} else{
					cout << setw(15) << 0;
				}
			}

			cout << endl << endl;
		}
	}

	calculateA();
	calculateB();

	// {
	// 	cout << endl << "matrix:" << endl;

	// 	for(int i = 0; i < 6; ++i){
	// 		for(int j = 0; j < 6; ++j){
	// 			if(i == j){
	// 				cout << setw(15) << n[i];
	// 			} else if(j == i - 1){
	// 				cout << setw(15) << 0;
	// 			} else if(i == j - 1){
	// 				cout << setw(15) << U[i];
	// 			} else{
	// 				cout << setw(15) << 0;
	// 			}
	// 		}

	// 		cout << endl << endl;
	// 	}
	// }

	{ // Print vector x
		cout<< "[x]:" << endl;
		
		for(int i = 0; i < 6; ++i){
			cout << setw(10) << x[i];
		}

		cout << endl;
	}
}