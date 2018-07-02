#include<stdio.h>
#include<string.h>
#include "game.h"

void Init() {
    static Prop props[] = {
       {1, 3000, "双倍经验卡", "双击666"}, 
       {2, 1000, "魔女斗篷", "抗魔披风"}, 
       {3, 3500, "霸者重装", "霸者重装"}, 
       {4, 3050, "抵抗之靴", "抵御伤害"}, 
       {5, 4000, "不死鸟之眼", "法抗"}, 
    };

    static Player players[] = {
        {1, "孙建春", "123456", .gold=50000, .bag.max=10},
        {2, "赵  祥", "123456", .gold=15000, .bag.max=10},
        {3, "叶  伟", "123456", .gold=5000, .bag.max=10},
        {4, "公孙策", "123456", .gold=10000, .bag.max=10},
        {5, "计明亮", "123456", .gold=66000, .bag.max=10},
    };

    playerArray = players;
    propArray = props;
    playerNum = sizeof(players) / sizeof(Player);
    propNum = sizeof(props) / sizeof(Prop);
    
}

void ShowPlayer() {
    int i, j;
    printf("%-5s %-18s %-15s %-18s\n", "序号", "姓名", "密码", "金币");
    for(i = 0; i < playerNum; i++) {
        printf("%-5d %-18s %-15s %-18.2lf\n", playerArray[i].id, playerArray[i].username, playerArray[i].password, playerArray[i].gold);
        for(j = 0; j < playerArray[i].bag.count; j++) {
            printf("%-5d %-18s %-15.2lf %-12s %-5d\n", playerArray[i].bag.prop[j].id, playerArray[i].bag.prop[j].name, playerArray[i].bag.prop[j].price, playerArray[i].bag.prop[j].desc, playerArray[i].bag.prop[j].stock);
        }
    }
}

void ShowProp() {
    int i;
    printf("%-5s %-12s %-10s %-12s\n", "序号", "名称", "价格", "简介");
    for(i = 0; i < propNum; i++) {
        printf("%-5d %-12s %-10.2lf %-12s\n", propArray[i].id, propArray[i].name, propArray[i].price, propArray[i].desc);
    }
}

Prop * GetProp(Prop *prop, int num, int propId) {
    int i;
    for(i = 0; i < num; i++) {
        if(propId == prop[i].id) {
            return &prop[i];
        }
    }

    return NULL;
}


void Trade(Player *player, int propId) {
    Prop *prop = GetProp(propArray, propNum, propId);
    //TODO: judge null
    if(player->bag.count >= player->bag.max) {
        printf("超过背包最大槽位\n");
        return;
    }    
    if(player->gold < prop->price) {
        printf("金币数不足\n");
        return;
    }
    
    Prop *property = NULL;
    property = GetProp(player->bag.prop, player->bag.count, propId);
    player->gold -= prop->price;
    if(property != NULL) {
        property->stock++;
    } else {
        int newIndex = player->bag.count;
        player->bag.prop[newIndex].id = prop->id;
        player->bag.prop[newIndex].price = prop->price;
        strcpy(player->bag.prop[newIndex].name, prop->name);
        strcpy(player->bag.prop[newIndex].desc, prop->desc);
        player->bag.prop[newIndex].stock = 1;
        player->bag.count++;
  }
}
