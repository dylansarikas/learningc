#include <stdio.h>
#include <string.h>
int main() {
    char first[100], second[100], both[100];
  	int max = 99;

  	printf("Enter two strings\n");
    
  	fgets(first, max, stdin);
  	first[strcspn(first, "\n")] = 0; /* gets rid of trailing /n */
  	fgets(second, max, stdin);

  	strcat(first, " & ");
  	strcat(first, second);
  	printf("%s\n", first);
  	return 0;
}