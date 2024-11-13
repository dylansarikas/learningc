#include <stdio.h>
main() {
    int c, d, inspace;
 	inspace = 0;
    while ((c = getchar()) != EOF) {
      	if (c == ' ' && inspace == 0) {
          	putchar(c);
          	inspace = 1;
        }
      	else if (c == ' ' && inspace == 1)
        	continue;
        else {
        	putchar(c);
      		inspace = 0;
        }
    } 
}