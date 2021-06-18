#include "saving.h"

char *savefileName[2] = {"Please enter savefile name : ", "請輸入儲存檔案名稱 : "};
char *failed[2] = {"Failed to open the file.", "無法開啟該檔案"};
void save(u8 langauge, player p[], u8 playerCount, u8 end, u8 level, card deck[110], card discard[110], role r[5])
{
    char savename[100];
    printf("%s", savefileName[langauge]);
    fgets(savename, 99, stdin);
    savename[strcspn(savename, "\n")] = '\0';
    FILE *pFile = fopen(savename, "w");
    savefile s = {0};
    s.header[0] = 'S';
    s.header[1] = 'J';
    s.playerCount = playerCount;
    s.gameend = end;
    s.level = level;
    for (i32 i = 0; i < 110; i++)
    {
        s.deck[i] = deck[i];
        s.discard[i] = discard[i];
    }
    for (i32 i = 0; i < playerCount; i++)
    {
        s.players[i] = p[i];
    }
    for (i32 i = 0; i < 5; i++)
    {
        s.roles[i] = r[i];
    }
    u8 used = 0;
    for (i32 i = 0; i < 5; i++)
        used += r[i].used;
    s.nowPlaying = 4 - (playerCount - used);
    fwrite(&s, sizeof(savefile), 1, pFile);
    fclose(pFile);
    return;
}

i32 load(u8 langauge, savefile *loadfile)
{
    char savename[100];
    printf("%s", savefileName[langauge]);
    fgets(savename, 99, stdin);
    savename[strcspn(savename, "\n")] = '\0';
    FILE *p = NULL;
    if ((p = fopen(savename, "r")) == NULL)
    {
        printf("%s\n", failed[langauge]);
        return -1;
    }
    savefile l = {0};
    fread(&l, sizeof(savefile), 1, p);
    if (l.header[0] != 'S' || l.header[1] != 'J')
    {
        char *wrong[2] = {"This is not a savefile format.", "此檔案不是存檔"};
        printf("%s\n", wrong[langauge]);
        fclose(p);
        return -1;
    }
    *loadfile = l;
    return 1;
}