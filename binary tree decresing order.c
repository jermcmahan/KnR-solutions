#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 100
#define NDISTINCT 1000
struct tnode{
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};
struct tnode *talloc(void);
struct tnode *talloc(void){
    return (struct tnode *) malloc(sizeof(struct tnode));
}
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
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
struct tnode *addtree(struct tnode *, char *);
int getword(char *, int);
void sortlist(void);
void treestore(struct tnode *);
struct tnode *list[NDISTINCT];
int non = 0;
int main(int argc, char *argv[]) {
    struct tnode *root;
    char word[MAXWORD];
    int i;
    root = NULL;
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }
    treestore(root);
    sortlist();
    for (i = 0; i < non; i++) {
        printf("[%d]: %s\n", list[i]->count, list[i]->word);
    }
    return EXIT_SUCCESS;
}
void treestore(struct tnode *p){
    if (p != NULL) {
        treestore(p->left);
        if (non < NDISTINCT) {
            list[non++] = p;
        }
        treestore(p->right);
    }
}
void sortlist(){
    int gap, i, j;
    struct tnode *temp;
    for (gap = non/2; gap > 0; gap /= 2) {
        for (i = gap; i < non; i++) {
            for (j = i-gap; j >= 0; j -= gap) {
                if ((list[j]->count) >= (list[j + gap]->count)) {
                    break;
                }
                temp = list[j];
                list[j] = list[j + gap];
                list[j + gap] = temp;
            }
        }
    }
}
struct tnode *addtree(struct tnode *p, char *w){
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    }
    else if (cond < 0) {
        p->left = addtree(p->left, w);
    }
    else {
        p->right = addtree(p->right, w);
    }
    return p;
}
