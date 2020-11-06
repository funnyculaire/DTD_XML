//
//  main.c
//  projetC
//
//  Created by Rebecca on 21/10/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void openFile(char* filePath, char* dtdPath);
char* getPath(int val);
int checkDtd(char* dtdPath);
int main(int argc, const char * argv[]) {
    int value;
    int restart = 1;
    int result;

    while(restart == 1){
        printf("Do you want to start? enter 1 for yes.\n");
        scanf("%d", &value);

        if(value == 1){
            char *file = getPath(1);
            //"/Users/bk/Desktop/C/ProjetC/DTD_XML/files/xml1.xml";
            char *dtd = getPath(0);
            //"/Users/bk/Desktop/C/ProjetC/DTD_XML/files/dtdGood1.dtd";
            //"/Users/bk/Desktop/C/ProjetC/DTD_XML/files/dtdErreur2.dtd"
            //openFile(file, dtd);

            result = checkDtd(dtd);

            printf("Do you want to relaunch the program? enter 1 for yes.\n");
            scanf("%d", &value);

            if(value != 1){
                restart = 0;
            }
        } else {
            restart = 0;
        }
    }

    return 0;
}

char* getPath(int val){
    int size = 500;
    int *pSize = &size;
    char *str[*pSize];
    if(val == 1){
        printf("Enter the path to the xml\n");
    } else if(val == 0){
        printf("Enter the path to the dtd\n");
    }

    scanf("%s", &str);
    printf("\n");

    for(int i = 0; i < *pSize; i++){
        if(str[i] == "\n"){
            str[i] = "\0";
        }
    }

    return str;
}

void openFile(char* filePath, char* dtdPath){
    FILE* f = fopen(filePath, "r");
    FILE* dtd = fopen(dtdPath, "r");

    if(f != NULL){
        char *str[1000];
        fread(str, 1, 1000, f);
        printf("%s",str);
    } else {
        printf("Couldn't open xml file.");
    }
    printf("\n");

    if(dtd != NULL){
        char *str2[1000];
        fread(str2, 1, 1000, dtd);
        printf("%s",str2);
    } else {
        printf("Couldn't open DTD file.");
    }
    printf("\n");
}

int checkDtd(char* dtdPath){
    FILE* dtd = fopen(dtdPath, "r");

    if(dtd == NULL){
        printf("Couldn't open DTD file.");
        return 0;
    }

    char *type = "<!DOCTYPE \0";
    char *element = "<!ELEMENT \0";
    char *endType = " [\n\0";
    char *end = ">\n\0";
    char *tab = "\t";
    char *str[11];
    char *str2[50];
    char *str3[50];
    int cmp, i;
    int j = 0;
    char c;
    fread(str, 1, 10, dtd);
    str[10] = "\0";

    cmp = strcmp(type, str);

    if(cmp != 0){
        printf("Your dtd is in a wrong format.\n");
        return 0;
    }

    cmp = 1;

    for(i = 0; cmp != 0; i++){
        c = fgetc(dtd);
        //fread(str2[i], 1, 1, dtd);
        cmp = strcmp(c, " ");
        if(cmp == 0) {
            str2[i] = "\0";
        } else {
            str2[i] = c;
        }
    }

    //fread(str2, 1, 5, dtd);
    printf("%s", str2);

    printf("Test.\n");

    return 1;
}
