
extern char solidblock,moveblock,deathblock,wall,player1,target,object,p1u,p1r,p1d,p1l,quit,opp,opptarget,putwhat;
extern int x,y;

int blocked(char there){
    if(there==opptarget)
        return 0;
    else if(there==solidblock||there==moveblock||there==wall||there==player1||there==target||there==object||there==opp)
        return 1;
    else
        return 2;
}

char findroute(int index,char targ,char*map){
    char c;
    int i,j,targetindex=findchar(map,targ);
    for(i=-y;i<=y;i++){
        for(j=-x;j<=x;j++)
            if(index+(i*x)+j==targetindex)
                break;
        if(index+(i*x)+j==targetindex)
            break;
    }
    if(i>0&&blocked(index+x)!=1)
        return 'S';
    else if(i<0&&blocked(index-x)!=1)
        return 'W';
    if(j>0&&blocked(index+1)!=1)
        return 'D';
    else if(j<0&&blocked(index-1)!=1)
        return 'A';

}

void ai(int indexes[],char targ,char*map){
    int i,ind;
    for(i=0;(ind=indexes[i])!=-2;i++){
        if(ind==-1)
            continue;
        else
            findroute(ind,targ,map);
    }
}
