#ifndef INIT_H
#define INIT_H
#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



#define HAUTEUR 3
#define PLAY "Play to the game"
#define CONTINUE "Continue the game"
#define ECHEC "Echec"
#define QUIT "Quit the game"
#define PLACEMENT_ERR "Placement incorrect"
#define VIDE "  "
#define BOXWINSIZEX 4
#define BOXWINSIZEY 3
#define PTSMAX 20
#define TROPCHER "Trop cher"
#define TAILLETAB 11
#define TAILLEPPIECEECHECS 20
#define TAILLESTR 150
#define SAVENAME "sauvegarde.txt"
#define TAILLE_TAB_MOVE 100
#define TAILLE_MOVE 3
#define TAILLE_TYPE 1


typedef struct{
  char type;
  int price;
  char move[TAILLE_TAB_MOVE][TAILLE_MOVE];
  int taille;
  int hasMove;
}piece;

typedef struct{
    int x;
    int y;
}coord;

piece reset();
piece makePawn1();
piece makePawn2();
piece makeRook();
piece makeKnight();
piece makeBishop();
piece makeQueen();
piece makeKing();
piece makePrince();
piece makeCentaur();
piece makeVaillant();
piece makeArcher();

piece placementBase(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour);

#endif