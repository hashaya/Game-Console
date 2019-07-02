#include <stdio.h>

extern int x, y, putindex, putammo, endofgame, attackrange, computerindex, pointperdot, player1index;
extern char putwhat, p1r, p1l, p1u, p1d, solidblock, wall, opp, moveblock, target, opptarget, putbutton, point, deathblock, object;

int attack(int index, char map[], char control, int attackrange){
    int i, attacknode = index;
    if (control == 72){
        for(i = 0; i <= attackrange; i++){
            map[attacknode - x - 2] = ' ';
            attacknode = attacknode - x - 2;
        }
    }
    else if (control == 75){
        for(i = 0; i <= attackrange; i++){
            map[attacknode - 1] = ' ';
            attacknode--;
        }
    }
    else if (control == 77){
        for(i = 0; i <= attackrange; i++){
            map[attacknode + 1] = ' ';
            attacknode++;
        }
    }
    else if (control == 80){
        for(i = 0; i <= attackrange; i++){
            map[attacknode + x + 2] = ' ';
            attacknode = attacknode + x + 2;
        }
    }
    return index;
}



void move(int index, int to, char map[]){
    char what = map[index];
    if (putindex == index){
        map[index] = putwhat;
        putammo--;
    }
    else
        map[index] = ' ';
    if (to != -1)
        map[to] = what;

}

int moveb(int index, char control, char map[], int blockorobject){
    /* function for moving moveblocks and objects
       blockorobject = 0 for moveblock and 1 for object; */
    if (blockorobject == 0){
        if (control == p1r){
            if (map[index + 2] != solidblock && map[index + 2] != wall && map[index + 2] != opp && map[index + 2] != target && map[index + 2] != moveblock && map[index + 2] != object){
                move(index + 1, index + 2, map);
                move(index, index + 1, map);
                return index + 1;
            }
            return index;
        }
        else if (control == p1l){
            if (map[index - 2] != solidblock && map[index - 2] != wall && map[index - 2] != opp && map[index - 2] != target && map[index - 2] != moveblock && map[index - 2] != object){
                move(index - 1, index - 2, map);
                move(index, index - 1, map);
                return index - 1;
            }
            return index;
        }
        else if (control == p1d){
            if (map[index + 2 * x + 4] != solidblock && map[index + 2 * x + 4] != wall && map[index + 2 * x + 4] != opp && map[index + 2 * x + 4] != target && map[index + 2 * x + 4] != moveblock && map[index + 2 * x + 4] != object){
                move(index + x + 2, index + 2 * x + 4, map);
                move(index, index + x + 2, map);
                return index + x + 2;
            }
            return index;
        }
        else if (control == p1u){
            if (map[index - 2 * x - 4] != solidblock && map[index - 2 * x - 4] != wall && map[index - 2 * x - 4] != opp && map[index - 2 * x - 4] != target && map[index - 2 * x - 4] != moveblock && map[index - 2 * x - 4] != object){
                move(index - x - 2, index - 2 * x - 4, map);
                move(index, index - x - 2, map);
                return index - x - 2;
            }
            return index;
        }
    }
    else if (blockorobject == 1){
        if (control == p1r){
            if (map[index + 2] != solidblock && map[index + 2] != wall && map[index + 2] != opp && map[index + 2] != moveblock && map[index + 2] != object){
                if (map[index + 2] == target)
                    endofgame = 1;
                move(index + 1, index + 2, map);
                move(index, index + 1, map);
                return index + 1;
            }
            return index;
        }
        else if (control == p1l){
            if (map[index - 2] != solidblock && map[index - 2] != wall && map[index - 2] != opp && map[index - 2] != moveblock && map[index - 2] != object){
                if (map[index - 2] == target)
                    endofgame = 1;
                move(index - 1, index - 2, map);
                move(index, index - 1, map);
                return index - 1;
            }
            return index;
        }
        else if (control == p1d){
            if (map[index + 2 * x + 4] != solidblock && map[index + 2 * x + 4] != wall && map[index + 2 * x + 4] != opp && map[index + 2 * x + 4] != moveblock && map[index + 2 * x + 4] != object){
                if (map[index + 2 * x + 4] == target)
                    endofgame = 1;
                move(index + x + 2, index + 2 * x + 4, map);
                move(index, index + x + 2, map);
                return index + x + 2;
            }
            return index;
        }
        else if (control == p1u){
            if (map[index - 2 * x - 4] != solidblock && map[index - 2 * x - 4] != wall && map[index - 2 * x - 4] != opp && map[index - 2 * x - 4] != moveblock && map[index - 2 * x - 4] != object){
                if (map[index - 2 * x - 4] == target)
                    endofgame = 1;
                move(index - x - 2, index - 2 * x - 4, map);
                move(index, index - x - 2, map);
                return index - x - 2;
            }
            return index;
        }
    }
}

int action(int index, char control, char map[]){ // returns new index

    if (control == '\0'){
        return index;
    }
    int to;
    if (control == p1r || control == 'D')
        to = index + 1;
    else if (control == p1u || control == 'W')
        to = index - x - 2;
    else if (control == p1l || control == 'A')
        to = index - 1;
    else if (control == p1d || control == 'S')
        to = index + x + 2;
    else if (control == putbutton){
        putindex = index;
        return index;
    }
    else if (control == 72 || control == 75 || control == 77 || control == 80) // arrow keys
        return attack(index, map, control, attackrange);
    // move
    char what;
    if(map[to] != solidblock && map[to] != wall && to != computerindex){
        if(map[to]==target){
            if (control == p1l || control == p1d || control == p1r || control == p1u){
                move(index, to, map);
                endofgame = 1;
            }
        }
        else if(map[to] == opptarget && opptarget != point){
            if (control == 'A' || control == 'S' || control == 'D' || control == 'W'){
                move(index, to, map);
                endofgame = -1;
            }
        }
        else if(map[to] == point){
            what = map[index];
            addpoint(what, pointperdot);
            move(index, to, map);
            make(map, point, 1);
        }
        else if(map[to] == deathblock){
            move(index, -1, map);
            endofgame = -1;
        }
        else if(map[to] == moveblock){
            return moveb(index, control, map, 0);
        }
        else if(map[to] == object){
            return moveb(index, control, map, 1);
        }
        else
            move(index, to, map);
        return to;
    }
    return index;
}
