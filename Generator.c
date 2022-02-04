#include <stdio.h>
#include <stdlib.h>

int main( int argc, char *argv[] )  {

   if( argc == 2 ) {
      char *fn = argv[1];
      FILE *fp = fopen(fn, "r");

      if (fp == NULL)
      {
         printf("[Generator]: File open error %s", fn);
         return 1;
      }

      unsigned char buf[256];

      while (fgets(buf, (unsigned) 256, fp))
        printf("%s", buf);

      fclose(fp);
   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied.\n");
   }
   else {
      printf("One argument expected.\n");
   }
}
