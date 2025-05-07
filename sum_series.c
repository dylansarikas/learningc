int sumseries(ival)
    int ival;
{
  	int step, sum, down;
	if (ival < 0)
		return 0;
	if (ival > 100)
		return -1;
    down = ival - 1;
    step = sumseries(down);
  	sum = ival + step;
    return sum;
}