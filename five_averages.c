#include "stdio.h"

main () {
	double c, total, average;
  	total = 0;
  
  	while ((c = getchar()) != EOF){
    	scanf("%lf", &c);
    	total += c;
    }
  	
  	average = total / 5.0;
  
	printf("The total is: %.1f\n", total);
  	printf("The average is: %.1f\n", average);
}