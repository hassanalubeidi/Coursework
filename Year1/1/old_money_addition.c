#include <stdio.h>

struct OldMoney {
   int  pounds;
   int  shillings;
   int  pennies;
};

struct OldMoney new_to_old_money(int p) {
	struct OldMoney old_money;

	int pounds, shillings, pennies, left_over;

	pounds = p / 240;
	left_over = p - (240 * pounds);

	shillings = left_over / 12;
	left_over = left_over - (12 * shillings);

	pennies = p % 12;

	
	old_money.pounds = pounds;
	old_money.shillings = shillings;
	old_money.pennies = pennies;

	return old_money;
}

int int_old_to_new_money(int pounds, int shillings, int pennies) {
	return (pounds * 240) + (shillings * 12) + pennies;
}

void printSumPSP( int xPounds,
 				  int xShillings,
 				  int xPennies,
				  int yPounds,
				  int yShillings,
				  int yPennies) {

	int x_in_pennies = int_old_to_new_money(xPounds, xShillings, xPennies);
	int y_in_pennies = int_old_to_new_money(yPounds, yShillings, yPennies);

	int total_pennies = x_in_pennies + y_in_pennies;

	struct OldMoney old_money_total = new_to_old_money(total_pennies);
	printf("%d pounds, %d shillings and %d pennies\n", old_money_total.pounds, old_money_total.shillings, old_money_total.pennies);

}

int main() {
	printSumPSP(1,4,3,2,17,8);
	printSumPSP(1,5,9,0,1,11);
	printSumPSP(1,19,11,0,0,1);
}