#define N 4
#define TOLX 1e-8L
#define TOLF 1e-8L
using namespace std;

double** createMatrix(int size){
	double** matrix;
	matrix = new double*[size];

	for (int i = 0; i < size; i++) {
		matrix[i] = new double[size];
		for (int j = 0; j < size; j++) {
			matrix[i][j] = 0.0;
		}
	}

	return matrix;
}

double* createArray(int size) {
	double* array;
	array = new double[size];
	
	for (int i = 0; i < size; i++)
		array[i] = 0.0;
	
	return array;
}

double* copyArrayValues(double* a) {
	double* copy = createArray(N+1);
	for (int i = 1; i <= N; i++)
		copy[i] = a[i];
	
	return copy;
}

double* subtractArrays(double* a, double* b){
	double* difference = createArray(N+1);
	for (int i = 1; i <= N; i++)
		difference[i] = a[i] - b[i];
	return difference;
}

double max(double* array){
	double max = 0.0;

	// wyznacz największą wartość bezwzględną danego wektora i zwróć ją
	for (int i = 1; i <= N; i++) {
		if (fabs(array[i]) > max)
			max = fabs(array[i]);
	}

	return max;
}

double calculateResiduum(double** a, double *b, double *x){
	double* ax = createArray(N+1);//Ах
	double* residuum_vector = createArray(N+1);//r

	// rozwiąż poszczególne równania układu dla danego przybliżenia
	// i wstaw rozwiązania do tablicy ax
	for (int i = 1; i <= N; i++) {
		double row_sum = 0.0;
		for (int j = 1; j <= N; j++) {
			row_sum += a[i][j] * x[j];
		}
		ax[i] = row_sum;
	}
	// odejmij wektor z obliczonymi równaniami od wektora z danymi rozwiązaniami b
	residuum_vector = subtractArrays(ax, b);//ресидиум

	return max(residuum_vector);
}

void SORWrapper(void (*f)(double**, double*, double*)) {
	double** a = createMatrix(N+1);
	double* b = createArray(N+1);
	double* x = createArray(N+1);

	double A[4][4] = {
		{ 100.L, 	1.L, 	-2.L, 	3.L 		},
		{ 4.L, 		300.L, 	-5.L, 	6.L 	},
		{ 7.L, 		-8.L, 	400.L, 	9.L 	},
		{ -10.L, 	11.L, 	-12.L, 	200.L 	}
	};

	double b_[4] = { 395.L, 603.L, -415.L, -606.L };

	for (int i = 1; i <= N; ++i){
		for (int j = 0; j <= N; ++j){
			a[i][j] = A[i - 1][j - 1];
		}

		b[i] = b_[i - 1];
		x[i] = 1.L;
	}

	(*f)(a, b, x);
}