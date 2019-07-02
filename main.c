#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DELAY 200 //ms
#define TIMEREDUCTION 0.2 //s
#define GLANCETIME 5 //s

char m[10], g[10];
char *map, legend[1000], note[10000], guide[1000], dialogue[1000], gamename[100] = "";
char solidblock='\0',moveblock='\0',deathblock='\0',wall='\0',target='\0',object='\0',quit='\0',opp='\0',opptarget='\0',blankespace='\0', pausebut = '\0', point, control;
char putbutton='\0',putwhat='\0', putammo = 0, putindex = -1;
char player1='\0',p1u='\0',p1d='\0',p1l='\0',p1r='\0';
int player1score, player1index;
float gametime = -1;
int x, y, pointperdot, mode = 0, attackrange = 0, raindbpf = 0, computerscore = -1, computerindex[100], stages, currentstage = 0, glanceon, pai, aiscore, numberofpoints;
int endofgame; // -1 if palyer1 loses, 1 if wins, 0 if game should be continued
int anote = 0, aguide = 0, adialogue = 0;

void aiplay(char map[], int computerindex){
    return;

}

int main(){
    hidecursor();
    srand(time(NULL));
    system("cls");
    ui(); // name of game
    char txt[] = ".txt";
    strcpy(m, "map-");
    strcat(strcat(m,gamename),txt);
    strcpy(g, "game-");
    strcat(strcat(g,gamename),txt);
    //if (filemain(gamename, map, legend) != 0) in tabe bayad tori taghir konad ke faghat legend ra bekhanad
    //    return end(0); // error
    player1score = 0;
    computerscore = 0;
    system("cls");
    if (anote)
        strcpy(note, getstring("note", 0, gamename));
    if (strcmp(note, "") != 0)
        printmessege(note, 0);

    int mapsize;
    if (mode == 0){ // single-stage
        //printf("%s\n\n", strcat(strcat(m,gamename),".txt"));
        mapsize = readsize(m);
        // some checks for errors
        map = (char *)malloc(mapsize * sizeof(char) + 1);
        readmap(m, map);
        readfile(g,legend);
        applyLegend(map, legend);
        if (aguide)
            strcpy(guide, getstring("guide", 0, gamename));

        if (strcmp(guide, "") != 0)
            printmessege(guide, GLANCETIME);
        if (glanceon == 1) // yani agar dar file baazi darkhaaste glance dade shode bashad
            glance(map, GLANCETIME);
        endofgame = 0;
        int temptime = clock();
        while (gametime > 0.1){ // main loop for single-stage games
            control = '\0';
            while (clock() < temptime + DELAY) {
                if (kbhit())
                    control = _getch();
                if (control == quit)
                    exit(0);
                else if (control == pausebut)
                    pause(pausebut, guide);
            }
            player1index = action(player1index, control, map);
            if (pai == 1)
                aiplay(map, computerindex);
            gametime -= TIMEREDUCTION;
            system("cls");
            print_screen(map);
            printscore(player1score, computerscore, aiscore); // aiscore shows that ai can have score or not (default = 0)
            printf("Plyer1index = %d", player1index);
            temptime = clock();
            if (endofgame != 0)
                break;
        }
        endgame(endofgame, currentstage);
    }
    else if (mode == 1){ // multi-stage
        int temptime;
        currentstage = 1;
        while (currentstage != -1 && currentstage <= stages){ // main loop for multi-stage games
            mapsize = readsize(strcat(strcat("map-",gamename),".txt"),map);
            // some checks for errors
            map = (char *)malloc(mapsize * sizeof(char) + 1);
            readmap(strcat(strcat("map-",gamename),".txt"),map);
            applyLegend(legend);
            make(map, point, numberofpoints);
            strcpy(guide, getstring("guide", currentstage, gamename));
            if (strcmp(guide, "") != 0)
                printmessege(guide, GLANCETIME);
            if (glanceon == 1) // yani agar dar file baazi darkhaaste glance dade shode bashad
                glance(map, GLANCETIME);
            endofgame = 0;
            temptime = clock();
            while (gametime > 0.1){ // loop for each state
                control = '\0';
                while (clock() < temptime + DELAY) {
                    control = _getch();
                    if (control == quit)
                        exit(0);
                    else if (control == 'p')
                        pause(guide);
                }
                move(player1index, control, map);
                if (pai == 1)
                    aiplay(map, computerindex);
                gametime -= TIMEREDUCTION;
                system("cls");
                print_screen(map);
                printscore(player1score, computerscore, aiscore, gametime); // aiscore shows that ai can have score or not (default = 0)
                temptime = clock();
                if (endofgame != 0)
                    break;
            }
            if (endofgame != 1){
                currentstage = -1;
            }
            else
                currentstage++;
            strcpy(dialogue, getstring("dialogue", currentstage - 1, gamename));
            if (strcmp(guide, "") != 0)
                (dialogue, GLANCETIME);
            free(map);
        }
        endgame(endofgame, currentstage - 1);
    }
    return 0;
}
