#include <stdio.h>


char plural(double x) { 
	char plural_letter;
	if (x == 1) { plural_letter=' '; } else { plural_letter='s'; }
	return plural_letter;
}

int is_penultimate(int pounds, int y, int i) {
	int denominations[4] = {20, 10, 5, 1};
	int left_over = pounds;
	int x, last_null;
	for(int j = 0; j < 3; j++) {
		x = left_over / denominations[j];
		left_over = left_over - (x * denominations[j]);
		if (last_null != -1) {
			last_null = j;
			printf("|%d|", j);
		}
	}

	if (i == last_null-1) { return 1; }
	
	return -1;
}

void print_smallest_money(int pounds) {
	int denominations[4] = {20, 10, 5, 1};
	int left_over = pounds;
	int next_x_left_over;
	printf("£%d consits of", pounds);
	int next_x,next_next_x, x;
	for(int i = 0;i < 4; i++) {
		
		x = left_over / denominations[i];
		left_over = left_over - (x * denominations[i]);
		
		if(x != 0) { // ends output when smallest denomination reached
			if (i < 3) { next_x = left_over / denominations[i+1]; next_x_left_over = left_over - (x * denominations[i+1]);}
			if (i < 2) { next_next_x = next_x_left_over / denominations[i+2]; }
			printf(" %d £%d", x, denominations[i]); // prints maths logic
			if(i != 3) { // only 1 pound coins are not notes
				printf(" note%c", plural(x));

				//dealing with "," and "and" grammar
				// if (next_x != 0) {
					if (is_penultimate(pounds, x, i) == 1) { printf("and"); } else { printf(",");}
				// }
				
			}else {
				printf(" pound coin%c", plural(x));
			}
			// if(i == 2) {
			// 	if (next_x != 0) { printf("\band"); }
			// }
			
		}
		
		
	}
	printf("\n");


}

int main() {
	print_smallest_money(15);
	print_smallest_money(79);
	print_smallest_money(10);
	print_smallest_money(26);
}

