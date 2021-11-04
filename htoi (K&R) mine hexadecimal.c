#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define TRUE 1
#define FALSE 0
int hexalpha_to_int(int c);
unsigned int htoi(const char s[]);
int main(int argc, char *argv[]) {
    char *endp = NULL;
    char *test[] = { "a0", "0xf0", "7F", "700", "abcdef"};
    unsigned int result;
    unsigned int check;
    //int i = 0;
    //for (i = 0; test[i] != '\0'; i++) {}
    size_t numberOfTests = (sizeof(test) / sizeof(test[0]));
    size_t thisTest = 0;
    
    for (thisTest = 0; thisTest < numberOfTests; thisTest++) {
        result = htoi(test[thisTest]);
        check = strtoul(test[thisTest], &endp, 16);
        if ((*endp != '\0' && result == 0) || result == check) {
            printf("%s --> %u\n", test[thisTest], result);
        }
        else {
            printf("failed result is %u, correct is %u\n", result, check);
        }
    }
    return EXIT_SUCCESS;
}
int hexalpha_to_int(int c){
    char array[] = "aAbBcCdDeEfF";
    int i = 0;
    int answer = 0;
    for (i = 0; answer == 0 && array[i] != '\0'; i++) {
        if (c == array[i]) {
            answer = 10 + (i/2);
        }
    }
    return answer;
}
unsigned int htoi(const char s[]){
    unsigned int answer = 0;
    int i = 0;
    int valid = TRUE;
    int hex;
    if (s[i] == '0' && (s[i++] == 'x' || s[i++] == 'X')) {
        i += 2;
    }
    while (valid == TRUE && s[i] != '\0') {
        answer = answer * 16;
        if (s[i] >= '0' && s[i] <= '9') {
            answer += (s[i] - '0');
        }
        else {
            hex = hexalpha_to_int(s[i]);
            if (hex == 0) {
                valid = FALSE;
            }
            else {
                answer += hex;
            }
        }
        i++;
    }
    if (valid == FALSE) {
        answer = 0;
    }
    return answer;
}