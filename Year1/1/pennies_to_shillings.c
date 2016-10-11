#include <stdio.h>

char plural(double x) { 
	char plural_letter;
	if (x == 1) {
		plural_letter=' ';
	} else {
		plural_letter='s';
	}
	return plural_letter;
}

void printPSP(int p) {
	int pounds, shillings, pennies, left_over;

	pounds = p / 240;
	left_over = p - (240 * pounds);

	shillings = left_over / 12;
	left_over = left_over - (12 * shillings);

	pennies = p % 12;

	printf("%d pennie%c is %d pound%c, %d shilling%c and %d pennie%c\n", p, plural(p), pounds, plural(pounds), shillings, plural(shillings), pennies, plural(pennies));
}



int main() {
	printPSP(11);
	printPSP(13);
	printPSP(42);
	printPSP(100);
}
