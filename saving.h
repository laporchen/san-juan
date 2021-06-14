#include "struct.h"

/* 
in every savefile:
player:
    playerheader;
 */

void save(u8 langauge, player p[], u8 playerCount, u8 end, u8 level, card deck[110], card discard[110],role r[5]);
i32 load(u8 langauge,savefile *loadfile);
