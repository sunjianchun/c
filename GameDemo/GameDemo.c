#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <math.h>
#include "GameDemo.h"


/* 怪物等级 */
char monsterLevel[10][20] = {
    "小小菜鸟", "初出茅庐", "新手进阶", "武林高手", "霸气侧漏", "天人合一"};

void Init() {
    X = 0;
    Y = 0;

    //初始化门派信息
    static Martial martials[] = {
        {1, "华山", "正派", {3, 5}, 0, "华山派"},
        {2, "武当", "正派", {1, 5}, 0, "武当派"},
        {3, "峨眉", "正派", {4, 2}, 0, "峨眉派"}
    };
    
    martialArray = martials;
    //初始化怪物
    static Monster monsters[] = {
        {1, "海绵宝宝", 1, 100, 3, 3, 1000, 5000, 5000, 0, {0, 0}},
        {2, "霸王龙", 2, 100, 3, 3, 1000, 5000, 5000, 0, {1, 0}},
        {3, "地狱男爵", 3, 100, 3, 3, 1000, 5000, 5000, 0, {0, 5}},
        {4, "恶魔", 1, 100, 3, 3, 1000, 5000, 5000, 0, {0, 5}},
        {5, "地狱之火", 1, 100, 3, 3, 1000, 5000, 5000, 0, {0, 0}},
        {6, "寒冰射手", 2, 100, 3, 3, 1000, 5000, 5000, 0, {0, 0}},
        {7, "僵尸", 5, 100, 3, 3, 1000, 5000, 5000, 0, {0, 0}},
        {8, "海带", 1, 100, 3, 3, 1000, 5000, 5000, 0, {0, 0}}
    };

    monsterArray = monsters;
    monsterNum = sizeof(monsters) / sizeof(Monster);
    //初始化游戏玩家
    static Player players[] = {
        {9527, "唐伯虎", "bohu.tang", 100, 3, 1, 10000, 5000, 90000, 100000, .coord.x = 3, .coord.y=3, .weapon={.id=1, .name="帝王天烈剑", .level=1, .stock=5, .price=500, .proptype=Weapon, .minValue.minAttack=50, .maxValue.maxAttack=90, .desc="上古时期的宝剑"}, .aromr={.id=2, .name="荆棘之甲", .level=2, .stock=50, .price=5000, .proptype=Aromr, .minValue.minDefence=2, .maxValue.maxDefence=8, .desc="保护铠甲，反弹伤害"}, .martial={1, "华山", "正派", {3, 5}, 0, "华山派"}},
        {9528, "夏侯惇", "houdun.xiao", 100, 3, 1, 10000, 5000, 90000, 100000, .coord.x = 1, .coord.y=5}
    };

    playerArray = players;


    //初始化道具
    static Prop props[] = {
        {.id=1, .name="帝王天烈剑", .level=1, .stock=5, .price=500, .proptype=Weapon, .minValue.minAttack=1, .maxValue.maxAttack=5, .desc="上古时期的宝剑"},
        {.id=2, .name="荆棘之甲", .level=2, .stock=50, .price=5000, .proptype=Aromr, .minValue.minDefence=2, .maxValue.maxDefence=8, .desc="保护铠甲，反弹伤害"},
        {.id=3, .name="玉露琼浆", .level=1, .stock=5, .price=10, .proptype=Con, .minValue.minPower=1, .maxValue.maxPower=5, .desc="回复生命值和蓝Buff"},
        {.id=4, .name="暗影战斧", .level=2, .stock=5, .price=10, .proptype=Weapon, .minValue.minAttack=2, .maxValue.maxAttack=6, .desc="提升战力和物理伤害"},
        {.id=5, .name="不死鸟之眼", .level=1, .stock=5, .price=500, .proptype=Aromr, .minValue.minDefence=1, .maxValue.maxDefence=5, .desc="提升法抗"}
    }; 

    propArray = props;
    propNum = sizeof(props) / sizeof(Prop);

    //初始化地图
    static Map maps[8][8] = {
        {
            {1, "天山", 1, {0, 0}, "这里充满了西域文化！" },
            {2, "艾泽", 2, {0, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之a"},
            {3, "钱宁河", 2, {0, 2}, "钱宁河是南瞻部洲最大的两条干流之一，两岸山色秀美，直通东海。河上商贾来往，滋养了多少风花雪月的故事。河中接近石塘附近，有一天然形成的大漩涡，不知道存在了多少年，相传有水龙王居住于此，实际上，这是通往龙门水府的大门.“龙门水府”位于石塘县西南的钱宁河水下，原本是石塘县河伯的水下住宅。附近有水族的聚居点“小江屯”，与东南方的喇叭沟、九曲湾、石沟洞一脉相连，势力达到水下最远的钱宁水坝。" },
            {4, "西班牙", 3, {0, 3}, "西南欧伊比利亚半岛的一个国家。迦太基人曾在西班牙沿海一带建立过殖民地，他们把该地叫作Span(兔子)" }, 
            {5, "马德里", 4, {0, 4}, "西班牙首都及中部一省的名称，其阿拉伯语形式是Medshrid，它与意为“建筑的用材”，“木材”的matria一词有关。当初此地木材很丰富，阿拉伯人曾以建造房屋等。 " }, 
            {6, "阿尔赫", 1, {0, 5}, "西班牙南部安达卢西亚地区加的斯省的一个游览胜地和港口。名称起源于阿拉伯语的Jezir-al-chandra(绿色的岛)。公元711年，来自非洲沙漠的阿拉伯人在此登陆，对一望无际的绿色原野留有深刻印象，故有此名。 " }, 
            {7, "阿拉贡", 2, {0, 6}, "西班牙东北部历史上的一个地区。该地区名称源于凯尔特语或前凯尔特语的ar(流动)，此名用来称呼埃布罗河的支流阿拉贡河的，后来成为一个发布王国及地区的名称。" }, 
            {8, "阿利", 3, {0, 7}, "西班牙东南部一省及省会的名称，源于阿拉伯语阿勒坎特(Alkant)，阿拉伯语名称是来自拉丁语名鲁坎提(Lucentum)(闪闪发光的)。 " } 

        },
        {
            {9, "阿斯图", 1, {1, 0}, "西班牙西北部历史上的一个地区，因阿斯图里亚斯(Asturia)河而得名，该河名是由伊比利亚语的asta(岩石)和ura(水)两词组合而成。 " },
            {10, "埃布", 2, {1, 1}, "位于西班牙北部，流向东南，注入地中海。该河名源自古罗马名伊伯鲁(Iberus)，Iberus源于巴斯克语的ebr，而ebr又可能源自凯尔特语的iber(河流)。 "},
            {11, "埃斯", 2, {1, 2}, "西班牙马德里省西北一小城镇。此城名源于西班牙语的escoria(矿渣、炉渣)，即古罗马开矿遗留下来的矿渣堆，此镇因其精美的建筑，高超的艺术而著称。 " },
            {12, "特雷", 3, {1, 3}, "历史上西班牙的一省。名称源于古罗马省名埃什特雷马杜里，该省名又源于拉丁语的extrema ab Duera(离杜拉河最远的地方)。历史上，罗马在西班牙半岛的领土是从地中海延伸开来的，因此埃什特雷马杜里位于罗马领土的西端。" }, 
            {13, "天山", 4, {1, 4}, "这里充满了西域文化！" }, 
            {14, "天山", 1, {1, 5}, "这里充满了西域文化！" }, 
            {15, "天山", 2, {1, 6}, "这里充满了西域文化！" }, 
            {16, "天山", 3, {1, 7}, "这里充满了西域文化！" } 
        },
        {
            {17, "天山", 1, {2, 0}, "这里充满了西域文化！" },
            {18, "艾泽", 2, {2, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之"},
            {19, "天山", 2, {2, 2}, "这里充满了西域文化！" },
            {20, "天山", 3, {2, 3}, "这里充满了西域文化！" }, 
            {21, "天山", 4, {2, 4}, "这里充满了西域文化！" }, 
            {22, "天山", 1, {2, 5}, "这里充满了西域文化！" }, 
            {23, "天山", 2, {2, 6}, "这里充满了西域文化！" }, 
            {24, "天山", 3, {2, 7}, "这里充满了西域文化！" } 
        },
        {
            {25, "天山", 1, {3, 0}, "这里充满了西域文化！" },
            {26, "艾泽", 2, {3, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之"},
            {27, "天山", 2, {3, 2}, "这里充满了西域文化！" },
            {28, "天山", 3, {3, 3}, "这里充满了西域文化！" }, 
            {29, "天山", 4, {3, 4}, "这里充满了西域文化！" }, 
            {30, "天山", 1, {3, 5}, "这里充满了西域文化！" }, 
            {31, "天山", 2, {3, 6}, "这里充满了西域文化！" }, 
            {32, "天山", 3, {3, 7}, "这里充满了西域文化！" } 
        },
        {
            {33, "天山", 1, {4, 0}, "这里充满了西域文化！" },
            {34, "艾泽", 2, {4, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之"},
            {35, "天山", 2, {4, 2}, "这里充满了西域文化！" },
            {36, "天山", 3, {4, 3}, "这里充满了西域文化！" }, 
            {37, "天山", 4, {4, 4}, "这里充满了西域文化！" }, 
            {38, "天山", 1, {4, 5}, "这里充满了西域文化！" }, 
            {39, "天山", 2, {4, 6}, "这里充满了西域文化！" }, 
            {40, "天山", 3, {4, 7}, "这里充满了西域文化！" } 
        },
        {
            {41, "天山", 1, {5, 0}, "这里充满了西域文化！" },
            {42, "艾泽", 2, {5, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之"},
            {43, "天山", 2, {5, 2}, "这里充满了西域文化！" },
            {44, "天山", 3, {5, 3}, "这里充满了西域文化！" }, 
            {45, "天山", 4, {5, 4}, "这里充满了西域文化！" }, 
            {46, "天山", 1, {5, 5}, "这里充满了西域文化！" }, 
            {47, "天山", 2, {5, 6}, "这里充满了西域文化！" }, 
            {48, "天山", 3, {5, 7}, "这里充满了西域文化！" } 
        },
        {
            {49, "天山", 1, {6, 0}, "这里充满了西域文化！" },
            {50, "艾泽", 2, {6, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之"},
            {51, "天山", 2, {6, 2}, "这里充满了西域文化！" },
            {52, "天山", 3, {6, 3}, "这里充满了西域文化！" }, 
            {53, "天山", 4, {6, 4}, "这里充满了西域文化！" }, 
            {54, "天山", 1, {6, 5}, "这里充满了西域文化！" }, 
            {55, "天山", 2, {6, 6}, "这里充满了西域文化！" }, 
            {56, "天山", 3, {6, 7}, "这里充满了西域文化！" } 
        },
        {
            {57, "天山", 1, {7, 0}, "这里充满了西域文化！" },
            {58, "艾泽", 2, {7, 1}, "它是泰坦赐予无边黑暗中一个渺小位面的名字，这个世界上曾经唯一的大陆被泰坦命名为卡利姆多——“永烁星光之"},
            {59, "天山", 2, {7, 2}, "这里充满了西域文化！" },
            {60, "天山", 3, {7, 3}, "这里充满了西域文化！" }, 
            {61, "天山", 4, {7, 4}, "这里充满了西域文化！" }, 
            {62, "光明顶", 1, {7, 5}, "这里充满了西域文化！" }, 
            {63, "天山", 2, {7, 6}, "这里充满了西域文化！" }, 
            {64, "天山", 3, {7, 7}, "这里充满了西域文化！" } 
        }
    };

    mapArray = maps;
}

void ShowProp() {
    int i;
    for(i = 0; i < propNum; i++) {
        printf("%d\t%s\t%.0lf%d\t%d\t%d\t%s\n", propArray[i].id, propArray[i].name, propArray[i].price, propArray[i].proptype, propArray[i].level, propArray[i].stock, propArray[i].desc);
        switch(propArray[i].proptype){
        case Weapon:
            printf("%s%d\t%s%d\n", "最小攻击力: ", propArray[i].minValue.minAttack, "最大攻击力: ", propArray[i].maxValue.maxAttack);
            break;
        case Aromr:
            printf("%s%d\t%s%d\n", "最小防御力: ", propArray[i].minValue.minDefence, "最大防御力: ", propArray[i].maxValue.maxDefence);
            break;
        case Con:
            printf("%s%d\t%s%d\n", "最小回复力: ", propArray[i].minValue.minPower, "最大回复力: ", propArray[i].maxValue.maxPower);
            break;
        }
    }   
}

void ShowMap(char key) {
    Map *map = NULL;
    int i, j;
    for(i = 0; i < 8; i++) {
        SetPosition('C', MARGIN_X);
        printf("|");
        for(j = 0; j < 8; j++) {
            if (mapArray[i][j].coord.x == X && mapArray[i][j].coord.y == Y) {
                SetColor(mapArray[i][j].name, 1, 33, 44); 
                printf("\t");
                map = &mapArray[i][j]; 
            } else {
                printf("%s\t", mapArray[i][j].name);
            }
        }
        SetPosition('D', COL * 10); //为了让光标恢复原位
        SetPosition('C', MARGIN_X + COL - 2);
        printf("|\n");
    }
    SetPosition('C', MARGIN_X);
    printf("%s\n", SEP);
    ProcessMainMenu(key);
}


void ShowWelcome() {
    SetPosition('C', MARGIN_X);
    printf("%s\n", SEP);
    SetPosition('C', MARGIN_X);
    printf("|");
    SetPosition('C', MARGIN_X);
    printf("%s", "欢迎来到笑傲江湖世界《C语言版本》");
    SetPosition('D', COL * 10); //为了让光标恢复原位
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");
    SetPosition('C', MARGIN_X);
    printf("%s\n", SEP);
}


void ShowMapInformation(Map *map) {
    int j;
    int i = 0;
    int num = 90;
    char *desc = map -> desc;
    int strLen = strlen(desc);
    int line = strLen / num;
    //TODO: line 和 行高(7)的比较
    SetPosition('C', MARGIN_X);
    printf("|");
    SetPosition('C', MARGIN_X + 4);
    printf("玩家当前所在地图 《%s》", map -> name);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");
    for(j = 0; j < strLen; j++) {
        if (j % num == 0) {
            SetPosition('C', MARGIN_X);
            printf("%c", '|');
            if(j == 0) {
                printf("%s", "    ");
            }
            printf("%c", desc[j]);
            
        } else if (j % num == num - 1 || desc[j + 1] == '\0') {
            printf("%c", desc[j]);
            SetPosition('D', COL * 3);
            SetPosition('C', MARGIN_X + COL - 2);
            printf("|\n");
        } else {
            printf("%c", desc[j]);
        }
    }

    for (i = 0; i < 7 - line - 1; i++) {
        SetPosition('C', MARGIN_X);
        printf("|");
        SetPosition('C', COL - 3);
        printf("|\n");
    }
    SetPosition('C', MARGIN_X);
    printf("%s\n", SEP);
}

void ShowMainMeun() {
    SetPosition('C', MARGIN_X);
    printf("游戏菜单\n");
    SetPosition('C', MARGIN_X);
    printf("1、自我欣赏\n");
    SetPosition('C', MARGIN_X);
    printf("2、探查(打怪)\n");
    SetPosition('C', MARGIN_X);
    printf("3、回总舵\n");
    SetPosition('C', MARGIN_X);
    printf("4、购买装备\n");
    SetPosition('C', MARGIN_X);
    printf("5、举目四望(待完成)\n");
    SetPosition('C', MARGIN_X);
    printf("6、到此一游(待完成)\n");
    SetPosition('C', MARGIN_X);
    printf("7、退出游戏\n");
       
}


void Process() {
    char choice, key;
    key = '\0';
    system("clear");
    SetConsoleTitle("笑傲江湖C语言版本 春晓");
    ShowWelcome();
    ShowMap('0');
    ShowMainMeun();
    while(1) {
        usleep(200000);
        choice = getch();
        //printf("choice is : %c", choice);
        if(choice != '0') { 
            switch(choice) {
                case 'w':
                    X--;
                    key = MapInfo;
                    break;
                case 'a':
                    Y--;
                    key = MapInfo;
                    break;
                case 's':
                    X++;
                    key = MapInfo;
                    break;
                case 'd':
                    Y++;
                    key = MapInfo;
                    break;
                case '1':
                    key = Introduce;
                    break;
                case '2':
                    key = Attack;
                    break;
                case '3':
                    key = GoHome;
                    break;
                case '4':
                    break;
                case '5':
                    break;
                case '6':
                    break;
                case '7':
                    break;
                default:
                    choice = '\0';
                    break;
            }
        }; 
        if(X < 0) X = 7;
        if(Y < 0) Y = 7;
        if(X > 7) X = 0;
        if(Y > 7) Y = 0;

        if(key != '\0' && choice != '\0') {
            system("clear");
            SetConsoleTitle("笑傲江湖C语言版本 春晓");
            ShowWelcome();
            ShowMap(key);
            ShowMainMeun();
        }
    }
}

void ProcessMainMenu(char key) {
    switch (key) {
        case MapInfo: 
            {
                Map *map;
                map = NULL;
                map = &mapArray[X][Y];
                ShowMapInformation(map);
                break;
            }
        case Introduce:
            {
                Player *player;
                player = &playerArray[0];
                ShowPlayerInfo(player);
                break;
            }
        case Attack:
            {
                ShowMonsterInformation();
                break;
            }
        case GoHome:
            {
                X = playerArray[0].martial.coord.x;
                Y = playerArray[0].martial.coord.y;
                Process();
                break;
            }
        default:
            printf("%c\n", key);
            break;
    }
}

void ShowPlayerInfo(Player *player) {
    SetPosition('C', MARGIN_X);
    printf("|");
    SetPosition('C', MARGIN_X + 4);
    printf("大侠%s的游戏资料如下：", player -> name);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("|");
    SetPosition('C', COL - 3);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("|");
    printf("姓名：%s\t\t密码：%s", player -> name, player -> pass);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("|");
    printf("生命：%d\t\t\t等级：%d", player -> life, player -> level);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("|");
    printf("经验值：%d\t\t\t血量：%d", player -> exp, player -> hp);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("|");
    printf("内力：%d\t\t\t最大内力：%d", player -> mp, player -> mpMax);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");
    
    SetPosition('C', MARGIN_X);
    printf("|");
    printf("金币：%d\t\t\t", player -> gold);
    SetPosition('D', COL * 3);
    SetPosition('C', MARGIN_X + COL - 2);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("|");
    SetPosition('C', COL - 3);
    printf("|\n");

    SetPosition('C', MARGIN_X);
    printf("%s\n", SEP);
}

void ShowMonsterInformation() {

    //符合条件的怪物数组
    Monster monsters[8];
    int i, j;
    j = 0;
    for(i = 0; i < monsterNum; i++) {
        if(monsterArray[i].coord.x == X && monsterArray[i].coord.y == Y && monsterArray[i].state == 0) {
            //方法一：memcpy
            memcpy(&monsters[j], &monsterArray[i], sizeof(monsterArray[i]));
            //方法二：逐个赋值
            //monsters[j].id = monsterArray[i].id;
            //strcpy(monsters[j].name, monsterArray[i].name);
            //... 
            j++;   
        }
    }

    //printf("数量：%d\n", j);
    SetPosition('C', MARGIN_X + 13);
    if(j == 0) {
        printf("地图 《%s》没有怪物，非常安全。", mapArray[X][Y].name);

        for (i = 0; i <= 6; i++) {
            printf("\n");
        }

        SetPosition('C', MARGIN_X);
        printf("按(q)返回:\n");
    } else {
        printf("地图 《%s》的怪物如下：", mapArray[X][Y].name);
        printf("\n");
        printf("\n");
        for(i = 0;i < j; i++) {
            if (i % 2 == 0) {
                SetPosition('C', MARGIN_X);
                printf("%d、%s（%s）\t\t", i + 1, monsters[i].name, monsterLevel[monsters[i].level]);
            } else if (i % 2 == 1){
                printf("%d、%s（%s）\n", i + 1, monsters[i].name, monsterLevel[monsters[i].level]);
            }
        }

        for (i = ceil(j / 2); i < 5; i++) {
            printf("\n");
        }

        char c;
        //判断输入的合规
        SetPosition('C', MARGIN_X);
        printf("请输入您要打怪的编号，按(q)返回: ");
        int result, value; 
        if(result = scanf("%d", &value) != EOF){
            if(value > 0 && value <= j) {
               Fight(&playerArray[0], monsters[value].id); 
            } else {
                printf("输入不合法，返回: ");
            }
        } else {
                printf("输i入不合法，返回: ");
        }
    }

    SetPosition('D', MARGIN_X * 3);
    SetPosition('C', MARGIN_X);
    printf("%s\n", SEP);
} 

void Fight(Player *player, int id) {
    int count = 0;
    while(1) {
        SetPosition('D', MARGIN_X * 30);
        SetPosition('C', MARGIN_X);
        count++;
        if(player -> hp <= 0) {
            player -> hp = 0;
            break;
        }
        if(monsterArray[id].hp <= 0) {
            monsterArray[id].state = 1;
            monsterArray[id].hp = 0;
            break;
        }
        int playerAttack = GetRandom(player -> weapon.minValue.minAttack, player -> weapon.maxValue.maxAttack);
        int playerDefence = GetRandom(player -> aromr.minValue.minDefence, player -> aromr.maxValue.maxDefence);

        monsterArray[id].hp = monsterArray[id].hp - (playerAttack > monsterArray[id].diff ? playerAttack - monsterArray[id].diff : 0);
        player -> hp = player -> hp - (monsterArray[id].attack > playerDefence ? monsterArray[id].attack - playerDefence : 0);
        usleep(100000);
        printf("第%d回合: %s血量%d %s血量%d\n", count, player -> name, player -> hp, monsterArray[id].name, monsterArray[id].hp); 

    } 

    if(player -> hp > 0 && monsterArray[id].hp <= 0) {
        player -> exp += monsterArray[id].exp;
        player -> gold += GetRandom(monsterArray[id].minMoney, monsterArray[id].maxMoney); 
    }

}


