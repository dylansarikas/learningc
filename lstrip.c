void py_lstrip(inp)
    char inp[];
{
    char *shift = inp;
  
  	while (*inp == ' ') inp++;
  
  	while ((*shift++ = *inp++));
  
  	return 0;
}