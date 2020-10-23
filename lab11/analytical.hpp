double **analytical(int n, int m, double dt, double h) {
	double **result = createBlankMatrix(n, m);

	double x = x_min;
	double t = t_min;

	// Fill matrix with analytical values for comparison
	for (int i = 0; i < n; ++i, t += dt, x = x_min) {
		for (int j = 0; j < m; ++j, x += h) {
			result[i][j] = 0.5L * erfl((x + b_param) / (2.L * sqrt(D_param * t))) - 0.5L * erfl((x - b_param) / (2.L * sqrt(D_param * t)));
		}
	}

	return result;
}