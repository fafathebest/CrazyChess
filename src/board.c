#include "../include/board.h"
#include "../include/veriffication.h"
#include "../include/dataManipulation.h"
#include "../include/init.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

//Initialise toutes les fonctionnalitées ncurses nécessaires
void initGame(){

    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    
    //initialisation des couleurs
    start_color(); 
    init_pair(4, COLOR_MAGENTA, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(1, COLOR_WHITE, COLOR_BLUE);
    init_pair(0, COLOR_BLUE, COLOR_RED);
    refresh();
    
}

//Interface menu ----------------------------------------------------------

void genLogo(WINDOW* logo,coord terminal, char crazychess[10][100]){
    logo=newwin(10, 100, 1, (terminal.x-100)/2);
    int y = (getmaxy(logo) - 3) / 2;
    int x = (getmaxx(logo) - strlen(crazychess[2])) / 2;
    for (int i=0;i<=5;i++){
        mvwprintw(logo, y-1+i, x, "%s", crazychess[i]);
    }
    box(logo, 0, 0);
    wrefresh(logo);
}

void genPlay(WINDOW* play,coord terminal){
    play=newwin(5, 50, 13, (terminal.x-50)/2);
    int y = (getmaxy(play) -1) / 2;
    int x = (getmaxx(play) - strlen(PLAY)) / 2;
    mvwprintw(play, y, x, "%s", PLAY);
    box(play, 0, 0);
    wrefresh(play);
}

void genPlayContinue(WINDOW* play_continue,coord terminal){
    play_continue=newwin(5, 50, 18, (terminal.x-50)/2);
    int y = (getmaxy(play_continue) -1) / 2;
    int x = (getmaxx(play_continue) - strlen(CONTINUE)) / 2;
    mvwprintw(play_continue, y, x, "%s", CONTINUE);
    box(play_continue, 0, 0);
    wrefresh(play_continue);
}

void genQuit(WINDOW* quit,coord terminal){
    quit=newwin(5, 50, 23, (terminal.x-50)/2);
    int y = (getmaxy(quit) -1) / 2;
    int x = (getmaxx(quit) - strlen(QUIT)) / 2;
    mvwprintw(quit, y, x, "%s", QUIT);
    box(quit, 0, 0);
    wrefresh(quit);
}

void clearTerm(){
    clear();
    refresh();
}   

void thingsToDo( WINDOW* logo,WINDOW* play,WINDOW* play_continue,WINDOW* quit){
    delwin(logo);
    delwin(play);
    delwin(play_continue);
    delwin(quit);
    clearTerm();
}

void genTotal(WINDOW* logo,WINDOW* play,WINDOW* play_continue,WINDOW* quit,coord terminal,char crazychess[10][100]){
    genLogo(logo,terminal,crazychess);
    genPlay(play,terminal);    
    genPlayContinue(play_continue,terminal);
    genQuit(quit,terminal);
}

//-------------------------------------------------------------------------

//segmente le terminal en cases de 6*3
MEVENT getClickPos(MEVENT *event){
    event->x /= 6 ;
    event->y /= 3 ;
    return *event;
}

//verrifie si la position est valide
int validStartPos(coord position){
    for (int i=0;i<=4;i++){
        if (position.x>=(i-1)&&position.x<=(TAILLETAB-i)&&position.y==(TAILLETAB-i)){
            return 1;
        }
    }
    return 0;
}

//change la valeur du tableau un fois validée
void replaceTab(piece chessTable[TAILLETAB][TAILLETAB],coord pairs[2],piece piecesBoard[TAILLEPPIECEECHECS],int round){
    if ((pairs[1].y-1*4+pairs[1].x-12)*2+round<TAILLEPPIECEECHECS){
        chessTable[pairs[0].y][pairs[0].x] = piecesBoard[((pairs[1].y-1)*4+pairs[1].x-12)*2+round];
    }
}

//reset l'échiquier (transforme toutes les cases de l'échiquier en reset)
void resetTabFunc(piece chessTable[TAILLETAB][TAILLETAB]){
    for (int i=0;i<TAILLETAB;i++){
        for (int e=0;e<TAILLETAB;e++){
            chessTable[i][e] = reset();
        }
    }
}


//génère l'affichage du tableau
void genBoardStartup(WINDOW* boxv[TAILLETAB][TAILLETAB],WINDOW *win,WINDOW *boxwin[3][4],int height,int width, coord basePlacement,char *str,coord placement,int round,piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour){
    char inCase;

    win = newwin(height*TAILLETAB, width*6, basePlacement.y, basePlacement.x+width*TAILLETAB);
    box(win,0,0);
    wrefresh(win);

    for (int i = 1;i<=strlen(PLACEMENT_ERR);i++){
        mvwaddch(win,1,i,' ');
        wrefresh(win);

    }
    if(strcmp(str,PLACEMENT_ERR)==0){
        mvwprintw(win,1,1,"%s",PLACEMENT_ERR);
        wrefresh(win);
       
    }
    else if(strcmp(str,TROPCHER)==0){
        mvwprintw(win,1,1,"%s",TROPCHER);
        wrefresh(win);
       
    }
    else if (*str!=' '&&*(str+1)!=' '){
        

        mvwaddch(win,1,2,*str);
        if (*(str+1)>'9'){
            mvwaddch(win,1,3,'1');
            mvwaddch(win,1,4,*(str+1)-10);
        }else{
        mvwaddch(win,1,3,*(str+1));
        }

        wrefresh(win);
    }  
   

    for(int i=0;i<TAILLETAB;i++){
        for(int e=0;e<TAILLETAB;e++){
            boxv[i][e]=newwin(height, width, basePlacement.y+height*i, basePlacement.x+width*e);
            wbkgd(boxv[i][e], COLOR_PAIR((i*TAILLETAB+e)%2));
            if (chessTable[i][e].type==0){
                inCase = ' ';
            }
            else{
                inCase = chessTable[i][e].type;
            }
            mvwaddch(boxv[i][e], 1, 2, inCase);
              
            wrefresh(boxv[i][e]);
        }
    }

    for(int i=0;i<3;i++){
        for(int e=0;e<4;e++){
            boxwin[i][e]=newwin(height, width, basePlacement.y+height*i+3, basePlacement.x+width*TAILLETAB+width*e+6);
            wbkgd(boxwin[i][e], COLOR_PAIR(1)); 
            if ((i*4+e)*2+tour<TAILLEPPIECEECHECS-2&&round!=3){
                mvwaddch(boxwin[i][e], 1, 2,(piecesBoard[(i*4+e)*2+tour].type));
            }
            wrefresh(boxwin[i][e]);
        }

    }

    if (round%2){
        if (placement.x==32&&placement.y==32){
            wbkgd(boxv[placement.y][placement.x], COLOR_PAIR((placement.x*TAILLETAB+placement.y)%2));
            wrefresh(boxv[placement.y][placement.x]);
        }
        else{
            wbkgd(boxv[placement.y][placement.x], COLOR_PAIR(2));
            wrefresh(boxv[placement.y][placement.x]);
        }
    }
    else if(round%2==0){
        if (placement.x==32&&placement.y==32){
            wbkgd(boxwin[placement.y][placement.x], COLOR_PAIR((placement.x*TAILLETAB+placement.y)%2));
            wrefresh(boxwin[placement.y][placement.x]);
        }
        else{
            wbkgd(boxwin[placement.y-1][placement.x-12], COLOR_PAIR(3));
            wrefresh(boxwin[placement.y-1][placement.x-12]);
        }
    }
}

//génère l'iterraction avec le programme
void preGame(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS]){

    piece tempChessTable[TAILLETAB][TAILLETAB];

    coord pairs[2];
    int selecteur = 0;


    coord dplc;
    dplc.x=32;
    dplc.y=32;

    coord terminal;
    terminal.y = 0;
    terminal.x = 0;

    getmaxyx(stdscr, terminal.y, terminal.x); 

    int height = HAUTEUR;
    int width = 2*height;
    coord basePlacement;

    basePlacement.y = 3;
    basePlacement.x = 6*2;

    WINDOW* boxv[TAILLETAB][TAILLETAB];
    WINDOW* win;
    WINDOW *boxwin[3][4];
    
    coord test;
    test.y=0;
    test.x=0;
    MEVENT event;
    coord placement;
    placement.x = 31;
    placement.y = 31;

    int points[2]={0};
    int tour=0;


    for (int z=0;z<2;z++){
        placementBase(chessTable,piecesBoard,tour);
        genBoardStartup(boxv,win,boxwin,height,width,basePlacement,VIDE,dplc,selecteur,chessTable,piecesBoard,selecteur);
        while (points[tour]!=PTSMAX){
            placementBase(chessTable,piecesBoard,tour);
            int ch = getch();
            if (ch == KEY_MOUSE) {
                points[tour]=coumpt(chessTable,tour);

                getmaxyx(stdscr, test.y, test.x);
                    
                if (getmouse(&event) == OK) {
                                    
                    event = getClickPos(&event);
                    placement.x = event.x-2;
                    placement.y = event.y-1;              
                    if (placement.x>=12&&placement.x<16 && placement.y>=1 &&placement.y<4 && selecteur==0){
                        pairs[1]=placement;
                        char* str = coordsToStr(placement.x, placement.y);

                        if(  points[tour] + piecesBoard[((pairs[1].y-1)*4+pairs[1].x-12)*2+tour].price <=PTSMAX){
                            genBoardStartup(boxv,win,boxwin,height,width,basePlacement,str,placement,selecteur,chessTable,piecesBoard,tour);
                            selecteur=1;
                        }
                        else{
                            genBoardStartup(boxv,win,boxwin,height,width,basePlacement,TROPCHER,dplc,selecteur,chessTable,piecesBoard,tour);

                        }
                            
                    }

                    else if (placement.x>=0&&placement.x<TAILLETAB && placement.y>=0&&placement.y<TAILLETAB && selecteur){
                        pairs[0]=placement;
                        char* str = coordsToStr(placement.x, placement.y);

                        if (validStartPos(pairs[0])){
                            replaceTab(chessTable, pairs,piecesBoard,tour);
                            genBoardStartup(boxv,win,boxwin,height,width,basePlacement,str,placement,selecteur,chessTable,piecesBoard,tour);
                        }
                        else{
                            genBoardStartup(boxv,win,boxwin,height,width,basePlacement,PLACEMENT_ERR,dplc,selecteur,chessTable,piecesBoard,tour);
                        }
                            

                        selecteur=0;
                        placementBase(chessTable,piecesBoard,tour);
                        if ( coumpt(chessTable,tour) == PTSMAX && !tour){
                            for (int i=0;i<TAILLETAB;i++){
                                for (int e=0;e<TAILLETAB;e++){
                                    tempChessTable[i][e]=chessTable[i][e];
                                    chessTable[i][e] = reset();
                                }
                            }
                            tour = 1;
                        }

                        if ( coumpt(chessTable,tour) == PTSMAX &&  tour){
                            for (int i=0;i<TAILLETAB;i++){
                                for (int e=0;e<TAILLETAB;e++){
                                    if (chessTable[i][e].type == 0){
                                        chessTable[i][e] = tempChessTable[TAILLETAB-i][e];
                                    }
                                    
                                        
                                }
                            }
                            invertArray(chessTable);
                            points[tour]=PTSMAX;
                        }
                    }
                    else{
                        genBoardStartup(boxv,win,boxwin,height,width,basePlacement,PLACEMENT_ERR,dplc,!selecteur,chessTable,piecesBoard,tour);
                    }
                }
            }
        }
    }
    placementBase(chessTable,piecesBoard,0);

}

//génère l'affichage du tableau
void genPlateau (WINDOW* boxv[TAILLETAB][TAILLETAB],WINDOW* win,int height,int width,coord basePlacement,char *str,coord placement,piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS]){
    char inCase;
    
    for(int i=0;i<TAILLETAB;i++){
        for(int e=0;e<TAILLETAB;e++){
            boxv[i][e]=newwin(height, width, basePlacement.y+height*i, basePlacement.x+width*e);
            wbkgd(boxv[i][e], COLOR_PAIR((i*TAILLETAB+e)%2));
            if (chessTable[i][e].type==0){
                inCase = ' ';
            }
            else{
                inCase = chessTable[i][e].type;
            }
            mvwaddch(boxv[i][e], 1, 2, inCase);
              
            wrefresh(boxv[i][e]);
        }
    }

    
    win = newwin(height*TAILLETAB, width*6, basePlacement.y, basePlacement.x+width*TAILLETAB);
    box(win,0,0);
    wrefresh(win);

    

    for (int i = 1;i<=strlen(PLACEMENT_ERR);i++){
        mvwaddch(win,1,i,' ');
        wrefresh(win);

    }
    if(strcmp(str,ECHEC)==0){
        for (int i = 1;i<=strlen(ECHEC);i++){
            mvwprintw(win,1,1,"%s",ECHEC);
            wrefresh(win);
        }
    }

    else if(strcmp(str,PLACEMENT_ERR)==0){
        mvwprintw(win,1,1,"%s",PLACEMENT_ERR);
        wrefresh(win);
       
    }
    else if (*str!=' '&&*(str+1)!=' '){
        

        mvwaddch(win,1,2,*str);
        if (*(str+1)>'9'){
            mvwaddch(win,1,3,'1');
            mvwaddch(win,1,4,*(str+1)-10);
        }else{
        mvwaddch(win,1,3,*(str+1));
        }

        wrefresh(win);
    }  

    if (placement.x==32&&placement.y==32){
        wbkgd(boxv[placement.y][placement.x], COLOR_PAIR((placement.x*TAILLETAB+placement.y)%2));
        wrefresh(boxv[placement.y][placement.x]);
    }
    else{
        wbkgd(boxv[placement.y][placement.x], COLOR_PAIR(2));
        wrefresh(boxv[placement.y][placement.x]);
    }
}

//génère l'iterraction avec le programme
int *game(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour,int verifCheck[TAILLETAB][TAILLETAB][2]){
    
    piece tempChessTable[TAILLETAB][TAILLETAB];
    resetTabFunc(tempChessTable);
    
    coord dplc;
    dplc.x=32;
    dplc.y=32;
    
    coord terminal;
    terminal.y = 0;
    terminal.x = 0;

    getmaxyx(stdscr, terminal.y, terminal.x); 

    int height = HAUTEUR;
    int width = 2*height;
    coord basePlacement;

    basePlacement.y = 3;
    basePlacement.x = 6*2;

    WINDOW* boxv[TAILLETAB][TAILLETAB];
    WINDOW* win;
    
    genPlateau(boxv,win,height,width,basePlacement,VIDE,dplc,chessTable,piecesBoard);
    genPlateau(boxv,win,height,width,basePlacement,VIDE,dplc,chessTable,piecesBoard);
    
    coord test;
    test.y=0;
    test.x=0;
    MEVENT event;
    coord placement;
    placement.x = 0;
    placement.y = 0;

    int selection = 0;
    char selectionjeux[3];
    char strTemp[3];
    strcpy(strTemp,"11");
    

    while (1){
        
        int ch = getch();
        if (ch == KEY_MOUSE) {
            
            getmaxyx(stdscr, test.y, test.x);
            if (terminal.y!=test.y||terminal.x!=test.x){
                genPlateau(boxv,win,height,width,basePlacement,VIDE,dplc,chessTable,piecesBoard);
            }
            if (getmouse(&event) == OK) {
                
                event = getClickPos(&event);
                placement.x = event.x-2;
                placement.y = event.y-1;

                
                if (placement.x>=0&&placement.x<TAILLETAB && placement.y>=0&&placement.y<TAILLETAB){
                    
                    char* str = coordsToStr(placement.x, placement.y);

                    if (tour*32+65<=chessTable[placement.y][placement.x].type && tour*32+90 >= chessTable[placement.y][placement.x].type&&!selection){
                        
                        genPlateau(boxv,win,height,width,basePlacement,str,placement,chessTable,piecesBoard);
                        placeToPlay(chessTable,str ,boxv,height,width,basePlacement,1,0);
                        strcpy(selectionjeux,str);
                        selection=1;
                        
                    }
                    else if (verifMove(chessTable,str,placeToPlay(chessTable,selectionjeux ,boxv,height,width,basePlacement,0,0),selectionjeux,piecesBoard)){

                        if (selection){
                            piece tempChessTable[TAILLETAB][TAILLETAB];
                            
                            resetTabFunc(tempChessTable);
                            for (int i=0;i<TAILLETAB;i++){
                                for (int e=0;e<TAILLETAB;e++){
                                    
                                    if(isAlpha(chessTable[i][e].type)){
                                        tempChessTable[i][e]=chessTable[i][e];
                                        //printw("%c",chessTable[i][e].type);
                                    }
                                    else{
                                        //tempChessTable[i][e]=reset();
                                        //printw(" ");
                                    }
                                }
                                //printw("\n");
                            }//Marche par la voix du saint esprit

                            changes(tempChessTable,selectionjeux,str);
                            
                            int *verrifTab = checkVerrif(verifCheck,tempChessTable ,boxv, height, width, basePlacement);
                            
                            /*for (int i=0;i<2;i++){
                                printw("%d",verrifTab[i]);
                            }*/

                            if(!verrifTab[!tour]){
                                //echecs=checkMate(chessTable,checkVerrif(verifCheck,tempChessTable ,boxv, height, width, basePlacement),boxv, height,width, basePlacement);
                                changes(chessTable,selectionjeux,str);
                                genPlateau(boxv,win,height,width,basePlacement,str,dplc,chessTable,piecesBoard);
                                if (tour){tour=0;}else{tour=1;} 
                                strcpy(strTemp,str);
                            }
                            else{
                                //checkMate(chessTable,verifCheck,strTemp,boxv,height,width,basePlacement,piecesBoard);
                                genPlateau(boxv,win,height,width,basePlacement,ECHEC,dplc,chessTable,piecesBoard);
                                int *mateOrNot = checkMate(tempChessTable,verifCheck,str,boxv,height,width,basePlacement,piecesBoard);        
                                if(mateOrNot[0]==1||mateOrNot[1]==1){
                                    return mateOrNot;
                                }

                            }

                            
                             

                            

                                                   
                            
                            /*resetTabFunc(tempChessTable);
                            printw("pass");
                            for (int i=0;i<TAILLETAB;i++){
                                for (int e=0;e<TAILLETAB;e++){
                                    tempChessTable[i][e]=chessTable[i][e];
                                }
                            }
                            changes(tempChessTable,selectionjeux,str);
                            
                            if(checkVerrif(verifCheck,tempChessTable ,boxv, height, width, basePlacement)){
                                
                                

                                resetTabFunc(chessTable);
                                for (int i=0;i<TAILLETAB;i++){
                                    for (int e=0;e<TAILLETAB;e++){
                                        chessTable[i][e]=tempChessTable[i][e];
                                    }
                                }
                                if (tour){tour=0;}else{tour=1;}
                            }
                            else{genPlateau(boxv,win,height,width,basePlacement,PLACEMENT_ERR,dplc,chessTable,piecesBoard);} */

                        }
                        else{
                            genPlateau(boxv,win,height,width,basePlacement,PLACEMENT_ERR,dplc,chessTable,piecesBoard);
                        }
                        selection=0;
                    } 
                    
                    else{
                        genPlateau(boxv,win,height,width,basePlacement,PLACEMENT_ERR,dplc,chessTable,piecesBoard);
                        selection=0;
                    }

                }
                else {
                    genPlateau(boxv,win,height,width,basePlacement,PLACEMENT_ERR,dplc,chessTable,piecesBoard);
                }

                
            }
            

        }
        backup(chessTable,tour);
    }
}


//génère l'iterraction avec le programme
int mainMenu(){
    char crazychess[10][100]; 

    strcpy(crazychess[0] , "   ______          _____               ________                        ___   ____  ____  ____ ");
    strcpy(crazychess[1] , "  / ____/________ /__  /  __  __      / ____/ /_  ___  __________     |__ \\ / __ \\/ __ \\/ __ \\");
    strcpy(crazychess[2] , " / /   / ___/ __ `/ / /  / / / /_____/ /   / __ \\/ _ \\/ ___/ ___/_______/ // / / / / / / / / /");
    strcpy(crazychess[3] , "/ /___/ /  / /_/ / / /__/ /_/ /_____/ /___/ / / /  __(__  |__  )_____/ __// /_/ / /_/ / /_/ /");
    strcpy(crazychess[4] , "\\____/_/   \\__,_/ /____/\\__, /      \\____/_/ /_/\\___/____/____/     /____/\\____/\\____/\\____/");
    strcpy(crazychess[5] , "                       /____/" );

    coord terminal;
    terminal.y = 0;
    terminal.x = 0;
    WINDOW* logo;
    WINDOW* play;
    WINDOW* play_continue;
    WINDOW* quit;

    getmaxyx(stdscr, terminal.y, terminal.x);

    genLogo(logo,terminal,crazychess);
    genPlay(play,terminal);    
    genPlayContinue(play_continue,terminal);
    genQuit(quit,terminal);
    
    coord test;
    test.y=0;
    test.x=0;
    MEVENT event;
    coord placement;
    placement.x = 31;
    placement.y = 31;
    

    while (1){
        int ch = getch();
        if (ch == KEY_MOUSE) {
            
            getmaxyx(stdscr, terminal.y, terminal.x);

            if (terminal.y!=test.y||terminal.x!=test.x){
                thingsToDo(logo,play,play_continue,quit);
                genTotal(logo,play,play_continue,quit,terminal,crazychess);
                getmaxyx(stdscr, test.y, test.x);
            }
            
            if (getmouse(&event) == 0) { 
                mvwaddch(quit, 1, 3, event.x);
                mvwaddch(quit, 1, 3, event.y);
                wrefresh(quit);

                if (placement.x = 31 && placement.y == 31){
                genTotal(logo,play,play_continue,quit,terminal,crazychess);
                }

                placement.x = event.x;
                placement.y = event.y;

                if ((placement.x>=(terminal.x-50)/2)&&(placement.x<=(terminal.x-50)/2+50)){
                    if (placement.y>13&&placement.y<18){
                        thingsToDo(logo,play,play_continue,quit);
                        return 1;
                    } 
                    else if (placement.y>18&&placement.y<23){
                        thingsToDo(logo,play,play_continue,quit);
                        return 2;
                    } 
                    else if (placement.y>23&&placement.y<28){
                        thingsToDo(logo,play,play_continue,quit);
                        return 3;
                    }
                }
                
            }
        }
    }
}

//écran de fin
int endMenu(int result){

    char logo1[2][10][100]; 

    strcpy(logo1[0][0],"    ____  __                           ___    _       ___     ");
    strcpy(logo1[0][1],"   / __ \\/ /___ ___  _____  _____     <  /   | |     / (_)___ ");
    strcpy(logo1[0][2],"  / /_/ / / __ `/ / / / _ \\/ ___/_____/ /____| | /| / / / __ \\");
    strcpy(logo1[0][3]," / ____/ / /_/ / /_/ /  __/ /  /_____/ /_____/ |/ |/ / / / / /");
    strcpy(logo1[0][4],"/_/   /_/\\__,_/\\__, /\\___/_/        /_/      |__/|__/_/_/ /_/ ");
    strcpy(logo1[0][5],"              /____/                                          ");


    strcpy(logo1[1][0],"    ____  __                           ___      _       ___     ");
    strcpy(logo1[1][1],"   / __ \\/ /___ ___  _____  _____     |__ \\    | |     / (_)___ ");
    strcpy(logo1[1][2],"  / /_/ / / __ `/ / / / _ \\/ ___/_______/ /____| | /| / / / __ \\");
    strcpy(logo1[1][3]," / ____/ / /_/ / /_/ /  __/ /  /_____/ __/_____/ |/ |/ / / / / /");
    strcpy(logo1[1][4],"/_/   /_/\\__,_/\\__, /\\___/_/        /____/     |__/|__/_/_/ /_/ ");
    strcpy(logo1[1][5],"              /____/                                            ");

    coord terminal;
    terminal.y = 0;
    terminal.x = 0;
    WINDOW* logo;
    WINDOW* quit;

    getmaxyx(stdscr, terminal.y, terminal.x);
    
    clearTerm();
    genLogo(logo,terminal,logo1[result]);
  

    sleep(5);
    

}
