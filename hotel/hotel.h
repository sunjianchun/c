#ifndef HOTAL_H_INCLUDED 
#define HOTAL_H_INCLUDED 
#define N 5
#define HOTEL_1 872.0
#define HOTEL_2 1838.0
#define HOTEL_3 789.0
#define HOTEL_4 1658.0
#define DISCOUNT 0.95

int get_hotel(void);
int get_days(void);
int get_cost(int days, double price);
#endif //HOTAL_H_INCLUDED
