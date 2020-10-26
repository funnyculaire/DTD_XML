//
//  main.c
//  projetC
//
//  Created by Rebecca on 21/10/2020.
//

#include "DTD_XML.h"
#include <stdio.h>
#include <stdlib.h>

void openFile(char* filePath, char* dtdPath);
char* getPath(int val);
int main(int argc, const char * argv[]) {
    
    char *file = getPath(1);
    char *dtd = getPath(0);
    
    openFile(file, dtd);
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
