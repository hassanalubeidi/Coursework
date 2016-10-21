#include <stdio.h>

void mandelbrot(double x, double y) {
	int it;
	double r, i;
	double r2, i2;
	double tmp;

	it = 4096;
	r = i = 0; r2= 0; i2 =0;
	do {
		tmp = r2 - i2 + x;
		i = 2 * r * i + y;
		r = tmp;
		r2 = r*r; i2 = i*i;
	} while((r2 + i2) <= 4.0 && --it);
	if (it == 0.0) {
		printf(" ");
	} else {
		printf("*");
	}
	
}

int main() {
	// mandelbrot(0.5,0.5);

	for(double row=0.0; row <= 53; row++) {
		for(double column=0.0; column<=80; column++) {
			double x_coefficent = 3.0 / 80.0;
			double y_coefficent = 2.0 / 53.0;

			
			double x = (column * y_coefficent) - 1.5;
			double y = (row * x_coefficent) - 1;
			// printf("%f %f\n", x, y);
			mandelbrot(x,y);
		}
		printf("\n");
	}


}

