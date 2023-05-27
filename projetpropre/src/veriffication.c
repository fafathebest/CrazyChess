#include "../include/veriffication.h"
#include "../include/board.h"
#include "../include/dataManipulation.h"
#include "../include/init.h"

#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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

