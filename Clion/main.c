//TODO : Comparatison XML / DTD  ||


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
    int sizeTable =0 ;
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

        for(int ij=0; ij <20; ij++){
           if (dtdResult[ij][0] != '\0'){
               // printf("%s \n",dtdResult[ij]);
               sizeTable++;
           }
        }

        if(doubleElement == 0 || Dtderror == 1 ||  Xmlerror == 1) {
            printf("Il y a une erreur dans votre dtd ou xml. \n");
            printf("%d\n", doubleElement);
            printf("%d\n", Dtderror);
            printf("%d\n", Xmlerror);
        } else {
            int longueurXml = fileSize(file);
            char* xml_charTable = (char*) malloc (longueurXml*sizeof(char));

            //int xml_Table = (int *)malloc(sizeTable*sizeof(int));

            char** xml_result = (char**) malloc(size*sizeof(char*));

            for (int i = 0; i < size ; i++) {
                xml_result[i] = (char*) malloc( sizeof(char) *size);
            }

            stockFile(donneePath,xml_result);

            int result = compare(xml_result,dtdResult,size,elementIndex);

            if (result == 1) {
                printf("Ce Xml et ce Dtd sont compatibles.\n");
            } else {
                printf("Ce Xml et ce Dtd ne sont pas compatibles.\n");
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
