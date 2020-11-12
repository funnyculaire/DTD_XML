//
//  main.c
//  projetC
//
//  Created by Rebecca on 21/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void openFile(char* filePath, char* dtdPath);
char* getPath(int val);
int checkDtd(char* dtdPath, char** dtdResult);
void getElement(int i, char** dtdResult, FILE* dtd, int value );
int checkElement(FILE* dtd);
void getTag(int i, char **dtdResult, FILE *dtd, int value);

int main(int argc, const char * argv[]) {
    int value, i, result;
    int restart = 1;
    char ** dtdResult;
    int size = 50;

    dtdResult = (char**) malloc(sizeof(char *) * size);

    for(i = 0; i < size ; i++){
        dtdResult[i] = (char *) malloc(sizeof(char) * size);
    }

    printf("Do you want to start? enter 1 for yes.\n");
    scanf("%d", &value);

    while(value == 1){
        char *file = getPath(1);
        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/xml1.xml";
        char *dtd = getPath(0);
        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtdGood1.dtd";
        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtdErreur2.dtd"
        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtd3.dtd"
        //openFile(file, dtd);
        if(checkDtd(dtd, dtdResult) == 0) {
            return 0;
        }

        //printf("Array : \n");
        /*for(i = 0; i < size ; i++){
            printf("M : %s\n", &dtdResult[i][0]);
        }*/

        printf("Do you want to relaunch the program? enter 1 for yes.\n");
        scanf("%d", &value);
    }


    return EXIT_SUCCESS;
}
