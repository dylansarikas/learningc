static int brap = 0;

int bump()
{
  return brap++;
}

void start(val)
{
  brap = val;
}