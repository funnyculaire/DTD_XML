//
//  main.c
//  projetC
//
//  Created by Rebecca on 21/10/2020.
// gcc -Wall main.c -o prog pkg-config --cflags

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

void openFile(char* filePath, char* dtdPath);
char* getPath(int val);
int checkDtd(char* dtdPath, char** dtdResult, int* elementIndex, char** dtdAttribute, int *attributeSize);
void getElement(int i, char** dtdResult, FILE* dtd, int* elementIndex, int j);
int checkElement(FILE* dtd);
void getTag(int i, char **dtdResult, FILE *dtd, int value);
int checkDoublons(char **dtdResult, int* elementIndex, size);
void getAttribute(FILE *dtd, char **dtdAttribute, int k);
int checkAttribute(char **dtdAttribute, int *attributeSize, char **dtdResult, int* elementIndex, int* size);

int main(int argc, const char * argv[]) {
    int value, i, result, doubleElement, attError;
    char ** dtdResult;
    char ** dtdAttribute;
    int size = 50;
    int *elementIndex;
    int *attributeSize;
    int tabError = 1;

    printf("Do you want to start? enter 1 for yes.\n");
    scanf("%d", &value);

    while(value == 1){
        dtdResult = (char**) malloc(sizeof(char *) * size);
        dtdAttribute = (char**) malloc(sizeof(char *) * size);
        elementIndex = malloc(sizeof(int) * size);

        for(i = 0; i < size ; i++){
            dtdResult[i] = (char *) malloc(sizeof(char) * size);
            dtdAttribute[i] = (char *) malloc(sizeof(char) * size);
            elementIndex[i] = 2;
        }

        char *file = getPath(1);
        char *dtd = getPath(0);

        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtd3.dtd"
        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtd4.dtd"

        if(checkDtd(dtd, dtdResult, elementIndex, dtdAttribute, attributeSize) == 0) {
            tabError = 1;
        } else {
            tabError = 0;
        }

        doubleElement = checkDoublons(dtdResult, elementIndex, size);
        attError = checkAttribute(dtdAttribute, attributeSize, dtdResult, elementIndex, size);

        if(doubleElement == 0 || tabError == 1 || attError == 1) {
            printf("Il y a une erreur dans votre dtd\n");
        } else {
            printf("Continuité du code\n");
        }

        for(i = 0; i < size ; i++){
            free(dtdResult[i]);
        }

        //free(file);
        //free(dtd);
        free(dtdResult);
        free(elementIndex);

        printf("Do you want to relaunch the program? enter 1 for yes.\n");
        scanf("%d", &value);
    }


    return EXIT_SUCCESS;
}


