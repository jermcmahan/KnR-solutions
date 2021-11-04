#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define NKEYS (sizeof(keytab) / sizeof(keytab[0]))
#define MAXWORD 100
char buf[MAXWORD];
int bufp = 0;
int getch(void){
    return (bufp > 0)? buf[--bufp] : getchar();
}
void ungetch(int c){
    if (bufp > MAXWORD) {
        printf("error: ungetch()!\n");
    }
    else {
        if (c != EOF) {
            buf[bufp++] = c;
        }
    }
}
int comment(void){
    int c;
    while ((c = getch()) != EOF) {
        if (c == '*') {
            if ((c == getch()) == '/') {
                break;
            }
            else {
                ungetch(c);
            }
        }
    }
    return c;
}
struct key{
    char *word;
    int count;
}keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};
int getword(char *word, int limit);
int tabsearch(char *word, struct key tab[], int n);
int main(int argc, char *argv[]) {
    int n;
    char word[MAXWORD];
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            if ((n = tabsearch(word, keytab, NKEYS)) >= 0) {
                keytab[n].count++;
            }
        }
    }
    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count) {
            printf("[%d]%s\n", keytab[n].count, keytab[n].word);
        }
    }
    return EXIT_SUCCESS;
}
int getword(char *word, int limit){
    int c, d;
    char *w = word;
    while (isspace(c = getch())) {
    }
    if (c != EOF) {
        *w++ = c;
    }
    if (isalpha(c) || c == '_' || c == '#') {
        for (; --limit > 0; w++) {
            if (!isalnum(*w = getch()) && *w != '_') {
                ungetch(*w);
                break;
            }
        }
    }
    else if (c == '\'' || c == '*') {
        for (; --limit > 0; w++) {
            if ((*w = getch()) == '\\') {
                *++w = getch();
            }
            else if (*w == c) {
                w++;
                break;
            }
            else if (*w == EOF) {
                break;
            }
            else if (c == '/') {
                if ((d = getch()) == '*') {
                    c = comment();
                }
                else {
                    ungetch(d);
                }
            }
        }
    }
    *w = '\0';
    return c;
}
int tabsearch(char *word, struct key tab[], int n){
    int cond;
    int low, high;
    high = n - 1;
    low = 0;
    while (low <= high) {
        if ((cond = strcmp(word, tab[low].word)) > 0) {
            low++;
        }
        else if (cond < 0) {
            return -1;
        }
        else {
            return low;
        }
    }
    return -1;
}