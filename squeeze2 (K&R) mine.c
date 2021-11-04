#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void squeeze(char s[], char t[]);
int main(int argc, char *argv[]) {
    char *leftstr[] = {"hello", "world", "jearbear"};
    char *rightstr[] = {"hi", "lol", "cheese"};
    char buffer[32] = {0};
    size_t leftnums = sizeof leftstr / sizeof leftstr[0];
    size_t rightnums = sizeof rightstr / sizeof rightstr[0];
    size_t left = 0;
    size_t right = 0;
    for (left = 0; left < leftnums; left++) {
        for (right = 0; right < rightnums; right++) {
            strcpy(buffer, leftstr[left]);
            squeeze(buffer, rightstr[right]);
            printf("[%s] - [%s] = [%s]\n", leftstr[left], rightstr[right], buffer);
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