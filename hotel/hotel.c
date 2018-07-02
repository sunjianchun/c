#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"

char hotel_info[N][50] = {
        "巴黎贝罗酒店",
        "巴黎香榭丽舍广场酒店",
        "巴黎阿斯托利亚拉斯特拉奥佩拉酒店",
        "巴黎斯克里布索菲特酒店",
        "退出"
    };

double hotel_price[N] = {HOTEL_1, HOTEL_2, HOTEL_3, HOTEL_4};

int get_days() {
    int days, result;
    while(1) {
        printf("请输入您要入住的天数\n");
        result = scanf("%d", &days);
        if (result != 1) {
            printf("输入不合法，");
            scanf("%*s"); //用来处理非整数输入，*表示输入项在读入后不赋值给对应变量
            fflush(stdin); //清空缓冲区，作用同上
            continue;
        }
        if (days < 1) { 
            printf("输入不合法，");
            continue;
        } else {
            break;
        }
    }
    return days;
}


int get_hotel() {
    printf("=============酒店管理系统===========\n");
    int i;
    for (i = 0; i < sizeof(hotel_info)/50; i++) {
       printf("%d、%s\n", (i + 1), hotel_info[i]);
    }
    int hotel, result;
    while(1) {
        printf("请输入您要入住的酒店\n");
        result = scanf("%d", &hotel);
        if (result != 1) {
            printf("输入不合法，");
            scanf("%*s"); //用来处理非整数输入，*表示输入项在读入后不赋值给对应变量
            fflush(stdin); //清空缓冲区，作用同上
            continue;
        }
        if (hotel > 6 || hotel < 1) { 
            printf("输入不合法，");
            continue;
        } else if (hotel == 5) {
            exit(0);
        } else {
            break;
        }
    }
    return hotel - 1;
}


int get_cost(int days, double price) {
    int i;
    double total = 0;
    for(i = 0; i < days; i++) {
        total = total + price * DISCOUNT;
    }

    return total;
}

