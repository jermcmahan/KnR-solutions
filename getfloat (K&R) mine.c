#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int getfloat(float *ptr);
void ungetch(int c);
int getch(void);
char buffer[100];
int bufp = 0;
int main(int argc, char *argv[]) {
    float number;
    int c;
    while (c != EOF) {
        printf("Enter a number!\n");
        c = getfloat(&number);\
        if (number != 0.0) {
            printf("You entered: %f\n", number);
        }
        if (c == EOF) {
            printf("you have reached EOF!\n");
        }
        if (!isdigit(c) && !isspace(c) && c != EOF) {
            printf("error: not a number!\n");
            break;
        }
    }
    return EXIT_SUCCESS;
}
int getfloat(float *ptr){
    int c, sign;
    float power;
    while (isspace(c = getch())) {
        
    }
    if (!isdigit(c) && c != EOF && c != '-' && c != '+' && c != '.') {
        ungetch(c);
        return 0;
    }
    sign = (c == '-')? -1 : 1;
    if (c == '+' || c == '-') {
        c = getch();
    }
    for (*ptr = 0.0; isdigit(c); c = getch()) {
        *ptr = 10.0 * *ptr + (c - '0');
    }
    if (c == '.') {
        c = getch();
    }
    for (power = 1.0; isdigit(c); c = getch()) {
        *ptr = 10.0 * *ptr + (c - '0');
        power *= 10.0;
    }
    *ptr *= sign / power;
    if (c != EOF) {
        ungetch(c);
    }
    return c;
}
int getch(void){
    return (bufp > 0) ? buffer[--bufp] : getchar();
}
void ungetch(int c){
    if (bufp >= 1000) {
        printf("ungetch\n");
    }
    else {
        if (c != EOF) {
            buffer[bufp++] = c;
        }
    }
}