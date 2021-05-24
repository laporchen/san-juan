#pragma once
#include "stdio.h"
#include "stdint.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"

#define i8 int8_t
#define u8 uint8_t
#define i16 int16_t
#define u16 uint16_t
#define i32 int32_t
#define u32 uint32_t
#define i64 int64_t
#define u64 uint64_t
#define CLEAN printf("\e[1;1H\e[2J");
#define PRINTDECK for (i32 i = 0; i < 110;i++)\
                {printf("%s %d %d\n", deck[i].cardName, i,deck[i].place);}
#define DECKSIZE  110
#define GAMEEND 12
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
    void(*cardFunc);
} card;

typedef struct _role
{
    u8 used;
    u8 id;
    string roleName;
    string desription;
    void(*effect);
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
    void(*func);
} player;


//general functions
void init(u8);
void menu();
void about();
void setting();
void mainGame();
void GameEnd();
void printPlayerStatus(player*);
void shuffle();
void draw(player*);
void recycleCard();
void discardCard(u8 p, u8 chosedCard);
void readDes(u8,u8);
void printPlayerCard(player*);
void printPlayerBoard(player *);
void chooseRole(u8 goveror);
u8 chooseAction(u8 p);
void produce(player *,u8 card);
void sell(player *, u8 card,u8 price);
void printCPUstatus(player*p);
void computerAction(player*p);
void roleReset(role r[]);
//role functions
void builder(u8 goveror);
void producer(u8 goveror);
void trader(u8 goveror);
void councilor(u8 goveror);
void prospector(u8 goveror);
//card functions
void indigo(u8 cardowner);
void sugar(u8 cardowner);
void tobacco(u8 cardowner);
void coffee(u8 cardowner);
void silver(u8 cardowner);
void tower(u8 cardowner);
void chapel(u8 cardowner);
void smithy(u8 cardowner);
void poorHouse(u8 cardowner);
void blackMarket(u8 cardowner);
void crane(u8 cardowner);
void carpenter(u8 cardowner);
void quarry(u8 cardowner);
void well(u8 cardowner);
void aqueduct(u8 cardowner);
void marketStand(u8 cardowner);
void marketHall(u8 cardowner);
void tradingPost(u8 cardowner);
void archive(u8 cardowner);
void perfecture(u8 cardowner);
void goldMine(u8 cardowner);
void library(u8 cardowner);
void statue(u8 cardowner);
void victoryColumn(u8 cardowner);
void hero(u8 cardowner);
void guildHall(u8 cardowner);
void cityHall(u8 cardowner);
void triumhalArch(u8 cardowner);
void palace(u8 cardowner);