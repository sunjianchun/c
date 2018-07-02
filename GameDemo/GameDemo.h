#ifndef GAMEDEMO_H_INCLUDE
#define GAMEDEMO_H_INCLUDE
#define SEP "-------------------------------------------------------------------------"
#define COL 74
#define MARGIN_X 20
/*********************************
 *
 * Name: GameDemo.h
 * Description: 用来定义一些核心的结构和函数
 * Date: 2018-06-21
 *
 ********************************/
#include<stdio.h>
#include<string.h>

/*************游戏结构类型定义************/
//玩家、地图、装备、怪物
typedef enum _proptype{
    Weapon, Aromr, Con, Card, Frag
}PropType;

/*************坐标类型定义************/
typedef struct _coord {
    int x;
    int y;
}COORD;

/* 游戏信息区枚举类型 */
typedef enum _informationtype {
    MapInfo = '0', Introduce = '1', Attack = '2', GoHome = '3', BuyProp = '4'
}InformationType;


/* 游戏地图结构 */
typedef struct _map {
    int id;                         //地图编号
    char name[50];                  //地图名称
    int minLevel;                   //玩家进入地图的最低等级
    COORD coord;                    //地图的坐标
    char desc[1000];                 //地图描述      
}Map;

/* 道具-武器、防具、消耗品、卡片*/
typedef struct _property{
    int id;                         //道具id
    char name[50];                  //道具名字
    int level;                      //道具级别
    int stock;                      //道具的库存或者玩家背包中的叠加数量
    double price;                   //道具的价格
    PropType proptype;              //道具的类型
    union{                          //联合 - 多选一
        int minAttack;              //最小攻击力
        int minDefence;             //最小防御力
        int minPower;               //最小能量值
    }minValue;
    union{                          //联合 - 多选一
        int maxAttack;              //最大攻击力
        int maxDefence;             //最大防御力
        int maxPower;               //最大能量值
    }maxValue;
    char desc[200];                 //道具描述
}Prop;


typedef struct _test {
    int id;
    union{
        int aaa;
        int bbb;
    };
    char desc[50];
}Test;
/********玩家门派结构********/
typedef struct _martial {
    int id;
    char name[50];
    char type[50];                  //门派类型
    COORD coord;
    int isOpen;
    char desc[100];
}Martial;

/* 玩家信息的定义 */
typedef struct _player {
    int id;
    char name[50];
    char pass[50];
    int life;                       //玩家生命值
    int level;                      //玩家等级
    int exp;                        //玩家经验值
    int hp;                         //玩家的血量
    int mp;                         //玩家的内力值
    int mpMax;                      //玩家的最大内力值
    int gold;                       //玩家的金币数量
    COORD coord;                    //玩家的坐标
    Prop weapon;                    //玩家的武器
    Prop aromr;                     //玩家的防御
    Martial martial;                //玩家的门派
}Player;

/*************怪物类型定义************/
typedef struct _monster {
    int id;
    char name[50];
    int level;
    int hp;                         //怪物的生命值
    int attack;                     //怪物的攻击力
    int diff;                       //怪物的防御力
    int minMoney;                   //杀死怪物获得最小的金币
    int maxMoney;                   //杀死怪物获得的最大金币
    int exp;                        //杀死怪物玩家获得的经验
    int state;                      //怪物的状态 0：已死 1： 存活
    COORD coord;                    //怪物的坐标
}Monster;

//地图坐标
int X;
int Y;
Prop *propArray;
int propNum;
Map (*mapArray)[8];
Player *playerArray;
Monster *monsterArray;
int monsterNum;
Martial *martialArray;

/*************游戏函数类型定义************/
void Init();
/* 显示游戏的属性信息 */
void ShowProp();
/* 显示游戏的欢迎信息 */
void ShowWelcome();
/* 显示游戏的地图 */
void ShowMap(char key);
/* 显示游戏的地图描述信息 */
void ShowMapInformation(Map *map);
/* 显示游戏下方的游戏信息 */
void ShowInformation(char *desc);
/* 显示游戏下方的怪物信息 */
void ShowMonsterInformation();
/* 显示游戏的主菜单 */
void ShowMainMeun();
/* 游戏处理函数 */
void Process();
/* 整体输出函数 */
void Print(char key);
/* 处理游戏主菜单函数 */
void ProcessMainMenu(char key);
/* 打印玩家信息函数 */
void ShowPlayerInfo(Player *player);
/* 打怪函数 */
void Fight(Player *player, int id);

#endif /* ifndef GAMEDEMO_H_INCLUDE */
