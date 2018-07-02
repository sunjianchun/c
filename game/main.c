#include<stdio.h>
#include "game.h"
extern Player *playerArray;
int main()
{   
    Init();
    ShowPlayer();
    ShowProp();
    Trade(&playerArray[1], 1);
    Trade(&playerArray[1], 2);
    Trade(&playerArray[1], 3);
    Trade(&playerArray[1], 4);
    Trade(&playerArray[1], 4);
    Trade(&playerArray[1], 5);
    Trade(&playerArray[1], 5);
    ShowPlayer();
    ShowProp();
    return 0;
}
