#include <stdio.h>

void add_money(int time, int duration) {
	int duration_hours = duration / 100;
	int duration_minutes = duration % (duration_hours * 100);
 	printf("%d\n%d\n", duration_hours, duration_minutes);
	int ans;
	ans = time + duration_hours * 100;
	ans = ans + duration_minutes;

	printf("Start time is %d. Duration is %d. End time is %d in the ", time, duration, ans);
	if( (time / 1200) == 1 ) {
		printf("afternoon\n");
	} else {
		printf("morning\n");
	}
}



int main() {
	add_money(1201, 190);
}