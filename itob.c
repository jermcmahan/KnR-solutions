#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char s[]);
void itob(int n, char s[], int b);
int main(int argc, char *argv[]) {
    char buffer[10] = {0};
    int i, j;
    while (scanf("%d", &i) != '\0') {
        scanf("%d", &j);
        itob(i, buffer, j);
        printf("%d in %d is %s\n", i, j, buffer);
    }   
    return EXIT_SUCCESS;
}
void itob(int n, char s[], int b){
    static char digits[] = {"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    int i, sign;
    i = 0;
    if (b < 2 || b > 32) {
        fprintf(stderr, "Ex3_5: Cannot support base %d\n", b);
        EXIT_FAILURE;
    }
    if ((sign = n) < 0) {
        n = -n;
    }
    do {
        s[i++] = digits[n % b];
    } while ((n /= b) > 0);
    if (sign < 0) {
        s[i++] = '-';
    }
    s[i] = '\0';
    reverse(s);
}
void reverse(char s[]){
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
