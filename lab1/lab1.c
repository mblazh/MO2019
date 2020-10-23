#include <stdio.h>

int main() {	
	int doubleMantysa = 0, floatMantysa = 0; 
	float floatEpsilon = (float) 1;
	double doubleEpsilon = (double) 1;

	while ((floatEpsilon / (float) 2 + (float) 1) > (float) 1) {
		floatEpsilon /= (float) 2;
		++floatMantysa;
	}

	while ((doubleEpsilon / (double) 2 + (double) 1) > (double) 1) {
		doubleEpsilon /= (double) 2;
		++doubleMantysa;
	}
	
	printf("float:\n\tLiczba bitow mantysy: %i\n\tEpsilon maszynowy: %e\n\tPrecyzja arytmetyki: %e\ndouble:\n\tLiczba bitow mantysy: %i\n\tEpsilon maszynowy: %e\n\tPrecyzja arytmetyki: %e\n", 
		floatMantysa, 
		floatEpsilon,
		floatEpsilon / (float) 2, 
		doubleMantysa, 
		doubleEpsilon,
		doubleEpsilon / (double) 2
	);
}