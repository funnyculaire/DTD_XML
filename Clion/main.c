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

int checkDtd(char* dtdPath, char** dtdResult, int* elementIndex, char** dtdAttribute, int *attributeSize);
void getElement(int i, char** dtdResult, FILE* dtd, int* elementIndex, int j);
int checkElement(FILE* dtd);
void getTag(int i, char **dtdResult, FILE *dtd, int value);
int checkDoublons(char **dtdResult, int* elementIndex, size);
int compare(char **xml_result, char **dtdResult, int longueurDtd, int* elementIndex);
void getAttribute(FILE *dtd, char **dtdAttribute, int k);
int checkAttribute(char **dtdAttribute, int *attributeSize, char **dtdResult, int* elementIndex, int* size);
void getFile(char *file);
void getDtd(char *dtd);

int main(int argc, const char * argv[]) {
    int value, i, doubleElement, attError;
    char ** dtdResult;
    char ** dtdAttribute;
    int size = 50;
    int *elementIndex;
    int *attributeSize;
    int dtdError;
    int xmlError;
    char * file;
    char * dtd;
    char* donneePath = "donnee_xml.txt";

    printf("Do you want to start? enter 1 for yes.\n");
    scanf("%d", &value);

    while(value == 1){
        dtdResult = (char**) malloc(sizeof(char *) * size);
        dtdAttribute = (char**) malloc(sizeof(char *) * size);
        elementIndex = malloc(sizeof(int) * size);
        file = malloc(sizeof(char) * 500);
        dtd = malloc(sizeof(char) * 500);

        for(i = 0; i < size ; i++){
            dtdResult[i] = (char *) malloc(sizeof(char) * size);
            dtdAttribute[i] = (char *) malloc(sizeof(char) * size);
            elementIndex[i] = 2;
        }

        getFile(file);
        getDtd(dtd);

        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtd3.dtd"
        //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtd4.dtd"

        if(checkDtd(dtd, dtdResult, elementIndex, dtdAttribute, attributeSize) == 0) {
            dtdError = 1;
        } else {
            dtdError = 0;
        }

        if(checkXml(file) == 0) {
            xmlError = 1;
        } else {
            xmlError = 0;
        }

        doubleElement = checkDoublons(dtdResult, elementIndex, size);
        attError = checkAttribute(dtdAttribute, attributeSize, dtdResult, elementIndex, size);
//printf("file: %s\n", file);
        //printf("dtd: %s\n", dtd);

        if(doubleElement == 0 || dtdError == 1 || xmlError == 1 || attError == 1) {
            printf("Il y a une erreur dans votre dtd ou xml\n");
            printf("%d\n", doubleElement);
            printf("%d\n", dtdError);
            printf("%d\n", xmlError);
        } else {
            char** xml_result = (char**) malloc(size*sizeof(char*));
            //char**  xml_attribute = (char**) malloc(size*sizeof(char*));
            for (int i = 0; i < size ; i++) {
                xml_result[i] = (char*) malloc( sizeof(char) *size);
                // xml_attribute[i] = (char*) malloc( sizeof(char) *size);
            }

            stockFile(donneePath,xml_result/*, xml_attribute*/);

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

        //free(file);
        //free(dtd);
        free(dtdResult);
        free(elementIndex);

        printf("Do you want to relaunch the program? enter 1 for yes.\n");
        scanf("%d", &value);
    }


    return EXIT_SUCCESS;
}




