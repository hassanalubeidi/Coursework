#include <stdio.h>


double calcE(double m, double c) {
	double c_squared = c * c;
	double e = m * c_squared;
	return e;
}

void printE(double m, double c) {
	double energy = calcE(m, c) * 10;
	printf("Energy available from object of mass %.3fKG is %.2fPJ \n", m, energy);
}



int main() {
	double c = 2.99792458;

	printE(1, c);
	printE(3.142, c);
	printE(10, c);
	printE(42, c);
}