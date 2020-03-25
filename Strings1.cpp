#include "TXLib.h"

int StrInStr (const char Ps[], const char Str[]);
bool IsFind  (const char Ps[], const char Str[], int start);
int RunTest  ();
int LenS (const char Str[]);

int main()
    {
    RunTest ();
    }

// Возвращает первое вхождение Подстроки в строке. Если совпадения нет, то возвращает -1
int StrInStr(const char Ps[], const char Str[])
    {
    int i = 0;
    int start = 0;
    int number = -1;
    while (Str[start] != '\0')
        {
        if (IsFind(Ps, Str, start)) return start;
        else start++;
        }
    return -1;
    }

// Проверяет совпадает ли подстрока с частью строки, начиная с символа start
bool IsFind(const char Ps[], const char Str[], int start)
    {

    int t = start;
    int d = LenS(Ps);

    for (int i = 0; i < d; i++)
        {
        if (Str[t] == '\0')  break;
        if (Str[t] != Ps[i]) break;
        t++;
        };

    return ( t - start == d) ;

    }

// Тест работы функции
int RunTest ()
    {
    $unittest (StrInStr("", "abc"),      0);
    $unittest (StrInStr("a", "abc"),     0);
    $unittest (StrInStr("b", "abc"),     1);
    $unittest (StrInStr("c", "abc"),     2);

    $unittest (StrInStr("bcd", "abcd"),  1);
    $unittest (StrInStr("bcd", "abct"), -1);
    $unittest (StrInStr("bcd", "abcd"),  1);
    $unittest (StrInStr("bcd", "abc"),  -1);

    }

// Длина строки
int LenS (const char Str[])
    {
    int d = 0;

    while (Str[d] != '\0') d++;


    return d;
    }

