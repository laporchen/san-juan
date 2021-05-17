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

typedef char string[200];

typedef struct _card
{
    u8 played;
    u8 id;
    string cardName;
    string description;
    char type;
    char phase;
    u8 cost;
    u8 vp;
    u8 hasProduct;
} card;

typedef struct _role
{
    u8 id;
    string roleName;
    string ability;
    string privilege;
} role;

typedef struct _player
{
    u8 cardCount;
    card hand[12];
    u8 point;
    u8 playerOrder;
} player;



void init();
void menu();
void about();
void setting();
void mainGame();
void GameEnd();
