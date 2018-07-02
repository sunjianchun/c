#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>
#include "GameLib.h"

int getch(int d) {
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
        return ch;
    }else{
        return d;
    }
}

void SetPosition(char direct, int n) {
    //printf("\033[10C");
    printf("%s%d%c", "\033[", n, direct);
}

void SetConsoleTitle(char * name) {
    printf("\033]2;%s\007\n\033[1A", name);
}

void SetColor(const char *msg, const int displayStyle, const int foreColor, const int backColor) {
    char * pfmt = NULL;
    pfmt = (char*)malloc(sizeof("\033[") + sizeof(displayStyle) + sizeof(";") + sizeof(foreColor) + sizeof(";") + sizeof(backColor) + sizeof("m"));
    if(NULL == pfmt) {
        printf("Malloc error! File: %s, Line: %d\n", __FILE__, __LINE__);
        return;
    }
    sprintf(pfmt, "%s%d%s%d%s%d%s", "\033[", displayStyle, ";", foreColor, ";", backColor, "m");
    fprintf(stdout, pfmt);
    printf(msg);
    fflush(stdout);
    fprintf(stdout, "\033[0m");
    free(pfmt);
}

int GetRandom(int min, int max) {
    srand(time(NULL));
    return rand() % (max - min + 1) + min;
    
} 
