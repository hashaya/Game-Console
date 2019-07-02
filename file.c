#include <stdio.h>
#include <stdlib.h>
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

//char mapnummode = '0';
extern char dialogue[], map[];
extern char solidblock,moveblock,deathblock,wall,player1,target,object,p1u,p1r,p1d,p1l,quit,opp,opptarget,blankespace,putbutton,putwhat,point, pausebut;
extern float gametime;
extern int x, y,attackrange,raindbpf,putammo,pai, pointperdot, pai, glanceon, mode, numberofpoints, player1index, stages;

char map[MAXFILESIZE],legend[MAXFILESIZE],note[1000],guide[1000],dialoge[1000];

int readsize(char *filename){
    FILE *fp = fopen(filename, "r");
    printf("FILENAME = %s\n\n", filename);
    int a = fscanf(fp, "%dx%d", &y, &x);
    fclose(fp);
    printf("MAP = %d\n\n", a);
    return x*y;
}

void readmap(char*filename,char saveto[]){ //opens a map file, gets the dimensions, and stores the rest in a string
    char c;
    int i;
    FILE*fp;
    fp=fopen(filename,"r");
    fscanf(fp, "%dx%d\n", &y, &x);
    x -= 2;
    y -= 2;

    /*x=strtoint(fp); //gets a number and puts it in x
    y=strtoint(fp+findchar(fp,'x')); //moves until it finds 'x' and gets a number after that*/
    for(i=0;(c=getc(fp))!=EOF;){ //puts everything except \n s in a string
        if(c!='\n'){
            saveto[i]=c;
            i++;
        }

    }
    saveto[i]='\0';
    fclose(fp);

}

void readfile(char*filename,char saveto[]){ //opens a file and puts all it's contents in a string
    char c;
    int i;

    FILE*fp;
    fp=fopen(filename,"r");

    for(i=0;(c=getc(fp))!=EOF;i++){
        saveto[i]=c;
    }
    saveto[i+1]='\n';
    saveto[i+2]='\0';
    fclose(fp);
}

void readlegend(char*filename,char saveto[]){ //opens a file and puts all it's contents in a string
    char c;
    int i;
    FILE*fp;
    fp=fopen(filename,"r");
    for(i=0;(c=getc(fp))!=EOF;i++){
        saveto[i]=c;
    }
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

char*mapreader(int num,char*filename){
    char*saveto;
    char number[10];
    saveto=(char*)malloc(x*y*sizeof(char));
    itoa(num,number,10);
    readmap(strcat(filename,number),saveto);
    return saveto;
}
void applyLegendLine(char *map, char *line){
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
    if(strcmp(act,"solidblock")==0)
        solidblock=op[0];
    else if(strcmp(act,"moveblock")==0)
        moveblock=op[0];
    else if(strcmp(act,"deathblock")==0)
        deathblock=op[0];
    else if(strcmp(act,"wall")==0)
        wall=op[0];
    else if(strcmp(act,"character")==0){
        player1 = op[0];
        player1index = findchar(map, player1);
    }
    else if(strcmp(act,"target")==0)
        target=op[0];
    else if(strcmp(act,"object")==0)
        object=op[0];
    else if(strcmp(act,"pause")==0)
        pausebut=op[0];
    ////////////////////////////////settings
    else if(strcmp(act,"time")==0)
        gametime=(float)strtoint(op);
    else if(strcmp(act,"rpoint")==0){
        sscanf(op, "%c,%d,%d", &point, &pointperdot, &numberofpoints);
        make(map, op[0], numberofpoints);
    }
    else if(strcmp(act,"up")==0)
        p1u=op[0];
    else if(strcmp(act,"down")==0)
        p1d=op[0];
    else if(strcmp(act,"left")==0)
        p1l=op[0];
    else if(strcmp(act,"right")==0)
        p1r=op[0];
    else if(strcmp(act,"attack")==0)
        attackrange=strtoint(op);
    else if(strcmp(act,"raindb")==0)
        raindbpf=strtoint(op);
        //
    else if(strcmp(act,"quit")==0)
        quit=op[0];
    else if(strcmp(act,"mode"))
        mode=op[0];
    else if(strcmp(act,"glance"))
        glanceon=strtoint(op);
    else if(strcmp(act,"multistage"))
        stages=strtoint(op);
    ////////////////////////////opponent and put!
    else if(strcmp(act,"opp")==0){
        opp=op[0];
        opptarget=op[2];
    }
    else if(strcmp(act,"put")==0){
        putbutton=op[0];
        putwhat=op[2];
        putammo=strtoint(op[4]);
    }
    if(opp!='\0')
        pai=0;
    else
        pai=1;
}

void applyLegend(char *map, char legend[]){
    char c, line[60];
    int i, l;
    for(i = 0, l = 0;(c=legend[i])!='\0';i++, l++){
        line[l]=c;
        if(c=='\n'){
            line[l+1]='\0';
            applyLegendLine(map, line);
            l=-1;
        }
    }
    line[l+1]='\0';
    applyLegendLine(map, line);
    player1index = findchar(map, player1);

}

char *getstring(char what[], int n, char*gamename){
    char num[10], string[10000];
    if (n == 0)
        num[0] = '\0';
    else
        itoa(n,num,10);
    readfile(strcat(strcat(strcat(strcat(what, num), "-"), gamename), ".txt"), string);
    return string;
}

int getdialoge(char*filename,char dialoge[],int initial){
    char c;
    int i;
    FILE*fp;
    fp=fopen(filename,"r");
    for(i=initial;(c=getc(fp))!='\n';i++){
        dialoge[i]=c;
    }
    i++;
    fclose(fp);
    return i;
}

int filemain(char gamename[], char legend[], char map[]){
    readmap(strcat(strcat("map-",gamename),".txt"),map);
    readfile(strcat(strcat("game-",gamename),".txt"),legend);
    applyLegend(map, legend);
    readfile(strcat("note-",gamename),note);
    readfile(strcat("guide-",gamename),guide);
    readfile(strcat("dialogue-",gamename),dialogue);
    return 0;
}

