#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a helper function*/
int getColtransPos(int i, const int* cols, int numCols, int lenCol){
    int col = cols[i % numCols];
    int row = i / numCols;
    int pos = (col * lenCol) + row;
    return pos;
}

/*cols should be a permutation of [0,numCols)*/
char* coltrans(const char* istring, const int* cols, int numCols){
    int lenCol = (strlen(istring) + numCols - 1) / numCols;
    int lenOutput = lenCol * numCols;
    char* ostring = malloc( lenOutput + 1 );
    ostring[lenOutput] = '\0';
    int i;
    //fill in the cypher letters
    for(i = 0; istring[i]; ++i){
        int pos = getColtransPos(i, cols, numCols, lenCol);
        ostring[pos] = istring[i];
    }
    //fill in the 
    for(; i < lenOutput; ++i){
        int pos = getColtransPos(i, cols, numCols, lenCol);
        ostring[pos] = 'a';
    }
    return ostring;
}

int main(int argc, char* argv[]){
    //hand insufficient 
    if(argc < 3){
        printf("%s\n", "Error, not enough arguments given.");
        return 1;
    }

    //get the key
    int lenKey = argc - 2;
    int* key = malloc(sizeof(int)*lenKey);
    int i;
    for(i = 0; i < lenKey; ++i){
        key[i] = atoi(argv[i+2]);
    }
     
    //run the encription
    char* cyphertext = coltrans(argv[1], key, lenKey);
    printf("%s\n", cyphertext);

    //cleanup
    free(key);
    free(cyphertext);
    return 0;
}
