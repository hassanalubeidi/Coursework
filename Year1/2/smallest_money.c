#include <stdio.h>


char plural(double x) { 
	char plural_letter;
	if (x == 1) {
		plural_letter=' '; // C didn't like me returning an empty char
	} else {
		plural_letter='s';
	}
	return plural_letter;
}

void print_smallest_money(int pounds) {
	int denominations[4] = {20, 10, 5, 1};
	int left_over = pounds;

	printf("£%d consits of", pounds);

	for(int i = 0;i < 4; i++) {
		int next_x;
		int x = left_over / denominations[i];
		left_over = left_over - (x * denominations[i]);
		if (i != 3) { next_x = left_over / denominations[i+1]; }
		
		if(x != 0) {
			printf(" %d £%d", x, denominations[i]);
			if(i != 3) {
				printf(" note%c", plural(x));
				if (next_x != 0) { printf(","); }
			}else {
				printf(" pound coin%c", plural(x));
			}
			if(i == 2) {
				if (next_x != 0) { printf(" and"); }
			}
		}
		
	}
	printf("\n");


}

int main() {
	print_smallest_money(10);
	print_smallest_money(79);
	print_smallest_money(10);
	print_smallest_money(4);
}

