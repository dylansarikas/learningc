void calcpay(p,r,h)
    float *p,r,h;
{
	if (h > 40)
      *p = ((h - 40) * (r * 1.5)) + (40 * r);
  	else
      *p = r * h;
}