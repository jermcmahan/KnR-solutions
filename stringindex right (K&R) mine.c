#include <stdio.h>
#include <stdlib.h>
//rightmost occurence
int stringindex(char s[], char t);
typedef struct{
    char *data;
    char testchar;
    int expected;
}TEST;
int main(int argc, char *argv[]) {
    TEST test[] = {{"Hello world", 'o', 7},
        {"This string is littered with iiiis", 'i', 32},
        {"No 'see' letters in here", 'c', -1}};
    size_t tests = sizeof test/ sizeof test[0];
    size_t i;
    int position;
    for (i = 0; i < tests; i++) {
        position = stringindex(test[i].data, test[i].testchar);
        printf("Searching [%s] for last occurrence of %c.\n",
        test[i].data, test[i].testchar);
        printf("Expected result: %d\n", test[i].expected);
        printf("%sorrect (%d).\n", position == test[i].expected ? "C" : "Inc", 
        position);
        if(position != -1) {
              printf("Character found was %c\n", test[i].data[position]);
        }
    }
    return EXIT_SUCCESS;
}
int stringindex(char s[], char t){
    int i = 0;
    int count = -1;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == t) {
            count = i;
        }
    }
    return count;
}