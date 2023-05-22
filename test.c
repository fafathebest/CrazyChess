#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



#define HAUTEUR 3
#define PLAY "Play to the game"
#define CONTINUE "Continue the game"
#define QUIT "Quit the game"
#define PLACEMENT_ERR "Placement incorrect"
#define PIECE 'k','K','q','Q','b','B','n','N','r','R','p','P'
#define VIDE "  "
#define BOXWINSIZEX 4
#define BOXWINSIZEY 3
#define TAILLEPPIECEECHECS 12
#define PTSMAX 50
#define TROPCHER "Trop cher"



#define TAILLE_TAB_MOVE 100
#define TAILLE_MOVE 3
#define TAILLE_TYPE 1


//STRUCTURES ET CONSTRUCTEURS POUR PIECES\\

typedef struct{
  char type;
  int price;
  char move[TAILLE_TAB_MOVE][TAILLE_MOVE];
  int taille;
}piece;

piece reset(){
    piece p;
    p.type=0;
    p.price=0;
    p.taille=0;
    p.move[1][1] = 0;
    return p;
}



piece makePion1(){
    piece p;
    p.type='P';
    p.price=1;
    p.taille=3;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A2", "@2", "B2"};
    for (int i=0; i<p.taille; i++) {
            strcpy(p.move[i], deplacement[i]);
        }
    return p;
}

piece makePion2(){
    piece p;
    p.type='p';
    p.price=1;
    p.taille=3;
    char deplacement[TAILLE_TAB_MOVE][TAILLE_MOVE]={"A0", "@0", "B0"};
    for (int i=0; i<p.taille; i++) {
            strcpy(p.move[i], deplacement[i]);
        }
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
    return p;
}


piece placementBase(piece chessTable[11][11],piece piecesEchequier[TAILLEPPIECEECHECS],int tour){
    
    for (int i=0;i<=4;i++){
        chessTable[11-i][i-1] = piecesEchequier[tour];
    }
    for (int i=0;i<=4;i++){
        chessTable[11-i][11-i] = piecesEchequier[tour];
    }

    chessTable[8][5] = piecesEchequier[TAILLEPPIECEECHECS-2+tour];
    
}


void invert_2d_array(piece array[11][11]) {
    for (int i = 0; i < 11 / 2; i++) {
        for (int j = 0; j < 11; j++) {
            piece temp = array[i][j];
            array[i][j] = array[11 - 1 - i][j];
            array[11 - i][j] = temp;
        }
    }
}



typedef struct{
    int x;
    int y;
}coord;

char* coords_to_str(int x, int y) {

    char* str = (char*) malloc(sizeof(char) * 3);

    str[0] = 'A'+ x;
    str[1] = '1' + y;
    str[2] = '\0';

    return str;
}

int coumpt(piece chessTable[11][11],int player){
    int points=0;
    for (int i=0;i<11;i++){
        for (int e=0;e<11;e++){
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

void svg(char text[], char mode[]){
    FILE *f;
    f = fopen("sauvegarde.txt", mode);
    strcat(text, "\n");
    fprintf(f, "%s",text);
    fclose(f);
}

void gest_fichier(char text[],char mode[],int create_mode){
    if (create_mode){remove("sauvegarde.txt");}
    svg(text,mode);
    
    
}

void creation(char text[],char mode[]) {gest_fichier(text,mode,1);}

/*int main(){
    char mode[5];
    char fichier[100];
    strcpy(fichier,"sauvegaaaaaaaaaaarde.txt");
    strcpy(mode,"a");
    creation(fichier,mode);
    return 0;
}
*/

 
void init_game(){

    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    
    start_color(); 
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_GREEN);
    init_pair(1, COLOR_RED, COLOR_BLUE);
    init_pair(0, COLOR_BLUE, COLOR_RED);
    refresh();
    
}


void gen_logo(WINDOW* logo,coord terminal, char crazychess[10][100]){
    logo=newwin(10, 100, 1, (terminal.x-100)/2);
    int y = (getmaxy(logo) - 3) / 2;
    int x = (getmaxx(logo) - strlen(crazychess[2])) / 2;
    for (int i=0;i<=5;i++){
        mvwprintw(logo, y-1+i, x, "%s", crazychess[i]);
    }
    box(logo, 0, 0);
    wrefresh(logo);
}

void gen_play(WINDOW* play,coord terminal){
    play=newwin(5, 50, 13, (terminal.x-50)/2);
    int y = (getmaxy(play) -1) / 2;
    int x = (getmaxx(play) - strlen(PLAY)) / 2;
    mvwprintw(play, y, x, "%s", PLAY);
    box(play, 0, 0);
    wrefresh(play);
}

void gen_play_continue(WINDOW* play_continue,coord terminal){
    play_continue=newwin(5, 50, 18, (terminal.x-50)/2);
    int y = (getmaxy(play_continue) -1) / 2;
    int x = (getmaxx(play_continue) - strlen(CONTINUE)) / 2;
    mvwprintw(play_continue, y, x, "%s", CONTINUE);
    box(play_continue, 0, 0);
    wrefresh(play_continue);
}

void gen_quit(WINDOW* quit,coord terminal){
    quit=newwin(5, 50, 23, (terminal.x-50)/2);
    int y = (getmaxy(quit) -1) / 2;
    int x = (getmaxx(quit) - strlen(QUIT)) / 2;
    mvwprintw(quit, y, x, "%s", QUIT);
    box(quit, 0, 0);
    wrefresh(quit);
}

void clear_term(){
    clear();
    refresh();
}   

void les_trucs_a_faire( WINDOW* logo,WINDOW* play,WINDOW* play_continue,WINDOW* quit){
    delwin(logo);
    delwin(play);
    delwin(play_continue);
    delwin(quit);
    clear_term();
}

void gen_total(WINDOW* logo,WINDOW* play,WINDOW* play_continue,WINDOW* quit,coord terminal,char crazychess[10][100]){
    gen_logo(logo,terminal,crazychess);
    gen_play(play,terminal);    
    gen_play_continue(play_continue,terminal);
    gen_quit(quit,terminal);
}


MEVENT get_click_pos(MEVENT *event){
    event->x /= 6 ;
    event->y /= 3 ;
    return *event;
}


int validStartPos(coord position){
    for (int i=0;i<=4;i++){
        if (position.x>=(i-1)&&position.x<=(11-i)&&position.y==(11-i)){
            return 1;
        }
    }
    return 0;
}

void replaceTab(piece chessTable[11][11],coord pairs[2],char pieces[12],piece piecesEchequier[TAILLEPPIECEECHECS],int round){
    if ((pairs[1].y-1*4+pairs[1].x-12)*2+round<TAILLEPPIECEECHECS){
        chessTable[pairs[0].y][pairs[0].x] = piecesEchequier[((pairs[1].y-1)*4+pairs[1].x-12)*2+round];
    }
}


void genplateau_start(WINDOW* boxv[11][11],WINDOW *win,WINDOW *boxwin[3][4],int hauteur,int largeur, coord basePlacement,char pieces[12],char *str,coord placement,int round,piece chessTable[11][11],piece piecesEchequier[TAILLEPPIECEECHECS],int tour){
    char inCase;

    win = newwin(hauteur*11, largeur*6, basePlacement.y, basePlacement.x+largeur*11);
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
   

    for(int i=0;i<11;i++){
        for(int e=0;e<11;e++){
            boxv[i][e]=newwin(hauteur, largeur, basePlacement.y+hauteur*i, basePlacement.x+largeur*e);
            wbkgd(boxv[i][e], COLOR_PAIR((i*11+e)%2));
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
            boxwin[i][e]=newwin(hauteur, largeur, basePlacement.y+hauteur*i+3, basePlacement.x+largeur*11+largeur*e+6);
            wbkgd(boxwin[i][e], COLOR_PAIR(1)); 
            if ((i*4+e)*2+tour<TAILLEPPIECEECHECS-2&&round!=3){
                mvwaddch(boxwin[i][e], 1, 2,(piecesEchequier[(i*4+e)*2+tour].type));
            }
            wrefresh(boxwin[i][e]);
        }

    }

    if (round%2){
        if (placement.x==32&&placement.y==32){
            wbkgd(boxv[placement.y][placement.x], COLOR_PAIR((placement.x*11+placement.y)%2));
            wrefresh(boxv[placement.y][placement.x]);
        }
        else{
            wbkgd(boxv[placement.y][placement.x], COLOR_PAIR(2));
            wrefresh(boxv[placement.y][placement.x]);
        }
    }
    else if(round%2==0){
        if (placement.x==32&&placement.y==32){
            wbkgd(boxwin[placement.y][placement.x], COLOR_PAIR((placement.x*11+placement.y)%2));
            wrefresh(boxwin[placement.y][placement.x]);
        }
        else{
            wbkgd(boxwin[placement.y-1][placement.x-12], COLOR_PAIR(3));
            wrefresh(boxwin[placement.y-1][placement.x-12]);
        }
    }
}

void pre_game(piece chessTable[11][11],piece piecesEchequier[TAILLEPPIECEECHECS]){

    piece tempChessTable[11][11];

    coord pairs[2];
    int selecteur = 0;


    coord dplc;
    dplc.x=32;
    dplc.y=32;
    char pieces[12] = {PIECE};

    coord terminal;
    terminal.y = 0;
    terminal.x = 0;

    getmaxyx(stdscr, terminal.y, terminal.x); 
    //printw("La taille de l'ecran est %d lignes x %d colonnes\n", terminal.y, terminal.x);
    //sleep(1); 

    int hauteur = HAUTEUR;
    int largeur = 2*hauteur;
    coord basePlacement;

    basePlacement.y = 3;
    basePlacement.x = 6*2;

    WINDOW* boxv[11][11];
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
        placementBase(chessTable,piecesEchequier,tour);
        genplateau_start(boxv,win,boxwin,hauteur,largeur,basePlacement,pieces,VIDE,dplc,selecteur,chessTable,piecesEchequier,selecteur);
        while (points[tour]!=PTSMAX){
            placementBase(chessTable,piecesEchequier,tour);
            int ch = getch();
            if (ch == KEY_MOUSE) {
                points[tour]=coumpt(chessTable,tour);

                getmaxyx(stdscr, test.y, test.x);
                    
                if (getmouse(&event) == OK) {
                                    
                    event = get_click_pos(&event);
                    placement.x = event.x-2;
                    placement.y = event.y-1;              

                    if (placement.x>=12&&placement.x<16 && placement.y>=1 &&placement.y<4 && selecteur==0){
                        pairs[1]=placement;
                        char* str = coords_to_str(placement.x, placement.y);
                        svg(str,"a");
                        if(  points[tour] + piecesEchequier[((pairs[1].y-1)*4+pairs[1].x-12)*2+tour].price <=PTSMAX){
                            genplateau_start(boxv,win,boxwin,hauteur,largeur,basePlacement,pieces,str,placement,selecteur,chessTable,piecesEchequier,tour);
                            selecteur=1;
                        }
                        else{
                            genplateau_start(boxv,win,boxwin,hauteur,largeur,basePlacement,pieces,TROPCHER,dplc,selecteur,chessTable,piecesEchequier,tour);

                        }
                            
                    }

                    else if (placement.x>=0&&placement.x<11 && placement.y>=0&&placement.y<11 && selecteur){
                        pairs[0]=placement;
                        char* str = coords_to_str(placement.x, placement.y);
                        svg(str,"a");

                        if (validStartPos(pairs[0])){
                            replaceTab(chessTable, pairs, pieces,piecesEchequier,tour);
                            genplateau_start(boxv,win,boxwin,hauteur,largeur,basePlacement,pieces,str,placement,selecteur,chessTable,piecesEchequier,tour);
                        }
                        else{
                            genplateau_start(boxv,win,boxwin,hauteur,largeur,basePlacement,pieces,PLACEMENT_ERR,dplc,selecteur,chessTable,piecesEchequier,tour);
                        }
                            

                        selecteur=0;
                        placementBase(chessTable,piecesEchequier,tour);
                        if ( coumpt(chessTable,tour) == PTSMAX && !tour){
                            for (int i=0;i<11;i++){
                                for (int e=0;e<11;e++){
                                    tempChessTable[i][e]=chessTable[i][e];
                                    chessTable[i][e] = reset();
                                }
                            }
                            tour = 1;
                        }
                        if ( coumpt(chessTable,tour) == PTSMAX &&  tour){
                            for (int i=0;i<11;i++){
                                for (int e=0;e<11;e++){
                                    if (chessTable[i][e].type == 0){
                                        chessTable[i][e] = tempChessTable[11-i][e];
                                    }
                                    
                                        
                                }
                            }
                            invert_2d_array(chessTable);
                            points[tour]=PTSMAX;
                        }
                    }
                    else{
                        genplateau_start(boxv,win,boxwin,hauteur,largeur,basePlacement,pieces,PLACEMENT_ERR,dplc,!selecteur,chessTable,piecesEchequier,tour);
                    }
                }
            }
        }
    }
}
    



void genplateau (WINDOW* boxv[11][11],WINDOW* win,int hauteur,int largeur,coord basePlacement,char *str,coord placement,piece chessTable[11][11],piece piecesEchequier[TAILLEPPIECEECHECS]){
    char inCase;
    
    for(int i=0;i<11;i++){
        for(int e=0;e<11;e++){
            boxv[i][e]=newwin(hauteur, largeur, basePlacement.y+hauteur*i, basePlacement.x+largeur*e);
            wbkgd(boxv[i][e], COLOR_PAIR((i*11+e)%2));
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

    
    win = newwin(hauteur*11, largeur*6, basePlacement.y, basePlacement.x+largeur*11);
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
        wbkgd(boxv[placement.y][placement.x], COLOR_PAIR((placement.x*11+placement.y)%2));
        wrefresh(boxv[placement.y][placement.x]);
    }
    else{
        wbkgd(boxv[placement.y][placement.x], COLOR_PAIR(2));
        wrefresh(boxv[placement.y][placement.x]);
    }
}

void game(piece chessTable[11][11],piece piecesEchequier[TAILLEPPIECEECHECS]){
    coord dplc;
    dplc.x=32;
    dplc.y=32;
    
    char pieces[12] = {PIECE};
    
    coord terminal;
    terminal.y = 0;
    terminal.x = 0;

    getmaxyx(stdscr, terminal.y, terminal.x); 
    //printw("La taille de l'ecran est %d lignes x %d colonnes\n", terminal.y, terminal.x);
    //sleep(1); 

    int hauteur = HAUTEUR;
    int largeur = 2*hauteur;
    coord basePlacement;

    basePlacement.y = 3;
    basePlacement.x = 6*2;

    WINDOW* boxv[11][11];
    WINDOW* win;
    
    genplateau(boxv,win,hauteur,largeur,basePlacement,VIDE,dplc,chessTable,piecesEchequier);
    genplateau(boxv,win,hauteur,largeur,basePlacement,VIDE,dplc,chessTable,piecesEchequier);
    
    coord test;
    test.y=0;
    test.x=0;
    MEVENT event;
    coord placement;
    placement.x = 0;
    placement.y = 0;
    while (1){
        
        int ch = getch();
        if (ch == KEY_MOUSE) {
            getmaxyx(stdscr, test.y, test.x);
            if (terminal.y!=test.y||terminal.x!=test.x){
                genplateau(boxv,win,hauteur,largeur,basePlacement,VIDE,dplc,chessTable,piecesEchequier);
            }
            if (getmouse(&event) == OK) {

                event = get_click_pos(&event);
                placement.x = event.x-2;
                placement.y = event.y-1;


                if (placement.x>=0&&placement.x<11 && placement.y>=0&&placement.y<11){
                    
                    char* str = coords_to_str(placement.x, placement.y);
                    svg(str,"a");

                    genplateau(boxv,win,hauteur,largeur,basePlacement,str,placement,chessTable,piecesEchequier);
                }
                else {
                    genplateau(boxv,win,hauteur,largeur,basePlacement,PLACEMENT_ERR,dplc,chessTable,piecesEchequier);
                }

                
            }

            
        }

    }
}


int main_menu(){
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

    gen_logo(logo,terminal,crazychess);
    gen_play(play,terminal);    
    gen_play_continue(play_continue,terminal);
    gen_quit(quit,terminal);
    
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
                les_trucs_a_faire(logo,play,play_continue,quit);
                gen_total(logo,play,play_continue,quit,terminal,crazychess);
                getmaxyx(stdscr, test.y, test.x);
            }
            
            if (getmouse(&event) == 0) { 
                mvwaddch(quit, 1, 3, event.x);
                mvwaddch(quit, 1, 3, event.y);
                wrefresh(quit);

            

                printf("%d | %d\n",(COLS - 6) / 11 ,(LINES - 3) / 11+1);
                printf("%d | %d\n",event.x,event.y);

                if (placement.x = 31 && placement.y == 31){
                gen_total(logo,play,play_continue,quit,terminal,crazychess);
                }

                placement.x = event.x;
                placement.y = event.y;

                if ((placement.x>=(terminal.x-50)/2)&&(placement.x<=(terminal.x-50)/2+50)){
                    if (placement.y>13&&placement.y<18){
                        les_trucs_a_faire(logo,play,play_continue,quit);
                        return 1;
                    } 
                    else if (placement.y>18&&placement.y<23){
                        les_trucs_a_faire(logo,play,play_continue,quit);
                        return 2;
                    } 
                    else if (placement.y>23&&placement.y<28){
                        les_trucs_a_faire(logo,play,play_continue,quit);
                        return 3;
                    }
                }
                
            }
        }
    }
}



int main (){
    piece chessTable[11][11];
    for (int i=0;i<11;i++){
        for (int e=0;e<11;e++){
            chessTable[i][e] = reset();
        }
    }

    piece pion1 = makePion1();
    pion1.type = 'P';
    piece pion2 = makePion2();
    pion2.type = 'p';


    piece bishop1 = makeBishop();
    bishop1.type = 'B';
    piece bishop2 = makeBishop();
    bishop2.type = 'b';


    piece knight1 = makeKnight();
    knight1.type = 'N';
    piece knight2 = makeKnight();
    knight2.type = 'n';


    piece king1  = makeKing();
    king1.type = 'K';
    piece king2  = makeKing();
    king2.type = 'k';


    piece rook1 = makeRook();
    rook1.type = 'R';
    piece rook2 = makeRook();
    rook2.type = 'r';


    piece queen1 = makeQueen();
    queen1.type = 'Q';
    piece queen2 = makeQueen();
    queen2.type = 'q';



    piece piecesEchequier[TAILLEPPIECEECHECS]={pion1,pion2,bishop1,bishop2,knight1,knight2,rook1,rook2,queen1,queen2,king1,king2};

    init_game(); 
    switch(main_menu()){
        case 1 :
        pre_game(chessTable,piecesEchequier);
        clear_term();
        game(chessTable,piecesEchequier);
        break;
        case 2 :
        break;
        default:
        clear_term();
        endwin();
        exit(0);
        break;
    }
    
}







