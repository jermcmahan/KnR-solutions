#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAXHIST 15
#define MAXCHAR 128
int main(int argc, char *argv[]) {
    int c, i, len, max, cc[MAXCHAR] = {0};
    while ((c = getchar()) != EOF) {
        if (c < MAXCHAR) {
            ++cc[c];
        }
    }
    max = 0;
    for (i = 1; i < MAXCHAR; i++) {
        if (cc[i] > max) {
            max = cc[i];
        }
    }
    for (i = 1; i < MAXCHAR; i++) {
        if (isprint(i)) {
            printf("%5d - %c - %5d : ", i, i, cc[i]);
        }
        else {
            printf("%5d -   - %5d : ", i, cc[i]);
        }
        if (cc[i] > 0) {
            if ((len = cc[i] * MAXHIST / max) <= 0) {
                len = 1;
            }
        }
        else {
            len = 0;
        }
        while (len) {
            putchar('*');
            --len;
        }
        putchar('\n');
    }
    return EXIT_SUCCESS;
}