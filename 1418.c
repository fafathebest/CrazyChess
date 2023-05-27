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
#define TAILLEPPIECEECHECS 12
#define PTSMAX 20
#define TROPCHER "Trop cher"
#define TAILLETAB 11
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

piece placementBase(piece chessTable[TAILLETAB][TAILLETAB],piece piecesBoard[TAILLEPPIECEECHECS],int tour){
    
    for (int i=1;i<=4;i++){
        chessTable[TAILLETAB-i][i-1] = piecesBoard[tour];
    }
    for (int i=1;i<=4;i++){
        chessTable[TAILLETAB-i][TAILLETAB-i] = piecesBoard[tour];
    }

    chessTable[8][5] = piecesBoard[TAILLEPPIECEECHECS-2+tour];
    
}








int isUpperCase(char c) {
    if (c >= 'A' && c <= 'Z') {
        return 1; // Le caractère est une majuscule
    } else {
        return 0; // Le caractère n'est pas une majuscule
    }
}

int isLowerCase(char c) {
    if (c >= 'a' && c <= 'z') {
        return 1; // Le caractère est une majuscule
    } else {
        return 0; // Le caractère n'est pas une majuscule
    }
}

int isAlpha(char c){
    if(isLowerCase(c)!=isUpperCase(c)){
        return 1;
    }   
    return 0;
}


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

void initGame(){

    initscr();
    cbreak();
    curs_set(0);
    noecho();
    keypad(stdscr, TRUE);
    mousemask(ALL_MOUSE_EVENTS, NULL);
    
    start_color(); 
    init_pair(4, COLOR_MAGENTA, COLOR_RED);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    init_pair(2, COLOR_RED, COLOR_GREEN);
    init_pair(1, COLOR_RED, COLOR_BLUE);
    init_pair(0, COLOR_BLUE, COLOR_RED);
    refresh();
    
}

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

MEVENT getClickPos(MEVENT *event){
    event->x /= 6 ;
    event->y /= 3 ;
    return *event;
}

int validStartPos(coord position){
    for (int i=0;i<=4;i++){
        if (position.x>=(i-1)&&position.x<=(TAILLETAB-i)&&position.y==(TAILLETAB-i)){
            return 1;
        }
    }
    return 0;
}

void replaceTab(piece chessTable[TAILLETAB][TAILLETAB],coord pairs[2],piece piecesBoard[TAILLEPPIECEECHECS],int round){
    if ((pairs[1].y-1*4+pairs[1].x-12)*2+round<TAILLEPPIECEECHECS){
        chessTable[pairs[0].y][pairs[0].x] = piecesBoard[((pairs[1].y-1)*4+pairs[1].x-12)*2+round];
    }
}

void resetTabFunc(piece chessTable[TAILLETAB][TAILLETAB]){
    for (int i=0;i<TAILLETAB;i++){
        for (int e=0;e<TAILLETAB;e++){
            chessTable[i][e] = reset();
        }
    }
}



void changes(piece chess[TAILLETAB][TAILLETAB], char pos[3], char tar[3]){
	chess[tar[1]-49][tar[0]-65] = chess[pos[1]-49][pos[0]-65];
	chess[pos[1]-49][pos[0]-65] = reset();
		
}


int verifMove(piece chess[TAILLETAB][TAILLETAB],char str[TAILLE_MOVE],char (**listWords),char selectionjeux[3],piece piecesBoard[TAILLEPPIECEECHECS]){
    piece pion=chess[selectionjeux[1]-49][selectionjeux[0]-65];
    int count=0;
    char refee[2];
    refee[0] = 'A';
    refee[1] = '1';

    if(str[0]!=str[1]){
        for(int i=0;i<pion.taille;i++){
            for(int e=0;e<TAILLE_MOVE-1;e++){
                if(strcmp(listWords[i],"11")){
                    if(listWords[i][e]+selectionjeux[e]-refee[e]==str[e]){
                        count++;

                    }

                    if((isLowerCase(pion.type)*10+1==selectionjeux[1]-49)&&pion.type=='P'+32*isLowerCase(pion.type)){
                        chess[selectionjeux[1]-49][selectionjeux[0]-65] = piecesBoard[TAILLEPPIECEECHECS-4+isLowerCase(pion.type)];
                    }
                    
                    if(count==TAILLE_MOVE-1){
                        if(chess[selectionjeux[1]-49][selectionjeux[0]-65].hasMove==0){chess[selectionjeux[1]-49][selectionjeux[0]-65].hasMove=1;}
                        
                        return 1;
                    }
                }
            }
            count=0;
        }
    }
    
    return 0;
}

char** placeToPlay(piece chess[TAILLETAB][TAILLETAB], char pos[3],WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement,int affichage,int verrif){
    piece pion=chess[pos[1]-49][pos[0]-65];
    
    if (isAlpha(pion.type)){
        int cursor = 0;

        int ver1=0;

        char **tab = (char **)calloc(pion.taille+1 , sizeof(char *));
        for (int i = 0; i < pion.taille+1; i++) {
            tab[i] = (char *)calloc(TAILLE_MOVE , sizeof(char));
        }

        char dep[TAILLE_MOVE];


        switch(pion.type){
            case 'b':
            case 'B':
            case 'r':
            case 'R':
            for (int e=0;e<4;e++){
                for(int i=0;i<pion.taille/4;i++){
                    if (pos[1]-49+pion.move[i+e*pion.taille/4][1]-49>=0&&pos[1]-49+pion.move[i+e*pion.taille/4][1]-49<TAILLETAB&&pos[0]-65+pion.move[i+e*pion.taille/4][0]-65>=0&&pos[0]-65+pion.move[i+e*pion.taille/4][0]-65<TAILLETAB){
                        

                        if(chess[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65].type==0){
                            if(affichage){
                                wbkgd(boxv[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65], COLOR_PAIR(3));
                                wrefresh(boxv[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65]);
                            }    
                            strcpy(tab[cursor],pion.move[i+e*pion.taille/4]);
                            cursor++;
                                
                        }
                        else if((isUpperCase(chess[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65].type) != isUpperCase(chess[pos[1]-49][pos[0]-65].type))||verrif){
                            if(affichage){
                                wbkgd(boxv[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65], COLOR_PAIR(4));
                                wrefresh(boxv[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65]);
                            }    
                            strcpy(tab[cursor],pion.move[i+e*pion.taille/4]);
                            cursor++;
                            
                        }
                        if (chess[pos[1]-49+pion.move[i+e*pion.taille/4][1]-49][pos[0]-65+pion.move[i+e*pion.taille/4][0]-65].type!=0){
                            i=pion.taille;
                        }   
                        
                        
                    }
                }  
            }
            break;

            case 'q':
            case 'Q':
            case 'k':
            case 'K':
            for (int e=0;e<8;e++){
                for(int i=0;i<pion.taille/8;i++){
                    if (pos[1]-49+pion.move[i+e*pion.taille/8][1]-49>=0&&pos[1]-49+pion.move[i+e*pion.taille/8][1]-49<TAILLETAB&&pos[0]-65+pion.move[i+e*pion.taille/8][0]-65>=0&&pos[0]-65+pion.move[i+e*pion.taille/8][0]-65<TAILLETAB){
                        
                        
                        if(chess[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65].type==0){
                            if(affichage){
                                wbkgd(boxv[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65], COLOR_PAIR(3));
                                wrefresh(boxv[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65]);
                            }    
                            strcpy(tab[cursor],pion.move[i+e*pion.taille/8]);
                            cursor++;
                            
                        }
                        else if((isUpperCase(chess[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65].type) != isUpperCase(chess[pos[1]-49][pos[0]-65].type))||verrif){
                            if(affichage){
                                wbkgd(boxv[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65], COLOR_PAIR(4));
                                wrefresh(boxv[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65]);
                            }    
                            strcpy(tab[cursor],pion.move[i+e*pion.taille/8]);
                            cursor++;
                        }                
                        if (chess[pos[1]-49+pion.move[i+e*pion.taille/8][1]-49][pos[0]-65+pion.move[i+e*pion.taille/8][0]-65].type!=0){
                            i=pion.taille;
                        }   
                        
                        
                    }
                }  
            }
            break;

            case 'n':
            case 'N':
            for(int i=0;i<pion.taille;i++){
                if (pos[1]-49+pion.move[i][1]-49>=0&&pos[1]-49+pion.move[i][1]-49<TAILLETAB&&pos[0]-65+pion.move[i][0]-65>=0&&pos[0]-65+pion.move[i][0]-65<TAILLETAB){
                    
                    if((pos[1]-49+pion.move[i][1]-49>=0&&pos[1]-49+pion.move[i][1]-49<TAILLETAB)&&(pos[0]-65+pion.move[i][0]-65>=0&&pos[0]-65+pion.move[i][0]-65<TAILLETAB)){
                        if(chess[pos[1]-49+pion.move[i][1]-49][pos[0]-65+pion.move[i][0]-65].type==0){
                            if(affichage){
                                wbkgd(boxv[pos[1]-49+pion.move[i][1]-49][pos[0]-65+pion.move[i][0]-65], COLOR_PAIR(3));
                                wrefresh(boxv[pos[1]-49+pion.move[i][1]-49][pos[0]-65+pion.move[i][0]-65]);
                            }
                            strcpy(tab[cursor],pion.move[i]);
                            cursor++;
                        }
                        else if((isUpperCase(chess[pos[1]-49+pion.move[i][1]-49][pos[0]-65+pion.move[i][0]-65].type) != isUpperCase(chess[pos[1]-49][pos[0]-65].type))||verrif){
                            if(affichage){
                                wbkgd(boxv[pos[1]-49+pion.move[i][1]-49][pos[0]-65+pion.move[i][0]-65], COLOR_PAIR(4));
                                wrefresh(boxv[pos[1]-49+pion.move[i][1]-49][pos[0]-65+pion.move[i][0]-65]);
                            }
                            strcpy(tab[cursor],pion.move[i]);
                            cursor++;
                        }
                    }
                    
                    
                }
            
            }
            break;

            case 'p':
            case 'P':
            char eatPawn[2][3];
            char mwPawn[3];
            
            
            if((pos[1]+pion.move[2][1]-49<'3'+TAILLETAB&&pos[1]+pion.move[2][1]-49>='2')&&(pos[0]+pion.move[2][0]-65>='A'&&pos[0]+pion.move[2][0]-65<'B'+TAILLETAB)){
                eatPawn[0][0] = pos[0]+pion.move[2][0]-'A';
                eatPawn[0][1] = pos[1]+pion.move[2][1]-'2';
                eatPawn[0][2] = '\0';
            }
            else{
                eatPawn[0][0] = 0;
                eatPawn[0][1] = 0;
                eatPawn[0][2] = '\0';
            }
            if((pos[1]+pion.move[2][1]-49<'3'+TAILLETAB&&pos[1]+pion.move[2][1]-49>='2')&&(pos[0]+pion.move[2][0]-65>='@'&&pos[0]+pion.move[2][0]-65<'A'+TAILLETAB-2)){
                eatPawn[1][0] = pos[0]+pion.move[2][0]-'?';
                eatPawn[1][1] = pos[1]+pion.move[2][1]-'2';
                eatPawn[1][2] = '\0';
            }
            else{
                eatPawn[1][0] = 0;
                eatPawn[1][1] = 0;
                eatPawn[1][2] = '\0';
            }
            
            for(int i=0;i<2;i++){
                if(eatPawn[i][0]!=0&&eatPawn[i][1]!=0){
                    if((chess[eatPawn[i][1]-'0'][eatPawn[i][0]-'A'].type!=0)&&((isUpperCase(chess[eatPawn[i][1]-'0'][eatPawn[i][0]-'A'].type) != isUpperCase(chess[pos[1]-49][pos[0]-65].type))||verrif)){
                        mwPawn[0] = pion.move[2+i][0];
                        mwPawn[1] = pion.move[2+i][1];
                        mwPawn[2] = eatPawn[2+i][2];
                        if(affichage){   
                            wbkgd(boxv[eatPawn[i][1]-'0'][eatPawn[i][0]-'A'], COLOR_PAIR(4));
                            wrefresh(boxv[eatPawn[i][1]-'0'][eatPawn[i][0]-'A']); 
                        } 
                        strcpy(tab[cursor],mwPawn);
                        cursor++; 
                    }
                       
                }
                    
            }
            if (pion.hasMove==0){
                if ((chess[pos[1]-49+pion.move[0][1]-49][pos[0]-65+pion.move[0][0]-65].type==0)&&(chess[pos[1]-49+pion.move[1][1]-49][pos[0]-65+pion.move[1][0]-65].type==0)){
                    if(affichage){
                        wbkgd(boxv[pos[1]-49+pion.move[1][1]-49][pos[0]-65+pion.move[1][0]-65], COLOR_PAIR(3));
                        wrefresh(boxv[pos[1]-49+pion.move[1][1]-49][pos[0]-65+pion.move[1][0]-65]);
                    }
                    strcpy(tab[cursor],pion.move[1]);
                    cursor++;  
                }
            }

            if(chess[pos[1]-49+pion.move[0][1]-49][pos[0]-65+pion.move[0][0]-65].type==0){
                if(affichage){
                    wbkgd(boxv[pos[1]-49+pion.move[0][1]-49][pos[0]-65+pion.move[0][0]-65], COLOR_PAIR(3));
                    wrefresh(boxv[pos[1]-49+pion.move[0][1]-49][pos[0]-65+pion.move[0][0]-65]);
                }
                strcpy(tab[cursor],pion.move[0]);
                cursor++; 
            }
            break;
        }
        
        /*for (int e=0;e<pion.taille;e++){
        printw("%s ",tab[e]);
        }*/

        strcpy(tab[cursor],"11");
        
        return tab;

    }
    else{
        char **tab = (char **)malloc(1 * sizeof(char *));
        for (int i = 0; i < 1; i++) {
            tab[i] = (char *)malloc(TAILLE_MOVE * sizeof(char));
        }
        strcpy(tab[0],"11");
        return tab;

    }
}


int *checkVerrif(int verifCheck[TAILLETAB][TAILLETAB][2],piece chess[TAILLETAB][TAILLETAB],WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement){

    int *returnCheck=calloc(2,sizeof(int));
    
    int affichage = 0;
    int verrif=0;
    char pos[3];
    coord king[2];
    for(int i=0;i<2;i++){
        king[i].x = 0;
        king[i].y = 0;
    }
    int count=0;

    for (int i=0;i<TAILLETAB;i++){
        for (int e=0;e<TAILLETAB;e++){
            for(int x=0; x<chess[i][e].taille;x++){
                verifCheck[i][e][x]=0;
            }
        }
    }

    for (int i=0;i<TAILLETAB;i++){
        
        for (int e=0;e<TAILLETAB;e++){
            
            if (isAlpha(chess[i][e].type)){
                
                count=0;
                pos[0] = 'A'+e;
                pos[1] = '1'+i;
                pos[2] = '\0';

                char** allMooves = (placeToPlay(chess,pos,boxv,height,width,basePlacement,affichage,verrif));

                if (isAlpha(chess[i][e].type)){
                    if(chess[i][e].type=='K'+32*isLowerCase(chess[i][e].type)){
                        king[isLowerCase(chess[i][e].type)].x=e; 
                        king[isLowerCase(chess[i][e].type)].y=i; 
                    }
                    count=0;
                    while(!strcmp(allMooves[count],"11")==0){
 
                        verifCheck[pos[1]-2*'1'+allMooves[count][1]][pos[0]-2*'A'+allMooves[count][0]][isLowerCase(chess[i][e].type)]++;
                        
                        count++;
                    }
                }
            }    
        }
    }
    
    for (int i=0;i<2;i++){
        //printw("%c%d ",chess[king[i].y][king[i].x].type,verifCheck[king[i].y][king[i].x][isUpperCase(chess[king[i].y][king[i].x].type)]);
        if(verifCheck[king[i].y][king[i].x][isUpperCase(chess[king[i].y][king[i].x].type)]!=0){
            returnCheck[isUpperCase(chess[king[i].y][king[i].x].type)]=1;
            
        }
    }
    return returnCheck;

    
}


int *checkMate(piece chess[TAILLETAB][TAILLETAB], int verifCheck[TAILLETAB][TAILLETAB][2], char strTemp[3], WINDOW *boxv[TAILLETAB][TAILLETAB], int height, int width, coord basePlacement, piece piecesBoard[TAILLEPPIECEECHECS]) {
    
    int *returnCheck=calloc(2,sizeof(int));

    piece tempChessTable[TAILLETAB][TAILLETAB];
    resetTabFunc(tempChessTable);

    int count = 0 ;
    int counter = 0 ;

    int affichage = 0;
    int verrif = 1;

    char pos[3];

    char **checkMoves=NULL;
    
    for (int z=0;z<2;z++){
        for (int y=0;y<TAILLETAB;y++){
            for (int x=0;x<TAILLETAB;x++){
                
                if (chess[x][y].type == 'K'+32*z){
                    count = 0;
                    for (int i=0;i<3;i++){
                        for (int e=0;e<3;e++){
                            if (y-1-i<0||x-1-e<0){
                                count++;
                            }
                            else if(verifCheck[y-1-i][x-1-e][z]!=0){
                                count++;
                            }
                        }
                    }
                 
                    if(count==9){
                        count=1;
                    }
                    else{
                        count=0;
                    }

                    counter = 0 ;

                    checkMoves = placeToPlay(chess,strTemp,boxv,height,width,basePlacement,affichage,verrif);
                    while(strcmp(checkMoves[counter],"11")!=0){
                        pos[0] = strTemp[1] + checkMoves[counter][1] - '1' ;
                        pos[1] = strTemp[0]  + checkMoves[counter][0] - 'A' ;
                        pos[2] = '\0';
                        
                        printw("%s ",pos);
                        counter++;
                    }
                    counter = 0 ;
                    while(strcmp(checkMoves[counter],"11")!=0){


                        pos[0] = strTemp[1] + checkMoves[counter][1] - 2*'1' ;
                        pos[1] = strTemp[0]  + checkMoves[counter][0] - 2*'A' ;
                        pos[2] = '\0';


                        if(verifCheck[pos[0]][pos[1]][0]==verifCheck[pos[0]][pos[1]][1]&&count){
                            resetTabFunc(tempChessTable);
                            for (int i=0;i<TAILLETAB;i++){
                                for (int e=0;e<TAILLETAB;e++){
                                    tempChessTable[i][e]=chess[i][e];
                                }
                            }

                            tempChessTable[pos[0]][pos[1]] = piecesBoard[0];

                            if(!checkVerrif(verifCheck,tempChessTable,boxv,height,width,basePlacement)[z]){
                                returnCheck[z]=1;
                            }
                        }
                        counter ++;
                    }


                }
            }
            
        }
        
    }
    return returnCheck;

}


/*
int isNotMate(int target[2],piece chess[TAILLETAB][TAILLETAB],int *checkVerrif,WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement){
    char pos[3];
    int affichage = 0;
    int count=0;
    int count1=0;
    int verrif=1;
    pos[0] = 'A'+target[1];
    pos[1] = '1'+target[0];
    pos[2] = '\0';
    char** targetPawn = (placeToPlay(chess,pos,boxv,height,width,basePlacement,affichage,verrif));

    for (int f=0;f<TAILLETAB;f++){
        for (int g=0;g<TAILLETAB;g++){
            pos[0] = 'A'+g;
            pos[1] = '1'+f;
            pos[2] = '\0';
            char** allMooves = (placeToPlay(chess,pos,boxv,height,width,basePlacement,affichage,verrif));
            count1=0;
            while(!strcmp(targetPawn[count],"11")==0){
                count=0;
                while(!strcmp(allMooves[count],"11")==0){
                    if(strcmp(targetPawn[count],allMooves[count])==0){
                        return 1;
                    }
                }
            }

        }
    }
    return 0;

}


int checkMate(piece chess[TAILLETAB][TAILLETAB],int *checkVerrif,WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement){
    int count=0;
    int count1=0;
    int count2=0;
    char pos[3];
    int checkPiece[TAILLETAB*TAILLETAB][2][2] = {0};
    int affichage = 0;
    int verrif=1;

    
    for (int i=0;i<TAILLETAB;i++){
        for (int e=0;e<TAILLETAB;e++){
            if(chess[i][e].type=='K'+32*isLowerCase(chess[i][e].type)){
                    

                for (int f=0;f<TAILLETAB;f++){
                    for (int g=0;g<TAILLETAB;g++){
                        count=0;
                        pos[0] = 'A'+g;
                        pos[1] = '1'+f;
                        pos[2] = '\0';
                        char** allMooves = (placeToPlay(chess,pos,boxv,height,width,basePlacement,affichage,verrif));

                        if (isAlpha(chess[f][g].type)){
                            count=0;
                            while(!strcmp(allMooves[count],"11")==0){
                                if(pos[1]-2*'1'+allMooves[count][1]==e && pos[0]-2*'A'+allMooves[count][0]==i){
                                    checkPiece[count1][isLowerCase(chess[i][e].type)][0]=e;
                                    checkPiece[count1][isLowerCase(chess[i][e].type)][1]=i;
                                    count1++;
                                }      
                                count++;
                                
                            }
                        }  
                        for(int i=0;i<count;i++){
                            
                            if(isNotMate(checkPiece[i][isLowerCase(chess[i][e].type)],chess,checkVerrif,boxv,height,width,basePlacement)){
                                return 0;
                            }
                            count2++;
                        }
                        if(count2==count){
                            return 1+isLowerCase(chess[i][e].type);
                        }   
                    }     
                }
            }
        }               
    }  
}
*/


/*int checkMate(piece chess[TAILLETAB][TAILLETAB],int verifCheck[TAILLETAB][TAILLETAB][2],char strTemp[3],WINDOW *boxv[TAILLETAB][TAILLETAB],int height,int width,coord basePlacement,piece piecesBoard[TAILLEPPIECEECHECS]){

    piece tempChessTable[TAILLETAB][TAILLETAB];

    int count=0;
    int affichage = 0;
    int verrif=1;


    
    for (int i=0;i<TAILLETAB;i++){
        for (int e=0;e<TAILLETAB;e++){
            //printw("%c|%d||",chess[i][e].type,chess[i][e].type=='K'+32*isLowerCase(chess[i][e].type));

            if(chess[i][e].type=='K'+32*isLowerCase(chess[i][e].type)){
                //printw("%d",verifCheck[strTemp[1]-'A'][strTemp[0]-'1'][isLowerCase(chess[strTemp[1]-'A'][strTemp[0]-'1'].type)]);
                    
                //printw("%c",verifCheck[strTemp[1]-'A'][strTemp[0]-'1'][isLowerCase(chess[strTemp[1]-'A'][strTemp[0]-'1'].type)]);
                if(verifCheck[strTemp[1]-'A'][strTemp[0]-'1'][isLowerCase(chess[strTemp[1]-'A'][strTemp[0]-'1'].type)]!=0){
                    printw("ok");
                    return 0;
                }
                    
                count=0;
                char** allMooves = (placeToPlay(chess,strTemp,boxv,height,width,basePlacement,affichage,verrif));
                while(!(strcmp(allMooves[count],"11")==0)){
                    printw("%s",allMooves[count]);
                    resetTabFunc(tempChessTable);
                    for (int i=0;i<TAILLETAB;i++){
                        for (int e=0;e<TAILLETAB;e++){
                                
                            if(isAlpha(chess[i][e].type)){
                                tempChessTable[i][e]=chess[i][e];
                                //printw("%c",tempChessTable[i][e].type);
                            }
                            else{
                                
                                //printw(" ");
                            }
                        }
                        //printw("\n");
                    }

                    tempChessTable[strTemp[1]-'1'][strTemp[0]-'A']=piecesBoard[0];
                    //printw("%c",tempChessTable[strTemp[1]-'1'][strTemp[0]-'A'].type);
                            
                    int *verrifTab = checkVerrif(verifCheck,tempChessTable,boxv,height,width,basePlacement);

                    if(verrifTab[isLowerCase(chess[strTemp[1]-'A'][strTemp[0]-'1'].type)]!=0){
                        //printw("%d",verrifTab[isLowerCase(chess[strTemp[1]-'A'][strTemp[0]-'1'].type)]);
                        return 0;
                    }   
                    count++;
                }
            }
        }
    }
    return 1;
}*/






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
                            invert_2d_array(chessTable);
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
                                printw("%d,%d",mateOrNot[0],mateOrNot[1]);

                                
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




/*
int endMenu(){
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
*/



int main (){
    int tour=0;
    piece chessTable[TAILLETAB][TAILLETAB];
    resetTabFunc(chessTable);
    
    int verifCheck[TAILLETAB][TAILLETAB][2]={0};

    
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

    piece piecesBoard[TAILLEPPIECEECHECS]={pion1,pion2,bishop1,bishop2,knight1,knight2,rook1,rook2,queen1,queen2,king1,king2};
    

    initGame(); 

    
    switch(mainMenu()){
        case 1 :
        preGame(chessTable,piecesBoard);
        clearTerm();
        game(chessTable,piecesBoard,tour,verifCheck);
        clearTerm();
    
        break;
        case 2 :

        tour = loadSave(chessTable,piecesBoard);
        game(chessTable,piecesBoard,tour,verifCheck);
        clearTerm();
        resetTabFunc(chessTable);
        backup(chessTable,0);//mettre une condition dans le menu
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

