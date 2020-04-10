#include "TXLib.h"

typedef unsigned long long THesh (const char Str[], int LenStr);
typedef void TSkip (unsigned long long* Value, char CharOut, char CharAdd, unsigned long long HideSeek = 0);

THesh HeshSumm;
THesh HeshSS;

TSkip SkipHeshSumm;
TSkip SkipHeshSS;

int RunTest  (THesh*, TSkip*);
int LenS (const char Str[]);
bool IsFind  (const char Ps[], const char Str[], int start);

int StrInStr (THesh*, TSkip*, const char Ps[], const char Str[]);

unsigned long long Maska (int len);

int main()
    {
    RunTest (&HeshSS, &SkipHeshSS);
    }

// Определение хэш значения строки. Сумма кодов символов.
unsigned long long HeshSumm (const char Str[], int LenStr)
    {
    int sum = 0;
    int i = 0;
    while ((Str[i] != '\0') && (i<LenStr))
        {
        sum += Str[i];
        i++;
        }
    return sum;
    }

void SkipHeshSumm (unsigned long long* Value, char CharOut, char CharAdd, unsigned long long HideSeek)
    {
     *Value -= CharOut;
     *Value += CharAdd;
    }

void SkipHeshSS   (unsigned long long* Value, char CharOut, char CharAdd, unsigned long long HideSeek)
   {
    *Value = (*Value << 8) + CharAdd;
    *Value = *Value & HideSeek;
   }

// Возвращает первое вхождение Подстроки в строке. Если совпадения нет, то возвращает -1
int StrInStr(THesh* Hesh, TSkip* Skip, const char Ps[], const char Str[])
    {
    int i = 0;
    int start = 0;
    int number = -1;

    int LenPs = LenS(Ps);
    int LenStr = LenS(Str);

    unsigned long long HeshPs = (*Hesh) (Ps, LenPs);
    unsigned long long HeshInclude = (*Hesh) (Str, LenPs);
    unsigned long long Hide = Maska (LenPs*8);

    while (start <= LenStr - LenPs)
        {
        if (HeshPs == HeshInclude)
            {
            if (IsFind(Ps, Str, start)) return start;
                else ;
            }
        else
            {
            (*Skip) (&HeshInclude, Str[start], Str[start + LenPs], Hide);
            };
        start++;
        }

    return -1;
    }


// Определение хэш значения строки. Аналог Систем счисления.
unsigned long long HeshSS (const char Str[], int LenStr)
    {
    int result = 0;
    int i = 0;
    while ((Str[i] != '\0') && (i<LenStr))
        {
        result = result << 8 + Str[i];
        i++;
        }
    return result;
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
int RunTest (THesh* Hesh, TSkip* Skip)
    {

    $unittest (StrInStr(Hesh, Skip, "", "abc"),      0);

    $unittest (StrInStr(Hesh, Skip,"a", "abc"),     0);
    $unittest (StrInStr(Hesh, Skip,"b", "abc"),     1);
    $unittest (StrInStr(Hesh, Skip,"c", "abc"),     2);
    $unittest (StrInStr(Hesh, Skip,"123","123"),  0);

    $unittest (StrInStr(Hesh, Skip,"bcd", "abcd"),  1);
    $unittest (StrInStr(Hesh, Skip,"bcd", "abct"), -1);
    $unittest (StrInStr(Hesh, Skip,"bcd", "abcd"),  1);
    $unittest (StrInStr(Hesh, Skip,"bcd", "abc"),  -1);

    $unittest (StrInStr(Hesh, Skip,"ABCDEFGH1234567890", "123"),  -1);
    $unittest (StrInStr(Hesh, Skip,"1","ABCDEFGH1234567890"),  8);
    $unittest (StrInStr(Hesh, Skip,"123","ABCDEFGH1234567890"),  8);

    $unittest (StrInStr(Hesh, Skip,"123","1234567890"),  0);
    $unittest (StrInStr(Hesh, Skip,"9","1234567890"),  8);
    $unittest (StrInStr(Hesh, Skip,"90","1234567890"),  8);
    $unittest (StrInStr(Hesh, Skip,"901","1234567890"),  -1);

    $unittest (StrInStr(Hesh, Skip,"1234567890","12341234567890"),  4);

    }

// Заполняет последние len битов 1
unsigned long long Maska (int len)
    {
    unsigned long long result = 0;
    for (int i = 1; i <= len; i++) result = (result << 1) + 1;
    return result;
    }

// Длина строки
int LenS (const char Str[])
    {
    int d = 0;

    while (Str[d] != '\0') d++;

    return d;
    }

// update