#ifndef GAME_H
#define GAME_H
#define MAX_PROPERTY_NUM 8          //道具最大数量
#define MAX_PLAYER_NUM 8            //道具最大数量
#define STRING_LENGTH 50            //最大字符长度
#define MAX_PKG_NUM 10              //最大包容量

typedef struct _property {
    int id;                         //道具唯一Id
    double price;                   //单价
    char name[STRING_LENGTH];       //名字
    char desc[STRING_LENGTH];       //描述
    int stock;                      //数量
}Prop;

typedef struct _bag {
    int playerId;                   //所属玩家ID
    int count;                      //背包中道具种类数量
    int max;                        //背包最大槽位
    Prop prop[MAX_PROPERTY_NUM];    //背包的道具数组
}Bag;


typedef struct _player {
    int id;                         //玩家Id
    char username[STRING_LENGTH];   //姓名
    char password[STRING_LENGTH];   //密码
    Bag bag;                        //背包
    double gold;                    //金币的数量
}Player;

Player *playerArray;               //全局玩家数组
Prop *propArray;                   //全局道具数组
int playerNum;                 //全局玩家数量
int propNum;                   //全局道具种类数量

void Init();
void ShowProp();
void ShowPlayer();
Prop * GetProp(Prop *prop, int, int);
void Trade(Player *player, int propId);

#endif /* ifndef GAME_H */
