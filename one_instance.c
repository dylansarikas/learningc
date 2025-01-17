int main() {
    char line[1000];
    char keep[1000];
  	char lst[1000];
  	int compar;

  	strcpy(lst, "begin");
    while(gets(line) != NULL ) {
        strcpy(keep, line);
      	compar = strcmp(lst, keep);
      	if (compar > 0 || compar < 0) {
          printf("%s\n",keep);
          strcpy(lst, keep);
        }          
    }
}