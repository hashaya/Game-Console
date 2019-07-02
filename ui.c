#include <stdio.h>

extern char gamename[];
int gameisavailable(char gamename[]); // returns 1 and 0 for available and unavailable game files
void ui();



int gameisavailable(char gamename[]){
    char filename[120] = "map-";
    strcpy(filename, strcat(filename, gamename));
    strcpy(filename, strcat(filename, ".txt"));
    if (fopen(filename, "r") != NULL){
        strcpy(filename, "game-");
        strcpy(filename, strcat(filename, gamename));
        strcpy(filename, strcat(filename, ".txt"));
        if (fopen(filename, "r") != NULL)
            return 1;
    }
    return 0;
}

void ui(){
    printf("\n Console Starting...");
    sleep(1);
    while(gamename != "quit"){
        system("cls");
        printf("\n Enter the name of game\n ");
        gets(gamename);
        if (!gameisavailable(gamename)){
            printf("\n Game not available, try again...\n Press any key to continue\n ");
            getchar();
        }
        else{
            printf("\n Game successfully loaded.\n ");
            sleep(1);
            return;

        }

    }
}
