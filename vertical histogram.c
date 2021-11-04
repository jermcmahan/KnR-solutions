// veritcal histogram with function version in comments
// veritcal histogram with function version in comments
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH 10
#define IN 1
#define OUT 0
/*int i = 0;
int j = 0;
int c = 0;
int word_length = 0;
int inspace = 0; 
int firstletter = 0;
long value = 0;
long maxvalue = 0;
long length[MAX_LENGTH + 1] = {0};
void readhistogram(void);
void printhistogram(long maxvalue, long length[]);*/
int main(int argc, char *argv[]) {
    int i, j, c;
    i = j = c = 0;
    int word_length = 0;
    int inspace = 0;
    int firstletter = 0;
    long value = 0;
    long maxvalue = 0;
    long length[MAX_LENGTH +1] = {0};
    
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (inspace == 0) {
                inspace = 1;
                firstletter = 0;
                if (word_length <= MAX_LENGTH) {
                    if (word_length > 0) {
                        value = ++length[word_length - 1];
                        if (value > maxvalue) {
                            maxvalue = value;
                        }
                    }
                }
                else {
                    value = ++length[MAX_LENGTH];
                    if (value > maxvalue) {
                        maxvalue = value;
                    }
                }
            }
        }
        else {
            if (inspace == 1 || firstletter == 1) {
                firstletter = 0;
                inspace = 0;
                word_length = 0;
            }
            word_length++;
        }
    }
    for (value = maxvalue; value > 0; value--) {
        printf("%4ld  | ", value);
        for (i = 0; i <= MAX_LENGTH; i++) {
            if (length[i] >= value) {
                printf("*  ");
            }
            else {
                printf("   ");
            }
        }
        putchar('\n');
    }
    printf("      +");
    for (j = 0; j <= MAX_LENGTH; j++) {
        printf("---");
    }
    printf("\n       ");
    for (i = 1; i <= MAX_LENGTH; i++) {
        printf("%2d ", i);
    }
    printf(">%d\n", MAX_LENGTH);
    //readhistogram();
    //printhistogram(maxvalue, length);
    return EXIT_SUCCESS;
}
/*void readhistogram(void){
    while ((c = getchar()) != EOF) {
        if (c == ' ' || c == '\t' || c == '\n') {
            if (inspace == 0) {
                inspace = 1;
                firstletter = 0;
                if (word_length <= MAX_LENGTH) {
                    if (word_length > 0) {
                        value = ++length[word_length - 1];
                        if (value > maxvalue) {
                            maxvalue = value;
                        }
                    }
                }
                else {
                    value = ++length[MAX_LENGTH];
                    if (value > maxvalue) {
                        maxvalue = value;
                    }
                }
            }
        }
        else {
            if (inspace == 1 || firstletter == 1) {
                firstletter = 0;
                inspace = 0;
                word_length = 0;
            }
            word_length++;
        }
    }
}
void printhistogram(long maxvalue, long length[]){
    for (value = maxvalue; value > 0; value--) {
        printf("%4ld  | ", value);
        for (i = 0; i <= MAX_LENGTH; i++) {
            if (length[i] >= value) {
                printf("*  ");
            }
            else {
                printf("   ");
            }
        }
        putchar('\n');
    }
    printf("      +");
    for (j = 0; j <= MAX_LENGTH; j++) {
        printf("---");
    }
    printf("\n       ");
    for (i = 1; i <= MAX_LENGTH; i++) {
        printf("%2d ", i);
    }
    printf(">%d\n", MAX_LENGTH);
}*/