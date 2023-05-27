#ifndef DATAMANIPULATION_H
#define DATAMANIPULATION_H

#include"./init.h"



void invertArray(piece array[TAILLETAB][TAILLETAB]);
char* coordsToStr(int x, int y);
int coumpt(piece chessTable[TAILLETAB][TAILLETAB],int player);
int remove(const char* fichierASupprimer);
int isFileExist(const char *fileName);
void svg(char text[], char mode[]);
void fileGest(char text[],char mode[],int create_mode);
void creation(char text[],char mode[]);
int splitInt(char* str);
char* readFileInString();
char* fenGen(piece tab[TAILLETAB][TAILLETAB]);
void fenRec(piece chess[TAILLETAB][TAILLETAB], char save[TAILLETAB][TAILLETAB], piece piecesBoard[TAILLEPPIECEECHECS]) ;
int loadSave(piece chess[TAILLETAB][TAILLETAB], piece piecesBoard[TAILLEPPIECEECHECS]);
char* concInt(char* str, int num) ;
void suppInt(char* str);
void backup(piece chessTable[TAILLETAB][TAILLETAB],int tour);


#endif