#include <stdio.h>
#include <stdlib.h>
#define MAX_LINE 1000
int getlines(char s[], int limit);
void copy(char to[], char from[]);
int main(int argc, char *argv[]) {
    char line[MAX_LINE];
    int length;
    char longest[MAX_LINE];
    int max = 0;
    while ((length = getlines(line, MAX_LINE)) > 0) {
        printf("%d: %s\n", length, line);
        if (length > max) {
            max = length;
            copy(longest, line);
        }
    }
    if (max > 0) {
        printf("%d: %s [is the longest]", max, longest);
    }
    putchar('\n');
    return EXIT_SUCCESS;
}
int getlines(char s[], int limit){
    int i, j, c;
    for (i = 0, j = 0; (c = getchar()) !=EOF && c != '\n'; i++) {
        if (i < limit) {
            s[j++] = c;
        }
        if (c == '\n') {
            if (i < limit) {
                s[j++] = c;
            }
            i++;
        }
        // use tab to break from loop; can be changed or removed
        if (c == '\t') {
            break;
        }
    }
    s[j] = '\0';
    return i;
}
void copy(char to[], char from[]){
    int i = 0;
    while ((to[i] = from[i]) != '\0') {
        i++;
    }
}