#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//LOOK!! simplified version in comments below
//replaces many spaces for a tab! prefered other version entab
//this is detab!! not entab
#define MAX_BUFFER   1024
#define SPACE        ' '
#define TAB          '\t'

int CalculateNumberOfSpaces(int Offset, int TabSize)
{
    printf("%d",TabSize - (Offset % TabSize));
    return 0;    
}

/* K&R's getline() function from p29 */
int getlines(char s[], int lim)
{
  int c, i;

  for(i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if(c == '\n')
  {
    s[i] = c;
    ++i;
  }
  s[i] = '\0';

  return i;
}

int main(void)
{
  char  Buffer[MAX_BUFFER];
  int TabSize = 5; /* A good test value */

  int i, j, k, l;

  while(getlines(Buffer, MAX_BUFFER) > 0)
  {
    for(i = 0, l = 0; Buffer[i] != '\0'; i++)
    {
      if(Buffer[i] == TAB)
      {
        j = CalculateNumberOfSpaces(l, TabSize);
        for(k = 0; k < j; k++)
        {
          putchar(SPACE);
          l++;
        }
      }
      else
      {
        putchar(Buffer[i]);
        l++;
      }
    }
  }

  return 0;
}/* function version of entab simpler; no calculate space rather count variable;

#include <stdio.h>

#define MAXLINE 1000    /* maximum characters of a line */
//#define TABWIDTH 2      /* tabsize */
/*
int getlines(char line[], int maxline);
void detab(char to[], char from[]);

int main(void)
{
    int len;                /* current line length */
   // char line[MAXLINE];     /* current input line */
    //char nline[MAXLINE];    /* detabed line saved here */
/*
    while ((len = getlines(line, MAXLINE)) > 0) {
        detab(nline, line);
        printf("%s", nline);
    }

    return 0;
}

/* getline: reads a line s, return line length */
/*int getlines(char s[], int lim)
{
    int i, c;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

/* detab: replaces tabs with blanks */
/*void detab(char to[], char from[])
{
    int i, j, n;

    i = j = n = 0;
    while ((to[j] = from[i]) != '\0') {
        if (to[j] == '\t')
            for (n = 0; n < TABWIDTH; ++n, ++j)
                to[j] = ' ';
        else
            ++j;
        ++i;
    }
}*/