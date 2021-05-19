#include "sanJuan.h"

const u8 cardCounts[] = {10, 8, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2};
const u8 CardCost[] = {1, 2, 3, 4, 5, 3, 3, 1, 2, 2, 2, 3, 4, 2, 3, 2, 4, 2, 1, 3, 1, 5, 3, 4, 5, 6, 6, 6, 6};
const u8 type[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};
const u8 phase[] = {3, 3, 3, 3, 3, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9};
const u8 cost[] = {1, 2, 3, 4, 5, 3, 3, 1, 2, 2, 2, 3, 4, 2, 3, 2, 4, 2, 1, 3, 1, 5, 3, 4, 5, 6, 6, 6, 6};

/*
phase:
1:round begin
2:builder phase
3:producer phase
4:trader phase
5:councilor phase
6:prospector phase
7:all phase
8:no phase
9:game end
*/
//card-------------------------------------------------------------------------
const string roleName[2][5] = {{"Builder\n", "Producer\n", "Trader\n", "Councilor\n", "Prosoector\n"},
                               {"建築師\n", "生產者\n", "商人\n", "市長\n", "淘金者\n"}};
const string roleDescription[2][5] = {{"Action\nStart from governor's left,clock wise.Player can choose to build a building and pay the card cost\n\nPrivilege\nGovernor can pay 1 less of the cost. The final cost can't lower than 1 cost.\n",
                                       "Action\nStart from governor's left,clock wise.Player can choose produce 1 product.\n\nPrivilege\nGovernor can product an extra product.\n",
                                       "Action\nStart from governor's left,clock wise.Player can sell 1 product.\n\nPrivilege\nGovernor can sell an extra product.\n\nFlip 1 price list.\nThe product's value depents on the list.\n",
                                       "Action\nStart from governor's left,clock wise.Player can draw 2 cards and keep one.\n\nPrivilege\nGovernor can draw 5 cards and keep one\n",
                                       "Action\nNone.\n\nPrivilege\nGovernor can draw 1 card.\n"},
                                      {"行動\n從總督左邊開始，順時鐘方向，玩家選擇1張欲建造的建築卡，並支付卡片費用。\n\n特權\n總督在建造時，可以少支付1個費用，但最後的費用不能少於1。\n",
                                       "行動\n從總督左邊開始，順時鐘方向，玩家可以生產1個貨品。\n\n特權\n總督可以多生產1個貨品。\n",
                                       "行動\n從總督左邊開始，順時鐘方向，玩家可以販賣1個貨品。\n\n特權\n總督可以多販賣1個貨品。\n\n翻開1張價目表，貨品價格依照價目表決定。\n",
                                       "行動\n從總督左邊開始，順時鐘方向，玩家抽2張牌選擇1張留著。\n\n特權\n總督可以抽5張牌並選擇1張留著。\n",
                                       "行動\n無。\n\n特權\n總督可以抽1張牌。\n"}};
const char cardNameData[2][30][30] = {{"\033[0;35mIndigo plant\033[0m", "\033[0;33mSugar Mill\033[0m", "\033[0;32mTobacco storage\033[0m",
                                       "\033[0;34mCoffee Roaster\033[0m", "\033[0;36mSilver smelter\033[0m",
                                       "Tower", "Chapel", "Smithy", "Poor House", "Black Market", "Crane", "Carpenter",
                                       "Quarry", "Well", "Aqueduct", "market Stand", "Market Hall", "Trading Post", "Archive",
                                       "Perfecture", "Gold mine", "Library", "Statue", "Victory Column", "Hero", "Guild Hall", "City Hall",
                                       "Triumhal Arch", "Palace"},
                                      {"\033[0;35m染料廠\033[0m", "\033[0;33m蔗糖廠\033[0m", "\033[0;32m菸草廠\033[0m", "\033[0;34m咖啡廠\033[0m", "\033[0;36m白銀廠\033[0m", "塔樓", "禮拜堂", "鐵匠鋪", "救濟院",
                                       "黑市", "起重機", "木工場", "採石場", "水井", "溝渠", "攤販", "市場", "交易所", "檔案館", "辦公處", "金礦坑", "圖書館",
                                       "雕鑄像紀念碑", "勝利柱紀念碑", "英雄像紀念碑", "同業會館", "市政廳", "凱旋門", "宮殿"}};
const string cardDescription[2][30] = {{"\nproducer phase\nowner produces 1 indigo\n",
                                        "\nproducer phase\nowner produces 1 sugar\n",
                                        "\nproducer phase\nowner produces 1 tobacco\n",
                                        "\nproducer phase\nowner produces 1 coffee\n",
                                        "\nproducer phase\nowner produces 1 silver\n",
                                        "\nbeginning of a round\nwhen the governor checks players’ hands for the card limit of 7,\na player with a towerhasa hand limit of 12 instead of 7.\nOf course, if the owner of a tower has more than 12 cards at the\nbeginning of a round,he must discard all cards over 12 to the discard stack.\n",
                                        "\nbeginning of a round\nbefore the governor checks the players’ card limits(of 7 or 12),\nthe owner of a chapel may place any one of his hand cards\nface down under the chapel. At game end, the player scores 1 victory point for each card under his chapel.\n",
                                        "\nbuilder phase\nWhen the owner of a smithy builds a production building, he may pay one\ncard less to build it. When a player builds a violet building,\nhe gets no advantage from a smithy.\n",
                                        "\nbuilder phase\nAfter the owner of a poor house has built a building, he may draw 1 card\nfrom the card supply, adding it to his hand, if he has only 0\nor 1 card in his hand.\n",
                                        "\nbuilder phase\nWhen the owner of a black market builds any building,he may use up to 2 of\nhis goods(from his production buildings) instead of cards from\nhis hand, placing them face down on the discard stack just\nlike cards from his hand.\n",
                                        "\nbuilder phase\nThe owner of a crane may overbuild any of his existing buildings, placing the\nnew building card completely covering the old card. By doing\nso, he reduces the cost of the new building by the cost of\nthe old building.\n",
                                        "\nbuilder phase\nAfter the owner of a carpenter builds a violet building and paysthe buildingcost,\nhe may draw 1 card from the cardsupply and add it to his hand.\nThe carpenter has no special function when the player\nbuilds a production building.\n",
                                        "\nbuilder phase\nWhen the owner of a quarry builds a violet building, he pays 1 card less to build\nthe building.The quarry has no special function when the player\nbuilds a production building.\n",
                                        "\nproducer phase\nIn the producer phase, if the owner of a well produces at least 2 goods, he draws an additional card from\nthe cardsupply, adding it to hishand. It matters not whether he\nis the producer or not.\n",
                                        "\nproducer phase\nIn the producer phase, the owner of an aquaduct may produce 1 more good than otherwise possible\n",
                                        "\ntrader phase\nDuring the trader phase, if the owner of a market stand sells at least 2 goods,\nhe draws an additional card from the cardsupply, adding it to his hand.\nIt matters not whether he is the trader or not.\n",
                                        "\ntrader phase\nWhen the owner of a market hall sells at least one good,he draws 1 card more than\nthe price of the good sold from the card supply. If he sells more than 1 good,\nhe only draws one extra card, not 1 extra\ncard for each good sold.\n",
                                        "\ntrader phase\nDuring the trader phase, the owner of a trading post may sell 1 additional good from\nhis production buildings.\n",
                                        "\ncouncillor phase\nWhen any player selects the councillor role, the owner of an archive adds all cards\nhe draws to his hand and then chooses which cards to discard from his entire hand.\nIn other words,the player may discard drawn cards or cards he\nalready had in his hand instead of just drawn cards.\n",
                                        "\ncouncillor phase\nIn the councillor phase, the owner of a prefecture may keep 2 cards instead of 1\n",
                                        "\nprospector phase\nAfter a player selects the prospector role and takes the privilege (or not),\neach player who owns a gold mine, in clockwise order,may turn over\nthe top-most 4 cards from the card supply, placing them face up on the table:\n• if all four cards have different building costs,\nthe player adds any one of the cards to his hand and discards the other 3 cards face down on the discard stack.\n• if at least 2 of the cards have the same building cost, the player gets no card\nand discards all 4 cards face down onthe discard stack.\n",
                                        "\nall phases\nThe owner of a library may double the privilege of the role he selects.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\ngame end\nAt game end, the owner of a guild hall scores 2 victory points for each production building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a city hall scores 1 victory point for each violet building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a triumphal arch scores victory points(VP) for the monuments\nin hisplay area: for 1 monument he scores 4 VP, for 2 monument she scores 6 VP,\nand for 3 monuments he scores 8 VP.\n",
                                        "\ngame end\nAt game end, the owner of a palace scores an extra 1/4 of his victory points\n"},
                                       {"\nproducer phase\nowner produces 1 indigo\n",
                                        "\nproducer phase\nowner produces 1 sugar\n",
                                        "\nproducer phase\nowner produces 1 tobacco\n",
                                        "\nproducer phase\nowner produces 1 coffee\n",
                                        "\nproducer phase\nowner produces 1 silver\n",
                                        "\nbeginning of a round\nwhen the governor checks players’ hands for the card limit of 7,\na player with a towerhasa hand limit of 12 instead of 7.\nOf course, if the owner of a tower has more than 12 cards at the\nbeginning of a round,he must discard all cards over 12 to the discard stack.\n",
                                        "\nbeginning of a round\nbefore the governor checks the players’ card limits(of 7 or 12),\nthe owner of a chapel may place any one of his hand cards\nface down under the chapel. At game end, the player scores 1 victory point for each card under his chapel.\n",
                                        "\nbuilder phase\nWhen the owner of a smithy builds a production building, he may pay one\ncard less to build it. When a player builds a violet building,\nhe gets no advantage from a smithy.\n",
                                        "\nbuilder phase\nAfter the owner of a poor house has built a building, he may draw 1 card\nfrom the card supply, adding it to his hand, if he has only 0\nor 1 card in his hand.\n",
                                        "\nbuilder phase\nWhen the owner of a black market builds any building,he may use up to 2 of\nhis goods(from his production buildings) instead of cards from\nhis hand, placing them face down on the discard stack just\nlike cards from his hand.\n",
                                        "\nbuilder phase\nThe owner of a crane may overbuild any of his existing buildings, placing the\nnew building card completely covering the old card. By doing\nso, he reduces the cost of the new building by the cost of\nthe old building.\n",
                                        "\nbuilder phase\nAfter the owner of a carpenter builds a violet building and paysthe buildingcost,\nhe may draw 1 card from the cardsupply and add it to his hand.\nThe carpenter has no special function when the player\nbuilds a production building.\n",
                                        "\nbuilder phase\nWhen the owner of a quarry builds a violet building, he pays 1 card less to build\nthe building.The quarry has no special function when the player\nbuilds a production building.\n",
                                        "\nproducer phase\nIn the producer phase, if the owner of a well produces at least 2 goods, he draws an additional card from\nthe cardsupply, adding it to hishand. It matters not whether he\nis the producer or not.\n",
                                        "\nproducer phase\nIn the producer phase, the owner of an aquaduct may produce 1 more good than otherwise possible\n",
                                        "\ntrader phase\nDuring the trader phase, if the owner of a market stand sells at least 2 goods,\nhe draws an additional card from the cardsupply, adding it to his hand.\nIt matters not whether he is the trader or not.\n",
                                        "\ntrader phase\nWhen the owner of a market hall sells at least one good,he draws 1 card more than\nthe price of the good sold from the card supply. If he sells more than 1 good,\nhe only draws one extra card, not 1 extra\ncard for each good sold.\n",
                                        "\ntrader phase\nDuring the trader phase, the owner of a trading post may sell 1 additional good from\nhis production buildings.\n",
                                        "\ncouncillor phase\nWhen any player selects the councillor role, the owner of an archive adds all cards\nhe draws to his hand and then chooses which cards to discard from his entire hand.\nIn other words,the player may discard drawn cards or cards he\nalready had in his hand instead of just drawn cards.\n",
                                        "\ncouncillor phase\nIn the councillor phase, the owner of a prefecture may keep 2 cards instead of 1\n",
                                        "\nprospector phase\nAfter a player selects the prospector role and takes the privilege (or not),\neach player who owns a gold mine, in clockwise order,may turn over\nthe top-most 4 cards from the card supply, placing them face up on the table:\n• if all four cards have different building costs,\nthe player adds any one of the cards to his hand and discards the other 3 cards face down on the discard stack.\n• if at least 2 of the cards have the same building cost, the player gets no card\nand discards all 4 cards face down onthe discard stack.\n",
                                        "\nall phases\nThe owner of a library may double the privilege of the role he selects.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\nMomument\nNo special effect.\n",
                                        "\ngame end\nAt game end, the owner of a guild hall scores 2 victory points for each production building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a city hall scores 1 victory point for each violet building\nin his play area.\n",
                                        "\ngame end\nAt game end, the owner of a triumphal arch scores victory points(VP) for the monuments\nin hisplay area: for 1 monument he scores 4 VP, for 2 monument she scores 6 VP,\nand for 3 monuments he scores 8 VP.\n",
                                        "\ngame end\nAt game end, the owner of a palace scores an extra 1/4 of his victory points\n"}};
//card-------------------------------------------------------------------------

//textLanguage-----------------------------------------------------------------
string startMenuText[2] = {"\tSAN JUAN\n\n1)Start Game\n2)About Project\n3)Language Setting\n4)Quit\nPlease choose a option.\n", "\t聖胡安\n\n1)開始遊戲\n2)關於\n3)語言選擇\n4)離開\n請選擇。\n"};
string invalid[2] = {"Invalid option,please try another one.\n", "無效的選項，請再試一次。\n"};
string bye[2] = {"See Ya\n", "88\n"};
string gamestart[2] = {"How many CPU is playing (1-3)?\n", "要幾個電腦玩家(1-3)?\n"};
string actionMenu[2] = {{"Choose an action\n1)See your cards\n2)See your board\n3)Choose role\n4)End\n"},
                        {"選擇行動\n1)檢視手牌\n2)檢視場上\n3)選擇職業\n4)結束\n"}};
string cardInspect[2] = {{"Choose an action\n1)Inspect card description\n2)Other\n"},
                         {"選擇行動\n1)檢視卡牌敘述\n2)其他\n"}};
string chooseCard[2] = {{"Choose a card(Enter -1 to leave)\n"},
                        {"選擇一張卡(輸入-1退出)\n"}};
string chooseRoleText[2] = {{"Choose a role\n1)Builder\n2)Producer\n3)Trader\n4)Councilor\n5)Prospector\n"},
                            {"選擇一項職業\n1)建築師\n2)生產者\n3)商人\n4)市長\n5)淘金者\n"}};
string inspectRole[2] = {{"Choose an action\n1)Confirm\n2)See the ability\n3)back\n"},
                         {"選擇行動\n1)確認\n2)檢視能力\n3)返回\n"}};
//textLanguage-----------------------------------------------------------------
u8 language = 0;
u8 drawCnt = 0;
void (*menuFunc[3])() = {mainGame, about, setting};
void (*roleFunc[5])(u8 governor) = {builder, producer, trader, councilor, prospector};
role roles[5] = {0};
player players[4] = {0};
card deck[110] = {0};
void menu()
{
    setbuf(stdin, NULL);
    while (1)
    {
        printf("%s", startMenuText[language]);
        int option = -1;
        scanf("%d", &option);
        while ((option > 4 || option < 0))
        {
            setbuf(stdin, NULL);
            option = -1;
            printf("%s", invalid[language]);
            scanf("%d", &option);
        }
        CLEAN
        setbuf(stdin, NULL);
        if (option == 4)
        {
            printf("%s", bye[language]);
            break;
        }
        else
        {
            menuFunc[option - 1]();
        }
    }
    return;
}
void init(u8 playercount)
{
    for (i32 i = 0; i < 5; i++)
    {
        roles[i].id = i;
        strncpy(roles[i].desription, roleDescription[language][i], sizeof(string));
        strncpy(roles[i].roleName, roleName[language][i], sizeof(string));
        roles[i].effect = roleFunc[i];
    }
    for (i32 i = 0; i < 4; i++)
    {
        memset(&players[i], 0, sizeof(player));
        players[i].maxCard = 7;
        players[i].cardCount = 4;
        players[i].playerOrder = i;
        players[i].point = 0;
    }
    //init deck
    i32 index = 0;
    for (u8 i = 0; i < 29; i++)
    {
        for (i32 j = 0; j < cardCounts[i]; j++)
        {
            strncpy(deck[index].cardName, cardNameData[language][i], sizeof(deck[index].cardName));
            strncpy(deck[index].description, cardDescription[language][i], sizeof(deck[index].description));
            deck[index].place = 1;
            deck[index].id = i;
            deck[index].type = type[i];
            deck[index].vp = phase[i];
            deck[index].cost = cost[i];
            index++;
        }
    }
    for (i32 i = 0; i <= playercount; i++)
    {
        players[i].cardCount = 4;
        deck[i].place = 3;
        players[i].board[0] = deck[i];
        players[i].boardCount = 1;
        memset(&deck[i], 0, sizeof(card));
    }
    shuffle();
    /* for (int i = 0; i < 110; i++)
    {
        if(deck[i].place != 1)
            continue;
        printf("Card:%s\n%s\n\n", deck[i].cardName, deck[i].description);
    } */
    for (i32 i = 0; i <= playercount; i++)
    {
        players[i].cardCount = 0;
        for (i32 j = 0; j < 4; j++)
        {
            draw(&players[i]);
        }
    }
    return;
}
void mainGame()
{
    u8 playercnt = -1;
    printf("%s", gamestart[language]);
    scanf("%hhd", &playercnt);
    while ((playercnt > 4 || playercnt < 0))
    {
        setbuf(stdin, NULL);
        playercnt = -1;
        printf("%s", invalid[language]);
        scanf("%hhd", &playercnt);
    }
    CLEAN
    setbuf(stdin, NULL);
    init(playercnt);

    u8 gameProgressing = 0;
    printPlayerStatus(&players[0]);
    while (gameProgressing)
    {
        printPlayerStatus(&players[0]);
    }
    GameEnd();
    return;
}
void GameEnd()
{
}
void about()
{
    CLEAN
    string projectAbout[2] = {"\tAbout the project\n\nProgramming-II Final Project\tSan Juan\nProgrammer:Lapor Chen(Cheng-Wei Chen)\nStudent ID:409474016S\n", "\t關於\n\n程式設計二期末專題 聖胡安\n作者:陳韡承\n學號:40947916S\n"};
    printf("%s\n", projectAbout[language]);
    return;
}
void setting()
{
    string settingStr[2] = {"\tChoose a language\n\n1)English\n2)中文\n", "\t選擇語言\n\n1)English\n2)中文\n"};
    printf("%s", settingStr[language]);
    int la = -1;
    scanf("%d", &la);
    while ((la > 2 || la < 1))
    {
        setbuf(stdin, NULL);
        printf("%s", invalid[language]);
        scanf("%d", &la);
    }
    language = la - 1;
    CLEAN
    return;
}
void printPlayerStatus(player *p)
{
    u8 choice = -1;
    while (choice != 4)
    {
        CLEAN
        printf("%s", actionMenu[language]);
        choice = -1;
        scanf("%hhd", &choice);
        while ((choice > 4 || choice < 1))
        {
            setbuf(stdin, NULL);
            choice = -1;
            printf("%s", invalid[language]);
            scanf("%hhd", &choice);
        }
        CLEAN
        setbuf(stdin, NULL);
        if (choice == 4)
            break;
        if (choice == 1)
        {
            for (int i = 0; i < p->cardCount; i++)
            {
                printf("%d)%s\n", i + 1, p->hand[i].cardName);
            }
            printf("\n");
            printf("%s", cardInspect[language]);
            u8 choice2 = -1;
            scanf("%hhd", &choice2);
            while ((choice2 > 2 || choice2 < 1))
            {
                setbuf(stdin, NULL);
                choice2 = -1;
                printf("%s", invalid[language]);
                scanf("%hhd", &choice2);
            }
            CLEAN
            setbuf(stdin, NULL);
            if (choice2 == 1)
            {
                readDes(players[0], 0);
            }
        }
        if (choice == 2)
        {
            for (int i = 0; i < p->boardCount; i++)
            {
                printf("%d)%s\n", i + 1, p->board[i].cardName);
            }
            printf("\n");
            printf("%s", cardInspect[language]);
            u8 choice2 = -1;
            scanf("%hhd", &choice2);
            while ((choice2 > 2 || choice2 < 1))
            {
                setbuf(stdin, NULL);
                choice2 = -1;
                printf("%s", invalid[language]);
                scanf("%hhd", &choice2);
            }
            CLEAN
            setbuf(stdin, NULL);
            if (choice2 == 1)
            {
                readDes(players[0], 1);
            }
        }
        if (choice == 3)
        {
            chooseRole(0);
        }
    }
    return;
}
void readDes(player p, u8 mode)
{
    CLEAN
    if (mode)
    {

        i8 choice = -2;
        while (1)
        {
            for (i32 i = 0; i < p.boardCount; i++)
            {
                printf("%d)%s\n", i + 1, p.board[i].cardName);
            }
            printf("%s", chooseCard[language]);
            choice = -2;
            scanf("%hhd", &choice);

            if (choice == -1)
                break;
            while ((choice > p.boardCount || choice < 1))
            {
                setbuf(stdin, NULL);
                choice = -2;
                printf("%s", invalid[language]);
                scanf("%hhd", &choice);
                if (choice == -1)
                    break;
            }
            CLEAN
            if (choice == -1)
                break;
            printf("\t%s\nCost:%d\nVictory Point:%d\n\n%s", p.board[choice - 1].cardName, p.board[choice - 1].cost, p.board[choice - 1].vp, p.board[choice - 1].description);

            setbuf(stdin, NULL);
        }
    }
    else
    {
        while (1)
        {
            for (i32 i = 0; i < p.cardCount; i++)
            {
                printf("%d)%s\n", i + 1, p.hand[i].cardName);
            }
            i8 choice = -2;
            printf("%s", chooseCard[language]);
            choice = -2;
            scanf("%hhd", &choice);

            if (choice == -1)
                break;
            while ((choice > p.cardCount || choice < 1))
            {
                setbuf(stdin, NULL);
                choice = -2;
                printf("%s", invalid[language]);
                scanf("%hhd", &choice);
                if (choice == -1)
                    break;
            }
            CLEAN
            if (choice == -1)
                break;
            if (language)
                printf("\t%s\n費用:%d\n勝利點數:%d\n\n%s", p.hand[choice - 1].cardName, p.hand[choice - 1].cost, p.hand[choice - 1].vp, p.hand[choice - 1].description);
            else
                printf("\t%s\nCost:%d\nVictory Point:%d\n\n%s", p.hand[choice - 1].cardName, p.hand[choice - 1].cost, p.hand[choice - 1].vp, p.hand[choice - 1].description);

            setbuf(stdin, NULL);
        }
    }
    return;
}
void shuffle()
{
    for (i32 a = 0; a < 100; a++)
    {
        for (i32 i = 0; i < 110; i++)
        {
            i32 c = rand() % 110;
            if (!deck[i].place == 0 || !deck[c].place)
                continue;
            card tmp = deck[i];
            deck[i] = deck[c];
            deck[c] = tmp;
        }
    }
    return;
}
void draw(player *p)
{
    if (drawCnt == 110)
        return;
    while (deck[drawCnt].place != 1)
        drawCnt++;
    deck[drawCnt].place = 2;
    i32 i = 0;
    while (p->hand[i].place == 2)
        i++;
    p->hand[i] = deck[drawCnt];
    p->cardCount++;
    memset(&deck[drawCnt], 0, sizeof(card));
    drawCnt++;
    return;
}
void chooseRole(u8 goveror)
{
    while (1)
    {
        u8 choice = -1;
        printf("%s", chooseRoleText[language]);
        scanf("%hhd", &choice);
        while ((choice > 5 || choice < 1))
        {
            setbuf(stdin, NULL);
            choice = -1;
            printf("%s", invalid[language]);
            scanf("%hhd", &choice);
        }
        CLEAN
        setbuf(stdin, NULL);

        while (1)
        {
            printf("%s", inspectRole[language]);
            u8 choice2 = 0;
            scanf("%hhd", &choice2);
            while (choice2 > 3 || choice2 < 1)
            {
                setbuf(stdin, NULL);
                choice2 = 0;
                printf("%s", invalid[language]);
                scanf("%hhd", &choice2);
            }
            CLEAN
            setbuf(stdin, NULL);
            if (choice2 == 1)
            {
                roleFunc[choice-1](goveror);
                return;
            }
            if (choice2 == 2)
            {
                printf("%s\n", roles[choice-1].desription);
            }
            if (choice2 == 3)
                break;
        }
    }
}
//role functions
void builder(u8 goveror)
{
}
void producer(u8 goveror)
{
}
void trader(u8 goveror)
{
}
void councilor(u8 goveror)
{
}
void prospector(u8 goveror)
{
    printf("%d\n", goveror);
    draw(&players[goveror]);
    return;
}