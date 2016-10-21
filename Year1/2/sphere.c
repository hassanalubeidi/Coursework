#include <stdio.h>


double vol(double r) {
	double answer;
	double pi = 3.14159265;
	if(r >= 0) {
		answer = (4.0/3) * (pi) * (r * r * r);
		return answer;
	}else if(r < 0 ) {
		answer = -1;

		printf("You tried to input a negative radius");
		return answer;
	}
	return -1; //C doesn't like not returning things
}

void print_vol(double r) {
	printf("The volume of a sphere with radius %f is %f\n", r, vol(r));
}



int main() {
	print_vol(1);
	print_vol(4.657);
	print_vol(-0.5);
	print_vol(10);
	print_vol(42);
	
}