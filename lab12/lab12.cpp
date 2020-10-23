#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#define PI 3.14159265359

using namespace std;

#define a -1
#define b 1
#define dx 1e-3
#define n 14

double f(double x){
	return x / (1.L + 20.L * x * x * x * x);
}

double x[n];

void chooseX(bool chebyshewMode){
	if (chebyshewMode){
		double curly;
		for (int i = 0; i < n; ++i){
			curly = cos(((2.L * i + 1.L) / (2.L * n + 2.L)) * PI);
			x[i] = (b + a) / 2.L + ((b - a) / 2.L) * curly;
	 	}
	} else{
		for (int i = 0; i < n; ++i){
			x[i] = a + i * ((b - a) / (n - 1.L));
	 	}
	}
}

void newtons(string graphNumber){
	double c[n][n];

	for (int variable = 0; variable < n; ++variable){ // Fill rank 0
		c[variable][0] = f(x[variable]);
	}

	for (int rank = 1; rank < n; ++rank){
		for (int variable = 0; variable < n - rank; ++variable){
			c[variable][rank] = (c[variable + 1][rank - 1] - c[variable][rank - 1]) / (x[rank + variable] - x[variable]);
		}
	}	

	fstream output = fstream(string("graphs/newtonsPoints") + graphNumber, ios::out);

	for (int i = 0; i < n; ++i){
		output << x[i] << "\t" << f(x[i]) << endl;
	}

	output = fstream(string("graphs/newtons") + graphNumber, ios::out);
	double value;

	for (double ix = a; ix <= b; ix += dx){
		value = c[0][n - 1];
		for (int rank = n - 1; rank > 0; --rank){
			value *= (ix - x[rank - 1]);
			value += c[0][rank - 1];
		}

		output << ix << "\t" << value << endl;
	}

	output.close();
}

void writeReference(){
	fstream output = fstream(string("graphs/reference"), ios::out);

	for (double ix = a; ix <= b; ix += dx){
		output << ix << "\t" << f(ix) << endl;
	}

	output.close();
}

int main(){
	chooseX(false);
	newtons("0");

	chooseX(true);
	newtons("1");

	writeReference();
}