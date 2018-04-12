#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int bitIndex(int from, int index){
    return (from & ( 1 << index )) >> index;
}

void lfsr(char* m, char key, const int* config, int lenConfig){
    int i;
    char state = key;
    //for each char
    for (i = 0; m[i]; ++i){
        //encript it
        char stream = state;
        m[i] ^= stream;
        //advance the stream one char forward
        int j;
        for(j = 0; j < sizeof(char); ++j){
            //get the next bit, for each bit in the char
            char bit = bitIndex(stream, config[0]);
            int k;
            for(k = 1; k < lenConfig; ++k){
                bit ^= bitIndex(stream, config[k]);
            }
            stream <<= 1; 
            stream |= 1 & bit; //mask away noise in higher bytes
        }
    }
}

int main(int argc, char* argv[]){
    if(argc < 4){
        printf("%s\n", "Not enough arguments given;");
        return 1;
    }
    char* m = malloc(strlen(argv[1]));
    strcpy(m, argv[1]);
    int lenConfig = argc-3;
    int* config = malloc(sizeof(int)*lenConfig);
    int i;
    for(i = 0; i < lenConfig; ++i){
        config[i] = atoi(argv[i+3]);
    }
    //encrypt
    lfsr(m, atoi(argv[2]), config, lenConfig);
    printf("%s\n", m);
    //cleanup
    free(m);
    free(config);
    return 0;
}
