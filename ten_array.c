#include <stdio.h>
int main() {
   int i, v, arr[10], found[10], index = 0, q, total = 0;
   for(i=0;i<10;i++) {
       scanf("%d", &v);
       if (v == 100){
         found[index] = i;
         index++;
       }
       arr[i] = v;
   }
   for(i=0; i<10; i++ ) printf("numb[%d] = %d\n", (9-i), arr[(9-i)]);
  
  	printf("\nSearching for entries equal to 100\n");
  	printf("\n");
  
  	for(q=0; found[q] != 0; q++) {
      printf("Found 100 at %d\n", found[q]);
      total++;
    }
  	printf("\n");
  	printf("Found %d entries with 100\n", total);
  	return 0;
}