#include<stdio.h>

struct Martial {
    int id;
    char name[30];
    int type;
    int count;
};


struct Hero {
    int id;
    char name[30];
    struct Martial martial;
    char sex[20];
};


int main(int argc, char *argv[])
{
    struct Hero hero = {1, "孙建春", {1, "少林", .count=10}, "男"};
    printf("-------英雄属性-------\nID：\t%d\n姓名：\t%s\n派别：\t%s\n性别：\t%s\n", hero.id, hero.name, hero.martial.name, hero.sex);
    return 0;
}
