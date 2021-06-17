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
#define MIN(a,b) (((a)<(b))?(a):(b))
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
    u8 extraProduce;
    u8 extraTrade;
    u8 extraCard;
    u8 library;
    u8 archive;
    u8 quarry;
    u8 smithy;
    u8 productsCount;
    u8 crane;
    u8 blackMarket;
} player;

typedef struct _savefile 
{
    char header[2];
    u8 playerCount;
    u8 gameend;
    u8 level;
    u8 nowPlaying;
    role roles[5];
    player players[4];
    card deck[110];
    card discard[110];
} savefile;