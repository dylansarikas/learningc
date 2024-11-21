int lower(c) /* convert c to lower case; ASCII only */
int c;
{
  return (c >= 'A' && c <= 'Z') ? (c + 'a' - 'A') : (c);
}