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
u8 lang = 1;
u8 playercnt = 0;
u8 deckSize = 0;
u8 disCardSize = 0;
int main()
{
    printf("%s", savefileName[lang]);
    char file[100] = {0};
    fgets(file, 99, stdin);
    file[strcspn(file, "\n")] = '\0';
    FILE *p = NULL;
    if ((p = fopen(file, "r")) == NULL)
    {
        printf("%s\n", failed[lang]);
        return -1;
    }
    else
    {
        savefile s = {0};
        fread(&s, sizeof(s), 1, p);
        playercnt = s.playerCount;
        fclose(p);
        for (i32 i = 0; i < 110; i++)
            if (s.deck[i].place == 1)
                deckSize++;
        for (i32 i = 0; i < 110; i++)
            if (s.discard[i].place == 1)
                disCardSize++;
        while (1)
        {

            printf("%s%s", menu[lang], choose[lang]);
            u8 choice = -1;
            scanf("%hhd", &choice);
            while (choice > 6 || choice < 1)
            {
                INVALID
                setbuf(stdin, NULL);
                choice = -1;
                scanf("%hhd", &choice);
            }
            setbuf(stdin, NULL);
            CLEAN
            if (choice == 6)
            {
                return 0;
            }
            if (choice == 5)
            {
                printf("%s\n", savefileName[lang]);
                char file[100] = {0};
                fgets(file, 99, stdin);
                file[strcspn(file, "\n")] = '\0';
                FILE *p = NULL;
                p = fopen(file, "w");
                fwrite(&s, sizeof(s), 1, p);
                fclose(p);
                return 0;
            }
            if (choice == 4)
            {
                langSet();
            }
            if (choice == 3)
            {
                char *pr[2] = {"Player", "玩家"};
                char *choosePlayer[2] = {"Choose a player\n", "選擇一個玩家\n"};
                char *chosed[2] = {"Chosen : ", "已選擇 "};
                while (1)
                {
                    setbuf(stdin, NULL);

                    printf("1)%s\n", pr[lang]);
                    for (i32 i = 1; i < playercnt; i++)
                        printf("%d)CPU %d\n", i + 1, i);
                    printf("%d)%s\n", playercnt + 1, goback[lang]);
                    printf("%s\n", choosePlayer[lang]);
                    u8 playerChoice = -1;
                    scanf("%hhd", &playerChoice);
                    CLEAN
                    if (playerChoice == playercnt + 1)
                        break;
                    while (playerChoice > playercnt || playerChoice < 1)
                    {

                        INVALID
                        playerChoice = -1;
                        setbuf(stdin, &playerChoice);
                        scanf("%hhd", &playerChoice);
                    }

                    while (1)
                    {
                        setbuf(stdin, NULL);

                        if (playerChoice == 1)
                            printf("%s%s\n", chosed[lang], pr[lang]);
                        else
                            printf("%sCPU %d\n", chosed[lang], playerChoice - 1);
                        printf("%s", playerMenu[lang]);
                        u8 choice = -1;
                        scanf("%hhd", &choice);
                        if (choice == 5)
                            break;
                        while (choice > 5 || choice < 1)
                        {
                            INVALID
                            playerChoice = -1;
                            setbuf(stdin, &choice);
                            scanf("%hhd", &choice);
                        }
                        CLEAN
                        if (choice == 1)
                            printHand(&s.players[playerChoice - 1]);
                        if (choice == 2)
                            printBoard(&s.players[playerChoice - 1]);
                        if (choice == 3)
                            editHand(&s.players[playerChoice - 1], s.deck, s.discard);
                        if (choice == 4)
                            editBoard(&s.players[playerChoice - 1], s.deck, s.discard);
                    }
                }
            }
            if (choice == 2)
                printDiscardDeck(s.discard);
            if (choice == 1)
                printDeck(s.deck);
            enterToConti
                CLEAN
        }
    }
}

void langSet()
{

    char *settingStr[2] = {"\tChoose a language\n\n1)English\n2)中文\n", "\t選擇語言\n\n1)English\n2)中文\n"};
    printf("%s", settingStr[lang]);
    int la = -1;
    scanf("%d", &la);
    while ((la > 2 || la < 1))
    {
        INVALID
        setbuf(stdin, NULL);
        scanf("%d", &la);
    }
    lang = la - 1;

    return;
}

void printDeck(card d[110])
{
    i32 count = 0;
    i32 index = 0;
    for (i32 i = count; i < 110; i++)
    {
        if (d[i].place == 1)
        {
            printf("%3d)%s %d\n", index + 1, d[i].cardName, d[i].place);
            index++;
        }
    }
    printf("\n");
    return;
}
void printDiscardDeck(card d[110])
{
    i32 count = 0;
    i32 index = 0;
    for (i32 i = count; i < 110; i++)
    {
        if (d[i].place == 0 && d[i].cost != 0)
        {
            printf("%3d)%s\n", index + 1, d[i].cardName);
            index++;
        }
    }
    printf("\n");
    return;
}
void printHand(player *p)
{
    char *text[2] = {"Hand:\n", "手牌:\n"};
    char *none[2] = {"None", "無"};
    printf("\t%s", text[lang]);
    if (p->cardCount == 0)
        printf("%s\n", none[lang]);

    for (i32 i = 0; i < p->cardCount; i++)
    {
        printf("%2d)%s %d\n", i + 1, p->hand[i].cardName, p->hand[i].place);
    }
    return;
}
void printBoard(player *p)
{
    char *text[2] = {"Board:\n", "場地:\n"};
    char *none[2] = {"None", "無"};
    printf("\t%s", text[lang]);
    if (p->boardCount == 0)
        printf("%s\n", none[lang]);
    for (i32 i = 0; i < p->boardCount; i++)
    {
        printf("%2d)%s %d\n", i + 1, p->board[i].cardName, p->board[i].place);
    }
    return;
}
void editHand(player *p, card d[110], card dis[110])
{
    while (1)
    {

        printf("%s", editMenu[lang]);
        u8 choice = -1;
        scanf("%hhd", &choice);
        if (choice == 3)
            return;
        while (choice > 3 || choice < 1)
        {
            INVALID
            scanf("%hhd", &choice);
        }
        CLEAN
        if (choice == 1)
        {

            char *limit[2] = {"Error. Hand limit is 20 cards\n", "錯誤 手牌上限為20張牌\n"};
            if (p->cardCount == 20)
            {
                printf("%s", limit[lang]);
                continue;
            }
            addCard(p, d);
        }
        if (choice == 2)
        {

            char *error[2] = {"Error. You have no card\n", "錯誤 你沒有手牌\n"};
            if (p->cardCount == 0)
            {
                printf("%s", error[lang]);
                continue;
            }
            delCard(p, d, dis);
        }
    }
}

void editBoard(player *p, card d[110], card dis[110])
{
    while (1)
    {

        printf("%s", editMenu[lang]);
        u8 choice = -1;
        scanf("%hhd", &choice);
        if (choice == 3)
            return;
        while (choice > 3 || choice < 1)
        {
            INVALID
            scanf("%hhd", &choice);
        }
        CLEAN
        if (choice == 1)
        {

            char *limit[2] = {"Error. Board limit is 20 cards\n", "錯誤 場地上限為20張牌\n"};
            if (p->boardCount == 12)
            {
                printf("%s", limit[lang]);
                continue;
            }
            addBoard(p, d);
        }
        if (choice == 2)
        {

            char *error[2] = {"Error. You have no card on board\n", "錯誤 你場上沒有牌\n"};

            if (p->boardCount == 0)
            {
                printf("%s", error[lang]);
                continue;
            }
            delBoard(p, d, dis);
        }
    }
}
void giveCard(player *p, card c)
{
    u8 empty = 0;
    while (p->hand[empty].place == 2)
        empty++;
    p->hand[empty] = c;
    p->hand[empty].place = 2;
    p->cardCount++;
    deckSize--;
    return;
}
void discardCard(player *p, u8 chosedCard, card discard[110])
{
    u8 cardCnt = p->cardCount;
    u8 index = 0;
    while (discard[index].place != 0)
        index++;
    discard[index] = p->hand[chosedCard];
    discard[index].place = 0;
    card empty = {0};
    p->hand[chosedCard] = empty;
    p->hand[chosedCard] = p->hand[cardCnt - 1]; //take player's last card and place it in the empty spot
    p->hand[cardCnt - 1] = empty;
    p->cardCount--;
    return;
}
void addCard(player *p, card c[110])
{
    char *chooseOne[2] = {"Choose a card to add to your hand\n", "選擇一張卡加入手牌\n"};
    printDeck(c);
    printf("%s", chooseOne[lang]);
    u8 choice = -1;
    scanf("%hhd", &choice);
    while (choice > deckSize || choice < 1)
    {
        INVALID
        scanf("%hhd", &choice);
    }
    u8 deckIndex = -1;
    u8 tmp = 0;
    for (i32 i = 0; i < 110; i++)
    {
        if (c[i].place == 1)
            tmp++;
        if (tmp == choice)
        {
            deckIndex = i;
            break;
        }
    }
    printf("%d\n", deckIndex);
    if (deckIndex == -1)
        return;
    giveCard(p, c[deckIndex]);
    card empty = {0};
    c[deckIndex] = empty;
    return;
}
void delCard(player *p, card dis[110], card d[110])
{
    char *del[2] = {"Choose a card to delete\n", "選擇一張牌來刪除\n"};
    for (i32 i = 0; i < p->cardCount; i++)
    {
        printf("%d)%s\n", i + 1, p->hand[i].cardName);
    }
    printf("%s", del[lang]);
    u8 choice = -1;
    scanf("%hhd", &choice);
    while (choice > p->cardCount || choice < 1)
    {
        INVALID
        scanf("%hhd", &choice);
    }
    discardCard(p, choice - 1, d);
}
void addBoard(player *p, card c[110])
{
    char *chooseOne[2] = {"Choose a card to add to your board\n", "選擇一張卡加入場上\n"};
    printDeck(c);
    u8 choice = -1;
    scanf("%hhd", &choice);
    while (choice > deckSize || choice < 1)
    {
        INVALID
        scanf("%hhd", &choice);
    }
    u8 deckIndex = -1;
    u8 tmp = 0;
    for (i32 i = 0; i < 110; i++)
    {
        if (c[i].place == 1)
            tmp++;
        if (tmp == choice)
        {
            deckIndex = i;
            break;
        }
    }
    u8 index = -1;

    p->board[p->boardCount] = c[deckIndex];
    p->board[p->boardCount].place = 3;
    p->boardCount++;
    card empty = {0};
    c[deckIndex] = empty;
    deckSize--;
    return;
}
void delBoard(player *p, card dis[110], card c[110])
{
    char *del[2] = {"Choose a card to delete\n", "選擇一張牌來刪除\n"};
    for (i32 i = 0; i < p->boardCount; i++)
    {
        printf("%d)%s\n", i + 1, p->board[i].cardName);
    }
    printf("%s", del[lang]);
    u8 choice = -1;
    scanf("%hhd", &choice);
    while (choice > p->boardCount || choice < 1)
    {
        INVALID
        scanf("%hhd", &choice);
    }
    u8 index = -1;
    for (i32 i = 0; i < 110; i++)
    {
        if (dis[i].place != 0)
        {
            index = i;
            break;
        }
    }
    dis[index] = p->board[choice - 1];
    dis[index].place = 0;
    disCardSize++;
    p->board[choice - 1] = p->board[p->boardCount - 1];
    card empty = {0};
    p->board[p->boardCount - 1] = empty;
    p->boardCount--;
}