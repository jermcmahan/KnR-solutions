#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void expand(char s[], char t[]);
int main(int argc, char *argv[]) {
    char *s[] = { "a-z-", "z-a-", "-1-6-",
    "a-ee-a", "a-R-L", "1-9-1", "5-5", '\0'};
    char result[100];
    int i = 0;
    for (i = 0; s[i] != '\0'; i++) {
         expand(result, s[i]);
         printf("Unexpanded: %s\n", s[i]);
         printf("Expanded  : %s\n", result);
    }
       
    return EXIT_SUCCESS;
}
//EX3_3: Mismatched operands 'a-R'
//Unexpanded: a-R-L
//Expanded  : a-RQPONML
void expand(char s[], char t[]){
    char upper[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char lower[] = "abcdefghijklmnopqrstuvwxyz";
    char digits[] = "0123456789";
    int i = 0;
    int j = 0;
    char *start, *end, *p;
    while (t[i] != '\0') {
        if (t[i] == '-') {
            if (i == 0 || t[i+1] == '\0') {
                s[j++] = '-';
                i++;
            }
            else {
                if ((start = strchr(upper, t[i-1])) && (end = strchr(upper, t[i+1]))) {
                    
                }
                else if ((start = strchr(lower, t[i-1])) && (end = strchr(lower, t[i+1]))) {
                    
                }
                else if ((start = strchr(digits, t[i-1])) && (end = strchr(digits, t[i+1]))) {
                    
                }
                else {
                    fprintf(stderr, "EX3_3 mismatched operands %c - %c\n", t[i-1], t[i+1]);
                    s[j++] = t[i-1];
                    s[j++] = t[i++];
                    break;
                }
                p = start;
                while (p != end) {
                    s[j++] = *p;
                    if (end > start) {
                        p++;
                    }
                    else {
                        p--;
                    }
                }
                s[j++] = *p;
                i += 2;
            }
        }
        else {
            if (t[i+1] == '-' && t[i+2] != '\0') {
                i++;
            }
            else {
                s[j++] = t[i++];
            }
        }
    }
    s[j] = '\0';
}