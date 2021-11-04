#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
//LOOK!!!!
//for explanations check reverse program below in comments!!!
void discardNewLine(char s[]);
void reverse(char s[]);//can be represented by a int returning 0
int getlines(char s[], int limit);

int main(int argc, char *argv[]) {
    char line[MAX];
    while ((getlines(line, MAX)) > 0) {
        discardNewLine(line);
        reverse(line);
        printf("%s\n", line);
        //press enter to make line 0 and break loop!
    }
    printf("while loop finished process complete!\n");
    return EXIT_SUCCESS;
}
int getlines(char s[], int limit){
    int i, j, c;
    //test new getline prefered other way below in other version!
    for (i = 0; (c = getchar()) != EOF && i < limit && c != '\n'; i++)     
    {
        s[j++] = c;
        if (c == '\n') {
            i++;
        }
    }
    s[j] = '\0';
    return i;
}
void reverse(char s[]){
    int ch, i, j;
    //variables i and j can be swapped!
    for (i = 0; s[i] != '\0'; i++) {
        
    }
    i--;
    for (j = 0; j < i; j++) {
        ch = s[j];
        s[j] = s[i];
        s[i] = ch;
        i--;
    }
}
void discardNewLine(char s[]){
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\n') {
            s[i++] = '\0';
        }
    }
}// test version of reverse with advanced explanations!
/*
#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1000
#define MIN_LINE 10
#define TRUE 1
#define FALSE 0
void discardNewLine(char s[]);
int reverse(char s[]);
int getlines(char s[], int limit);
int main(int argc, char *argv[]) {
    char string[MAX_LINE] = {0};
    while ((getlines(string, MAX_LINE)) > 0) {
    discardNewLine(string);
    reverse(string);
    printf("%s\n", string);
    }
    printf("loop finished process complete\n");
    return EXIT_SUCCESS;
}
    int reverse(char s[])
    {
      char ch;
      int i, j;
      // prints how many numbers are saved in array s \test!
      for(j = 0; s[j] != '\0'; j++){
        printf("%d", j);
      }
      putchar('\n');
      j--;//decrements terminating '\0' value from s[j]
      //shows initial s[i] value
      for (i = 0; i < MAX_LINE; i++) {
        printf("%c", s[i]);
    }
    putchar('\n');
    // using transitivity/ s[i] = s[0] while s[j] = s[last value] and    
    //switches them
      for(i = 0; i < j; i++){
        ch   = s[i];
        s[i] = s[j];
        s[j] = ch;
        --j;
      }//prints reversed s[i] \test!
      for (i=0; i < MAX_LINE; i++) {
        printf("%c", s[i]);
    }
      return 0;
    }
int getlines(char s[], int limit){//can use pointer *s
    int c, i, j;
    for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (c < limit) {
            s[j++] = c;
        }
        if (c == '\n') {
            if (c < limit) {
                s[j++] = c;
            }
            i++;
        }
    }
    s[j] = '\0';
    return i;    
}
// if string s is a blank line with no characters except '\n' delete it
void discardNewLine(char s[]){
    int i;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == '\n') {
            s[i++] = '\0';
        }
    }
}
*/