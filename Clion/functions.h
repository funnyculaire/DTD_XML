void getElement(int i, char** dtdResult, FILE* dtd, int* elementIndex, int j);
void createDataTable( char dtd[20][20]);
int checkElement(FILE *dtd);

void getTag(int i, char **str, FILE *dtd, int value);

//Get file path to open them
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

// Function to open the files & read them
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


// Function to check dtd format & get the different element in it
int checkDtd(char* dtdPath, char **dtdResult, int* elementIndex){
    FILE* dtd = fopen(dtdPath, "r");

    if(dtd == NULL){
        printf("Couldn't open DTD file.");
        return 0;
    }

    int cmp, i, value, count;
    char c;
    int j = 0;

    getElement(0, dtdResult, dtd, elementIndex, j);

    cmp = strcmp("<!DOCTYPE", &dtdResult[0][0]);

    if(cmp != 0){
        printf("Your dtd is in a wrong format.\n");
        return 0;
    }

    getElement(1, dtdResult, dtd, elementIndex, j);
    //printf("%s",dtdResult);



    // Get the element after the doctype
    i = 2;
    while(c != EOF) {
        count = 0;

        // read each characters until we find a "<" or a "]"
        while (c != 60 && c != 93) {

            //if we get a "(" we will get the information in it
            if(c == 40 && i != 2) {
                getTag(i, dtdResult, dtd, 41);
                c = 41;
                i += 1;
            }
            c = fgetc(dtd);

            //count help to find the end of a tag
            if(c == 62) {
                count += 1;
            }
        }

        if(c == EOF) {
            return 0;
        }

        // We check if the tag start with an "!ELEMENT" & if the tag is closed before opening another one
        if(count == 1 || i == 2) {
            value = checkElement(dtd);
        } else {
            value = 0;
        }

        if (value != 1 && value != 2) {
            printf("Your dtd is in a wrong format.\n");
            return 0;
        } else if(value == 2) {
            // the case where we got to the end of file
            return 1;
        }


        // we store our element's name in our array
        getElement(i, dtdResult, dtd, elementIndex, j);
        j += 1;

        if(c != 93 && c != 40) {
            c = fgetc(dtd);
        }

        i += 1;



    }

    return 1;
}

int checkElement(FILE *dtd) {
    char c;
    char **str;
    int cmp, i;

    str = (char**) malloc(sizeof(char *) * 1);

    str[0] = (char *) malloc(sizeof(char) * 50);

    while(c != EOF && c != 32){
        strncat(&str[0][0], &c, 1);
        c = fgetc(dtd);
        //printf("%c", c);
    }

    cmp = strcmp("!ELEMENT", &str[0][0]);

    free(str[0]);
    free(str);

    if (c == EOF) {
        return 2;
    }

    if(cmp == 0) {
        return 1;
    }

    return 0;
}

void getElement(int i, char** dtdResult, FILE* dtd, int* elementIndex, int j){
    char c;

    // In the same time as we stock our element, we also stock its index in another array to retrieve them later
    if(i > 1) {
        elementIndex[j] = i;
    }

    c = fgetc(dtd);
    //printf("%c",c);

    while(c != 32 ){
        strncat(&dtdResult[i][0], &c, 1);
        c = fgetc(dtd);
       // printf("%c",c);
    }
}


void getTag(int i, char **dtdResult, FILE *dtd, int value) {
    char c;
    int count = 0;
    //c = 92;
    //strncat(&dtdResult[i][0], &c, 1);

    c = fgetc(dtd);
    printf("%c",c);

// We stock what's in "()"
    while(c != value ){
        if(c == 40){
            count += 1;
        }
        strncat(&dtdResult[i][0], &c, 1);
        c = fgetc(dtd);
    }

    // count helps to know how many "(" we have inside one and hence we will continue stocking
    // characters until every "(" has its closed one
    while(count > 0){
        if(c == 41){
            count -= 1;
        }
        strncat(&dtdResult[i][0], &c, 1);
        c = fgetc(dtd);
    }
}


int checkDoublons(char **dtdResult, int *elementIndex, int size) {
    int i, j, k, count, cmp;
    //We are checking if any element is stored several times
    for(i = 0; i < size - 1; i++){
        count = 0;

        for(k = 0; k < size; k++){
            if(i == elementIndex[k]){
                count += 1;
            }
        }

        if(count > 0) {
            for (j = i + 1; j < size; j++) {
                for(k = 0; k < size; k++){
                    if(j == elementIndex[k] ){
                        cmp = strcmp(dtdResult[i], dtdResult[j]);

                        if(cmp == 0) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

char* getBalise(int index, char **dtd_table){
    int size = 20;

    char *balise = (char*)malloc(sizeof(char)*size);
    for(int i = 0; i<20; i++){
        if(i == index){
            for(int j = 0; j<20; j++){
                balise[j] = dtd_table[i][j];
                //printf("%c", balise[j]);
            }
        }
    }
    return balise;
}

void createDataTable(char dtd_table[20][20]) {

    FILE* dtd_file = fopen("/Users/kevincheng/Desktop/dtd_file.txt", "r");

    int i=0 , j=0;

    int mychar;

    //dtd_file = fopen("..\dtd_file.txt", "r");
    if( dtd_file != NULL){//Si fichier non vide
        do{
            mychar = fgetc(dtd_file);
            dtd_table[i][j] = mychar;//Save char in tab
            j++;
            if(mychar == 10){
                i++;//On saute une ligne
                j=0;//retour à la ligne pour le tableau
            }
            //printf("%c", mychar);
        } while (mychar != EOF);
        printf("\n");

        fclose(dtd_file);
    }
}

int getSize (char* table ){
    int size = 0;
    int i = 0;
    while (table[i] != '\0'){
        size++;
        i++;
    }
    return size-1 ;
}

int compare(char dtd_table[20][20], char **dtd_result, int sizeDtdResult){

    for(int mot = 0; mot <20; mot++) {
        printf("%s", dtd_table[mot]);
        for (int i = 1; i < sizeDtdResult; i++) {
            char *balise = getBalise(i, dtd_result);
            int sizeBalise = getSize(balise);
            int sizemot = getSize(dtd_table[mot]);

            if (sizeBalise != sizemot) {
                printf("KO %d",i);
                printf("%s\n",balise);
                printf("%s \n",dtd_table[mot]);
                printf("%d ||  %d", sizemot , sizeBalise);
                return 0;
            } else {
                for (int p = 0; p < sizemot; p++) {
                    if (p > 0) {
                        if (balise[p] != dtd_table[mot][p]) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
        return 1;
}

void clearTable(char dtd_table[20][20]){
    for(int i = 0; i<20; i++){
        for(int j = 0; j<20; j++){
            dtd_table[i][j] = '\0';
        }
    }
}

/*
char** dtd_result = NULL;
FILE *file = fopen("..\dtd_file.txt", "r");
char dtd_table[20][20];

//Iniatialisation des cases à 0;
clearTable(dtd_table);

int result = compare(file,dtd_result, dtd_table);

for(int i = 0; i<20; i++){
    for(int j = 0; j<20; j++){
        printf("%c",dtd_table[i][j]);
    }
    printf("\n");
} */

// //Affichage des données
//       for(int jk=0;jk<i;jk++){
//           printf("%s",&dtdResult[jk][0]);
//       }
