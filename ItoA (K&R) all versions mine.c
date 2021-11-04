#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void reverse(char s[]);
void itoa(int n, char s[], int width);
int main(int argc, char *argv[]) {
    char buffer[20];
    itoa(255, buffer, 0);
    printf("Buffer: %s\n", buffer);
    return EXIT_SUCCESS;
}
void itoa(int n, char s[], int width){
    int i = 0;
    int sign = n;
    do {
        s[i++] = abs(n % 10) + '0';
    } while (n /= 10);
    if (sign < 0) {
        s[i++] = '-';
    }
    int j = 0;
    while (j < width) {
        s[i++] = ' ';
        j++;
    }
    s[i] = '\0';
    reverse(s);
}
void reverse(char s[]){
    int c, i, j;
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
        c = s[i], s[i] = s[j], s[j] = c;
    }
}