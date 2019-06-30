#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAXFILESIZE 1000000
#define SOLIDBLOCK "solidblock"
#define MOVEBLOCK "moveblock"
#define DEATHBLOCK "deathblock"
#define WALL "wall"
#define PLAYER1 "character"
#define TARGET "target"
#define OBJECT "object"

char sb='\0',mb='\0',db='\0',wl='\0',p1='\0',tg='\0',ob='\0',p1w='\0',p1a='\0',p1s='\0',p1d='\0',qu='\0',opp='\0',oppt='\0',blankespace='\0',putbutton='\0',putwhat='\0';
float gametime=-1.1;
int x, y,attackrange=0,raindbpf=0,putammo=0;

char map[MAXFILESIZE], legend[MAXFILESIZE];

void readFile(char*filename,char saveto[]){
    char c;
    int i;
    FILE*fp;
    fp=fopen(filename,"r");
    for(i=0;(c=getc(fp))!=EOF;i++)
        saveto[i]=c;
    saveto[i+1]='\n';
    saveto[i+2]='\0';
    fclose(fp);
}


int strtoint(char*str){
    char c;
    int num,i;
    for(i=0;(c=str[i])!='0'&&c!='1'&&c!='2'&&c!='3'&&c!='4'&&c!='5'&&c!='6'&&c!='7'&&c!='8'&&c!='9';i++);
    for(num=0;(c=str[i])!=','&&c!='\n'&&c!='\0';i++)
        num=num*10+(c-'0');
    return num;
}

int findchar(char str[],char t){
    int i;
    char c;
    for(i=0;(c=str[i])!=t;i++)
        if(c=='\0'||c=='\n'){
            printf("there was a problem finding %c.\n",t);
            return -1;
        }
    return i+1;
}

void makepoints(char name,int points,int number){

}

int randint(int upper,int lower){
    int num;
    num=(rand()%(upper-lower+1))+lower;
    return num;
}

void make(char board[],char what, int n){
    int place, i;
    i = 0;
    while (i < n) {
        for(place=randint((x*y)-(x+1), (x+1));board[place]!=' ';place=randint((x*y)-(x+1), (x+1)));
        board[place]=what;
        i++;
    }
}


void applyLegendLine(char*line){
    int i,n;
    char c;
    char act[25];
    char op[25];
    char *pop=op;
    for(i=0;(c=line[i])!='=';i++){
        act[i]=c;
    }
    act[i]='\0';
    for(i++,n=0;(c=line[i])!='\n';i++,n++)
        op[n]=c;

    op[n]='\0';
    /////////////////////////////////blocks
    if(strcmp(act,SOLIDBLOCK)==0)
        sb=op[0];
    else if(strcmp(act,MOVEBLOCK)==0)
        mb=op[0];
    else if(strcmp(act,DEATHBLOCK)==0)
        db=op[0];
    else if(strcmp(act,WALL)==0)
        wl=op[0];
    else if(strcmp(act,PLAYER1)==0)
        p1=op[0];
    else if(strcmp(act,TARGET)==0)
        tg=op[0];
    else if(strcmp(act,OBJECT)==0)
        ob=op[0];
    ////////////////////////////////settings
    else if(strcmp(act,"time")==0)
        gametime=(float)strtoint(op);
    else if(strcmp(act,"rpoint")==0)
        makepoints(op[0],strtoint(pop+1),strtoint((pop + 3) + findchar(pop + 3, ',')));
    else if(strcmp(act,"up")==0)
        p1w=op[0];
    else if(strcmp(act,"down")==0)
        p1s=op[0];
    else if(strcmp(act,"left")==0)
        p1d=op[0];
    else if(strcmp(act,"right")==0)
        p1a=op[0];
    else if(strcmp(act,"attack")==0)
        attackrange=strtoint(pop);
    else if(strcmp(act,"raindb")==0)
        raindbpf=strtoint(pop);
        //
    else if(strcmp(act,"quit")==0)
        qu=op[0];
    ////////////////////////////opponent and put!
    else if(strcmp(act,"opp")==0){
        opp=op[0];
        oppt=op[2];
    }
    else if(strcmp(act,"put")==0){
        putbutton=op[0];
        putwhat=op[2];
        putammo=strtoint(pop+4);
    }
}

void applyLegend(char legend[]){
    char line[60];
    char c;
    int i,l;
    for(i=0,l=0;(c=legend[i])!='\0';i++,l++){
        line[l]=c;
        if(c=='\n'){
            line[l+1]='\0';
            applyLegendLine(line);
            l=-1;
        }
    }
    line[l+1]='\0';
    applyLegendLine(line);
}

void move(){}

void moveai(){}

void play(){
    if(p1!='\0')
        move();
    if(opp!='\0')
        moveai();
}

int main(){
    srand(time(NULL));
    readFile("map01.txt",map);
    printf("%s\n",map);
    readFile("legend01.txt",legend);
    printf("%s\n",legend);
    applyLegend();
    play();
    printf("%c", mb);
    return 0;
}

