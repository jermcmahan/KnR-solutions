#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define MAXTOKEN 100
int gettoken(void); 
void dclspec(void);
int compare(char **s, char **t);
int typequal(void);
int typespec(void);
int tokentype;
char token[100];
char name[100];
char out[100];
char datatype[100];
int prevtoken;
char buf[100];
int bufp = 0;
enum {NAME, PARENS, BRACKETS};
enum {NO, YES};
void dcl(void);
void dirdcl(void);
void errmsg(char *s);
void parmdcl(void){
    do {
        dclspec();
    } while (tokentype == ",");
    if (tokentype != ')') {
        errmsg("missing ) int parameter declaration\n");
    }
}
void dclspec(void){
    char temp[MAXTOKEN];
    temp[0] = '\0';
    gettoken();
    do {
        if (tokentype != NAME) {
            prevtoken = YES;
            dcl();
        }
        else if (typespec() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else if (typequal() == YES) {
            strcat(temp, " ");
            strcat(temp, token);
            gettoken();
        }
        else {
            errmsg("unknown type in parameter list!\n");
        }
    } while (tokentype != ',' && tokentype != ')');
    strcat(out, temp);
    if (tokentype == ",") {
        strcat(out, ",");
    }
}
int typespec(void){
    static char *types[] = {"char", "int", "void"};
    char *pt = token;
    if (bsearch(&pt, types, sizeof(types)/sizeof(char *), sizeof(char *),
     compare) == NULL) {
        return NO;
    }
    else {
        return YES;
    }
}
int typequal(void){
    static char *typeq[] = {"const", "volatile"};
    char *pt = token;
    if (bsearch(&pt, typeq, sizeof(typeq)/sizeof(char *), sizeof(char *),
     compare) == NULL) {
        return NO;
    }
    else {
        return YES;
    }
}
int compare(char **s, char **t){
    return strcmp(*s, *t);
}
int getch(void){
    return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c){
    if (bufp > 100) {
        printf("ungetch()");
    }
    else {
        buf[bufp++] = c;
    }
}
int main(int argc, char *argv[]) {
    while (gettoken() != EOF) {
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n') {
            printf("syntax error!\n");
        }
        printf("%s:%s %s\n", name, out, datatype);
    }
    return EXIT_SUCCESS;
}
void dcl(void){
    int ns;
    for (ns = 0; gettoken() == '*'; ) {
        ns++;
    }
    dirdcl();
    while (ns-- > 0) {
        strcat(out, " pointer to");
    }
}
void dirdcl(void){
    int type;
    if (tokentype == '(') {
        dcl();
        if (tokentype != ')') {
            errmsg("error: missing )\n");
        }
    }
    else if (tokentype == NAME) {
        if (name[0] != '\0') {
            strcpy(name, token);
        }
    }
    else {
        errmsg("error: expected name or (dcl)\n");
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(') {
        if (type == PARENS) {
            strcat(out, " function returning");
        }
        else if (type == '(') {
            strcat(out, " function expecting");
            parmdcl();
            strcat(out, " and returning");
        }
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
void errmsg(char *msg){
    printf("%s", msg);
    prevtoken = YES;
}
int gettoken(void){
    int c, getch(void);
    void ungetch(int);
    char *p = token;
    if (prevtoken == YES) {
        prevtoken = NO;
        return tokentype;
    }
    while ((c = getch()) == ' ' || c == '\t') {
        
    }
    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; ) {
            
        }
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); ) {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else {
        return tokentype = c;
    }
}
