#include "sanJuan.h"

char startMenuTexts[] = "\tSAN JUAN\n\n1)Start Game\n2)About Project\n3)Language Setting\n4)Quit\nPlease choose a option.\n";
void menu()
{
    setbuf(stdin, NULL);
    printf("%s", startMenuTexts);
    int option = -1;
    scanf("%d", &option);
    if(option>4 || option <0)
    {
        printf("Invalid option,please try another one.\n");
        while((option>4 || option<0))
        {
            scanf("%d", &option);
        }
            
        
    }
    setbuf(stdin, NULL);
    if(option == 4)
    {
        printf("See Ya\n");
    }
    else
    {

    }
    return;
}

void mainGame()
{

}
void GameEnd()
{

}