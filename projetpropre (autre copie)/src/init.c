#include "../include/board.h"
#include "../include/veriffication.h"
#include "../include/dataManipulation.h"
#include "../include/init.h"

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
#define TAILLEPPIECEECHECS 20
#define PTSMAX 20
#define TROPCHER "Trop cher"
#define TAILLETAB 11
#define TAILLESTR 150
#define SAVENAME "sauvegarde.txt"
#define TAILLE_TAB_MOVE 100
#define TAILLE_MOVE 3
#define TAILLE_TYPE 1




piece reset(){
    piece p;
    p.type=0;
    p.price=0;
    p.taille=0;
    p.move[0][0] = 0;
    p.hasMove=0;
    return p;
}

piece makePawn1(){
    piece p;
    p.type='P';
    p.price=1;
    p.taille=4;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A0","A/", "@0","B0"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makePawn2(){
    piece p;
    p.type='p';
    p.price=1;
    p.taille=4;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2","A3", "@2","B2"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeRook(){
    piece p;
    p.type='R';
    p.price=5;
    p.taille=40;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2","A3","A4","A5","A6","A7","A8","A9","A:","A;",
        "B1","C1","D1","E1","F1","G1","H1","I1","J1","K1",
        "A0","A/","A.","A-","A,","A+","A*","A)","A(","A'",
        "@1","?1",">1","=1","<1",";1",":1","91","81","71"};
    for (int i=0; i<p.taille; i++) {
            strcpy(p.move[i], deplacement[i]);
        }
    p.hasMove=0;
    return p;
}

piece makeKnight(){
    piece p;
    p.type='N';
    p.price=3;
    p.taille=8;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"B3","C2","C0","B/","@/","?0","?2","@3"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeBishop(){
    piece p;
    p.type='B';
    p.price=3;
    p.taille=40;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"B2","C3","D4","E5","F6","G7","H8","I9","J:","K;",
        "B0","C/","D.","E-","F,","G+","H*","I)","J(","K'",
        "@0","?/",">.","=-","<,",";+",":*","9)","8(","7'",
        "@2","?3",">4","=5","<6",";7",":8","99","8:","7;"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeQueen(){
    piece p;
    p.type='Q';
    p.price=10;
    p.taille=80;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2","A3","A4","A5","A6","A7","A8","A9","A:","A;",
        "B2","C3","D4","E5","F6","G7","H8","I9","J:","K;",
        "B1","C1","D1","E1","F1","G1","H1","I1","J1","K1",
        "B0","C/","D.","E-","F,","G+","H*","I)","J(","K'",
        "A0","A/","A.","A-","A,","A+","A*","A)","A(","A'",
        "@0","?/",">.","=-","<,",";+",":*","9)","8(","7'",
        "@1","?1",">1","=1","<1",";1",":1","91","81","71",
        "@2","?3",">4","=5","<6",";7",":8","99","8:","7;"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeKing(){
    piece p;
    p.price=0;
    p.taille=8;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2","B2","B1","B0","A0","@0","@1","@2"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}



piece makePrince(){
    piece p;
    p.type='I';
    p.price=6;
    p.taille=24;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2","A3","A4",
        "B2","C3","D4",
        "B1","C1","D1",
        "B0","C/","D.",
        "A0","A/","A.",
        "@0","?/",">.",
        "@1","?1",">1",
        "@2","?3",">4"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeCentaur(){
    piece p;
    p.type='C';
    p.price=7;
    p.taille=48;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"@2","?3",">4","=5","<6",";7",":8","99","8:","7;",
        "B2","C3","D4","E5","F6","G7","H8","I9","J:","K;",
        "B0","C/","D.","E-","F,","G+","H*","I)","J(","K'",
        "@0","?/",">.","=-","<,",";+",":*","9)","8(","7'",
        "B3","C2","C0","B/","@/","?0","?2","@3"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeVaillant(){
    piece p;
    p.type='V';
    p.price=20;
    p.taille=88;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={
        "A2","A3","A4","A5","A6","A7","A8","A9","A:","A;",
        "B2","C3","D4","E5","F6","G7","H8","I9","J:","K;",
        "B1","C1","D1","E1","F1","G1","H1","I1","J1","K1",
        "B0","C/","D.","E-","F,","G+","H*","I)","J(","K'",
        "A0","A/","A.","A-","A,","A+","A*","A)","A(","A'",
        "@0","?/",">.","=-","<,",";+",":*","9)","8(","7'",
        "@1","?1",">1","=1","<1",";1",":1","91","81","71",
        "@2","?3",">4","=5","<6",";7",":8","99","8:","7;",
        "B3","C2","C0","B/","@/","?0","?2","@3"};
    for (int i=0; i<p.taille; i++) {
        strcpy(p.move[i], deplacement[i]);
    }
    p.hasMove=0;
    return p;
}

piece makeArcher(){
    piece p;
    p.type='A';
    p.price=8;
    p.taille=12;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2","A4","A5",
        "B1","D1","E1",
        "A0","A.","A-",
        "@1",">1","=1",};
    for (int i=0; i<p.taille; i++) {
            strcpy(p.move[i], deplacement[i]);
        }
    p.hasMove=0;
    return p;
}





piece placementBase(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour){
    
    for (int i=1;i<=4;i++){
        chessTable[TAILLETAB-i][i-1] = piecesBoard[tour];
    }
    for (int i=1;i<=4;i++){
        chessTable[TAILLETAB-i][TAILLETAB-i] = piecesBoard[tour];
    }

    chessTable[8][5] = piecesBoard[TAILLEPPIECEECHECS-2+tour];
    
}


