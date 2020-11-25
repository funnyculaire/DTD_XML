//  main.c
//  projetC
//
//  Created by Rebecca on 21/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int checkDtd(char* dtdPath, char** dtdResult, int* elementIndex);
void getElement(int i, char** dtdResult, FILE* dtd, int* elementIndex, int j);
int checkElement(FILE* dtd);
void getTag(int i, char **dtdResult, FILE *dtd, int value);
int checkDoublons(char **dtdResult, int* elementIndex, int size);
int compare(char **xml_result, char **dtdResult, int longueurDtd, int* elementIndex);

int main(int argc, const char * argv[]) {
    int value , i,doubleElement;
    char ** dtdResult;
    int size = 50;
    int *elementIndex;
    int Dtderror;
    int Xmlerror;
    char * file;
    char * dtd;
    char* donneePath = "donnee_xml.txt";

    printf("Do you want to start? enter 1 for yes.\n");
    scanf("%d", &value);

    while(value == 1){

        dtdResult = (char**) malloc(sizeof(char *) * size);
        elementIndex = malloc(sizeof(int) * size); // pour check doublon

        file = malloc(sizeof(char) *500);
        dtd = malloc(sizeof(char)*500);
        for(i = 0; i < size ; i++){
            dtdResult[i] = (char *) malloc(sizeof(char) * size);
            elementIndex[i] = 2;
        }

        getFile(file);
        getDtd(dtd);

        if(checkDtd(dtd, dtdResult, elementIndex) == 0) {
            Dtderror = 1;
        } else {
            Dtderror = 0;
        }

        if(checkXml(file) == 0) {
            Xmlerror = 1;
        } else {
            Xmlerror = 0;
        }

        doubleElement = checkDoublons(dtdResult, elementIndex, size);

        if(doubleElement == 0 || Dtderror == 1) {
            printf("Il y a une erreur dans votre DTD\n");
        } else if(Xmlerror == 1){
            printf("Il y a une erreur dans votre XML\n");
        } else {
            char** xml_result = (char**) malloc(size*sizeof(char*));

            for (int i = 0; i < size ; i++) {
                xml_result[i] = (char*) malloc( sizeof(char) *size);
            }

            stockFile(donneePath,xml_result);

            int result = compare(xml_result,dtdResult,size,elementIndex);

            if (result == 1) {
                printf("Ce Xml est valide.\n");
            } else {
                printf("Ce Xml n'est pas valide.\n");
            }
        }

        for(i = 0; i < size ; i++){
            free(dtdResult[i]);
        }

        free(dtdResult);
        free(elementIndex);

        printf("Do you want to relaunch the program? enter 1 for yes.\n");
        scanf("%d", &value);
    }
    return EXIT_SUCCESS;
}