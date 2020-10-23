#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include "etc.hpp"
#include "analytical.hpp"
#include "cdm.hpp"
#include "cnm.hpp"

using namespace std;

int main(){
	int modes[3] = {true, true, true};
	double lambda, h, dt;
	int n, m;

	// Create a graph for error dependence on h parameter for maximum t
	if (modes[0]){ 
		// The biggest probed value of h
		double h_max = 1.L; 
		// The smallest probed value of h
		double h_min = 0.05L; 
		double errors[2][19];
		// Error vector index
		int ei; 

		// Classic Direct Method
		for (h = h_max, ei = 0; h > h_min; h -= h_min, ++ei){
			lambda = 0.4;
			// Calculate dt dynamically to match recommended lambda value
			dt = (lambda * square(h)) / D_param; 
			// Calculate matrix row count dynamically
			n = ((t_max - t_min) / dt) + 2; 
			// Calculate matrix column count dynamically
			m = ((x_max - x_min) / h) + 1; 

			cout << "Using CDM with lambda = " << lambda << endl 
				<< "Step parameters: h = " << h << ", dt = " << dt << endl 
				<< "Matrix size: " << n << " x " << m << endl << endl;

			double** CDMreference = analytical(n, m, dt, h);
			double** CDMresults = CDM(n, m, dt, h, lambda);

			errors[0][ei] = h;
			errors[1][ei] = findMaxError(CDMreference, CDMresults, n, m);
		}

		writeErrors(errors, "graphs/CDMhErrors");

		// Crank Nicolson Method
		for (h = h_max, ei = 0; h > h_min; h -= h_min, ++ei){
			// Calculate matrix column count dynamically
			m = ((x_max - x_min) / h) + 1; 
			// Matrix must be square for this method
			n = m; 
			// Calculate dt dynamically
			dt = (t_max - t_min) / (n - 2); 
			lambda = D_param * (dt / square(h));

			cout << "Using CNM with lambda = " << lambda << endl 
				<< "Step parameters: h = " << h << ", dt = " << dt << endl 
				<< "Matrix size: " << n << " x " << m << endl << endl;

			double** CNMreference = analytical(n, m, dt, h);
			double** CNMresults = CNM(n, m, dt, h, lambda);

			errors[0][ei] = h;
			errors[1][ei] = findMaxError(CNMreference, CNMresults, n, m);
		}

		writeErrors(errors, "graphs/CNMhErrors");

		// Theoretical accuracy row (reference line)
		for (int i = 0; i < 19; ++i){
			errors[1][i] = square(errors[0][i]);
		}

		writeErrors(errors, "graphs/errorReference");
	}

	// Create graphs for numerical methods vs analytical method comparison
	if (modes[1]){
		// Classic Direct Method
		h = 0.1;
		// Set lambda to recommended value
		lambda = 0.4; 
		// Calculate dt dynamically to match recommended lambda value
		dt = (lambda * square(h)) / D_param; 
		// Calculate matrix row count dynamically
		n = ((t_max - t_min) / dt) + 2; 
		// Calculate matrix column count dynamically
		m = ((x_max - x_min) / h) + 1; 

		cout << "Using CDM with lambda = " << lambda << endl 
			<< "Step parameters: h = " << h << ", dt = " << dt << endl 
			<< "Matrix size: " << n << " x " << m << endl << endl;

		double** CDMreference = analytical(n, m, dt, h);
		writeCSV(CDMreference, n, m, "graphs/CDMreference.csv");
		write3t(CDMreference, n, m, "graphs/CDMreference", h);

		double** CDMresults = CDM(n, m, dt, h, lambda);
		writeCSV(CDMresults, n, m, "graphs/CDMresults.csv");
		write3t(CDMresults, n, m, "graphs/CDMresults", h);

		writeErrorCSV(CDMreference, CDMresults, n, m, "graphs/CDMerrors.csv");
		
		// Crank Nicolson Method
		h = 0.1;
		// Set lambda to recommended value
		lambda = 1.0; 
		// Calculate dt dynamically to match recommended lambda value
		dt = (lambda * square(h)) / D_param; 
		// Calculate matrix row count dynamically
		n = ((t_max - t_min) / dt) + 2; 
		// Calculate matrix column count dynamically
		m = ((x_max - x_min) / h) + 1; 

		cout << "Using CNM with lambda = " << lambda << endl 
			<< "Step parameters: h = " << h << ", dt = " << dt << endl 
			<< "Matrix size: " << n << " x " << m << endl << endl;

		double** CNMreference = analytical(n, m, dt, h);
		writeCSV(CNMreference, n, m, "graphs/CNMreference.csv");
		write3t(CNMreference, n, m, "graphs/CNMreference", h);
		
		double** CNMresults = CNM(n, m, dt, h, lambda);
		writeCSV(CNMresults, n, m, "graphs/CNMresults.csv");
		write3t(CNMresults, n, m, "graphs/CNMresults", h);

		writeErrorCSV(CNMreference, CNMresults, n, m, "graphs/CNMerrors.csv");
	}

	// Create graphs for error dependence on t parameter
	if (modes[2]){ 
		// Classic Direct Method
		h = 0.1;
		// Set lambda to recommended value
		lambda = 0.4; 
		// Calculate dt dynamically to match recommended lambda value
		dt = (lambda * square(h)) / D_param; 
		// Calculate matrix row count dynamically
		n = ((t_max - t_min) / dt) + 2; 
		// Calculate matrix column count dynamically
		m = ((x_max - x_min) / h) + 1; 

		cout << "Using CDM with lambda = " << lambda << endl 
			<< "Step parameters: h = " << h << ", dt = " << dt << endl 
			<< "Matrix size: " << n << " x " << m << endl << endl;

		double** CDMreference = analytical(n, m, dt, h);
		double** CDMresults = CDM(n, m, dt, h, lambda);
		writeErrorChange(CDMreference, CDMresults, n, m, "graphs/CDMtErrors", dt);

		// Crank Nicolson Method
		h = 0.1;
		// Set lambda to recommended value
		lambda = 1.0;
		// Calculate dt dynamically to match recommended lambda value
		dt = (lambda * square(h)) / D_param; 
		// Calculate matrix row count dynamically
		n = ((t_max - t_min) / dt) + 2; 
		// Calculate matrix column count dynamically
		m = ((x_max - x_min) / h) + 1; 

		cout << "Using CNM with lambda = " << lambda << endl 
			<< "Step parameters: h = " << h << ", dt = " << dt << endl 
			<< "Matrix size: " << n << " x " << m << endl << endl;

		double** CNMreference = analytical(n, m, dt, h);
		double** CNMresults = CNM(n, m, dt, h, lambda);
		writeErrorChange(CDMreference, CDMresults, n, m, "graphs/CNMtErrors", dt);
	}
}