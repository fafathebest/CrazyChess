#ifndef BOARD_H
#define BOARD_H


#include"./init.h"


void initGame();
void genLogo(WINDOW* logo,coord terminal, char crazychess[10][100]);
void genPlay(WINDOW* play,coord terminal);
void genPlayContinue(WINDOW* play_continue,coord terminal);
void genQuit(WINDOW* quit,coord terminal);
void clearTerm();
void thingsToDo( WINDOW* logo,WINDOW* play,WINDOW* play_continue,WINDOW* quit);
void genTotal(WINDOW* logo,WINDOW* play,WINDOW* play_continue,WINDOW* quit,coord terminal,char crazychess[10][100]);
MEVENT getClickPos(MEVENT *event);
int validStartPos(coord position);
void replaceTab(piece chessTable[TAILLETAB][TAILLETAB],coord pairs[2],piece piecesBoard[TAILLEPPIECEECHECS],int round);
void resetTabFunc(piece chessTable[TAILLETAB][TAILLETAB]);
void genBoardStartup(WINDOW* boxv[TAILLETAB][TAILLETAB],WINDOW *win,WINDOW *boxwin[3][4],int height,int width, coord basePlacement,char *str,coord placement,int round,piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour);
void preGame(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS]);
void genPlateau (WINDOW* boxv[TAILLETAB][TAILLETAB],WINDOW* win,int height,int width,coord basePlacement,char *str,coord placement,piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS]);
int *game(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour,int verifCheck[TAILLETAB][TAILLETAB][2]);
int mainMenu();
int endMenu(int result);



#endif