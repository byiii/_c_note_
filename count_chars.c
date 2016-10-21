#include <stdio.h>

/* count characters in input, 1st version */

int main()
{
  double nc;

  /* nc = 0; */
  /* while(getchar()!=EOF) { */
  /*   ++nc; */
  /* } */
  
  for(nc = 0; getchar() != EOF; ++nc)
    ;
  printf("character count: %.0f\n", nc);

  return 0;
}
