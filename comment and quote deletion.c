#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
int getlines(char s[], int limit);
int main(int argc, char *argv[]) {
    char line[MAX];
    int i, length;
    int incomment, inquote;
    incomment = inquote = i = 0;
    while ((length = getlines(line, MAX)) > 0) {
        i = 0;
        while (i < length) {
            if (line[i] == '"' && inquote == 0) {
                inquote = 1;
                //printf("%c", line[i]);  <= use this if you want quote
                //strings to be printed                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
                i++;
            }
            else if (inquote == 1) {
                i++;
            }
            else if (line[i] == '"' && inquote == 1) {
                inquote = 0;
                //printf("%c", line[i]); <= ''
                i++;
            }
            else if (inquote != 1) {
                if (line[i] == '/' && line[i+1] == '*') {
                    i += 2;
                    incomment = 1;
                }
                else if (line[i] == '*' && line[i+1] == '/') {
                    i += 2;
                    incomment = 0;
                }
                else if (incomment == 1) {
                    i++;
                }
                else {
                    printf("%c", line[i]);
                    i++;
                }
            }
            else {
                printf("%c", line[i]);
                i++;
            }
        }
        //printf("%i", i); counts number of characters used
        putchar('\n');
    }
    return EXIT_SUCCESS;
}
int getlines(char s[], int limit){
    int i, j, c;
    for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < limit) {
            s[j++] = c;
        }
        if (c == '\n') {
            if (i < limit) {
                s[j++] = c;
            }
            i++;
        }
    }
    s[j] = '\0';
    return i;
}