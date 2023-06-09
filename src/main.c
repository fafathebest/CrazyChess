#include "../include/board.h"
#include "../include/veriffication.h"
#include "../include/dataManipulation.h"
#include "../include/init.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


int main (){
    int tour=0;
    int winOrNot=0;
    piece chessTable[TAILLETAB][TAILLETAB];
    resetTabFunc(chessTable);
    
    int verifCheck[TAILLETAB][TAILLETAB][2]={0};

    //Setup des pièces
    
    piece pion1 = makePawn1();
    pion1.type = 'P';
    piece pion2 = makePawn2();
    pion2.type = 'p';

    piece bishop1 = makeBishop();
    bishop1.type = 'B';
    piece bishop2 = makeBishop();
    bishop2.type = 'b';

    piece knight1 = makeKnight();
    knight1.type = 'N';
    piece knight2 = makeKnight();
    knight2.type = 'n';

    piece rook1 = makeRook();
    rook1.type = 'R';
    piece rook2 = makeRook();
    rook2.type = 'r';

    piece queen1 = makeQueen();
    queen1.type = 'Q';
    piece queen2 = makeQueen();
    queen2.type = 'q';

    piece king1  = makeKing();
    king1.type = 'K';
    piece king2  = makeKing();
    king2.type = 'k';

    piece prince1  = makePrince();
    prince1.type = 'I';
    piece prince2  = makePrince();
    prince2.type = 'i';

    piece centaur1  = makeCentaur();
    centaur1.type = 'C';
    piece centaur2  = makeCentaur();
    centaur2.type = 'c';

    piece michelVaillant1  = makeVaillant();
    michelVaillant1.type = 'V';
    piece michelVaillant2  = makeVaillant();
    michelVaillant2.type = 'v';

    piece archer1  = makeArcher();
    archer1.type = 'A';
    piece archer2  = makeArcher();
    archer2.type = 'a';

    piece piecesBoard[TAILLEPPIECEECHECS]={pion1,pion2,bishop1,bishop2,knight1,knight2,rook1,rook2,prince1,prince2,centaur1,centaur2,michelVaillant1,michelVaillant2,archer1,archer2,queen1,queen2,king1,king2};
    

    initGame(); 
    
    
    switch(mainMenu()){//selection mode de jeux
        case 1 :
        preGame(chessTable,piecesBoard);
        clearTerm();

        if(game(chessTable,piecesBoard,tour,verifCheck)[0]==1){
            winOrNot =1;
        }  
        endMenu(winOrNot);


        clearTerm();

        resetTabFunc(chessTable);
        backup(chessTable,0);
        endwin();
        exit(0);
    
        break;
        case 2 :

        tour = loadSave(chessTable,piecesBoard);
        
        if(game(chessTable,piecesBoard,tour,verifCheck)[0]==1){
            winOrNot =1;
        }   
        endMenu(winOrNot);

        clearTerm();
        resetTabFunc(chessTable);
        backup(chessTable,0);
        endwin();
        exit(0);

        break;
        default:
        clearTerm();
        endwin();
        exit(0);
        break;
        
    }
    
}

