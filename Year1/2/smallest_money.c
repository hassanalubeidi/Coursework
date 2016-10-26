#include <stdio.h>
#include <math.h>
void smallest_money(int pounds); int number_of_positives(int binary_integer); void reset_splits(); char plural(int);
const int denominations[4] = {20,10,5,1};
int splits[4] = {0,0,0,0};
int main() {
	smallest_money(21);
}

void smallest_money(int pounds) {
	int x, remainder = pounds, bin_int = 0;
	reset_splits();
	for(int i = 0; i<4; i++) {
		x = remainder / denominations[i];
		remainder = remainder - (x * denominations[i]);
		splits[i] = x;
		if(x > 0) { bin_int += pow(2,3-i); }
	}
	int count = 0;
	int total_count = number_of_positives(bin_int);

	for(int i = 0; i< 4; i++) {
		if (splits[i] != 0){
			printf("%d £%d ", splits[i], denominations[i]);
			if(i == 3) {
				printf("pound coin%c", plural(splits[i]) );
			} else { printf("note%c", plural(splits[i]) ); }

			if (count != total_count) {
				if (count == total_count - 1) { printf(" and "); } else { printf(", "); }
				count++;
			}
		}
		
	}
	printf("\n");
}

int number_of_positives(int binary_integer) {
	int div = binary_integer, rem, count = 0;
	while(div != 0) {
		div = div/2;
		rem = div % 2;
		if(rem == 1) { count++; }
	}
	return count;
}

void reset_splits() {
	splits[0] = 0; splits[1] = 0; splits[2] = 0; splits[3] = 0;
}

char plural(int x) { 
	char plural_letter;
	if (x == 1) { plural_letter=' '; } else { plural_letter='s'; }
	return plural_letter;
}