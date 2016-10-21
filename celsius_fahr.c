#include <stdio.h>

/* /\* print Fahrenheit-Celsius table for fahr = 0, 20, ..., 300 *\/ */

#define LOWER 0
#define UPPER 300
#define STEP 20

int main()
{
   float fahr, celsius;
   float lower, upper, step;

   lower = 0; 
   upper = 300;
   step = 20;
   
   printf("Fahrenheit -- Celsius \n");
  /*  fahr = lower; */
  /*  while(fahr<=upper) { */
  /*    celsius = 5 * (fahr-32) / 9; */
  /*    printf("%10.1f    %7.1f %% \n", fahr, celsius); */
  /*   fahr = fahr + step; */
  /* } */

   for( fahr = UPPER; fahr>=LOWER; fahr = fahr - STEP) {
     printf("%10.1f    %7.1f \n", fahr, (5.0/9.0)*(fahr-32));
   }

  return 0;
}
