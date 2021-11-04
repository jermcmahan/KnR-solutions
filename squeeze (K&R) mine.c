#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void squeeze(char s[], char t[]);
int main(int argc, char *argv[]) {
    char *leftstring[] = {"hello", "world", "i am", "the", "jearbear"};
    char *rightstring[] = {"cheese", "burgers", "lol"};
    char buffer[32];
    size_t numsright = sizeof rightstring / sizeof rightstring[0];
    size_t numsleft = sizeof leftstring / sizeof leftstring[0];
    size_t left = 0;
    size_t right = 0;
    for (left = 0; left < numsleft; left++) {
        for (right = 0; right < numsright; right++) {
            strcpy(buffer, leftstring[left]);
            squeeze(buffer, rightstring[right]);
            printf("[%s] - [%s] = [%s]\n", leftstring[left], rightstring[right], buffer);
        }
    }
    return EXIT_SUCCESS;
}
void squeeze(char s[], char t[]){
    int i, j, k;
    for (k = 0; t[k] != '\0'; k++) {
        for (i = 0, j = 0; s[i] != '\0'; i++) {
            if (s[i] != t[k]) {
                s[j++] = s[i];
            }
        }
        s[j] = '\0';
    }
}
/*void squeeze2(char s1[], char s2[])
{
  int i, j, k;
  int instr2 = 0;

  for(i = j = 0; s1[i] != '\0'; i++)
  {
    instr2 = 0;
    for(k = 0; s2[k] != '\0' && !instr2; k++)
    {
      if(s2[k] == s1[i])
      {
        instr2 = 1;
      }
    } 

    if(!instr2)
    {
      s1[j++] = s1[i];
    } 
  }
  s1[j] = '\0';
}*/