#include <stdio.h>
#include <windows.h> // Used for hiding the cursor
#include <time.h>  // used for sleep

extern float gametime;
extern int x, y, player1score, computerscore;
extern char player1, opp, map[];

void hidecursor(); //hodes the cursor
void sleep(int delay); // makes delay for "delay" seconds
void printmessege(char *str, int delay); // prints str for "delay" seconds
void pause(char pausebut, char *pausemessege);
void print_screen(char map[]);
void printscore(int player1score, int computerscore, int aiscore);
void glance(char map[], int glancetime); // shows map for glancetime seconds
void endgame(int end, int stage);
void make(char map[], char what, int n);
void addpoint(char what, int pointperdot);

int randint(int upper,int lower);
int findchar(char str[], char x);
int intlen(int num);



void sleep(int delay){
    int temp = clock();
    while(clock() < temp + (delay * 1000));
}

void hidecursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void printmessege(char *str, int delay){
    printf("%s", str);
    if (delay == 0){
        printf("\nPress Enter to continue...");
        while (getchar() != '\n');
    }
    else
        sleep(delay);
}


void pause(char pausebut, char *pausemessege){
    system("cls");
    printf("\n Paused. Press %c again to continue.\n\n", pausebut);
    printf("%s", pausemessege);
    while(getchar() != pausebut);
    system("cls");
}

void print_screen(char map[]) {
    int i = 0;
    while (map[i] != '\0') {
        printf("%.*s\n", x + 2, map + i);
        i += x + 2;
    }
}

void printscore(int player1score, int computerscore, int aiscore){
    printf("\n");
    if (gametime > 0.0)
        printf("Remaining time: %0.1f\n\n", gametime);
    printf("Player 1 score: %d", player1score);
    if (aiscore == 1)
        printf("Computer score: %d", computerscore);
}

void glance(char map[], int glancetime) {
    int temp_time;
    while (glancetime != 0) {
        temp_time = clock();
        system("cls");
        printf("\n Take a look  at the map... %d\n\n", glancetime);
        glancetime--;
        print_screen(map);
        while (clock() < temp_time + 1000);
    }
}

void endgame(int end, int stage){
    system("cls");
    if (stage == 0){
        if (end == -1)
            printf("You lost, do your best next time!\n");
        if (end == 1)
            printf("You won! Congratulations!\n");
        printf("Press any key to quit");
        getchar();
    }
    else {
        if (stage < 0)
            printf("You lost this stage, do your best next time!\n");

        else
            printf("That's the end of game! Congrats!\n");
        printf("Press any key to quit.\n");
        getchar();
    }
}

int randint(int upper,int lower){
    int num;
    num=(rand()%(upper-lower+1))+lower;
    return num;
}

void make(char map[],  char what, int n){ //puts n number of a given symbol in empty spaces within the map
    int place, i;
    i = 0;
    while (i < n) {

        place=randint((x*y)-(x+1), (x+1));
        while (map[place] != ' '){
            place=randint((x*y)-(x+1), (x+1));
        }
        //for(place=randint((x*y)-(x+1), (x+1));map[place]!=' ';place=randint((x*y)-(x+1), (x+1))){

        //}

        map[place]=what;
        i++;
    }

}

void addpoint(char what, int addedpoint){
    if (what == player1)
        player1score += addedpoint;
    else if (what == opp)
        computerscore += addedpoint;

}

int findchar(char str[],char t){
    int i;
    char c;
    for(i=0;(c=str[i])!=t;i++){
        if(c=='\0'){
            return -1;
        }
    }
    return i;
}

int intlen(int num){
    int len = 1, i = 10;
    while(num/i != 0){
        i *= 10;
        len++;
    }
    return len;




}

