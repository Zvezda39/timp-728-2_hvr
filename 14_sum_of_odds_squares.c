#include <stdio.h>
#include <math.h>

int main()
{
  int n, i, sum_squad=0,x;
  (void) scanf ("%d", &n);
  for (i=1; i<=n; i++)
	{
    (void) scanf ("\n%d", &x);
    sum_squad += (i%2)*pow((double)x,2);
	}
  printf("%d\n", sum_squad);
  return 0;
}
