#include "struct.h"

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

const string startMenuText[2] = {"\tSAN JUAN\n\n1)New Game\n2)Load Game\n3)About Project\n4)Setting\n5)Save Ediotr\n6)Quit\nPlease choose a option.\n", "\t聖胡安\n\n1)新遊戲\n2)讀取遊戲\n3)關於\n4)設定\n5)存檔編輯器\n6)離開\n請選擇。\n"};
const string invalid[2] = {"Invalid option,please try another one.\n", "無效的選項，請再試一次。\n"};
const string bye[2] = {"See Ya\n", "88\n"};

//textLanguage-----------------------------------------------------------------
//cardStuff--------------------------------------------------------------------

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
                                        "\nbeginning of a round\nwhen the governor checks players’ hands for the card limit of 7,\na player with a tower has a hand limit of 12 instead of 7.\n",
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
                                       {"\n生產者階段\n持有者生產一個單位的染料\n",
                                        "\n生產者階段\n持有者生產一個單位的糖\n",
                                        "\n生產者階段\n持有者生產一個單位的菸草\n",
                                        "\n生產者階段\n持有者生產一個單位的咖啡\n",
                                        "\n生產者階段\n持有者生產一個單位的白銀\n",
                                        "\n回合開始\n已打出此張卡牌的人手牌上限從7張變為12張\n",
                                        "\n回合開始\n檢查手牌上限前，可以將一張手牌放到禮拜堂底下，遊戲結束時每張放到禮拜堂的牌可以得到額外一點勝利點數\n",
                                        "\n建築師階段\n已打出此張卡牌的玩家在建造生產建築物時可少支付1張手牌\n",
                                        "\n建築師階段\n已打出此張卡牌的玩家在行動完成後，若玩家手牌張數不多於1張時，可從卡牌堆抽取1張卡牌加入手牌\n",
                                        "\n建築師階段\n已打出此張卡牌的玩家最多可用2個貨品取代支付費用，1個貨品只能替代1張手牌\n",
                                        "\n建築師階段\n已打出此張卡牌的玩家可支付興建新建築物與原先擁有舊建築物的費用差額，將新建築物蓋在舊建築物的上方。被覆蓋的卡牌不計分亦無效能，被覆蓋的生產建築其上方貨品則須棄置，被覆蓋的禮拜堂其上方卡牌仍可保留計分\n",
                                        "\n建築師階段\n已打出此張卡牌的玩家在建造特殊建築物時可從卡牌堆上方抽取1張卡牌\n",
                                        "\n建築師階段\n已打出此張卡牌的玩家在建造特殊建築物時可少支付1張手牌\n",
                                        "\n生產者階段\n生產者階段時，已打出此張卡牌的玩家若生產2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌\n",
                                        "\n生產者階段\n生產者階段時，已打出此張卡牌的玩家可多生產1個貨品\n",
                                        "\n商人階段\n商人階段時，已打出此張卡牌的玩家若賣出2個以上貨品，可從卡牌堆上方抽取1張卡牌加入手牌\n",
                                        "\n商人階段\n商人階段時，已打出此張卡牌的玩家在行動完成後，可從卡牌堆上方抽取1張卡牌加入手牌\n",
                                        "\n商人階段\n商人階段時，已打出此張卡牌的玩家可多賣出1個貨品\n",
                                        "\n市長階段\n市長階段時，已打出此張卡牌的玩家在挑選卡牌時，可將卡牌堆上方抽取的卡牌全數加入手牌後再進行挑選，並將挑選外的其餘卡牌丟棄\n",
                                        "\n市長階段\n市長階段時，已打出此張卡牌的玩家從卡牌堆上抽取卡牌後，挑選其中2張加入手牌\n",
                                        "\n淘金者階段\n淘金者階段時，已打出此張卡牌的玩家可在行動完成後，從卡牌堆上方翻開4張卡牌，若4張卡牌的費用皆不相同，可挑選其中1張加入手牌。但只要任2張出現相同費用，則須全數棄置\n",
                                        "\n所有階段\n已打出此張卡牌的玩家的所有特權都變為兩倍\n",
                                        "\n紀念碑n\n無特殊效能\n",
                                        "\n紀念碑\n無特殊效能\n",
                                        "\n紀念碑\n無特殊效能\n",
                                        "\n遊戲結束\n遊戲結束時，已打出此張卡牌的玩家每擁有1棟生產建築物可額外獲得2分\n",
                                        "\n遊戲結束\n遊戲結束時，已打出此張卡牌的玩家每擁有1棟特殊建築物(包括此張卡牌)可額外獲得1分\n",
                                        "\n遊戲結束\n遊戲結束時，已打出此張卡牌的玩家若擁有1種紀念碑卡可額外獲得4分，擁有2種紀念碑卡可額外獲得6分，擁有3種紀念碑卡可額外獲得8分\n",
                                        "\n遊戲結束\n遊戲結束時，已打出此張卡牌的玩家可額外獲得該玩家總分的四分之一分數\n"}};
                                       