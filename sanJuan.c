#include "sanJuan.h"

char cardNameData[30][24] = {"Indigo plant", "Sugar Mill", "Tobacco storage", "Coffee Roaster", "Silver smelter",
                             "Tower", "Chapel", "Smithy", "Poor House", "Black Market", "Crane", "Carpenter",
                             "Quarry", "Well", "Aqueduct", "market Stand", "Market Hall", "Trading Post", "Archive",
                             "Perfecture", "Gold mine", "Library", "Statue", "Victory Column", "Hero", "Guild Hall", "City Hall",
                             "Triumhal Arch", "Palace"};
string startMenuText[2] = {"\tSAN JUAN\n\n1)Start Game\n2)About Project\n3)Language Setting\n4)Quit\nPlease choose a option.\n", "\t聖胡安\n\n1)開始遊戲\n2)關於\n3)語言選擇\n4)離開\n請選擇。\n"};
string invalid[2] = {"Invalid option,please try another one.\n", "無效的選項，請再試一次。\n"};
string bye[2] = {"See Ya\n", "88\n"};
u8 language = 0;

void (*menuFunc[3])() = {mainGame, about, setting};

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
            printf("%s\n",bye[language]);
            break;
        }
        else
        {
            menuFunc[option - 1]();
           
        }
    }
    return;
}

void mainGame()
{
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