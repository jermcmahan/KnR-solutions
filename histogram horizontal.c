#include <stdio.h>
#include <stdlib.h>
#define max 10
#define TRUE 1
#define FALSE 0

int main(int argc, char *argv[]) {
    int c = EOF;
    int array[max + 1];
    int j = 0;
    int i = 0;
    int nc = 0;
    int state = TRUE;
    //= to array[i] = {0};
    for (i = 0; i <= max; i++) {
        array[i] = 0;
        //printf("%d\n", array[i]);<= test to check is all 0's
    }
    //printf("%d\n", i); <= test for overflow in loop
    //wordcount program with array and nc ++
    while ((c = getchar()) !=EOF) {
        ++nc;
        if (c == ' ' || c == '\n' || c == '\t') {
            nc--;
            state = FALSE;
        }
        if (state == FALSE) {
            if (nc != 0 && nc <= max) {
                ++array[nc];
                //++value of array at nc ex if nc == 5 it ++ [5] which 
                //counts how many of each numer under MAX there is
            } 
            state = TRUE;
            nc = 0; 
        }
    }
    //printing out legal numbers every ith position of array
    for (i = 1; i <= max; i++) {
        printf("|%d| ", i);
        for (j = 0; j < array[i]; j++) {
            putchar('*'); 
        }
            putchar('\n');
    }
    return EXIT_SUCCESS;
}