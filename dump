extern char dialogue[], map[];
extern char solidblock,moveblock,deathblock,wall,player1,target,object,p1u,p1r,p1d,p1l,quit,opp,opptarget,blankespace,putbutton,putwhat,point, pausebut;
extern int x,y;

void raindb(int dbpf,int rain, int indexes[],char map[]){
    char there;
    int i,j,ind,place;
    for(i=0;(ind=indexes[i])!=-1;i++){
        there=map[ind];
        if(there!=solidblock&&there!=moveblock&&there!=deathblock&&there!=wall&&there!=object&&there!=target)
            ind+=x;
    }
    if(rain==1)
    for(j=0;j<dbpf;j++){
        for(place=randint((x*y)-(x+1), (x+1));map[place] != ' ';place=randint((x*y)-(x+1), (x+1)));
        map[place]=deathblock;
        i++;
    }
}
