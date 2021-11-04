#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAXWORD 100
#define HASHSIZE 101
char buf[MAXWORD];
int bufp = 0;
struct nlist{
    struct nlist *next;
    char *name;
    char *defn;
};
static struct nlist *hashtab[HASHSIZE];
unsigned hash(char *s);
void error(int, char *);
int getch(void);
void ungetch(int);
void getdef(void);
int getword(char *, int);
struct nlist *install(char *, char *);
struct nlist *lookup(char *);
void undef(char *);
void ungets(char *);
void skipblanks(void);

int main(int argc, char *argv[]) {
    char w[MAXWORD];
    struct nlist *p;
    while (getword(w, MAXWORD) != EOF) {
        if (*w == '#') {
            getdef();
            printf("getdef successful!\n");
        }
        else if (!isalpha(w[0])) {
            printf("%s\n", w);
        }
        else if ((p = lookup(w)) == NULL) {
            printf("%s", w);
            printf(" lookup error\n");
        }
        else {
            ungets(p->defn);
        }
    }
    return EXIT_SUCCESS;
}

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
unsigned hash(char *s){
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++) {
        hashval = *s + 31 *hashval;
    }
    return hashval % HASHSIZE;
}
struct nlist *lookup(char *s){
    struct nlist *np;
    for (np = hashtab[hash(s)]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            return np;
        }
    }
    return NULL;
}
struct nlist *install(char *name, char *defn){
    struct nlist *np;
    unsigned hashval;
    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        if (np == NULL || (np->name = strdup(name)) == NULL) {
            return NULL;
        }
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
    else {
        free((void *) np->defn);
    }
    if ((np->defn = strdup(defn)) == NULL) {
        return NULL;
    }
    return np;
}
void getdef(void){
    int c, i;
    char def[MAXWORD], dir[MAXWORD], name[MAXWORD];
    skipblanks();
    if (!isalpha(getword(dir, MAXWORD))) {
        error(dir[0], "getdef: expecting a directive after '#'");
    }
    else if (strcmp(dir, "define") == 0) {
        skipblanks();
        if (!isalpha(getword(name, MAXWORD))) {
            error(name[0], "getdef: non-alpha - name expected");
        }
        else {
            skipblanks();
            for (i = 0; i < MAXWORD - 1; i++) {
                if ((def[i] = getch()) == EOF || def[i] == '\n') {
                    break;
                }
            }
            def[i] = '\0';
            if (i <= 0) {
                error('\n', "getdef: incomplete define");
            }
            else {
                printf("%s->%s\n", name, def);
                install(name, def);
            }
        }
    }
    else if (strcmp(dir, "undef") == 0) {
        skipblanks();
        if (!isalpha(getword(name, MAXWORD))) {
            error(name[0], "getdef: non-alpha in undef");
        }
        else {
            undef(name);
        }
    }
    else {
        error(dir[0], "getdef: expecting a directive after '#'");
    }
}
void error(int c, char *s){
    printf("error %d: %s\n", c, s);
    while (c != EOF && c != '\n') {
        c = getch();
    }
}
void skipblanks(void){
    int c;
    while ((c = getch()) == ' ' || c == '\t') {
        
    }
    ungetch(c);
}
void undef(char *s){
    int h;
    struct nlist *prev, *np;
    prev = NULL;
    h = hash(s);
    for (np = hashtab[h]; np != NULL; np = np->next) {
        if (strcmp(s, np->name) == 0) {
            break;
        }
        prev = np;
    }
    if (np != NULL) {
        if (prev == NULL) {
            hashtab[h] = np->next;
        }
        else {
            prev->next = np->next;
        }
        free((void *) np->name);
        free((void *) np->defn);
        free((void *) np);
    }
}
void ungets(char *s){
    int len = strlen(s);
    while (len > 0) {
        ungetch(s[--len]);
    }
}