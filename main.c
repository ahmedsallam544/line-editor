#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#define enter 13
#define rightarrow 77
#define leftarrow  75
#define home  71
#define end 79
#define insert 82
#define delete 83
#define escape 27
#define black 0
#define white 15
WORD saved_attributes;
void textOrg()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), saved_attributes);
}

void textAti(int FontC, int BackC)
{
    WORD wColor = ((BackC & 0x0F) << 4) + (FontC & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
}
void gotoxy(int col, int row)
{
    // hello
    COORD coord= {0,0};
    coord.X = col;
    coord.Y = row;

    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
    // Obtain a handle to the console screen buffer.
    // in conjunction with the GetStdHandle() to retrieve the handle.)
    // Note that because it is a standard handle, we don't need to close it.
}

void main()
{
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;
    int n =0 ;
    int size = 20 ;
    int i = 0;
    char ch ;
    char name[size] ;
    int position = 0 ;
    int row, col = 0;
    char *ps ;
    ps = name ;
    // ps = (char*)malloc( size * sizeof(char)) ;
    char *pd = name ;

    char *pcurrent = name ;
    char *temp ;
    if(!pcurrent)
    {
        printf(" out of memory ");
        exit(1);
    }
    else
    {

        do
        {

            ch = getch();
            switch (ch)
            {
            case -32:
                ch = getch();
                switch (ch)
                {
                case leftarrow :
                    if(pcurrent != ps )
                    {
                        pcurrent-- ;
                        position--;
                    }
                    gotoxy(position,0);
                    break;
                case rightarrow :
                    if(position != pd-ps)
                    {
                        pcurrent++ ;
                        position++;
                    }
                    gotoxy(position,0);
                    break;

                case home:
                    pcurrent = ps ;
                    position = 0;
                    gotoxy(0,0);
                    break;

                case end :
                    pcurrent = pd;
                    position= pd-ps;
                    gotoxy(position,0);

                    break;
                case insert:
                    for(temp=pd; temp>pcurrent; temp--)
                    {
                        *temp= *(temp -1) ;

                    }
                    for(i=position ; i < (pd-ps); i++)
                    {
                        if(i==position)
                            printf(" ");
                        else
                            printf("%c",name[i]);

                    }
                    gotoxy(position,0);
                    break;

                case delete :
                    if(position!=pd-ps)
                    {
                        for(temp=pcurrent; temp<pd ; temp++ )
                        {

                            *temp = *(temp+1) ;
                        }
                        for(i=position; i < (pd-ps); i++)
                        {
                            if(i==(pd-ps)-1)
                                printf(" ");
                            else
                                printf("%c",name[i]);

                        }
                        pd-- ;
                        gotoxy(position,0);
                    }
                    break;
                }

                break ;

            case enter :
                pd='\0';
                printf("\n%s",name);

                break ;
            case escape:
                exit(1);
                system("cls");
                break;

            default :
                if(position< size)
                {
                    printf("%c",ch);
                    name[position]=ch ;
                    if(position==pd-ps)
                        pd++;
                    pcurrent++;
                    position++ ;
                    *pd = '\0' ;
                }
            }
        }
        while(ch != enter);

    }

    printf("\n-----------------------\n ");
    getch();
}
