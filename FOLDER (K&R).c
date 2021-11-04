#include <stdio.h>
//FOLD program cleverly finds closest space near end of line and adds 
// a '\n'
#define MAXLINE 1000 /* max input line size */
#define FOLDLENGTH 70
char line[MAXLINE] = {0}; /*current input line*/

int getlines(void); /* taken from the KnR book. */


int
main()
{
  int t,len;
  int location,spaceholder;
 /* The max length of a line */

  while ((len = getlines()) > 0 )
    {
      if( len < FOLDLENGTH )
    {
        printf("not past foldlength 70\n");
        printf("you typed:\n%s", line);
    }
      else
    {
    /* if this is an extra long line then we 
    ** loop through it replacing a space nearest
    ** to the foldarea with a newline.
    */
      t = 0;
      location = 0;
      while(t<len)
        {
          if(line[t] == ' ')
        spaceholder = t;

          if(location==FOLDLENGTH)
        {
          line[spaceholder] = '\n';
          location = 0;
        }
          location++;
          t++;
        }
    }
      printf ( "%s", line);
    }
  return 0;
}


/* getline: specialized version */
int getlines(void)
{
  int c, i;
  extern char line[];
  
  for ( i=0;i<MAXLINE-1 && ( c=getchar()) != EOF && c != '\n'; ++i)
    line[i] = c;
  if(c == '\n') 
    {
      line[i] = c;
      ++i;
    }
  line[i] = '\0';
  return i;

}