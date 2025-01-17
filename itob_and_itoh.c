void itob(n, s)
int n;
char s[];
{
   memset(s, 0, 1000);
   double begg = 0;
   int fin;
   char ch;
   while (pow(2, begg) <= n) {
     begg += 1;
   }
   fin = begg;
   /* printf("The total is: %.1f\n", begg); */
   while (begg > 0) {
     if (pow(2, (begg - 1)) <= n) {
       n = n - pow(2, (begg - 1));
       ch = '1';
     }
     else {
       ch = '0';
     }
     /* printf("N is: %.1i\n", n); */
     strncat(s, &ch, 1);
     begg -= 1;
  }
  s[fin] = '\0';
}
void itoh(n, s)
int n;
char s[];
{
  void reverse();
  memset(s, 0, 1000);
  double begg = 0;
  int fin;
  char ch;
  while (pow(2, begg) <= n) {
    begg += 1;
  }
  fin = begg;
  int temp;
  char here;
  while (n != 0) { 
    temp = n % 16;
    if (temp < 10) 
      temp = temp + 48; 
    else
      temp = temp + 87; 
    here = (char)temp;
    strncat(s, &here, 1);
    n = n / 16; 
  }
  reverse(s);
  s[fin] = '\0';
}