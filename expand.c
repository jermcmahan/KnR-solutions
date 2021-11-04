#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
void expand(char s[], char t[]);
int main(int argc, char *argv[]) {
    char *s[] = {"a-z-", "z-a-", "-1-6-", "a-ee-a", "a-R-L", "1-9-1", "5-5",  
    NULL};
    char result[100];
    int i = 0;
    while (s[i]) {
        expand(result, s[i]);
        printf("Unexpanded: %s\n", s[i]);
        printf("Expanded: %s\n", result);
        i++;
    }
    return EXIT_SUCCESS;
}
void expand(char s[], char t[]){
    static char upper[27] = {"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
    static char lower[27] = {"abcdefghijklmnopqrstuvwxyz"};
    static char digits[11] = {"0123456789"};
    char *start, *end, *p;
    int i = 0;
    int j = 0;
    while (t[i]) {
        switch (t[i]) {
            case '-':
            if (i == 0 || t[i+1] == '\0') {
                s[j++] = '-';
                i++;
                break;
            } 
            else {
                if (isupper(t[i])){
                    start = strchr(upper, t[i-1]);
                    end = strchr(upper, t[i+1]);
                }
                if (isupper(t[i])){
                    start = strchr(lower, t[i-1]);
                    end = strchr(lower, t[i+1]);
                }
                if (isupper(t[i])){
                    start = strchr(digits, t[i-1]);
                    end = strchr(digits, t[i+1]);
                }
                else {
                    fprintf(stderr, "EX3_3: Mismatched operands '%c-%c'\n", t[i-1],
                    t[i+1]);
                    s[j++] = t[i-1];
                    s[j++] = t[i++];
                    break;
                }
            }
            p = start;
            while (p != end) {
                s[j++] = *p;
                if (end > start) {
                    ++p;
                }
                else {
                    --p;
                }
            }
            s[j++] = *p;
            i += 2;
        }
        break;
        default:
        if (t[i+1] == '-' && t[i+2] != '\0') {
            i++;
        }
        else {
            s[j++] = t[i++];
        }
            break;
        }
    }
    s[j] = '\0';
}