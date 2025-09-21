#include <stdio.h>

int isPrime(int n)
{
    int k=2;
    while(k*k<=n)
    {
        if (n%k==0) return 0;
        k++;
    }
    return 1;
}

void primeFactors(int a, int m)
{
  for(int i=2; i<a+1; i++)
  {  
    if(m <= 0) break;

    if(a % i == 0 && isPrime(i))
    {
    m--;
    printf("%d\n", i);
      
    

  }
}

int main()
{
  int a, m;

	scanf("%d %d", &a, &m);

  if(a<=1){
    printf("ERROR");
    return 0;
  }

  primeFactors(a, m);

  return 0;
}
