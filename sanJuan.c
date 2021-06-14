#include "sanJuan.h"
#include "saving.h"
const u8 cardCounts[] = {10, 8, 8, 8, 8, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2, 2, 2, 2};
const u8 vp[] = {1, 1, 2, 2, 3, 2, 2, 1, 1, 1, 1, 2, 2, 1, 2, 1, 2, 1, 1, 2, 1, 3, 3, 4, 5, 0, 0, 0, 0};
const u8 type[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 2, 2};
const u8 phase[] = {3, 3, 3, 3, 3, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 4, 4, 4, 5, 5, 6, 7, 8, 8, 8, 9, 9, 9, 9};
const u8 cost[] = {1, 2, 3, 4, 5, 3, 3, 1, 2, 2, 2, 3, 4, 2, 3, 2, 4, 2, 1, 3, 1, 5, 3, 4, 5, 6, 6, 6, 6};
const u8 priceList[5][5] = {{1, 1, 2, 2, 3},
                            {1, 2, 2, 2, 3},
                            {1, 1, 2, 2, 2},
                            {1, 2, 2, 3, 3},
                            {1, 1, 1, 2, 2}};
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
const string productName[2][5] = {{"\033[0;35mIndigo\033[0m", "\033[0;33mSugar\033[0m", "\033[0;32mTabacco\033[0m", "\033[0;34mCoffee\033[0m", "\033[0;36mSilver\033[0m"},
                                  {"\033[0;35m染料\033[0m", "\033[0;33m糖\033[0m", "\033[0;32m菸草\033[0m", "\033[0;34m咖啡\033[0m", "\033[0;36m白銀\033[0m"}};
const string CPUdraw[2][2] = {{"CPU ", " drawed.\n"}, {"CPU ", " 抽了卡\n"}};
const string chooseOne[2] = {"Choose one to keep", "選擇一張留下"};
const string chosedCard[2] = {"Chosed ", "選擇"};
const string chosed[2] = {"You chosed", "你選擇了"};
const string drew[2] = {"You drew ", "你抽到了 "};
const string whatToBuild[2] = {"Choose a building to build.\n", "選擇一個建築來建造\n"};
const string built[2] = {"built", "建造"};
const string nobuild[2] = {"chosed to not build anything\n", "決定不蓋建築\n"};
const string costText[2] = {"Cost", "費用"};
const string notEnoughCard[2] = {"You don't have enough cost.\n", "手牌不足以負擔費用\n"};
const string whatToPay[2] = {"Choose a card to pay the building.", "選擇1張牌來支付建築"};
const string pass[2] = {"You pass.\n", "你選擇跳過\n"};
const string passChoice[2] = {"Pass", "跳過"};
const string produceText[2] = {"produce", "生產"};
const string yourTurn[2] = {"It's your turn.", "輪到你了"};
//card-------------------------------------------------------------------------
const string cardNameData[2][30] = {{"\033[0;35mIndigo plant\033[0m", "\033[0;33mSugar Mill\033[0m", "\033[0;32mTobacco storage\033[0m",
                                     "\033[0;34mCoffee Roaster\033[0m", "\033[0;36mSilver smelter\033[0m",
                                     "Tower", "Chapel", "Smithy", "Poor House", "Black Market", "Crane", "Carpenter",
                                     "Quarry", "Well", "Aqueduct", "market Stand", "Market Hall", "Trading Post", "Archive",
                                     "Perfecture", "Gold mine", "Library", "Statue", "Victory Column", "Hero", "Guild Hall", "City Hall",
                                     "Triumhal Arch", "Palace"},
                                    {"\033[0;35m染料廠\033[0m", "\033[0;33m蔗糖廠\033[0m", "\033[0;32m菸草廠\033[0m", "\033[0;34m咖啡廠\033[0m", "\033[0;36m白銀廠\033[0m", "塔樓", "禮拜堂", "鐵匠鋪", "救濟院",
                                     "黑市", "起重機", "木工場", "採石場", "水井", "溝渠", "攤販", "市場", "交易所", "檔案館", "辦公處", "金礦坑", "圖書館",
                                     "雕鑄像紀念碑", "勝利柱紀念碑", "英雄像紀念碑", "同業會館", "市政廳", "凱旋門", "宮殿"}};
//textLanguage-----------------------------------------------------------------
const string startMenuText[2] = {"\tSAN JUAN\n\n1)New Game\n2)Load Game\n3)About Project\n4)Setting\n5)Quit\nPlease choose a option.\n", "\t聖胡安\n\n1)新遊戲\n2)讀取遊戲\n3)關於\n4)設定\n5)離開\n請選擇。\n"};
const string invalid[2] = {"Invalid option,please try another one.\n", "無效的選項，請再試一次。\n"};
const string bye[2] = {"See Ya\n", "88\n"};

//textLanguage-----------------------------------------------------------------
u8 language = 1;
u8 playercnt = -1;
u8 cardLeftInDeck = 110;
u8 GAMEEND = 12;
u8 cpuLevel = 1;
u8 gameIsLoaded = 0;
u8 loadedOrder = -1;
u8 gameProgressing = 1;
void (*menuFunc[4])() = {mainGame, loadGame, about, setting};
void (*roleFunc[5])(player p[], u8 governor) = {builder, producer, trader, councilor, prospector};

role roles[5] = {0};
player players[4] = {0};
card deck[DECKSIZE] = {0};
card discard[DECKSIZE] = {0};
u8 discardSize = 0;
u8 discardDeckOrder = 0;
void menu()
{
    setbuf(stdin, NULL);
    while (1)
    {
        printf("%s", startMenuText[language]);
        int option = -1;
        scanf("%d", &option);
        while ((option > 5 || option < 1))
        {
            setbuf(stdin, NULL);
            option = -1;
            INVALID
            scanf("%d", &option);
        }
        CLEAN
        setbuf(stdin, NULL);
        if (option == 5)
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
    const string roleName[2][5] = {{"Builder", "Producer", "Trader", "Councilor", "Prosoector"}, {"建築師", "生產者", "商人", "市長", "淘金者"}};
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
    for (i32 i = 0; i < 5; i++)
    {
        roles[i].used = 0;
        roles[i].id = i;
        strncpy(roles[i].desription, roleDescription[language][i], sizeof(string));
        strncpy(roles[i].roleName, roleName[language][i], sizeof(string));
    }
    for (i32 i = 0; i < playercount; i++)
    {
        memset(&players[i], 0, sizeof(player));
        players[i].maxCard = 7;
        players[i].cardCount = 4;
        players[i].playerOrder = i;
        players[i].point = 0;
    }
    //init deck
    i32 index = 0;
    memset(deck, 0, sizeof(deck));
    for (u8 i = 0; i < 29; i++)
    {
        for (i32 j = 0; j < cardCounts[i]; j++)
        {
            strncpy(deck[index].cardName, cardNameData[language][i], sizeof(deck[index].cardName));
            strncpy(deck[index].description, cardDescription[language][i], sizeof(deck[index].description));
            deck[index].place = 1;
            deck[index].id = i;
            deck[index].type = type[i];
            deck[index].phase = phase[i];
            deck[index].vp = vp[i];
            deck[index].cost = cost[i];
            index++;
        }
    }
    for (i32 i = 0; i < playercount; i++)
    {
        deck[i].place = 3;
        players[i].board[0] = deck[i];
        players[i].boardCount = 1;
        memset(&deck[i], 0, sizeof(card));
    }
    shuffle();
    for (i32 i = 0; i < playercount; i++)
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
    const string gamestart[2] = {"How many CPU is playing (1-3)?\n", "要幾個電腦玩家(1-3)?\n"};
    const string newRound[2] = {"A new round has started.", "新的回合開始了"};
    if (gameIsLoaded != 1)
    {
        printf("%s", gamestart[language]);
        scanf("%hhd", &playercnt);
        while ((playercnt > 3 || playercnt < 1))
        {
            setbuf(stdin, NULL);
            playercnt = -1;
            INVALID
            scanf("%hhd", &playercnt);
        }
        playercnt++;
        CLEAN
        setbuf(stdin, NULL);
        init(playercnt);
    }

    u8 nowPlaying = loadedOrder;
    if (loadedOrder > playercnt)
        nowPlaying = rand() % playercnt;
    while (gameProgressing == 1)
    {
        for (i32 j = 0; j < playercnt; j++)
            if (players[j].boardCount == GAMEEND)
            {
                gameProgressing = 0;
                break;
            }
        printf("%s\n", newRound[language]);
        recycleCard();
        //PRINTDECK
        roleReset(roles); //reset role
        //Check tower
        for (i32 i = 0; i < playercnt; i++)
        {
            tower(&players[nowPlaying]);
        }
        for (i32 i = 0; i < playercnt; i++)
            chapel(&players[(nowPlaying + i) % playercnt]);
        for (i32 c = 0; c < playercnt; c++) //reduce cards
            reduceCard(&players[c]);

        for (i32 i = 0; i < playercnt; i++)
        {

            if (nowPlaying == 0)
            {
                printPlayerStatus(&players[nowPlaying]);
                if(gameProgressing != 1)
                    break;
            }
            else
            {
                computerAction(&players[nowPlaying]);
            }
            nowPlaying++;
            nowPlaying %= playercnt;
            for (i32 j = 0; j < playercnt; j++)
                if (players[j].boardCount == GAMEEND)
                {
                    gameProgressing = 0;
                    break;
                }
        }
        nowPlaying++;
        nowPlaying %= playercnt;
    }
    if(gameProgressing == 0)
        GameEnd();
    return;
}
void GameEnd()
{
    CLEAN
    string rank[2] = {"Rank", "排名"};
    string playerName[2] = {"Player", "玩家"};
    u8 vp[4] = {0};
    u8 order[4] = {0, 1, 2, 3};
    for (i32 i = 0; i < playercnt; i++)
        for (i32 j = 0; j < players[i].boardCount; j++)
            vp[i] += players[i].board[j].vp;

    for (i32 i = 0; i < playercnt; i++)
        for (i32 j = i; j < playercnt; j++)
        {
            if (vp[i] < vp[j])
            {
                u8 tmp1 = vp[i];
                u8 tmp2 = order[i];
                vp[i] = vp[j];
                order[i] = order[j];
                vp[j] = tmp1;
                order[j] = tmp2;
            }
        }
    printf("%s\n", rank[language]);
    for (i32 i = 0; i < playercnt; i++)
    {
        printf("No.%d\t", i + 1);
        if (order[i] == 0)
        {
            printf("%s %d\n", playerName[language], vp[i]);
        }
        else
        {
            printf("CPU %d %d\n", order[i], vp[i]);
        }
    }
    printf("\n\n\n\n\n");
    return;
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
    string choooseSetting[2] = {"1)Game setting\n2)Language\n", "1)遊戲選項\n2)語言選項\n"};
    string settingStr[2] = {"\tChoose a language\n\n1)English\n2)中文\n", "\t選擇語言\n\n1)English\n2)中文\n"};
    printf("%s", choooseSetting[language]);
    u8 choice = -1;
    scanf("%hhd", &choice);
    while ((choice > 2 || choice < 1))
    {
        INVALID
        setbuf(stdin, NULL);
        scanf("%hhd", &choice);
    }
    CLEAN
    if (choice == 1)
    {
        string gameSetting[2] = {"1)CPU level\n2)Ending requirement\n", "1)CPU 難度\n2)結束條件\n"};
        printf("%s", gameSetting[language]);
        scanf("%hhd", &choice);
        while ((choice > 2 || choice < 1))
        {
            INVALID
            setbuf(stdin, NULL);
            scanf("%hhd", &choice);
        }
        CLEAN
        if (choice == 1)
        {
            string levelSetting[2] = {"CPU level (1,2)\nCurrent setting : ", "CPU等級 (1,2)\n目前設定 : "};
            printf("%s %d\n", levelSetting[language], cpuLevel);
            scanf("%hhd", &choice);
            while ((choice > 2 || choice < 1))
            {
                INVALID
                setbuf(stdin, NULL);
                scanf("%hhd", &choice);
            }
            cpuLevel = choice;
        }
        else
        {
            string ending[2] = {"How many built cards are required to end the game (6-12)\nCurrent setting : ", "需要建造幾張卡來結束遊戲 (6-12)\n目前設定 : "};
            printf("%s %d\n", ending[language], GAMEEND);
            scanf("%hhd", &choice);
            while ((choice > 12 || choice < 6))
            {
                INVALID
                setbuf(stdin, NULL);
                scanf("%hhd", &choice);
            }
            GAMEEND = choice;
        }
    }
    else if (choice == 2)
    {
        printf("%s", settingStr[language]);
        int la = -1;
        scanf("%d", &la);
        while ((la > 2 || la < 1))
        {
            INVALID
            setbuf(stdin, NULL);
            scanf("%d", &la);
        }
        language = la - 1;
        CLEAN
    }
    return;
}
void printPlayerStatus(player *p)
{
    string actionMenu[2] = {{"Choose an action\n1)See your cards\n2)See your board\n3)Choose role\n4)Check other players\' board\n5)Save & Exit\n"}, //5)End\n
                            {"選擇行動\n1)檢視手牌\n2)檢視場上\n3)選擇職業\n4)檢視其他玩家資訊\n5)儲存遊戲並離開\n"}};                                  //5)結束\n
    while (1)
    {
        printf("%s", actionMenu[language]);
        if (chooseAction(0))
            break;
    }

    return;
}
void readDes(u8 p, u8 mode)
{
    string chooseCard[2] = {{"Choose a card.\n"},
                            {"選擇一個選項\n"}};
    string back[2] = {"Return", "返回"};
    CLEAN
    if (mode)
    {

        i8 choice = -2;
        while (1)
        {
            for (i32 i = 0; i < players[p].boardCount; i++)
            {
                printf("%d)%s\n", i + 1, players[p].board[i].cardName);
            }
            printf("%d)%s\n", players[p].boardCount + 1, back[language]);
            printf("%s", chooseCard[language]);
            choice = -2;
            scanf("%hhd", &choice);

            if (choice == players[p].boardCount + 1)
                break;
            while ((choice > players[p].boardCount + 1 || choice < 1))
            {
                setbuf(stdin, NULL);
                choice = -2;
                INVALID
                scanf("%hhd", &choice);
                if (choice == players[p].boardCount + 1)
                    break;
            }
            CLEAN
            if (choice == players[p].boardCount + 1)
                break;
            printf("\t%s\nCost:%d\nVictory Point:%d\n\n%s", players[p].board[choice - 1].cardName, players[p].board[choice - 1].cost, players[p].board[choice - 1].vp, players[p].board[choice - 1].description);

            setbuf(stdin, NULL);
        }
    }
    else
    {
        while (1)
        {
            for (i32 i = 0; i < players[p].cardCount; i++)
            {
                printf("%d)%s\n", i + 1, players[p].hand[i].cardName);
            }
            printf("%d)%s\n", players[p].cardCount + 1, back[language]);
            i8 choice = -2;
            printf("%s", chooseCard[language]);
            choice = -2;
            scanf("%hhd", &choice);

            if (choice == players[p].cardCount + 1)
                break;
            while ((choice > players[p].cardCount + 1 || choice < 1))
            {
                setbuf(stdin, NULL);
                choice = -2;
                INVALID
                scanf("%hhd", &choice);
                if (choice == players[p].cardCount + 1)
                    break;
            }
            CLEAN
            if (choice == players[p].cardCount + 1)
                break;
            if (language)
                printf("\t%s\n費用:%d\n勝利點數:%d\n\n%s", players[p].hand[choice - 1].cardName, players[p].hand[choice - 1].cost, players[p].hand[choice - 1].vp, players[p].hand[choice - 1].description);
            else
                printf("\t%s\nCost:%d\nVictory Point:%d\n\n%s", players[p].hand[choice - 1].cardName, players[p].hand[choice - 1].cost, players[p].hand[choice - 1].vp, players[p].hand[choice - 1].description);

            setbuf(stdin, NULL);
        }
    }
    return;
}
void shuffle()
{
    for (i32 a = 0; a < 100; a++)
    {
        for (i32 i = 0; i < DECKSIZE; i++)
        {
            i32 c = rand() % DECKSIZE;
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
    u8 drawCnt = 0;
    if (cardLeftInDeck == 0)
    {
        drawCnt = 0;
        recycleCard();
    }
    while (drawCnt < DECKSIZE && deck[drawCnt].place != 1)
        drawCnt++;
    deck[drawCnt].place = 2;
    i32 i = 0;
    while (p->hand[i].place == 2)
        i++;
    p->hand[i] = deck[drawCnt];
    p->cardCount++;
    memset(&deck[drawCnt], 0, sizeof(card));
    drawCnt++;
    cardLeftInDeck--;
    return;
}
void recycleCard()
{
    u8 cnt = 0, newCnt = 0;
    for (i32 i = 0; i < discardSize; i++)
    {
        cnt = newCnt;
        while (deck[cnt].place == 1)
            cnt++;
        newCnt = cnt + 1;
        deck[cnt] = discard[i];
        deck[cnt].place = 1;
    }
    discardSize = 0;
    shuffle();
}
void discardCard(player *p, u8 chosedCard)
{
    if (discardDeckOrder > 80)
        recycleCard();
    u8 cardCnt = p->cardCount;
    while (discard[discardDeckOrder].place != 0)
        discardDeckOrder++;
    discard[discardDeckOrder] = p->hand[chosedCard];
    discard[discardDeckOrder].place = 0;
    card empty = {0};
    p->hand[chosedCard] = empty;
    p->hand[chosedCard] = p->hand[cardCnt - 1]; //take player's last card and place it in the empty spot
    p->hand[cardCnt - 1] = empty;
    p->cardCount--;
    discardDeckOrder++;
    discardSize++;
    return;
}
void printPlayerCard(player *p)
{
    for (i32 i = 0; i < p->cardCount; i++)
    {
        printf("%d)%s %s %d VP: %d\n", i + 1, p->hand[i].cardName, costText[language], p->hand[i].cost, p->hand[i].vp);
    }
    return;
}
void printPlayerBoard(player *p)
{
    const string hasProduct[2][2] = {{"", "(has product)"}, {"", "(有貨品)"}};
    const string extraScore[2] = {"Extra's Score :", "額外分數:"};
    for (i32 i = 0; i < p->boardCount; i++)
    {

        printf("%d)%s %s ", i + 1, p->board[i].cardName, hasProduct[language][p->board[i].hasProduct]);
        if (p->board[i].chapelScore != 0)
        {
            printf("%s %d", extraScore[language], p->board[i].chapelScore);
        }
        printf("\n");
    }
    return;
}
void chooseRole(u8 goveror)
{
    string chooseRoleText[2] = {{"Choose a role\n"},
                                {"選擇一項職業\n"}};
    string inspectRole[2] = {{"Choose an action\n1)Confirm\n2)See the ability\n3)back\n"},
                             {"選擇行動\n1)確認\n2)檢視能力\n3)返回\n"}};
    string roleUsed[2] = {"Role is choosed in this round.", "此職業在這回合已被選擇"};
    string used[2] = {"(Used)", "(已選擇)"};
    while (1)
    {
        u8 choice = -1;
        printf("%s", chooseRoleText[language]);
        for (i32 i = 0; i < 5; i++)
        {
            printf("%d)%s", i + 1, roles[i].roleName);
            if (roles[i].used)
                printf("%s", used[language]);
            printf("\n");
        }
        scanf("%hhd", &choice);
        while ((choice > 5 || choice < 1))
        {
            setbuf(stdin, NULL);
            choice = -1;
            INVALID
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
                INVALID
                scanf("%hhd", &choice2);
            }
            CLEAN
            setbuf(stdin, NULL);
            if (choice2 == 1 && !roles[choice - 1].used)
            {
                roles[choice - 1].used = 1;
                roleFunc[choice - 1](players, goveror);
                return;
            }
            else if (choice2 == 1 && roles[choice - 1].used)
            {
                printf("%s\n", roleUsed[language]);
            }
            if (choice2 == 2)
            {
                printf("%s\n", roles[choice - 1].desription);
            }

            if (choice2 == 3)
                break;
        }
    }
}
u8 chooseAction(u8 p)
{
    string cardInspect[2] = {{"Choose an action\n1)Inspect card description\n2)Go back\n"},
                             {"選擇行動\n1)檢視卡牌敘述\n2)返回\n"}};
    u8 allChoice = 5;
    u8 choice = -1;
    scanf("%hhd", &choice);
    while ((choice > allChoice || choice < 1))
    {
        setbuf(stdin, NULL);
        choice = -1;
        INVALID
        scanf("%hhd", &choice);
    }
    CLEAN
    setbuf(stdin, NULL);
    if (choice == 1)
    {
        printPlayerCard(&players[p]);
        printf("%s", cardInspect[language]);
        u8 choice2 = -1;
        scanf("%hhd", &choice2);
        while ((choice2 > 2 || choice2 < 1))
        {
            setbuf(stdin, NULL);
            choice2 = -1;
            INVALID
            scanf("%hhd", &choice2);
        }
        CLEAN
        setbuf(stdin, NULL);
        if (choice2 == 1)
        {
            readDes(0, 0);
        }
    }
    if (choice == 2)
    {
        printPlayerBoard(&players[p]);
        printf("\n");
        printf("%s", cardInspect[language]);
        u8 choice2 = -1;
        scanf("%hhd", &choice2);
        while ((choice2 > 2 || choice2 < 1))
        {
            setbuf(stdin, NULL);
            choice2 = -1;
            INVALID
            scanf("%hhd", &choice2);
        }
        CLEAN
        setbuf(stdin, NULL);
        if (choice2 == 1)
        {
            readDes(0, 1);
        }
    }
    if (choice == 3)
    {
        chooseRole(0);
        return 1;
    }
    if (choice == 4)
    {
        printCPUstatus(players);
    }
    if (choice == 5)
    {
        saveGame();
        gameProgressing = -1;
        return 1;
    }
    return 0;
}
void printCPUstatus(player *p)
{
    const string stats[2][3] = {{"CPU", "Handcard", "Board"}, {"CPU", "手牌", "場上"}};
    for (i32 i = 1; i < playercnt; i++)
    {
        printf("%s %d\n%s %d\n%s\n", stats[language][0], i, stats[language][1], p[i].cardCount, stats[language][2]);
        printPlayerBoard(&p[i]);
        printf("\n");
    }
    return;
}
void produce(player *p, u8 card)
{
    p->board[card].hasProduct = 1;
    return;
}
void sell(player *p, u8 card, u8 price)
{
    p->board[card].hasProduct = 0;
    while (price--)
        draw(p);
    return;
}
void computerAction(player *p)
{
    SLEEP
    string cardUsed[2] = {"chooses", "選擇"};
    u8 actionChoice = rand() % 5;
    while (roles[actionChoice].used)
    {
        actionChoice = rand() % 5;
    }
    printf("CPU  %d %s %s\n\n", p->playerOrder, cardUsed[language], roles[actionChoice].roleName);
    roles[actionChoice].used = 1;
    roleFunc[actionChoice](players, p->playerOrder);
    return;
}
void roleReset(role r[])
{
    for (i32 i = 0; i < 5; i++)
    {
        r[i].used = 0;
    }
    return;
}
void reduceCard(player *p)
{
    string reduce[2] = {"Please choose a card to discard.", "請選擇1張牌捨棄"};
    i8 max = p->maxCard;

    while (p->cardCount > max)
    {
        if (p->playerOrder == 0)
        {
            u8 cardCnt = p->cardCount;
            printf("%s (%d/%d)\n", reduce[language], cardCnt, max);
            printPlayerCard(p);
            u8 choice = -1;
            scanf("%hhd", &choice);
            while (choice > cardCnt || choice < 1)
            {
                INVALID
                choice = -1;
                scanf("%hhd", &choice);
            }
            discardCard(p, choice - 1);
            CLEAN
        }
        else
        {
            u8 choice = rand() % p->cardCount;
            discardCard(p, choice);
        }
    }
    return;
}
u8 searchCard(player *p, u8 id)
{
    for (i32 i = 0; i < p->cardCount; i++)
        if (p->hand[i].id == id)
            return i;
    return 255;
}
u8 searchBoard(player *p, u8 id)
{
    u8 cnt = 0;
    for (i32 i = 0; i < p->boardCount; i++)
        if (p->board[i].id == id)
            cnt++;
    return cnt;
}
void giveCard(player *p, card c)
{
    u8 empty = 0;
    while (p->hand[empty].place == 2)
        empty++;
    p->hand[empty] = c;
    p->hand[empty].place = 2;
    p->cardCount++;
    return;
}
void loadGame()
{
    savefile savefileToLoad = {0};
    if (load(language, &savefileToLoad) == 1)
    {
        GAMEEND = savefileToLoad.gameend;
        cpuLevel = savefileToLoad.level;
        playercnt = savefileToLoad.playerCount;
        for (i32 i = 0; i < 110; i++)
        {
            deck[i] = savefileToLoad.deck[i];
            discard[i] = savefileToLoad.discard[i];
        }
        for (i32 i = 0; i < savefileToLoad.playerCount; i++)
        {
            players[i] = savefileToLoad.players[i];
        }
        for (i32 i = 0; i < 5; i++)
        {
            roles[i] = savefileToLoad.roles[i];
        }
        u8 nowPlaying = 0;
        i8 cnt = 0;
        for (i32 i = 0; i < 5; i++)
            cnt += roles[i].used;

        loadedOrder = (cnt + 1) % playercnt;
        for (i32 i = savefileToLoad.nowPlaying; i < playercnt; i++)
        {
            if (nowPlaying == 0)
            {
                printPlayerStatus(&players[nowPlaying]);
            }
            else
            {
                computerAction(&players[nowPlaying]);
            }
            nowPlaying++;
            nowPlaying %= playercnt;
        }
        gameIsLoaded = 1;
        mainGame();
    }
}
void saveGame()
{
    save(language, players, playercnt, GAMEEND, cpuLevel, deck, discard, roles);
}
//role functions
void builder(player p[], u8 goveror)
{
    u8 nowPlaying = goveror;
    for (i32 c = 0; c < playercnt; c++)
    {
        if (nowPlaying == 0)
            printf("%s\n", yourTurn[language]);
        smithy(&p[nowPlaying]);
        quarry(&p[nowPlaying]);
        library(&p[nowPlaying]);
        crane(&p[nowPlaying]);
        u8 costdown = 0;
        if (nowPlaying == goveror)
            costdown += 1 * p[nowPlaying].library;

        if (nowPlaying == 0)
        {
            u8 useCrane;
            if (p[nowPlaying].crane)
            {
                scanf("%hhd", &useCrane);
                while (useCrane != 1 && useCrane != 2)
                {
                    INVALID
                    scanf("%hhd", &useCrane);
                }
            }
            if (p[nowPlaying].cardCount == 0)
            {
                const string noHand[2] = {"No handcard,skip", "沒有手牌，跳過"};
                printf("%s\n", noHand[language]);
            }
            else if (useCrane == 1)
            {
                CLEAN
                const string craneText[2] = {"Choose a build to build over", "選擇一項建築來重蓋"};
                const string choicedBuilding[2] = {"Chosed building : ", "選擇的建築 : "};
                const string goback[2] = {"Return", "返回"};
                while (1)
                {
                    printPlayerBoard(&p[nowPlaying]);
                    printf("%d)%s\n", p[nowPlaying].boardCount + 1, passChoice[language]);
                    printf("%s\n", craneText[language]);
                    u8 choice = -1;
                    scanf("%hhd", &choice);
                    while (choice > p[nowPlaying].boardCount + 1 || choice < 1)
                    {
                        INVALID
                        scanf("%hhd", &choice);
                    }
                    if (choice == p[nowPlaying].boardCount + 1)
                    {
                        printf("%s", pass[language]);
                        break;
                    }
                    else
                    {
                        CLEAN
                        u8 chosed = choice - 1;
                        choice = -1;
                        printf("%s%s\n", choicedBuilding[language], p[nowPlaying].board[chosed].cardName);
                        printPlayerCard(&p[nowPlaying]);
                        printf("%d)%s\n", p[nowPlaying].cardCount + 1, passChoice[language]);
                        u8 choice = -1;
                        printf("%s", whatToBuild[language]);
                        scanf("%hhd", &choice);

                        if (choice == p[nowPlaying].cardCount + 1)
                            continue;

                        u8 originalCostdown = costdown;
                        if (p[nowPlaying].quarry && choice >= 1 && choice <= p[nowPlaying].cardCount)
                            if (p[nowPlaying].hand[choice - 1].id > 4)
                                costdown++;

                        if (p[nowPlaying].smithy && choice >= 1 && choice <= p[nowPlaying].cardCount)
                            if (p[nowPlaying].hand[choice - 1].id <= 4)
                                costdown++;

                        i8 finalCost = (p[nowPlaying].hand[choice - 1].cost - costdown - p[nowPlaying].board[chosed].cost);
                        u8 cannotPlay = (p[nowPlaying].cardCount != 0) && (choice > p[nowPlaying].cardCount + 1 || choice < 1 || !(p[nowPlaying].cardCount > finalCost));
                        while (cannotPlay)
                        {
                            if (choice > p[nowPlaying].cardCount + 1 || choice < 1)
                                INVALID
                            else
                                printf("%s", notEnoughCard[language]);
                            setbuf(stdin, NULL);
                            choice = -1;
                            costdown = originalCostdown;
                            scanf("%hhd", &choice);
                            if (p[nowPlaying].quarry && choice >= 1 && choice <= p[nowPlaying].cardCount)
                                if (p[nowPlaying].hand[choice - 1].id > 4)
                                    costdown++;
                            if (p[nowPlaying].smithy && choice >= 1 && choice <= p[nowPlaying].cardCount)
                                if (p[nowPlaying].hand[choice - 1].id <= 4)
                                    costdown++;
                        }
                        if (choice == p[nowPlaying].cardCount + 1)
                            continue;
                        else
                        {
                            if (finalCost < 1)
                                finalCost = 1;
                            u8 played = choice - 1;
                            i8 cardCost = finalCost;
                            u8 emptySlot = 0;
                            u8 extraValue = p[nowPlaying].board[chosed].extraValue;
                            discardCard(&p[nowPlaying], chosed);

                            while (p[nowPlaying].board[emptySlot].place != 0)
                                emptySlot++;
                            p[nowPlaying].board[emptySlot] = p[nowPlaying].hand[played];
                            p[nowPlaying].board[emptySlot].extraValue = extraValue;
                            card empty = {0};                                                             //to reset moved card
                            p[nowPlaying].hand[played] = empty;                                           //reset moved last card
                            p[nowPlaying].hand[played] = p[nowPlaying].hand[p[nowPlaying].cardCount - 1]; //take player's last card and place it in the empty spot
                            p[nowPlaying].hand[p[nowPlaying].cardCount - 1] = empty;
                            p[nowPlaying].cardCount--;
                            for (i32 i = 0; i < cardCost; i++)
                            {
                                printPlayerCard(&p[nowPlaying]);
                                printf("%s (%d/%d)\n", whatToPay[language], i + 1, cardCost);
                                u8 discard = -1;
                                scanf("%hhd", &discard);
                                while (discard > p[nowPlaying].cardCount || discard < 1)
                                {
                                    INVALID
                                    setbuf(stdin, NULL);
                                    discard = -1;
                                    scanf("%hhd", &discard);
                                }
                                discardCard(&p[nowPlaying], discard - 1);
                                CLEAN
                            }
                            p[nowPlaying].boardCount++;
                            printf("%s %s\n\n", built[language], p[nowPlaying].board[emptySlot].cardName);
                            if (p[nowPlaying].board[emptySlot].id > 4)
                                carpenter(&p[nowPlaying]);
                            break;
                        }
                    }
                }
            }
            else if (p[nowPlaying].crane == 0)
            {
                printPlayerCard(&p[nowPlaying]);
                printf("%d)%s\n", p[nowPlaying].cardCount + 1, passChoice[language]);
                u8 choice = -1;
                printf("%s", whatToBuild[language]);
                scanf("%hhd", &choice);
                u8 originalCostdown = costdown;
                if (p[nowPlaying].quarry && choice >= 1 && choice <= p[nowPlaying].cardCount)
                    if (p[nowPlaying].hand[choice - 1].id > 4)
                        costdown++;

                if (p[nowPlaying].smithy && choice >= 1 && choice <= p[nowPlaying].cardCount)
                    if (p[nowPlaying].hand[choice - 1].id <= 4)
                        costdown++;

                while ((p[nowPlaying].cardCount != 0) && (choice > p[nowPlaying].cardCount + 1 || choice < 1 || !(p[nowPlaying].cardCount > (p[nowPlaying].hand[choice - 1].cost - costdown))))
                {
                    if (choice > p[nowPlaying].cardCount + 1 || choice < 1)
                        INVALID
                    else
                        printf("%s", notEnoughCard[language]);
                    setbuf(stdin, NULL);
                    choice = -1;
                    costdown = originalCostdown;
                    scanf("%hhd", &choice);
                    if (p[nowPlaying].quarry && choice >= 1 && choice <= p[nowPlaying].cardCount)
                        if (p[nowPlaying].hand[choice - 1].id > 4)
                            costdown++;
                    if (p[nowPlaying].smithy && choice >= 1 && choice <= p[nowPlaying].cardCount)
                        if (p[nowPlaying].hand[choice - 1].id <= 4)
                            costdown++;
                }
                if (p[nowPlaying].cardCount == 0)
                    choice = 1;

                CLEAN
                if (!(p[nowPlaying].cardCount + 1 == choice))
                {
                    u8 played = choice - 1;
                    i8 cardCost = p[nowPlaying].hand[choice - 1].cost - costdown;
                    if (cardCost < 1)
                        cardCost = 1;
                    u8 emptySlot = 0;
                    while (p[nowPlaying].board[emptySlot].place != 0)
                        emptySlot++;
                    p[nowPlaying].board[emptySlot] = p[nowPlaying].hand[played];
                    card empty = {0};                                                             //to reset moved card
                    p[nowPlaying].hand[played] = empty;                                           //reset moved last card
                    p[nowPlaying].hand[played] = p[nowPlaying].hand[p[nowPlaying].cardCount - 1]; //take player's last card and place it in the empty spot
                    p[nowPlaying].hand[p[nowPlaying].cardCount - 1] = empty;
                    p[nowPlaying].cardCount--;
                    for (i32 i = 0; i < cardCost; i++)
                    {
                        printPlayerCard(&p[nowPlaying]);
                        printf("%s (%d/%d)\n", whatToPay[language], i + 1, cardCost);
                        u8 discard = -1;
                        scanf("%hhd", &discard);
                        while (discard > p[nowPlaying].cardCount || discard < 1)
                        {
                            INVALID
                            setbuf(stdin, NULL);
                            discard = -1;
                            scanf("%hhd", &discard);
                        }
                        discardCard(&p[nowPlaying], discard - 1);
                        CLEAN
                    }
                    p[nowPlaying].boardCount++;
                    printf("%s %s\n\n", built[language], p[nowPlaying].board[emptySlot].cardName);
                    if (p[nowPlaying].board[emptySlot].id > 4)
                        carpenter(&p[nowPlaying]);
                }
                else
                {
                    printf("%s", pass[language]);
                }
            }
        }
        else
        {
            SLEEP
            i8 played = -1;
            for (i32 i = 0; i < p[nowPlaying].cardCount; i++)
            {
                //printf("card count %d \n", p[nowPlaying].cardCount);
                //printf("%d > %d\n", p[nowPlaying].cardCount, p[nowPlaying].hand[i].cost - costdown);
                if (p[nowPlaying].cardCount > p[nowPlaying].hand[i].cost - costdown)
                {
                    played = i;
                    break;
                }
            }
            //printf("play %d\n", played);
            if (played >= 0 && p[nowPlaying].cardCount != 0)
            {
                p[nowPlaying].hand[played].place = 3;
                u8 emptySlot = 0;
                while (p[nowPlaying].board[emptySlot].place != 0)
                    emptySlot++;
                p[nowPlaying].board[emptySlot] = p[nowPlaying].hand[played];
                printf("%s %d %s %s\n\n", CPUdraw[language][0], nowPlaying, built[language], p[nowPlaying].board[emptySlot].cardName);
                i8 cardCost = p[nowPlaying].board[emptySlot].cost - costdown;
                if (cardCost < 1)
                    cardCost = 1;

                card empty = {0};                                                             //to reset moved card
                p[nowPlaying].hand[played] = p[nowPlaying].hand[p[nowPlaying].cardCount - 1]; //reset moved last card
                p[nowPlaying].hand[p[nowPlaying].cardCount - 1] = empty;
                p[nowPlaying].cardCount--;
                while (cardCost--)
                {
                    u8 cardToPay = 0;
                    for (i32 c = cardToPay; c < p[nowPlaying].cardCount; c++)
                    {

                        if (p[nowPlaying].hand[c].place == 2)
                        {
                            cardToPay = c;
                            break;
                        }
                    }
                    discardCard(&p[nowPlaying], cardToPay);
                }
                if (p[nowPlaying].board[emptySlot].id > 4)
                    carpenter(&p[nowPlaying]);
                p[nowPlaying].boardCount++;
            }
            else
            {
                printf("%s %d %s", CPUdraw[language][0], nowPlaying, nobuild[language]);
            }
        }
        poorHouse(&p[nowPlaying]);
        nowPlaying++;
        nowPlaying %= playercnt;
    }
}
void producer(player p[], u8 goveror)
{
    u8 nowPlaying = goveror;
    for (i32 c = 0; c < playercnt; c++)
    {
        u8 produceWellCount = 0;
        if (nowPlaying == 0)
            printf("%s\n", yourTurn[language]);
        aqueduct(&p[nowPlaying]);
        library(&p[nowPlaying]);
        u8 extra = 0 + p[nowPlaying].extraProduce;
        if (nowPlaying == goveror)
        {
            extra += 1 * p[nowPlaying].library;
        }
        if (nowPlaying == 0)
        {
            u8 isProduce = 0;
            const string produceCount[2][2] = {{"You can produce", "products."}, {"你可以生產", "個商品"}};
            const string whatToProduce[2] = {"Choose a building to produce.", "選擇一個建築來進行生產"};
            const string cantProduce[2] = {"This building can't produce or it already produced product.", "此建築物無法進行生產或是已經生產了貨品"};
            const string produced[2] = {"You produced", "你生產了"};
            for (i32 j = 0; j < 1 + extra; j++)
            {
                printf("%s %d %s\n", produceCount[language][0], 1 + extra - j, produceCount[language][1]);
                printPlayerBoard(&p[nowPlaying]);
                printf("%d)%s\n", p[nowPlaying].boardCount + 1, passChoice[language]);
                u8 choice = -1;
                printf("%s\n", whatToProduce[language]);
                scanf("%hhd", &choice);
                u8 maxChoice = p[nowPlaying].boardCount + 1;

                while ((choice > maxChoice || choice < 1) || (p[nowPlaying].board[choice - 1].type != 0) || (p[nowPlaying].board[choice - 1].hasProduct != 0))
                {
                    if (choice > maxChoice || choice < 1)
                        INVALID
                    else
                        printf("%s\n", cantProduce[language]);
                    setbuf(stdin, NULL);
                    choice = -1;
                    scanf("%hhd", &choice);
                }
                if (choice >= maxChoice)
                {
                    const string noProduce[2] = {"You produced nothing.", "你沒有生產"};
                    printf("%s\n\n", noProduce[language]);
                }
                else
                {
                    CLEAN
                    printf("%s %s\n\n", produced[language], productName[language][p[nowPlaying].board[choice - 1].cost - 1]);
                    produce(&p[nowPlaying], choice - 1);
                    produceWellCount++;
                }
            }
        }
        else
        {
            SLEEP
            u8 isProduce = 0;
            for (i32 j = 0; j < 1 + extra; j++)
            {
                for (i32 i = 0; i < p[nowPlaying].boardCount; i++)
                {
                    if (p[nowPlaying].board[i].id < 5 && !p[nowPlaying].board[i].hasProduct && !p[nowPlaying].board[i].type)
                    {

                        produce(&p[nowPlaying], i);
                        printf("%s %d %s %s\n", CPUdraw[language][0], nowPlaying, produceText[language], productName[language][p[nowPlaying].board[i].cost - 1]); //use cost to decide the name since all the cost is different for the five buildings
                        isProduce = 1;
                        produceWellCount++;
                        break;
                    }
                }
                if (!isProduce)
                {
                    const string noProduce[2] = {"produced nothing.", "沒有生產"};
                    printf("%s %d %s\n", CPUdraw[language][0], nowPlaying, noProduce[language]);
                    break;
                }
            }
        }
        if (produceWellCount >= 2)
            well(&p[nowPlaying]);
        nowPlaying++;
        nowPlaying %= playercnt;
    }
}
void trader(player p[], u8 goveror)
{

    u8 nowPlaying = goveror;
    u8 priceTag = rand() % 5;
    const string tradeCount[2][2] = {{"You can sell", "products."}, {"你可以販賣", "個貨品"}};
    const string whatToSell[2] = {"Choose a building to sell product.", "選擇一個貨品來進行販賣"};
    const string cantSell[2] = {"This building has no product.", "此建築物沒有貨品"};
    const string value[2] = {"Value", "價值"};
    const string priceText[2] = {"Price List", "價目表"};
    const string sold[2] = {"sold", "販買了"};
    const string you[2] = {"You", "你"};
    printf("%s\n", priceText[language]);
    for (i32 i = 0; i < 5; i++)
        printf("%s %s %d\n", productName[language][i], value[language], priceList[priceTag][i]);

    for (i32 c = 0; c < playercnt; c++)
    {
        if (nowPlaying == 0)
            printf("%s\n", yourTurn[language]);

        tradingPost(&p[nowPlaying]);
        library(&p[nowPlaying]);

        u8 extra = 0 + p[nowPlaying].extraTrade;
        if (nowPlaying == goveror)
            extra += 1 * p[nowPlaying].library;

        u8 sellCount = 0;
        if (nowPlaying == 0)
        {

            for (i32 j = 0; j < 1 + extra; j++)
            {

                printf("%s %d %s\n", tradeCount[language][0], 1 + extra - j, tradeCount[language][1]);
                printPlayerBoard(&p[nowPlaying]);
                printf("%d)%s\n", p[nowPlaying].boardCount + 1, passChoice[language]);
                u8 choice = -1;
                printf("%s\n", whatToSell[language]);
                scanf("%hhd", &choice);
                u8 maxChoice = p[nowPlaying].boardCount + 1;

                while (!(choice == maxChoice) && !(choice > maxChoice || choice < 1) && (!(p[nowPlaying].board[choice - 1].type == 0) || (p[nowPlaying].board[choice - 1].hasProduct == 0)))
                {

                    if (choice > maxChoice || choice < 1)
                        INVALID
                    else
                        printf("%s\n", cantSell[language]);
                    setbuf(stdin, NULL);
                    choice = -1;
                    scanf("%hhd", &choice);
                    if (choice == maxChoice)
                        break;
                }
                CLEAN
                if (choice == maxChoice)
                {
                    const string noProduce[2] = {"You sold nothing.", "你沒有販賣貨品"};
                    printf("%s\n\n", noProduce[language]);
                }
                else
                {
                    sellCount++;
                    sell(&p[nowPlaying], choice - 1, priceList[priceTag][p[nowPlaying].board[choice - 1].cost - 1]);
                    printf("%s%s %s\n\n", you[language], sold[language], productName[language][p[nowPlaying].board[choice - 1].cost - 1]);
                }
            }
        }
        else
        {
            SLEEP
            u8 isProduce = 0;
            for (i32 j = 0; j < 1 + extra; j++)
            {
                for (i32 i = 0; i < p[nowPlaying].boardCount; i++)
                {
                    if (p[nowPlaying].board[i].hasProduct && !p[nowPlaying].board[i].type)
                    {

                        sell(&p[nowPlaying], i, priceList[priceTag][p[nowPlaying].board[i].cost - 1]);
                        printf("%s %d %s %s\n\n", CPUdraw[language][0], nowPlaying, sold[language], productName[language][p[nowPlaying].board[i].cost - 1]); //use cost to decide the name since all the cost is different for the five buildings
                        isProduce = 1;
                        sellCount++;
                        break;
                    }
                }
                if (!isProduce)
                {
                    const string noProduce[2] = {"sold nothing.", "沒有販賣貨品"};
                    printf("%s %d %s\n\n", CPUdraw[language][0], nowPlaying, noProduce[language]);
                    break;
                }
            }
        }
        marketHall(&p[nowPlaying]);
        nowPlaying++;
        nowPlaying %= playercnt;
    }
}
void councilor(player p[], u8 goveror)
{
    u8 nowPlaying = goveror;
    for (i32 i = 0; i < playercnt; i++)
    {
        if (nowPlaying == 0)
            printf("%s\n", yourTurn[language]);
        perfecture(&p[nowPlaying]);
        archive(&p[nowPlaying]);
        library(&p[nowPlaying]);
        u8 cardsToChoose[10] = {-1};
        u8 keepCard = 1 + p[nowPlaying].extraCard;
        if (nowPlaying == 0)
        {
            u8 cnt = 2;
            if (goveror == nowPlaying)
                cnt += 3 * p[nowPlaying].library;
            if (cardLeftInDeck <= cnt)
                recycleCard();
            u8 drawCnt = 0;
            if (p[nowPlaying].archive)
            {
                const string reduce[2] = {"Please choose a card to discard.", "請選擇1張牌捨棄"};
                for (i32 i = 0; i < cnt; i++)
                    draw(&p[nowPlaying]);
                printPlayerCard(&p[nowPlaying]);
                for (i32 i = 0; i < cnt - keepCard; i++)
                {
                    u8 max = p[nowPlaying].cardCount;
                    printf("%s (%d/%d)\n", reduce[language], i, cnt - keepCard);
                    u8 choice = -1;
                    scanf("%hhd", &choice);
                    while (choice > max || choice < 1)
                    {
                        INVALID
                        choice = -1;
                        scanf("%hhd", &choice);
                    }
                    discardCard(&p[nowPlaying], choice - 1);
                }
            }
            else
            {
                for (i32 i = 0; i < 1 + p[nowPlaying].extraCard; i++)
                {
                    memset(cardsToChoose, 255, sizeof(cardsToChoose));
                    for (i32 j = 0; j < cnt - i; j++)
                    {
                        while (deck[drawCnt].place != 1)
                            drawCnt++;
                        cardsToChoose[j] = drawCnt;
                        printf("%d)%s\n", j + 1, deck[drawCnt].cardName);
                        drawCnt++;
                    }
                    printf("%s\n", chooseOne[language]);
                    u8 choice = -1;
                    scanf("%hhd", &choice);

                    while (choice > cnt || choice < 1)
                    {
                        setbuf(stdin, NULL);
                        choice = -1;
                        INVALID
                        scanf("%hhd", &choice);
                    }
                    giveCard(&p[nowPlaying], deck[cardsToChoose[choice - 1]]);
                    memset(&deck[cardsToChoose[choice - 1]], 0, sizeof(card));
                    printf("%s %s\n", chosed[language], p[0].hand[p->cardCount - 1].cardName);
                }
            }
            CLEAN
            shuffle();
        }
        else
        {
            string choosed[2] = {"a card.", "了一張卡"};
            SLEEP
            for (i32 i = 0; i < 1 + p[nowPlaying].extraCard; i++)
            {
                printf("%s %d %s%s\n", CPUdraw[language][0], nowPlaying, chosedCard[language], choosed[language]);
                draw(&p[nowPlaying]);
            }
        }
        nowPlaying++;
        nowPlaying %= playercnt;
    }
}
void prospector(player p[], u8 goveror)
{
    u8 nowPlaying = goveror;
    for (i32 c = 0; c < playercnt; c++)
    {
        goldMine(&p[nowPlaying]);
        if (nowPlaying == goveror)
        {
            if (goveror == 0)
                printf("%s\n", yourTurn[language]);
            library(&p[goveror]);
            for (i32 i = 0; i < 1 * p[goveror].library; i++)
            {
                u8 drawCnt = 0;
                if (cardLeftInDeck == 0)
                {
                    drawCnt = 0;
                    recycleCard();
                }
                while (deck[drawCnt].place != 1)
                    drawCnt++;
                if (goveror == 0)
                    printf("%s%s\n", drew[language], deck[drawCnt].cardName);
                draw(&p[goveror]);
            }
        }
        nowPlaying++;
        nowPlaying %= playercnt;
    }
    return;
}

//card functions
void tower(player *p) //id 5
{
    if (searchBoard(p, 5))
        p->maxCard = 12;
    else
        p->maxCard = 7;
    return;
}
void chapel(player *p) //id 6
{
    const string effect[2] = {"Chapel's effect,you can put a card under chapel.\nDo you want to use chapel's effect?\n1)Yes\n2)No",
                              "禮拜堂效果，你可以放一張牌到禮拜堂底下\n是否使用禮拜堂效果?\n1)使用\n2)不使用"};
    const string chapelChoose[2] = {"Choose one to put under chapel", "選擇一張放到禮拜堂底下"};
    const string cpuChapel[2] = {"put a card under chapel", "將一張牌放在禮拜堂底下"};
    for (i32 i = 0; i < p->boardCount; i++)
    {
        CLEAN
        if (p->playerOrder == 0 && p->board[i].id == 6)
        {
            printf("%s\n", effect[language]);
            u8 use = -1;
            scanf("%hhd", &use);
            while (use != 1 && use != 2)
            {
                INVALID
                use = -1;
                scanf("%hhd", &use);
            }
            if (use != 1)
                continue;

            printPlayerCard(p);
            u8 choice = -1;
            scanf("%hhd", &choice);
            while (choice < 1 || choice > p->cardCount)
            {
                INVALID
                choice = -1;
                scanf("%hhd", &choice);
            }
            discardCard(p, choice - 1);
            p->board[i].chapelScore++;
        }
        else if (p->playerOrder != 0 && p->board[i].id == 6)
        {

            for (i32 j = 0; j < p->cardCount; j++)
            {
                if (p->hand[j].cost < 3 && p->hand[j].vp < 3)
                {
                    printf("CPU %d %s\n", p->playerOrder, cpuChapel[language]);
                    discardCard(p, j);
                    p->board[i].chapelScore++;
                    break;
                }
            }
        }
    }
}
void smithy(player *p) //id 7
{
    const string smithEffect[2] = {"Smithy\'s effect,you can pay 1 less while building a production building.", "鐵匠鋪效果，建造生產建築時可以少支付一個費用"};
    if (searchBoard(p, 7))
    {
        p->smithy = 1;
        printf("%s\n", smithEffect[language]);
    }
    else
        p->smithy = 0;
    return;
}
void poorHouse(player *p) //id 8
{
    const string poor[2] = {"Poor house\'s effect,raw 1 card.", "救濟院效果，抽一張卡"};
    if (searchBoard(p, 8) && p->maxCard <= 1)
    {
        printf("%s\n", poor[language]);
        draw(p);
    }

    return;
}
void blackMarket(player *p, u8 *cost) //id 9
{
    const string effect[2] = {"Black Market\'s effect,you pay building with up to 2 products.", "黑市效果，可以用最多兩個貨品來支付建築"};
    const string useEffect[2] = {"Do you want to use Black Market\'s Effect?\n1)Yes\n2)No\n", "是否使用黑市效果\n1)使用\n2)不使用\n"};
    const string cantSell[2] = {"This building has no product.", "此建築物沒有貨品"};
    if (searchBoard(p, 9) != 0)
    {
    }
}
void crane(player *p) //id 10
{
    const string effect[2] = {"Crane\'s effect,you build over a building.", "起重機效果，可以蓋過一個現存的建築"};
    const string useEffect[2] = {"Do you want to use Crane\'s Effect?\n1)Yes\n2)No\n", "是否使用起重機效果\n1)使用\n2)不使用\n"};
    if (searchBoard(p, 10) != 0)
    {
        printf("%s\n%s", effect[language], useEffect[language]);
        p->crane = 1;
        return;
    }
    else
    {
        p->crane = 0;
        return;
    }
}
void carpenter(player *p) //id 11
{
    const string effect[2] = {"Carpenter\'s effect,you can draw a card.", "木工場效果，可以抽一張牌"};
    if (searchBoard(p, 11) != 0)
    {
        printf("%s\n", effect[language]);
        draw(p);
    }
}
void quarry(player *p) //id 12
{
    const string effect[2] = {"Quarry\'s effect,you can pay 1 less while building a city building.", "採石場效果，建造都市建築時可以少支付一個費用"};
    if (searchBoard(p, 12) != 0)
    {
        printf("%s\n", effect[language]);
        p->quarry = 1;
    }
    else
        p->quarry = 0;
}
void well(player *p) //id 13
{
    const string effect[2] = {"Well\'s effect,you can draw a card.", "水井效果，可以抽一張牌"};
    if (searchBoard(p, 13) != 0)
    {
        printf("%s\n", effect[language]);
        draw(p);
    }
}
void aqueduct(player *p) //id 14
{
    const string effect[2] = {"Aqueduct\'s effect,you can produce an extra product.", "溝渠效果，可以多生產一個貨品"};
    if (searchBoard(p, 14) != 0)
    {
        p->extraProduce = 1;
        printf("%s\n", effect[language]);
    }
    else
        p->extraProduce = 0;
    return;
}
void marketStand(player *p, u8 sellCount)
{
    const string effect[2] = {"Market Stand\'s effect,you can draw a card.", "攤販效果，可以抽一張牌"};
    if (searchBoard(p, 16) != 0 && sellCount >= 2)
    {
        printf("%s\n", effect[language]);
        draw(p);
    }
}
void marketHall(player *p) //id 16
{
    const string effect[2] = {"Market Hall\'s effect,you can draw a card.", "市場效果，可以抽一張牌"};
    if (searchBoard(p, 16) != 0)
    {
        printf("%s\n", effect[language]);
        draw(p);
    }
}
void tradingPost(player *p) //id 17
{
    const string effect[2] = {"Trading Post\'s effect,you can sell an extra product.", "交易所效果，可以多販賣一個貨品"};
    if (searchBoard(p, 17) != 0)
    {
        p->extraTrade = 1;
        printf("%s\n", effect[language]);
    }
    else
        p->extraTrade = 0;
    return;
}
void archive(player *p) //id 18
{
    const string effect[2] = {"Archive\'s effect,you can add the cards to your hand before discard them.", "檔案室效果，可以將牌加入手牌再選擇牌來保留"};
    if (searchBoard(p, 18) != 0)
    {
        p->archive = 1;
        printf("%s\n", effect[language]);
    }
    else
        p->archive = 0;
    return;
}
void perfecture(player *p) //id 19
{
    const string effect[2] = {"Perfecture\'s effect,you can keep an extra card.", "辦公處效果，可以多保留一張卡"};
    if (searchBoard(p, 19) != 0)
    {
        p->extraCard = 1;
        printf("%s\n", effect[language]);
    }
    else
        p->extraCard = 0;
    return;
}
void goldMine(player *p) //id 20
{
    const string you[2] = {"You ", "你"};
    const string effect[2][2] = {{"found gold!", "found nothing."}, {"找到了黃金", "什麼都沒找到"}};
    if (searchBoard(p, 20) == 0)
    {
        return;
    }
    else
    {
        card topDeck[4] = {0};
        u8 costTag[6] = {0};
        if (cardLeftInDeck <= 4)
            recycleCard();
        for (i32 i = 0; i < 4; i++)
        {
            u8 cardCnt = 0;
            while (deck[cardCnt].place != 1)
                cardCnt++;
            topDeck[i] = deck[cardCnt];
        }
        u8 foundGold = 1;
        for (i32 i = 0; i < 4; i++)
        {
            u8 point = topDeck[i].cost;
            if (costTag[point] == 0)
            {
                costTag[point] = 1;
            }
            else
            {
                foundGold = 0;
                break;
            }
        }
        if (p->playerOrder == 0)
        {
            if (!foundGold)
            {
                printf("%s%s\n", you[language], effect[language][1]);
            }
            else
            {
                printf("%s%s\n", you[language], effect[language][0]);
                for (i32 i = 0; i < 4; i++)
                {
                    printf("%d)%s\n", i + 1, topDeck[i].cardName);
                    printf("%s\n", chooseOne[language]);
                    u8 choice = -1;
                    scanf("%hhd", &choice);
                    while (choice > 4 || choice < 1)
                    {
                        INVALID
                        choice = -1;
                        scanf("%hhd", &choice);
                    }
                    giveCard(p, topDeck[choice]);
                }
            }
        }
        else
        {
            if (!foundGold)
                printf("CPU %d %s\n", p->playerOrder, effect[language][1]);
            else
            {
                printf("CPU %d %s\n", p->playerOrder, effect[language][0]);
                draw(p);
            }
        }
        shuffle();
    }
    return;
}
void library(player *p) //id 21
{
    const string effect[2] = {"library\'s effect,you have doubled the privilege.", "圖書館效果，所有特權都是雙倍效果"};
    if (searchBoard(p, 21) != 0)
    {
        p->library = 2;
        printf("%s\n", effect[language]);
    }
    else
        p->library = 1;
    return;
}
void statue(u8 cardowner)
{
    return;
}
void victoryColumn(u8 cardowner)
{
    return;
}
void hero(u8 cardowner)
{
    return;
}
void guildHall(player *p, u8 *vp) //id = 26
{
    u8 cnt = 0;
    u8 fac = 0;
    u8 hasGuild = 0;
    for (i32 i = 0; i < p->boardCount; i++)
        if (p->board[i].id == 25)
        {
            hasGuild = 1;
            break;
        }
    if (!hasGuild)
        return;
    for (i32 i = 0; i < p->boardCount; i++)
    {
        u8 id = p->board[i].id;
        if (id < 5)
        {
            fac += 2;
        }
    }
    *vp += fac;
    return;

    return;
}
void cityHall(player *p, u8 *vp)
{
    u8 cnt = 0;
    u8 hasCit = 0;
    for (i32 i = 0; i < p->boardCount; i++)
        if (p->board[i].id == 26)
        {
            hasCit = 1;
            break;
        }
    if (!hasCit)
        return;
    for (i32 i = 0; i < p->boardCount; i++)
    {
        u8 id = p->board[i].id;
        if (id > 4 && id < 30)
        {
            cnt++;
        }
    }
    *vp += cnt;
    return;
}
void triumhalArch(player *p, u8 *vp)
{
    u8 triCnt = 0, t1 = 0, t2 = 0, t3 = 0;
    u8 hasTri = 0;
    for (i32 i = 0; i < p->boardCount; i++)
        if (p->board[i].id == 27)
        {
            hasTri = 1;
            break;
        }
    if (!hasTri)
        return;
    for (i32 i = 0; i < p->boardCount; i++)
    {
        if (p->board[i].id == 22)
        {
            t1 = 1;
        }
        if (p->board[i].id == 23)
        {
            t2 = 1;
        }
        if (p->board[i].id == 24)
        {
            t3 = 1;
        }
    }
    triCnt = t1 + t2 + t3;
    if (triCnt == 1)
        *vp += 4;
    else if (triCnt == 2)
        *vp += 6;
    else if (triCnt == 3)
        *vp += 8;
    return;
}
void palace(player *p, u8 *vp)
{
    u8 cnt = 0;
    for (i32 i = 0; i < p->boardCount; i++)
        if (p->board[i].id == 29)
        {
            *vp = *vp + (u8)(*vp / 4.0);
            break;
        }
    return;
}