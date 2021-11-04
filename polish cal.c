#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define MAX 100
#define NUMBER '0'
#define NAME '1'
double pop(void);
void push(double f);
int getop(char s[]);
int getch(void);
void ungetch(int);
void math(char s[]);
void clear(void);
void print_help(void);
//int getlines(char s[], int limit);
int main(int argc, char *argv[]) {
    int type, i, var = 0;
    double op2;
    double op1, v;
    double variable[27] = {0.0};
    char s[MAX];
    //print_help();
    while ((type = getop(s)) != EOF) {
        switch (type) {
            case NUMBER:
                push(atof(s));
                break;
            case NAME:
                math(s);
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '%':
                op2 = pop();
                if (op2 != 0.0) {
                   fmod(pop(), op2);
                }
                else {
                   printf("error: division by zero\n");
                }
            case '=':
                pop();
                if (var >= 'A' && var <= 'Z') {
                   variable[var - 'A'] = pop();
                }
                else {
                   printf("error: no variable name!\n");
                }
            case '/':
               op2 = pop();
               if (op2 != 0.0)
                   push(pop() / op2);
               else
                   printf("error: zero divisor\n");
               break;
            //case 's':
            //push(sqrt(pop()));
            case '?':
               printf("\t%.8g\n", pop());
               break;
            case '!':
               clear();
               break;
            case '@':
               op2 = pop();
               push(op2);
               push(op2);
               break;
            case '~':
               op1 = pop();
               op2 = pop();
               push(op1);
               push(op2);
               break;
            
            case '\n':
               v = pop();
               printf("\t%.8g\n", v);
               break;
            default:
               if (type >= 'A' && type <= 'Z') {
                  push(variable[type - 'A']);
               }
               else if (type == 'v') {
                  push(v);
               }
               else {
                   printf("error: unknown command %s\n", s);
               }
            break; 
         }
        var = type;
    }
    return EXIT_SUCCESS;
}
int sp = 0;
double value[MAX];

int bufptr = 0;
double buffer[MAX];
// clear stack
void clear(void){
    sp = 0;
}
void math(char s[]){
    double op2;
    if (strcmp(s, "sin")) {
        push(sin(pop()));
    }
    else if (strcmp(s, "cos")) {
        push(cos(pop()));
    }
    else if (strcmp(s, "tan")) {
        push(tan(pop()));
    }
    else if (strcmp(s, "exp")) {
        push(exp(pop()));
    }
    else if (strcmp(s, "pow")) {
        op2 = pop();
        push(pow(pop(), op2));
    }
    else if (strcmp(s, "sqrt")) {
        push(sqrt(pop()));
    }
    else {
        printf("error: %s is not supported!\n", s);
    }
}
// returns the value of the first stack number
double pop(void){
    if (sp > 0) {
        return value[--sp];
    }
    else {
        printf("error: stack empty!\n");
        return 0.0;
    }
}
// puts the number of input into the array
void push(double f){
    if (sp < MAX) {
        value[sp++] = f;
    }
    else {
        printf("error: stack full, can't push %g\n", f);
    }
}
//organizes input into variables numbers negatives and fractions
//char line[]
//int li line index
//replace getch with line[i++]
//if line[li] == '\0' !getlines return eof
int getop(char s[]){
    int i, c;
    while ((s[0] = c = getch()) == ' ' || c == '\t') {
        
    }
    s[1] = '\0';
    i = 0;
    if (isupper(c)) {
        while (isupper(s[i++] = c)) {
            c = getch();
        }
        s[i] = '\0';
        return c;
    }
    /*if (islower(c)) {
        while (islower(s[i++] = c)) {
            c = getch();
        }
        s[i] = '\0';
        if (c != EOF) {
            ungetch(c);
        }
        if (strlen(s) > 1) {
            return NAME;
        }
        else {
            return c;
        }
    }*/
    if (!isdigit(c) && c != '.' && c != '-') {
        return c; 
        }     /* not a number */
    if (c == '-') {
        if ((c = getch()) == ' ') {
            return c;
        }
        else {
            s[++i] = c;
        }
    }
    else {
        s[++i] = c = getch();
    }
    if (isdigit(c)){    /* collect integer part */
        while (isdigit(s[++i] = c = getch())){
        }
    }
    if (c == '.') {    /* collect fraction part */
        while (isdigit(s[++i] = c = getch())){
                
            }
    }
    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }        
    return NUMBER;
}
// getchar() or return current filled array
int getch(void) {
    return (bufptr > 0) ? buffer[--bufptr] : getchar();
}
// adds elements of array s into array buffer and warns if too many elements are present
void ungetch(int c) {
    if (bufptr >= MAX) {
        printf("ungetch: too many characters!\n");
    }
    else {
        if (c != EOF) {
            buffer[bufptr++] = c;
        }
    }
}
/*void print_help(void)
{
        printf("The Polish Calculator\n");
        printf("-----------------------------------------------\n");
        printf("-> Enter equations in the form: \"1 1 + 2 5 + *\"\n");
        printf("-> Use \"A=1 B=2 C=3\" to store variables.\n");
        printf("-> Use \"A B C * *\" to use stored variables.\n");
        printf("-----------------------------------------------\n");
        printf(">>> Command Help:\n");
        printf(">>>     c:      Clear memory.\n");
        printf(">>>     p:      Print last character.\n");
        printf(">>>     s:      Swap last two characters.\n");
        printf(">>>     d:      Duplicate the last input.\n");
        printf(">>>     r:      Print the entire stack.\n");
        printf(">>>     v:      Print variable list.\n");
        printf(">>>     o:      pow(x,y), x^y, x > 0.\n");
        printf(">>>     i:      sin(x), sine of x.\n");
        printf(">>>     y:      cos(x), cosine of x.\n");
        printf(">>>     t:      tan(x), tangent of x.\n");
        printf(">>>     x:      exp(x), e^x, exponential function.\n");
        printf(">>>     q:      sqrt(x), x >= 0, square of x.\n");
        printf(">>>     f:      floor(x), largest integer not greater than x.\n");
        printf(">>>     l:      ceil(x), smallest integer not less than x.\n");
        printf(">>>     =:      Access the last successful solution.\n");
        printf(">>>     h:      Print this help text.\n");
}*/