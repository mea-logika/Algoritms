#include <iostream>
#include "stdio.h"

using namespace std;

const int n = 5;          // количество вершин графа
const bool Black = false;
const bool White = true;

void PrintArr (bool data[ n ][ n ] );
void Repaint (int first, bool Color [n], bool data[ n ][ n ]);
bool OneColor ( bool Color [n], int Connect [n]);



int main()
{
    bool Link [n][n] ;  // данные о связи вершин
    bool Color [n];     // цвет вершины
    int Connect [n];

    // покрасить все вершины в черный и определить отсутствие смежных вершин для каждой вершины
    for (int i = 0; i < n; i++)
    {
        Color [i] = Black;
        Connect [i] = 0;
    }

    // инициализация массива связей
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            Link [i][j] = false;

    int MaxLink;
    cin >> MaxLink;

    int v1, v2;
    int MaxConnect = -1;
    int MaxLinked;

    for (int i = 0; i < MaxLink; i++)
    {
        cin >> v1 >> v2;
        Connect [v1]++;
        Connect [v2]++;
        Link [v1] [v2] = true;
        Link [v2] [v1] = true;
        if ( Connect [v1] > MaxConnect)
        {
            MaxLinked = v1;
            MaxConnect = Connect [v1];
        }
    }

    PrintArr(Link);

    Repaint (MaxConnect, Color , Link);

    if (OneColor (Color, Connect))
        printf ("link");
    else printf ("NO link");



}

bool OneColor ( bool Color [n], int Connect [n])
{
    for (int i = 0; i < n; i++)
        if ( (Connect [i] >0) && (Color [i] != White) )
            return false;
    return true;

}



void PrintArr(bool data[n][n])
{
    printf ("\n--");
    for (int i = 0; i < n; i++)
         printf ("%d ", i);
    printf ("\n");
    for (int i = 0; i < n; i++)
    {
        printf ("%d ", i);;
        for (int j = 0; j < n; j++)
           printf ("%d ", data [i][j]);
        printf ("\n");
    }




}

void Repaint (int first, bool Color [n], bool Link[ n ][ n ])
{
    if (Color [first] == Black)
    {
        Color [first] = White;
        for (int i = 0; i < n; i++)
            if (Link [first][i])
                Repaint ( i, Color, Link);
    }




}



