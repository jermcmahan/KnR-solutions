#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DEFLINE 10
#define LINE 100
#define MAXLEN 100
void error(char *s);
int getlines(char *s, int limit);
int main(int argc, char *argv[]) {
    char *p;
    char *buf;
    char *bufend;
    char line[MAXLEN];
    char *lineptr[LINE];
    int first, i, last, len, n, nlines;
    if (argc == 1) {
        n = DEFLINE;
    }
    else if (argc == 2 && (*++argv)[0] == '-') {
        n = atoi(argv[0] + 1);
    }
    else {
        error("usage: tail [-n]");
    }
    if (n < 1 || n > LINE) {
        n = LINE;
    }
    for (i = 0; i < LINE; i++) {
        lineptr[i] = NULL;
    }
    if ((p = buf = malloc(LINE * MAXLEN)) == NULL) {
        error("tail: cannot allocate buf");
    }
    bufend = buf + LINE * MAXLEN;
    last = 0;
    nlines = 0;
    while ((len = getlines(line, MAXLEN)) > 0) {
        if (p + len + 1 >= bufend) {
            p = buf;
        }
        lineptr[last] = p;
        strcpy(lineptr[last], line);
        if (++last >= LINE) {
            last = 0;
        }
        p += len + 1;
        nlines++;
    }
    if (n > nlines) {
        n = nlines;
    }
    first = last - n;
    if (first < 0) {
        first += LINE;
    }
    for (i = first; n-- > 0; i = (i+1) % LINE) {
        printf("%s", lineptr[i]);
    }
    return EXIT_SUCCESS;
}
void error(char *s){
    printf("%s\n", s);
    EXIT_FAILURE;
}
int getlines(char *s, int limit){
    int i, c;
    for (i = 0; (c = getchar()) != EOF && c != '\n' && i < limit; i++) {
        *s++ = c;
        if (c == '\n') {
            *s++ = c;
            i++;
        }
    }
    *s = '\0';
    return i;
}