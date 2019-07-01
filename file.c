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

char solidblock='\0',moveblock='\0',deathblock='\0',wall='\0',player1='\0',target='\0',object='\0',p1u='\0',p1r='\0',p1d='\0',p1l='\0',quit='\0',opp='\0',opptarget='\0',blankespace=' ',putbutton='\0',putwhat='\0',mapnummode='0';
float gametime=-1.1;
int x, y,attackrange=0,raindbpf=0,putammo=0,pai;

char map[MAXFILESIZE],legend[MAXFILESIZE],note[1000],guide[1000],dialoge[1000];

void readmap(char*filename,char saveto[]){ //opens a map file, gets the dimensions, and stores the rest in a string
    char c;
    int i;
    FILE*fp;
    fp=fopen(filename,"r");
    x=strtoint(fp); //gets a number and puts it in x
    y=strtoint(fp+findchar(fp,'x')); //moves until it finds 'x' and gets a number after that
    for(i=0;(c=getc(fp))!=EOF;i++){ //puts everything except \n s in a string
        if(c=='\n')
            continue;
        else
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

void mapreader(char*num,char*filename,char saveto[]){
    readmap(strcat(filename,num),saveto);
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
        solidblock=op[0];
    else if(strcmp(act,MOVEBLOCK)==0)
        moveblock=op[0];
    else if(strcmp(act,DEATHBLOCK)==0)
        deathblock=op[0];
    else if(strcmp(act,WALL)==0)
        wall=op[0];
    else if(strcmp(act,PLAYER1)==0)
        player1=op[0];
    else if(strcmp(act,TARGET)==0)
        target=op[0];
    else if(strcmp(act,OBJECT)==0)
        object=op[0];
    ////////////////////////////////settings
    else if(strcmp(act,"time")==0)
        gametime=(float)strtoint(op);
    else if(strcmp(act,"rpoint")==0)
        makepoints(op[0],strtoint(pop+1),strtoint((pop + 3) + findchar(pop + 3, ',')));
    else if(strcmp(act,"up")==0)
        p1u=op[0];
    else if(strcmp(act,"down")==0)
        p1d=op[0];
    else if(strcmp(act,"left")==0)
        p1l=op[0];
    else if(strcmp(act,"right")==0)
        p1r=op[0];
    else if(strcmp(act,"attack")==0)
        attackrange=strtoint(pop);
    else if(strcmp(act,"raindb")==0)
        raindbpf=strtoint(pop);
        //
    else if(strcmp(act,"quit")==0)
        quit=op[0];
    else if(strcmp(act,"mode"))
        mapnummode=op[0];
    ////////////////////////////opponent and put!
    else if(strcmp(act,"opp")==0){
        opp=op[0];
        opptarget=op[2];
    }
    else if(strcmp(act,"put")==0){
        putbutton=op[0];
        putwhat=op[2];
        putammo=strtoint(pop+4);
    }
    if(opp!='\0'&&player1!='\0')
        pai=0;
    else if(player1!='\0')
        pai=1;
    else if(opp!='\0')
        pai=2;
    else
        pai=3;
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

int getstrings(char*filename,char note[],char guide[],char dialoge[]){
    char c;
    int i;
    FILE*fp;
    fp=fopen(filename,"r");
    for(i=0;(c=getc(fp))!='\n';i++){ //gets the note
        note[i]=c;
    }
    i++;
    for(i=0;(c=getc(fp))!='\n';i++){ //gets the guide
        guide[i]=c;
    }
    i++;
    for(i=0;(c=getc(fp))!='\n';i++){ //gets the first dialoge
        dialoge[i]=c;
    }
    i++;
    fclose(fp);
    return i; //returns the place in the file where the next dialoge starts
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

void filemain(char gamename[], char legend[], char map[]){
    readmap(strcat(strcat("map-",gamename),".txt"),map);
    readlegend(strcat(strcat("game-",gamename),".txt"),legend);
    applyLegend(legend);
    getstrings("strings.txt",note,guide,dialoge);
}

