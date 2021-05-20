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
void recycleCard(u8 player,u8 card);
void readDes(player,u8);
void chooseRole(u8 goveror);
//role functions
void builder(u8 goveror);
void producer(u8 goveror);
void trader(u8 goveror);
void councilor(u8 goveror);
void prospector(u8 goveror);
