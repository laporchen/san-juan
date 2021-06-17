#include "struct.h"
#define INVALID printf("%s", invalid[lang]);
#define enterToConti           \
    printf("%s", enter[lang]); \
    int c = getchar();         \
    int b = getchar();

char *enter[2] = {"Press enter to continue\n", "輸入Enter鍵繼續\n"};
char *savefileName[2] = {"Please enter savefile name : ", "請輸入儲存檔案名稱 : "};
char *failed[2] = {"Failed to open the file.", "無法開啟該檔案"};
char *menu[2] = {
    "1)View the deck\n2)View the discard pile\n3)View player\n4)Language setting\n5)Save & Exit\n6)Don't save & Exit\n", "1)查看牌堆\n2)查看棄牌堆\n3)查看玩家\n4)語言選擇\n5)保存並結束\n6)不保存並結束\n"};
char *playerMenu[2] = {
    "1)View the hand\n2)View the board\n3)Edit the hand\n4)Edit the board\n5)Return\n", "1)查看手牌\n2)查看場上\n3)編輯手牌\n4)編輯場上\n5)返回\n"};
char *choose[2] = {"Choose an option\n", "選擇一個選項\n"};
char *invalid[2] = {"Invalid option,please try another one.\n", "無效的選項，請再試一次。\n"};
char *goback[2] = {"Return", "返回"};
char *editMenu[2] = {"1)Add card\n2)Remove card\n3)Return", "1)新增卡片\n2)移除卡片\n3)返回\n"};

void printDeck(card d[110]);
void printDiscardDeck(card d[110]);
void printHand(player *p);
void printBoard(player *p);
void editHand(player *p, card d[110], card dis[]);
void editBoard(player *p, card d[110], card dis[]);
void langSet();
void discardCard(player *p, u8 chosedCard, card discard[110]);
void giveCard(player *p, card c);
void addCard(player *p, card c[110]);
void delCard(player *p, card dis[], card d[110]);
void addBoard(player *p, card c[110]);
void delBoard(player *p, card dis[], card d[110]);