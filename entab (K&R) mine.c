#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
#define TAB_SPACE 4
int getlines(char s[], int limit);
int main(int argc, char *argv[]) {
    int i = 0;
    int j = 0;
    int spaceCount = 0;
    int length;
    char line[MAX] = {0};
    while ((length = getlines(line, MAX)) > 0) {
        for (i = 0; i < length; i++) {
            if (line[i] == ' ') {
                spaceCount++;
            }
            else if (line[i] != ' ') {
                spaceCount = 0;
            }
            else if (spaceCount == TAB_SPACE) {
                i -= 3;
                length -= 3;
                line[i] = '\t';
                for (j = i + 1; j < length; j++) {
                    line[j] = line[j + 3];
                    //does this to every char after the tab to = the  
                    //char 3 ahead of it
                    //example line[7] = line[10] and so on 
                    //till the end which is line[997] = line[1000]
                    //line[MAX] = line[MAX + 3] but isnt over because
                    //we set the length and i back 3 spaces i -= 3
                }
                spaceCount = 0;
                line[length] = '\0';
            }
        }
        printf("%s\n", line);    
    }
    return EXIT_SUCCESS;
}
int getlines(char s[], int limit){
    int i, j, c;
    for (i = 0, j = 0; (c = getchar()) != EOF && c != '\n'; i++) {
        if (i < limit) {
            s[j++] = c;
        }
        else if (c == '\n') {
            if (i < limit) {
                s[j++] = c;
            }
            i++;
        }
    }
    s[j] = '\0';
    return i;
}