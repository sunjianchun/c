#include <stdio.h>
#include <stdlib.h>
#include "hotel.h"

extern char hotel_info[N][50];
extern double hotel_price[N];

int main() {
    int hotel = get_hotel();
    int days = get_days();
    double total = get_cost(days, hotel_price[hotel]);
    printf("\n");
    printf("=============订单结算===========\n");
    printf("入住酒店：%s\n", hotel_info[hotel]);
    printf("入住天数：%d\n", days);
    printf("总共花费：%.2lf\n", total);
}

