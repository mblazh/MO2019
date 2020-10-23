// LU Decomposition
void decompose(double **A, double **L, double **U, int n){ 
	for(int j = 0; j < n; ++j){
		for(int i = 0; i < n; ++i){
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
}

// Calculate y from [Ly = b]
void calculateY(double **L, double *y, double *b, int n){ 
	for(int i = 0; i < n; ++i){
		y[i] = b[i];

		for(int j = 0; j < i; ++j){
			y[i] -= L[i][j] * y[j];
		}
	}
}

// Calculate x from [Ux = y]
void calculateX(double **U, double *x, double *y, int n){ 
	for(int i = n - 1; i >= 0; --i){
		x[i] = y[i];

		for(int j = i + 1; j < n; ++j){
			x[i] -= U[i][j] * x[j];
		}

		x[i] /= U[i][i];
	}
}

double **CNM(int n, int m, double dt, double h, double lambda) {
	double **result = createBlankMatrix(n, n);
	double **A = createBlankMatrix(n, n);
	double **L = createBlankMatrix(n, n);
	double **U = createBlankMatrix(n, n);
	double b[n], y[n], x[n];

	writeGivenValues(result, n, m, h);

	for (int k = 1; k < n; ++k) {
		// Fill vector b
		b[0] = 0.L;
		b[n - 1] = 0.L;
		for (int i = 1; i < n - 1; ++i){
			b[i] = -((lambda / 2.L) * result[k - 1][i - 1] + (1.L - lambda) * result[k - 1][i] + (lambda / 2.L) * result[k - 1][i + 1]);
		}

		// Fill matrix A
		for (int i = 0; i < n; ++i){
			for (int j = 0; j < n; ++j){
				if((i == 0 && j == 0) || (i == n - 1 && j == n - 1)){
					A[i][j] = 1.L;
				} else if (i == j + 1 || i == j - 1){
					A[i][j] = lambda / 2.L;
				} else if (i == j){
					A[i][j] = -(1.L + lambda);
				} else{
					A[i][j] = 0.L;
				}
			}
		}

		// Commit LU decomposition
		decompose(A, L, U, n);
		// Calculate y from [Ly = b]
		calculateY(L, y, b, n); 
		// Calculate x from [Ux = y]
		calculateX(U, x, y, n); 

		// Copy row to result matrix
		for (int i = 0; i < n; ++i){
			result[k][i] = x[i];
		}
	}

	return result;
}