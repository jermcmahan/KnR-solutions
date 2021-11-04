#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int any(char s[], char t[]);
int main(int argc, char *argv[]) {
    char *leftstr[] = {"hello", "world"};
    char *rightstr[] = {"foshizzle", "jearbear"};
    size_t leftnums = (sizeof leftstr / sizeof leftstr[0]);
    size_t rightnums = (sizeof rightstr / sizeof rightstr[0]);
    size_t left = 0;
    size_t right = 0;
    int passed = 0;
    int failed = 0;
    int pos = -1;
    char *ptr = NULL;
    for (left = 0; left < leftnums; left++) {
        for (right = 0; right < rightnums; right++) {
            pos = any(leftstr[left], rightstr[right]);
            ptr = strpbrk(leftstr[left], rightstr[right]);
            if (pos == -1) {
                if (ptr != NULL) {
                    printf("Test %zd/%zd failed.\n", left, right);
                    failed++;
                }
                else {
                    printf("Test %zd/%zd passed.\n", left, right);
                    passed++;
                }
            }
            else {
                if (ptr == NULL) {
                    printf("Test %zd/%zd failed.\n", left, right);
                    failed++;
                }
                else {
                    if (ptr - leftstr[left] == pos) {
                        printf("Test %zd/%zd passed.\n", left, right);
                        passed++;
                    }
                    else {
                        printf("Test %zd/%zd failed.\n", left, right);
                        failed++;
                    }
                }
            }
        }
    }
    printf("\n\nTotal passes %d, fails %d, total tests %d\n", passed, failed,
    passed + failed);

    return EXIT_SUCCESS;
}
int any(char s[], char t[]){
    int i, j;
    int position = -1;
    for (j = 0; position == -1 && t[j] != '\0'; j++) {
        for (i = 0; position == -1 && s[i] != '\0'; i++) {
            if (s[i] == t[j]) {
                position = i;
            }
        }
    }
    return position;
}