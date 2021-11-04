#include <stdio.h>
#include <stdlib.h>
#define MAX 100
void expand(char s[], char t[]);
int main(int argc, char *argv[]) {
    int c;
    char buffer[MAX];
    char string[MAX];
    while (fgets(string, MAX, stdin)) {
        expand(string, buffer);
        printf("%s", buffer); //'\n' uneccassary because buffer contains one
    }
    return EXIT_SUCCESS;
}
void expand(char s[], char t[]){
    int c, i, j;
    i = j = 0;
    while ((c = s[i++]) != '\0') {
        if (s[i] == '-' && s[i+1] >= c) {
            i++;
            while (c < s[i]) {
                t[j++] = c++;
            }
        }
        else if (s[i] == '-' && s[i+1] <= c) {
            i++;
            while (c > s[i]) {
                t[j++] = c--;
            }
        }
        else {
            t[j++] = c;
        }
    }
    t[j] = '\0';
}