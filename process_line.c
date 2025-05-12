void process(line)
    char line[];
{
  	int i;
    printf("\nString: %s\n",line);
  	printf("Count=%lu\n",strlen(line));
  	if (strlen(line) > 10)
        printf("The ninth character is: %c\n", line[9]);
  	for(i = 0; i < strlen(line); i++) {
      if (line[i] == ' ')
        line[i] = '-';
    }
  	printf("String: %s\n",line);
}