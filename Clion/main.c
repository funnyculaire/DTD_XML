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
int checkDtd(char* dtdPath);

int main(int argc, const char * argv[]) {
    int value;
    int restart = 1;
    int result;


        printf("Do you want to start? enter 1 for yes.\n");
        scanf("%d", &value);

        while(value == 1){
            char *file = getPath(1);
            //"/Users/bk/Desktop/C/Projet/DTD_XML/files/xml1.xml";
            char *dtd = getPath(0);
            //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtdGood1.dtd";
            //"/Users/bk/Desktop/C/Projet/DTD_XML/files/dtdErreur2.dtd"
            //openFile(file, dtd);

            result = checkDtd(dtd);

            printf("Do you want to relaunch the program? enter 1 for yes.\n");
            scanf("%d", &value);
        }


    return 0;
}
