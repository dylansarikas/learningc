void py_rstrip(inp)
    char inp[];
{
    int index = strlen(inp) - 1;

    while (index >= 0 && inp[index] == ' ') {
        inp[index] = '\0';
        index--;
    }
  	return 0;
}