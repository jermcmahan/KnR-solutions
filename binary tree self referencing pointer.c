#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100
struct linklist{
    int lnum;
    struct linklist *ptr;
};
struct tnode{
    char *word;
    struct linklist *lines;
    struct tnode *left;
    struct tnode *right;
};
struct linklist *lalloc(void);
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *p, char *, int);
void addin(struct tnode *p, int);
int getword(char *, int);
int comment(void);
int getch(void);
void ungetch(int);
int noiseword(char *);

void treeprint(struct tnode *p);
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int linenum = 1;
    root = NULL;
    while (getword(word, MAXWORD)) {
        if (isalpha(word[0]) && noiseword(word) == -1) {
            root = addtree(root, word, linenum);
        }
        else if (word[0] == '\n') {
            linenum++;
        }
    }
    treeprint(root);
    return EXIT_SUCCESS;
}
int noiseword(char *w){
    static char *nw[] = {
        "a",
        "an",
        "and",
        "are",
        "in",
        "is",
        "of",
        "or",
        "that",
        "the",
        "this",
        "to"
    };
    int cond, mid;
    int low = 0;
    int high = sizeof(nw) / sizeof(char *) - 1;
    while (low <= high) {
        mid = (low + high) / 2;
        if ((cond = strcmp(w, nw[mid])) < 0) {
            high = mid - 1;
        }
        else if (cond > 0) {
            low = mid + 1;
        }
        else {
            return mid;
        }
    }
    return -1;
}
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
            if (c == EOF) {
                break;
            }
        }
    }
    else if ((c == '\'' || c == '*') && c != EOF) {
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
void addin(struct tnode *p, int linenum){
    struct linklist *temp;
    temp = p->lines;
    while (temp->ptr != NULL && temp->lnum != linenum) {
        temp = temp->ptr;
    }
    if (temp->lnum != linenum) {
        temp->ptr = lalloc();
        temp->ptr->lnum = linenum;
        temp->ptr->ptr = NULL;
    }
}
struct tnode *addtree(struct tnode *p, char *w, int linenum){
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->lines = lalloc();
        p->lines->lnum = linenum;
        p->lines->ptr = NULL;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0) {
        addin(p, linenum);
    }
    else if (cond < 0) {
        p->left = addtree(p->left, w, linenum);
    }
    else {
        p->right = addtree(p->right, w, linenum);
    }
    return p;
}
void treeprint(struct tnode *p){
    struct linklist *temp;
    if (p != NULL) {
        treeprint(p->left);
        printf("%s: \n", p->word);
        for (temp = p->lines; temp != NULL; temp = temp->ptr) {
            printf("[%d] ", temp->lnum);
        }
        printf("\n");
        treeprint(p->right);
    }
}
struct linklist *lalloc(void){
    return (struct linklist *) malloc(sizeof(struct linklist));
}
struct tnode *talloc(void){
    return (struct tnode *) malloc(sizeof(struct tnode));
}