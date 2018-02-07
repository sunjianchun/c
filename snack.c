#include<termio.h>
#include<stdio.h>
#include<unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>

#define _XOPEN_SOURCE 600
#define X 20
#define Y 40

struct coordinate{
    int x; //横坐标
    int y; //纵坐标
}snack[100] = {{5,5}};

int now_length = 1;
char lastDirection = 'w';


int kbhit(int d);
int draw(struct coordinate *s, int *food_x, int *food_y);
int run();
void flushSnack(struct coordinate *s, int x, int y);

int main() {
    run();
    return 0;
}

int kbhit(int d)
{
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


int draw(struct coordinate *s, int *food_x, int *food_y) {
    system("clear");
    if (((s + (now_length - 1)) -> x) <= 0 || ((s + (now_length - 1)) -> x) >= X - 1 || ((s + (now_length - 1)) -> y) <=0 || ((s + (now_length - 1)) -> y) >= Y - 1) {
        printf("GAME OVER!!!\n");
        return 1;
    }
    int i, j;
    for(i = 0; i < X; i++){
        for(j = 0; j < Y; j++){
            if (i == 0 || i == (X - 1)) {
                printf("#");
            }else if (j == 0 || j == (Y - 1)) {
                printf("#");
            }else {
               if (i == *food_x && j == *food_y){
                   printf("&");
                   continue;
               }
              int iter;
              int var = 0;
              for (iter = 0; iter < now_length; iter++){
                  if (i == ((s + iter) -> x) && j == ((s + iter) -> y)) {
                      var = 1;
                      break;
                  }
              }

              if(var == 0){
                printf(" ");
              }else{
                printf("*");
              }
          }
        }

        printf("%s", "\n");
              //int iter;
              //for (iter = 0; iter < now_length; iter++){
              //   printf("(%d,%d) ", (s + iter) -> x, (s + iter) -> y);
              //}
    }
    return 0;
}


int run() {
    srand(time(NULL));
    int fx = rand() % (X - 2);
    int fy = rand() % (Y - 2);
    int *food_x = &fx;
    int *food_y = &fy;
    char tmp;
    int x, y;

    while(1) {
        x = (snack + now_length - 1) -> x;
        y = (snack + now_length - 1) -> y;
        usleep(200000);
        tmp = kbhit(lastDirection);
        switch(tmp) {
            case 'w':
                x--;
                lastDirection = 'w';
                break;
            case 'a':
                y--;
                lastDirection = 'a';
                break;
            case 's':
                x++;
                lastDirection = 's';
                break;
            case 'd':
                y++;
                lastDirection = 'd';
                break;
            default:
                switch(lastDirection) {
                    case 'w':
                        x--;
                        lastDirection = 'w';
                        break;
                    case 'a':
                        y--;
                        lastDirection = 'a';
                        break;
                    case 's':
                        x++;
                        lastDirection = 's';
                        break;
                    case 'd':
                        y++;
                        lastDirection = 'd';
                        break;
                }
                break;
        }

        flushSnack(snack, x, y);

        while(1){
            if (((snack + (now_length - 1)) -> x) == *food_x && ((snack + (now_length - 1)) -> y) == *food_y){
                fx = rand() % (X - 2);
                fy = rand() % (Y - 2);
                food_x = &fx;
                food_y = &fy;
                //增加结构体数组 重新生成
                int iter;
                for(iter = now_length; iter >= 0; iter--){
                    if (iter != 0){
                        (snack + iter) -> x = (snack + iter - 1) -> x;
                        (snack + iter) -> y = (snack + iter - 1) -> y;
                    }
                }
                now_length++;
            }else{
                break;
            }
       }
       draw(snack, food_x, food_y);

    }

    return 0;
}

void flushSnack(struct coordinate *s, int x, int y){
    int i;
    for(i = 0; i < now_length; i++){
        if (i == now_length - 1){
            (s + i) -> x = x;
            (s + i) -> y = y;
        }else{
            (s + i) -> x = (s + i + 1) -> x;
            (s + i) -> y = (s + i + 1) -> y;
        }

    }


}
