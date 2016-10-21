#include <stdio.h>

void rectangle() {
	int width, height;
	printf("Please enter the width and height for your rectangle (separated by a comma, e.g. 3,4):");
	scanf("%d,%d", &width, &height);

	if ( (width >= 0 && height >= 0) && (width <= 80 && height <= 80)) { // Validates width & height are > 0 and < 80
		if ( (width != 0 || height != 0) ) { // Exit clause
			for(int i=0; i < height; i++) {
				for(int j=0; j<width; j++) {
					printf("*");
				}
				printf("\n");
			}
			printf("Retry or enter 0,0 to stop application\n");
			rectangle(); // recurse
		} 
	} else {
		printf("ERROR\n");
		rectangle(); // recurse
	}
}

int main() {
	rectangle();
}

