#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encrypt(char* string, const char step){
    int i;
    for(i = 0; string[i]; ++i){
        string[i] += step;
        while(string[i] > 122){
            string[i] -= 26;
        }
    }
}

int main(int argc, const char* argv[]){
    if(argc < 3){
        printf("%s", "Error: not enough arguments given\n");
        return 1;
    }
    char* string = malloc(strlen(argv[1]));
    strcpy(string, argv[1]);
    int step = atoi(argv[2]);
    encrypt(string, step);
    printf("%s\n", string);
    free(string);
    return 0;
}
