#include <stdio.h>
#include <math.h>

int main()
{
  int n, i, count=0;
  (void) scanf ("%d", &n);
  for (i=1; i<=n; i++)
  {
	int x;
	(void) scanf ("\n%d", &x);
	count-=x;
  }
  printf("%d\n", count);
  return 0;
}