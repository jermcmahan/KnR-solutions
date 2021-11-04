#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100
#define YES 1
#define NO 0
char buf[MAXWORD];
int bufp = 0;
int getch(void){
    return (bufp > 0)? buf[--bufp] : getchar();
}
void ungetch(int c){
    if (bufp > MAXWORD) {
        printf("ungetch()");
    }
    else {
        if (c != EOF) {
            buf[bufp++] = c;
        }
    }
}
struct tnode{
    char *word;
    int match;
    struct tnode *left;
    struct tnode *right;
};
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *, char *, int, int *);
void treeprint(struct tnode *);
int getword(char *, int);
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
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int found = NO;
    int num;
    num = (--argc && (*++argv)[0] == '-') ? atoi(argv[0]+1) : 6;
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word, num, &found);
        }
        found = NO;
    }
    treeprint(root);
    return EXIT_SUCCESS;
}
int compare(char *, struct tnode *, int, int *);
struct tnode *addtree(struct tnode *p, char *w, int num, int *found){
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->match = *found;
        p->left = p->right = NULL;
    }
    else if ((cond = compare(w, p, num, found)) < 0) {
        p->left = addtree(p->left, w, num, found);
    }
    else if (cond > 0) {
        p->right = addtree(p->right, w, num, found);
    }
    return p;
}
int compare(char *s, struct tnode *p, int num, int *found){
    int i;
    char *t = p->word;
    for (i = 0; *s == *t; i++, t++) {
        if (*s == '\0') {
            return 0;
        }
    }
    if (i >= num) {
        *found = YES;
        p->match = YES;
    }
    return *s - *t;
}
void treeprint(struct tnode *p){
    if (p != NULL) {
        treeprint(p->left);
        if (p->match > 0) {
            printf("%s\n", p->word);
        }
        treeprint(p->right);
    }
}
struct tnode *talloc(void){
    return (struct tnode *) malloc(sizeof(struct tnode));
}