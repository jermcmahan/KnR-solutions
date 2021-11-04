//FOLD program cleverly finds closest space near end of line and adds 
// a '\n' // new version used function fold() in else statement!
#include <stdio.h>
#include <stdlib.h>
#define FOLDLENGTH 70
#define MAX 1000
void fold(int length, char line[]);
int getlines(char s[], int limit);
int main(int argc, char *argv[]) {
    int length;
    char line[MAX] = {0};
    while ((length = getlines(line, MAX)) > 0) {
        if (length < FOLDLENGTH) {
            printf("error: not enough characters to fold|\n");
        }
        else {
            fold(length, line);
        }
        printf("%s\n", line);
    }
    return EXIT_SUCCESS;
}
/* if this is an extra long line then we 
loop through it replacing a space nearest
to the foldarea with a newline. */
void fold(int length, char line[]){
    int space = 0;
    int i = 0;
    int location = 0;
    while (i < length) {
        if (line[i] == ' ') {
            space = i;
        }
        else if (location == FOLDLENGTH) {
            line[space] = '\n';
            location = 0;
        }
        i++;
        location++;
    }
}
int getlines(char s[], int limit){
    int i, j, c;
    for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < limit) {
            s[j++] = c;
        }
        else if (c == '\n') {
            if (i < limit) {
                s[j++] = c;
            }
            i++;
        }
    }
    s[j] = '\0';
    return i;
}