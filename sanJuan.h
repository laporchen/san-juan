#pragma once
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include <unistd.h>
#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t
#define CLEAN printf("\e[1;1H\e[2J");
#define PRINTDECK                                                 \
    for (i32 i = 0; i < 110; i++)                                 \
    {                                                             \
        printf("%s %d %d id:%d\n", deck[i].cardName, i, deck[i].place,deck[i].id); \
    }
#define DECKSIZE 110
#define GAMEEND 6
#define INVALID printf("%s", invalid[language]);
#define SLEEP nanosleep((const struct timespec[]){{0, 600000000L}}, NULL);;
typedef char string[600];



typedef struct _card
{
    u8 place; //3 : onBoard 2 : inHand 1 : inDeck 0 : discard
    u8 played;
    u8 id;
    string cardName;
    string description;
    u8 type;
    u8 phase;
    u8 cost;
    u8 vp;
    u8 hasProduct;
    u8 extraValue;
    u8 chapelScore;
} card;

typedef struct _role
{
    u8 used;
    u8 id;
    string roleName;
    string desription;
} role;

typedef struct _player
{
    u8 cardCount;
    u8 maxCard;
    u8 boardCount;
    card hand[20];
    card board[15];
    u8 point;
    u8 playerOrder;
    u8 councilorExtraDraw;
    u8 extraProduce;
    u8 extraCostdown;
    u8 extraTrade;
    u8 extraCard;
    u8 library;
    u8 archive;
    u8 quarry;
} player;

//general functions
void init(u8);
void menu();
void about();
void setting();
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
void giveCard(player *p,card c);
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
void blackMarket(player *p,u8 *cost);
void crane(u8 cardowner);
void carpenter(player *p);
void quarry(player *p);
void well(player *p);
void aqueduct(player *p);
void marketStand(player *p,u8 sellCount);
void marketHall(player *p);
void tradingPost(player *p);
void archive(player *p);
void perfecture(player *p);
void goldMine(player *p);
void library(player *p);
void statue(u8 cardowner);
void victoryColumn(u8 cardowner);
void hero(u8 cardowner);
void guildHall(player *p,u8 *vp);
void cityHall(player *p,u8 *vp);
void triumhalArch(player *p,u8 *vp);
void palace(player *p ,u8 *vp);