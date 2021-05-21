#include "stdio.h"
struct player
{
    struct card[5];
};
struct card
{
    int cardValue;
};
int main()
{
    struct player p[20];
    memset(&p[3].card[2], 0, sizeof(card));
    printf("%d", p[3].card[2].cardvalue);
}
