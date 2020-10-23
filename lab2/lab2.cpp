/*								*/
/* 		Szereg Taylora		    */
/*								*/

#include <iostream>
#include <math.h>
#include <iomanip>

double f1(double x){
	return (1.L - exp(-x)) / x;
}

double f2(double x){
	long double result = 1;
	long double sign = -1;
	long double step = 1;

	for (int i = 2; i < 1000; ++i){
		step = step * (x / i);
		result += sign * step;
		sign = -sign;
	}

	return result;
}

int main(){
	using namespace std; 

	cout 
		<< setw(20) << "x" 
		<< setw(40) << "f1(x)" 
		<< setw(20) << "bl. wzgl. f1(x)" 
		<< setw(40) << "f2(x)"
		<< setw(20) << "bl. wzgl. f2(x)"
		<< setw(40) << "wynik ostateczny"
		<< setw(20) << "bl. wzgl. wyn. ost." 
		<< endl
		<< "===================================================================================================="
		<< "====================================================================================================" 
		<< endl;

	FILE* file = fopen("oneminexp_ref.txt", "r");
	double log10x, x, oneminexp;

	int c = 0;
	while (!feof(file)){
		fscanf (file, "%le", &log10x);
		fscanf (file, "%le", &x);
		fscanf (file, "%le", &oneminexp);

		if(c % 10 == 0){
			double f1value = f1(x);
			double f2value = f2(x);
			double f1diff = fabs(oneminexp - f1value) / oneminexp;
			double f2diff = fabs(oneminexp - f2value) / oneminexp;

			cout 
				<< setw(20) << x 
				<< setw(40) << f1value 
				<< setw(20) << f1diff 
				<< setw(40) << f2value 
				<< setw(20) << f2diff 
				<< setw(40) << (x < 5 ? f2value : f1value) 
				<< setw(20) << (x < 5 ? f2diff : f1diff) 
				<< endl;
		}

		c++;
	}

	fclose (file);
}