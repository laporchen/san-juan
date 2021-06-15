#pragma once
#include "struct.h"

#define PRINTDECK                                                                   \
    for (i32 i = 0; i < 110; i++)                                                   \
    {                                                                               \
        printf("%s %d %d id:%d\n", deck[i].cardName, i, deck[i].place, deck[i].id); \
    }
#define DECKSIZE 110
#define INVALID printf("%s", invalid[language]);
#define SLEEP                                                    \
    nanosleep((const struct timespec[]){{0, 600000000L}}, NULL); \
    ;
typedef char string[600];


//general functions
void init(u8);
void menu();
void about();
void setting();
void loadGame();
void saveGame();
void mainGame();
void GameEnd();
void printPlayerStatus(player *);
void shuffle();
void draw(player *);
void recycleCard();
void discardCard(player *p, u8 chosedCard);
void readDes(u8, u8);
void printPlayerCard(player *);
void printPlayerBoard(player *);
void chooseRole(u8 goveror);
u8 chooseAction(u8 p);
void produce(player *, u8 card);
void sell(player *, u8 card, u8 price);
void printCPUstatus(player *p);
void computerAction(player *p);
void roleReset(role r[]);
void reduceCard(player *p);
u8 searchCard(player *p, u8 id);
u8 searchBoard(player *p, u8 id);
void giveCard(player *p, card c);
//role functions
void builder(player p[], u8 goveror);
void producer(player p[], u8 goveror);
void trader(player p[], u8 goveror);
void councilor(player p[], u8 goveror);
void prospector(player p[], u8 goveror);
//card functions
void tower(player *p);
void chapel(player *p);
void smithy(player *p);
void poorHouse(player *p);
void blackMarket(player *p);
void crane(player *p);
void carpenter(player *p);
void quarry(player *p);
void well(player *p);
void aqueduct(player *p);
void marketStand(player *p, u8 sellCount);
void marketHall(player *p);
void tradingPost(player *p);
void archive(player *p);
void perfecture(player *p);
void goldMine(player *p);
void library(player *p);
void statue(u8 cardowner);
void victoryColumn(u8 cardowner);
void hero(u8 cardowner);
void guildHall(player *p, u8 *vp);
void cityHall(player *p, u8 *vp);
void triumhalArch(player *p, u8 *vp);
void palace(player *p, u8 *vp);