#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(int argc, char *argv[])
{
   int c, inspace;
   while((c = getchar()) !=EOF){
   if (c == ' ')   
      putchar(c);
      inspace = 1;
   if (c != ' '&& inspace != 0)
      putchar(c);
      inspace = 0;
   }
   return EXIT_SUCCESS;
}
