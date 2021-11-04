#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLINE 5000
char *lineptr[MAXLINE];
int getlines(char s[], int limit);
int readlines(char *lineptr[], int maxlines);
void writelines(char *lineptr[], int nlines);
void qsort1(void *v[], int left, int right,
                int (*comp)(void *, void *));
int numcmp(char *s1, char *s2);
void swap(void *v[], int i, int j);
int main(int argc, char *argv[]) {
    int nlines;
    int numeric = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0) {
        numeric = 1;
    }
    if ((nlines = readlines(lineptr, MAXLINE)) >= 0) {
         qsort1((void **) lineptr, 0, nlines-1,
              (int (*)(void *, void *))(numeric ? numcmp : strcmp));
        return EXIT_SUCCESS;
    }
    else {
        printf("input too big to sort!\n");
        return EXIT_FAILURE;
    }
}
int getlines(char s[], int limit){
    int i, c;
    for (i = 0; (c = getchar()) != EOF && i < limit; i++) {
        if (c == '\n') {
            s[i] = c;
            i++;
        }
        s[i] = c;
    }
    s[i] = '\0';
    return i;
}
int readlines(char *lineptr[], int maxlines){
    int len, nlines;
    char *p, line[MAXLINE];
    nlines = 0;
    while ((len = getlines(line, MAXLINE)) > 0) {
        if (nlines >= maxlines) {
            return -1;
        }
        else {
            line[len-1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    }
    return nlines;
}
void writelines(char *lineptr[], int nlines){
    int i;
    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
}
void qsort1(void *v[], int left, int right,
                int (*comp)(void *, void *))
{
int i, last;
         void swap(void *v[], int, int);
         if (left >= right)    /* do  nothing if array contains */
             return;           /* fewer than two elements */
         swap(v, left, (left + right)/2);
         last = left;
         for (i = left+1; i <= right;  i++)
             if ((*comp)(v[i], v[left]) < 0)
                 swap(v, ++last, i);
         swap(v, left, last);
         qsort1(v, left, last-1, comp);
         qsort1(v, last+1, right, comp);
}
int numcmp(char *s1, char *s2){
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) {
        return -1;
    }
    else if (v1 > v2) {
        return 1;
    }
    else {
        return 0;
    }
}
void swap(void *v[], int i, int j){
    void *temp;
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}