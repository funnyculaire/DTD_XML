void getElement(int i, char **str, FILE *dtd, int value);

int checkElement(FILE *dtd);

void getTag(int i, char **str, FILE *dtd, int value);

/*struct Element {
    char* name;
    char[] children;

};
typedef struct Element Element;
*/
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

char** checkDtd(char* dtdPath, char **str){
    FILE* dtd = fopen(dtdPath, "r");

    if(dtd == NULL){
        printf("Couldn't open DTD file.");
        return 0;
    }

    //char **str;
    int cmp, i, value, count;
    char c;

    getElement(0, str, dtd, 32);

    cmp = strcmp("<!DOCTYPE", &str[0][0]);

    if(cmp != 0){
        printf("Your dtd is in a wrong format.\n");
        return 0;
    }

    getElement(1, str, dtd, 32);

    printf("1st : %s\n", &str[1][0]);

    i = 2;
    while(c != 93) {
        count = 0;
//printf("#%c", c);
        while (c != 60 && c != 93) {
            if(c == 40 && i != 2) {
                getTag(i, str, dtd, 41);
                c = 41;
                printf("Enfant : %s\n", &str[i][0]);
                i += 1;
            }

            c = fgetc(dtd);

            if(c == 62) {
                count += 1;
            }


        }

        if(c == 93) {
            return 0;
        }

        if(count == 1 || i == 2) {
            value = checkElement(dtd);
        } else {
            value = 0;
        }

        if (value != 1) {
            printf("Your dtd is in a wrong format.\n");
            return 0;
        }

        getElement(i, str, dtd, 32);
        printf("Balise : %s\n", &str[i][0]);

        if(c != 93 && c != 40) {
            //printf("?");
            c = fgetc(dtd);
        }

        i += 1;
    }

    return str;
}

int checkElement(FILE *dtd) {
    char c;
    char **str;
    int cmp, i;

    str = (char**) malloc(sizeof(char **) * 8);

    for(i = 0; i < 8 ; i++){
        str[i] = (char **) malloc(sizeof(char *) * 50);
    }

    while(c != 32 ){
        strncat(&str[0][0], &c, 1);
        c = fgetc(dtd);
    }

    cmp = strcmp("!ELEMENT", &str[0][0]);
    //printf("<> : %s\n", &str[0][0]);

    for(i = 0; i < 8 ; i++){
        free(str[i]);
    }
    free(str);

    if(cmp == 0) {
        return 1;
    }

    return 0;
}

void getElement(int i, char **str, FILE *dtd, int value) {
    char c;

    c = fgetc(dtd);
    while(c != value ){
        strncat(&str[i][0], &c, 1);
        c = fgetc(dtd);
    }
}

void getTag(int i, char **str, FILE *dtd, int value) {
    char c;
    int count = 0;
    c = 92;
    strncat(&str[i][0], &c, 1);

    c = fgetc(dtd);

    while(c != value ){
        if(c == 40){
            count += 1;
        }
        strncat(&str[i][0], &c, 1);
        c = fgetc(dtd);
    }

    while(count > 0){
        if(c == 41){
            count -= 1;
        }
        strncat(&str[i][0], &c, 1);
        c = fgetc(dtd);
    }
}