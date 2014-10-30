#include "stdafx.h"
#include "conio.h"
#define IZQ 0
#define DER 1
int g_CoorMainChar;
int g_CoorShot;
int g_CoorEnemigo;
bool g_DireccionBala = 0;
bool g_DireccionEnemigo = 0;
const unsigned int WORLDWIDTH = 70;

void EnemigoMuerto()
{
    if (g_CoorEnemigo == g_CoorShot)
    {
        g_CoorEnemigo = -1;
        g_CoorShot = -1;
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
    g_CoorMainChar = 35;
    g_CoorShot=-1;
    g_CoorEnemigo = -1;
    while (TRUE)
    {
        unsigned int i;
        for (i = 0; i <= WORLDWIDTH; i++)
        {
            if      (i == g_CoorMainChar) printf("^");
            else if (i == g_CoorShot)     printf("-");
            else if (i == g_CoorEnemigo)  printf("O");
            else                          printf("_");
        }
        if (_kbhit())
        {
            char key = _getch();
            if (key == 's') g_CoorMainChar--;
            if (key == 'd') g_CoorMainChar++;
            if (key == 'x') g_CoorMainChar = g_CoorMainChar - 5; //Teletransporte IZQ
            if (key == 'c') g_CoorMainChar = g_CoorMainChar + 5; //Teletransporte DER
            if (g_CoorShot == -1)
            {
                if (key == 'a')
                {
                    g_CoorShot=g_CoorMainChar-1;
                    g_DireccionBala = IZQ;
                }
                if (key == 'f')
                {
                    g_CoorShot=g_CoorMainChar + 1;
                    g_DireccionBala = DER;
                }
            }
        }
        if (g_CoorShot > -1)
        {
            if (g_CoorShot > 70) g_CoorShot = -1;
            else
            {
                if (g_DireccionBala==DER) g_CoorShot++;
                else                      g_CoorShot--;
            }
        }
        if (g_CoorEnemigo == -1)
        {
            if (rand() % 2)
            {
                g_CoorEnemigo = WORLDWIDTH;
                g_DireccionEnemigo = IZQ;
            }
            else
            {
                g_CoorEnemigo = 0;
                g_DireccionEnemigo = DER;
            }
        }
        EnemigoMuerto();
        if ((g_CoorEnemigo == g_CoorMainChar | g_CoorEnemigo + 1 == g_CoorMainChar) | g_CoorEnemigo - 1 == g_CoorMainChar)
        {
            printf("\r                               GAME OVER                                    ");
            break;
        }
        if (g_CoorEnemigo > -1)
        {
            if (g_CoorEnemigo > 70) g_CoorEnemigo = -1;
            else
            {
                if (g_DireccionEnemigo == DER) g_CoorEnemigo++;
                else                           g_CoorEnemigo--;
            }
        }
        EnemigoMuerto();
        Sleep(50);
        printf("\r");
    }
    getchar();

	return 0;
}


