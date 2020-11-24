void getElement(int i, char** dtdResult, FILE* dtd, int* elementIndex, int j);
int checkElement(FILE *dtd);
void getTag(int i, char **str, FILE *dtd, int value);
void getAttribute(FILE *dtd, char **dtdAttribute, int k);

//Get file path to open them
void getFile(char *file) {
    printf("Enter the path to the xml\n");
    scanf("%s", file);
    printf("\n");

    for(int i = 0; i < 500; i++){
        if(file[i] == "\n"){
            file[i] = "\0";
        }
    }
}


void getDtd(char *dtd) {
    printf("Enter the path to the dtd\n");

    scanf("%s", dtd);
    printf("\n");

    for(int i = 0; i < 500; i++){
        if(dtd[i] == "\n"){
            dtd[i] = "\0";
        }
    }
}

// Function to check dtd format & get the different element in it
int checkDtd(char* dtdPath, char **dtdResult, int* elementIndex, char** dtdAttribute, int* attributeSize){
    FILE* dtd = fopen(dtdPath, "r");

    if(dtd == NULL){
        printf("Couldn't open DTD file.");
        return 0;
    }

    int cmp, i, value, count;
    char c;
    int j = 0;
    int k = 0;
    attributeSize = 0;

    getElement(0, dtdResult, dtd, elementIndex, j);

    cmp = strcmp("<!DOCTYPE", &dtdResult[0][0]);

    if(cmp != 0){
        printf("Your dtd is in a wrong format.\n");
        return 0;
    }

    getElement(1, dtdResult, dtd, elementIndex, j);

    // Get the element after the doctype
    i = 2;
    while(c != EOF) {
        if(value == 3){
            count = 1;
        } else {
            count = 0;
        }

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

        if (value != 1 && value != 2 && value != 3) {
            printf("Your dtd is in a wrong format.\n");
            return 0;
        } else if(value == 2) {
            // the case where we got to the end of file
            strncat(&dtdAttribute[k][0], "-1", 2);
            return 1;
        } else if(value == 1) {
            // we store our element's name in our array
            getElement(i, dtdResult, dtd, elementIndex, j);
            j += 1;
        } else if(value == 3) {
            getAttribute(dtd, dtdAttribute, k);
            k += 1;
            attributeSize = attributeSize + 1;
        }

        if(c != 93 && c != 40) {
            c = fgetc(dtd);
        }

        i += 1;
    }

    return 1;
}


int checkXml(char* file){
    FILE* xml = fopen(file, "r");

    if(xml == NULL){
        printf("Couldn't open XML file.");
        return 0;
    }

    char* version = "<?xml version=\"1.0\"";
    char* version2 = "<?xml version=\"1.1\"";
    char* chaine[20];
    //char* chaine2;
    int nbopen, nbclose, nboc, pos, again =1, again2 = 0;
    char letter;
    char letter2;
    FILE* fichier = NULL;

    fichier = fopen("donnee_xml.txt", "w+");
    rewind(xml);
    fgets(chaine, 20, xml);

    if (strcmp(chaine, version) == 0 || strcmp(chaine, version2)==0){
    }else{
        printf("La version n'est pas bonne");
        return 0;
    }

    nbopen = 1;
    nbclose = 0;
    nboc = 0;

    while (!feof(xml)){
        letter = fgetc(xml);
        letter2= letter;

        if (letter == '<'){
            nbopen +=1;
            pos = ftell(xml);

            if(fgetc(xml)=='/'){
                nboc +=1;
            }else{
                fseek(xml, -1, SEEK_CUR);

                while (again == 1){
                    letter2 = fgetc(xml);

                    if (letter2 == 32 || letter2 == 62 || letter2 == 9 || letter2 == 33){
                        again =0;
                    }else{
                        //printf("%c", letter2);
                        fputc(letter2, fichier);
                        fseek(fichier, 0, SEEK_CUR);
                        again2 = 1;
                    }
                }

                //printf("\n");
                if(again2 == 1){
                    fputc('\n', fichier);
                }

                fseek(xml, pos, SEEK_SET);
                again = 1;
                again2 = 0;
            }
        }

        if (letter == '>'){
            nbclose +=1;
        }

        if(letter == '/'){
            if(fgetc(xml) == '>'){
                nboc +=1;
                fseek(xml, -1, SEEK_CUR);
            }
        }
    }

    if (nbopen != nbclose){
        return 0;
    }

    fclose(fichier);
    return 1;
}

int checkElement(FILE *dtd) {
    char c;
    char **str;
    int cmp;

    str = (char**) malloc(sizeof(char *) * 1);

    str[0] = (char *) malloc(sizeof(char) * 50);

    while(c != EOF && c != 32){
        strncat(&str[0][0], &c, 1);
        c = fgetc(dtd);
    }

    cmp = strcmp("!ELEMENT", &str[0][0]);

    if (c == EOF) {
        free(str[0]);
        free(str);

        return 2;
    }

    if(cmp == 0) {
        free(str[0]);
        free(str);

        return 1;
    }

    cmp = strcmp("!ATTLIST", &str[0][0]);

    if(cmp == 0) {
        free(str[0]);
        free(str);
        return 3;
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

    while(c != 32 ){
        strncat(&dtdResult[i][0], &c, 1);
        c = fgetc(dtd);
    }
}

void getTag(int i, char **dtdResult, FILE *dtd, int value) {
    char c;
    int count = 0;

    c = fgetc(dtd);
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


int fileSize(char* file){
    FILE *Fichier = fopen(file, "r");
    int sizeXml=0;

    if(Fichier != NULL){
        while(!feof(Fichier)){
            if (fgetc(Fichier) == "\0"){
                sizeXml++;
            }
        }
    }

    fclose(Fichier);
    return sizeXml;
}

void stockFile(char *file, char** xml_result/*, char** xml_attribute */ ){
    FILE *Fichier = fopen(file,"r");

    if( Fichier != NULL ){
        int i=0;
        char c = fgetc(Fichier);
        // int count
        while(c != EOF){
            // count = 0;
            while( c != 10 && c != EOF){
                /*
             * if(c == 124) {
             *  count += 1;
             * }
             */
                //if(count != 0) {
                strncat(&xml_result[i][0], &c,1);
                c = fgetc(Fichier);
                //

                /*
             * strncat(&xml_attribute[i][0], &c,1);
                c = fgetc(Fichier);
             *
             * */
            }

            c = fgetc(Fichier);
            i++;
        }

        strncat(&xml_result[i][0],"-1",2);
        fclose(Fichier);
    } else {
        printf("Error");
        fclose(Fichier);
    }
}

void getAttribute(FILE *dtd, char **dtdAttribute, int k) {
    char c;

    c = fgetc(dtd);

    while(c != 62 ){
        strncat(&dtdAttribute[k][0], &c, 1);
        c = fgetc(dtd);
    }
}

int checkAttribute(char **dtdAttribute, int* attributeSize, char **dtdResult, int* elementIndex, int* size) {
    int i, j, k, l, count;
    char searchData[6] = "CDATA";
    char searchImplied[9] = "#IMPLIED";
    char searchRequired[10] = "#REQUIRED";
    char end[3] = "-1";

    for(i = 0, l = 1; i <= attributeSize && l != -1; i++){
        count = 0;

        if(strstr(&dtdAttribute[i][0], end) == NULL) {
            for (j = 2; j < size; j++) {
                for (k = 0; k < size; k++) {

                    if (j == elementIndex[k]) {
                        char *result = strstr(&dtdAttribute[i][0], &dtdResult[j][0]);

                        if (result != NULL) {
                            count += 1;
                        }
                    }
                }
            }

            if (count == 0) {
                return 1;
            }

            char *data = strstr(&dtdAttribute[i][0], searchData);
            char *implied = strstr(&dtdAttribute[i][0], searchImplied);
            char *required = strstr(&dtdAttribute[i][0], searchRequired);

            if (data == NULL) {
                return 1;
            }

            if (implied == NULL && required == NULL) {
                return 1;
            }
        } else {
            l = -1;
        }
    }

    return 0;
}


int compare(char **xml_result, char **dtdResult, int longueurDtd, int* elementIndex){
    char end[3] = "-1";
    int cmp = strcmp(&xml_result[0][0], &dtdResult[2][0]);
    int count, i, j, k, found;

    if (cmp == 0){

        for (i = 1; i < 20 ; i++) {
            found = 0;

            if(strstr(&xml_result[i][0], end) == NULL){

                for (j = 3; j < longueurDtd ; j++) {
                    count = 0;

                    for (k = 0; k < longueurDtd ; ++k) {

                        if(elementIndex[k] == j){
                            count += 1;
                        }
                    }

                    if (count>0){
                        cmp = strcmp(&xml_result[i][0], &dtdResult[j][0]);

                        if(cmp == 0){
                            found += 1;
                        }
                    }
                }

                if (found == 0){
                    return 0;
                }

            } else {
                return 1;
            }
        }

        return 1;

    } else {
        return 0;
    }
}