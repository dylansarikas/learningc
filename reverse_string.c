#include <stdio.h>
#include <string.h>
int main() {
  char t[1000];
  char *copy();
  void reverse();
  copy("Hello world", t);
  printf("%s\n", t);
  reverse(t);
  printf("%s\n", t);
  reverse(copy("XY", t));
  printf("%s\n", t);
  reverse(copy("Even", t));
  printf("%s\n", t);
  reverse(copy("Odd", t));
  printf("%s\n", t);
  reverse(copy("civic", t));
  printf("%s\n", t);
}

/* copy s1 to s2; assume s2 big enough */
char *copy(s1, s2)
char s1[], s2[];
{
    int i;
    for(i=0;(s2[i] = s1[i]);i++);
    return s2;
}

void reverse(t)
char t[];
{
  	int first, last;
  	char temp;
  
  	for (first = 0, last = strlen(t) - 1; first < last; first++, last--) {
      temp = t[first];
      t[first] = t[last];
      t[last] = temp;
    }
}