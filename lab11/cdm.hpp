double** CDM(int n, int m, double dt, double h, double lambda) {
	double** result = createBlankMatrix(n, m);
	// Write initial and boundary values to matrix
	writeGivenValues(result, n, m, h); 

	// Solve equations
	for (int k = 1; k < n; k++) {
		for (int i = 1; i < m - 1; i++) {
			result[k][i] = lambda * result[k - 1][i - 1] + (1.L - 2.L * lambda) * result[k - 1][i] + lambda * result[k - 1][i + 1];
		}
	}

	return result;
}