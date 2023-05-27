#include "../include/board.h"
#include "../include/veriffication.h"
#include "../include/dataManipulation.h"
#include "../include/init.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


void invert_2d_array(piece array[TAILLETAB][TAILLETAB]) {
    for (int i = 0; i < TAILLETAB / 2; i++) {
        for (int j = 0; j < TAILLETAB; j++) {
            piece temp = array[i][j];
            array[i][j] = array[TAILLETAB - 1 - i][j];
            array[TAILLETAB - i][j] = temp;
        }
    }
}

char* coordsToStr(int x, int y) {

    char* str = (char*) malloc(sizeof(char) * 3);

    str[0] = 'A'+ x;
    str[1] = '1' + y;
    str[2] = '\0';

    return str;
}

int coumpt(piece chessTable[TAILLETAB][TAILLETAB],int player){
    int points=0;
    for (int i=0;i<TAILLETAB;i++){
        for (int e=0;e<TAILLETAB;e++){
            if (chessTable[i][e].type!=0){
                if (player*32+41<=chessTable[i][e].type && player*32+90 >= chessTable[i][e].type){
                    points += chessTable[i][e].price;
                }
                
            }
        }
    }
    return points;
}

int remove(const char* fichierASupprimer);

int isFileExist(const char *fileName){
    FILE* file = fopen(fileName, "r");
    if (file != NULL) {
        return 1;
    } 
    return 0;
}

void svg(char text[], char mode[]){
    FILE *f;
    f = fopen("sauvegarde.txt", mode);
    strcat(text, "\n");
    fprintf(f, "%s",text);
    fclose(f);
}

void fileGest(char text[],char mode[],int create_mode){
    if (create_mode){remove(SAVENAME);}
    svg(text,mode);
    
    
}

void creation(char text[],char mode[]) {fileGest(text,mode,1);}

int splitInt(char* str) {
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ' ' && i < len - 1 && str[i+1] >= '0' && str[i+1] <= '9') {
            str[i] = '\0';
            return str[i+1]-'0';
        }
    }
}

char* readFileInString() {
    FILE* fichier = fopen(SAVENAME, "r");
    if (fichier == NULL) {
        return NULL;
    }
    fseek(fichier, 0, SEEK_END);
    long taille = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);
    char* str = malloc((taille + 1) * sizeof(char));
    if (str == NULL) {
        fclose(fichier);
        return NULL;
    }
    size_t result = fread(str, sizeof(char), taille, fichier);
    if (result != taille) {
        fclose(fichier);
        free(str);
        return NULL;
    }
    str[taille] = '\0';
    fclose(fichier);
    return str;
}

char* fenGen(piece tab[TAILLETAB][TAILLETAB]) {
    char *str = malloc((TAILLETAB*TAILLETAB + TAILLETAB) * sizeof(char));
    int add = 0;
    int add1 = 0;
    for (int i = 0; i < TAILLETAB; i++) {
        for (int e = 0; e < TAILLETAB; e++) {
            if (tab[i][e].type == 0) {
                add++;
            }
            else {
                if (add != 0) {
                    *(str + add1) = '0' + add;
                    add1++;
                    add = 0;
                }
                if(tab[i][e].type=='P'+32*isLowerCase(tab[i][e].type)&&tab[i][e].hasMove){
                    *(str + add1) = 'Z'+32*isLowerCase(tab[i][e].type);
                }
                else{
                    *(str + add1) = tab[i][e].type;
                }
                add1++;
                
            }
        }
        if (add != 0) {
            *(str + add1) = '0' + add;
            add1++;
            add = 0;
        }
        if (i != TAILLETAB - 1) {
            *(str + add1) = '/';
            add1++;
        }
    }

    *(str + add1) = '\0';
    return str;
}

void fenRec(piece chess[TAILLETAB][TAILLETAB], char save[TAILLETAB][TAILLETAB], piece piecesBoard[TAILLEPPIECEECHECS]) {
    for (int i = 0; i < TAILLETAB; i++) {
        int e = 0;
        int col = 0;
        while (e < strlen(save[i])) {
            if ('0'<=save[i][e]&&'9'>=save[i][e]) {
                int numEmpty = save[i][e] - '0';
                for (int k = 0; k < numEmpty; k++) {
                    chess[i][col] = reset();
                    col++;
                }
                e++;
            }
            else {
                for (int l = 0; l < TAILLEPPIECEECHECS; l++) {
                    if (save[i][e]=='Z'+32*isLowerCase(save[i][e])){
                        chess[i][col] = piecesBoard[isLowerCase(save[i][e])];
                        chess[i][col].hasMove=1;
                        col++;
                        break;
                    }
                    else if (piecesBoard[l].type == save[i][e]) {
                        chess[i][col] = piecesBoard[l];
                        col++;
                        break;
                    }
                }
                e++;
            }
        }
    }
}

int loadSave(piece chess[TAILLETAB][TAILLETAB], piece piecesBoard[TAILLEPPIECEECHECS]){
    char* str = malloc((TAILLETAB*TAILLETAB+ TAILLETAB) * sizeof(char));
    char save[TAILLETAB][TAILLETAB];
    char delimiter[] = "/";

    strcpy(str,readFileInString());

    
    if(str==NULL){
        return 2;
    }
    int tour = splitInt(str);
    char *token = strtok(str, delimiter);

    int i=0;
    while (token != NULL) {
        strcpy(save[i] , token);
        token = strtok(NULL, delimiter);
        i++;
    } 

    fenRec(chess, save, piecesBoard);

    return tour;
}

char* concInt(char* str, int num) {
    int strLen = strlen(str);
    int numLen = snprintf(NULL, 0, "%d", num);

    char* result = malloc((strLen + numLen )*2* sizeof(char));
    strcpy(result, str);
    sprintf(result + strLen, " %d", num);

    return result;
}

void suppInt(char* str) {
    int len = strlen(str);

    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ' ' && i < len - 1 && str[i+1] >= '0' && str[i+1] <= '9') {
            str[i] = '\0';
            break;
        }
    }
}

void backup(piece chessTable[TAILLETAB][TAILLETAB],int tour){
    svg(concInt(fenGen(chessTable),tour),"w");
}

