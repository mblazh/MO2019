#define PI 3.14159265359

// Given parameters
#define t_min   0.L
#define t_max   2.L
#define b_param 1.L
#define D_param 1.L

// x bounds
const double x_max = ceil(b_param + 6 * sqrt(D_param * t_max));
const double x_min = -x_max;

// Return x raised to 2 power
double square(double x){ 
	return x * x;
}

// Create blank n by m matrix
double **createBlankMatrix(int n, int m){ 
	double** matrix = new double*[n];
	
	for (int i = 0; i < n; ++i) {
		matrix[i] = new double[m];
	}

	return matrix;
}

// Compare two matrices and find the largest error in the last row
double findMaxError(double **reference, double **results, int n, int m){ 
	double max = 0.L;

	for (int i = 0; i < m; ++i) {
		double error = fabs(reference[n - 1][i] - results[n - 1][i]);
		
		if (error > max){
			max = error;
		}
	}

	return max;
}

// Write errors to a file in logarithmic scale
void writeErrors(double errors[2][19], std::string filename) { 
	std::fstream output = std::fstream(filename.c_str(), std::ios::out);

	for (int i = 0; i < 19; ++i) {
		output << log10(errors[0][i]) << "\t" << log10(errors[1][i]) << std::endl;
	}

	output.close();
}

// Write values and a scale to 3 files
void write3t(double** matrix, int n, int m, std::string filename, double h) { 
	std::fstream output;

	for (int k = 0; k < n; ++k) {
		// Create different files for the lowest t, the highest t and a middle
		if (k == 1 || k == ceil(n / 2.L) || k == n - 1) { 
			output = std::fstream(filename.c_str() + std::string("_t") + std::to_string(k), std::ios::out);

			for (int i = 0; i < m; ++i) {
				output << x_min + i * h << "\t" << matrix[k][i] << std::endl;
			}
		}
	}

	output.close();
}

// Write changes in maximum error value to file
void writeErrorChange(double** reference, double **results, int n, int m, std::string filename, double dt) { 
	std::fstream output = std::fstream(filename.c_str(), std::ios::out);

	for (int k = 0; k < n; ++k) {
		double max = 0.L;

		// Search maximum error in each row
		for (int i = 0; i < m; ++i) { 
			double error = fabs(reference[k][i] - results[k][i]);
			
			if (error > max){
				max = error;
			}
		}

		output << t_min + k * dt << "\t" << max << std::endl;
	}

	output.close();
}

// Write initial and boundary values
void writeGivenValues(double **matrix, int n, int m, double h){ 
	// Write initial values
	double x = x_min;
	for (int i = 0; i < m; ++i, x += h) {
		if (fabs(x) < b_param) {
			matrix[0][i] = 1.L;
		} else {
			matrix[0][i] = 0.L;
		}
	}

	// Write boundary values
	for (int i = 0; i < n; ++i) {
		matrix[i][0] = 0.L;
		matrix[i][m - 1] = 0.L;
	}
}

// Write matrix to csv file
void writeCSV(double **matrix, int n, int m, std::string filename){ 
	std::fstream output = std::fstream(filename.c_str(), std::ios::out);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			output << matrix[i][j] << ",";
		}

		output << std::endl;
	}

	output.close();
}

// Write difference between two matrices to csv file
void writeErrorCSV(double **matrixA, double **matrixB, int n, int m, std::string filename){ 
	std::fstream output = std::fstream(filename.c_str(), std::ios::out);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			output << fabs(matrixA[i][j] - matrixB[i][j]) << ",";
		}

		output << std::endl;
	}

	output.close();
}