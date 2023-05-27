#ifndef VERRIFICATION_H
#define VERRIFICATION_H


#include"./init.h"



int isUpperCase(char c);

int isLowerCase(char c);

int isAlpha(char c);

int verifMove(piece chess[TAILLETAB][TAILLETAB],char str[TAILLE_MOVE],char (**listWords),char selectionjeux[3],piece piecesBoard[TAILLEPPIECEECHECS]);

char** placeToPlay(piece chess[TAILLETAB][TAILLETAB], char pos[3],WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement,int affichage,int verrif);

int *checkVerrif(int verifCheck[TAILLETAB][TAILLETAB][2],piece chess[TAILLETAB][TAILLETAB],WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement);

int *checkMate(piece chess[TAILLETAB][TAILLETAB], int verifCheck[TAILLETAB][TAILLETAB][2], char strTemp[3], WINDOW *boxv[TAILLETAB][TAILLETAB], int height, int width, coord basePlacement, piece piecesBoard[TAILLEPPIECEECHECS]);

#endif