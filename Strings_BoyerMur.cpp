#include "TXLib.h"
//#include <iostream>
#include <string>


void RunTest  ();
int LenS (const char Str[]);
int StrInStr (const char Ps[], const char Str[]);
void Spaces (int Count);

int main()
    {


    RunTest ();
    }

void Spaces (int Count)
{
    for (int i = 1; i<=Count; i++)
    {
        printf(" ");
    }
}

// Возвращает первое вхождение Подстроки в строке. Если совпадения нет, то возвращает -1
int StrInStr(const char Ps[], const char Str[])
    {
    //int number = -1;

    int LenPs = LenS(Ps);
    int LenStr = LenS(Str);
    int  SdvigArr [256] = {};

// печать
    printf ("0123456789\n");
    printf ("%s \n\n", Ps);



    // заполнить массив сдвигов максимальными значениями
    for (int i = 1; i < 256; i++)
    {
        SdvigArr [i] = LenPs;

    }

    for (int i = 0; i < LenPs ; i++)
    {
        int code = (unsigned char) Ps[i];
        SdvigArr [code] = LenPs - (i+1);
        printf ("%c - %u - %u \n", Ps[i], code, SdvigArr [code]);

    }

// печать
    printf ("таблица сдвигов \n");
    printf ("%s \n", Ps);
    for (int i = 0; i < LenPs; i++)
            printf ("%c - %u \n", Ps[i], SdvigArr[(unsigned char) Ps[i]]);
    printf ("\n");
    printf ("%s \n", Str);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j<10; j++)
            printf ("%u", i);
    printf ("\n");

    for (int i = 0; i < 4; i++)
        for (int j = 0; j<10; j++)
            printf ("%u", j);
    printf ("\n%s\n", Str);
// конец блока печати

    int start = 0;
    while (start + LenPs <= LenStr)
    {

        bool finds = true;

        // печать
        Spaces (start);
        printf ("%s\n", Ps);
        // конец блока печати

        for (int i = LenPs - 1; i >= 0; i--)
        {
            // печать
            Spaces (start+i);
            printf("^\n");
            // конец блока печати

            if (Str[i + start] != Ps[i])
            {
                int code = (unsigned char) Str[i + start];
                if (SdvigArr [code ] !=0)
                    start = start + SdvigArr [code];
                else start++;

                finds = false;
                break;
            }
        }
        getch();

        if (finds)
            return (start);


    }
    return -1;



    }


// Тест работы функции
void RunTest ()
    {


    $unittest (StrInStr("", "abc"),      0);

    $unittest (StrInStr("a", "abc"),     0);
    $unittest (StrInStr("b", "abc"),     1);
    $unittest (StrInStr("c", "abc"),     2);
    $unittest (StrInStr("123","123"),  0);

    $unittest (StrInStr("bcd", "abcd"),  1);
    $unittest (StrInStr("bcd", "abct"), -1);
    $unittest (StrInStr("bcd", "abcd"),  1);
    $unittest (StrInStr("bcd", "abc"),  -1);

    $unittest (StrInStr("ABCDEFGH1234567890", "123"),  -1);
    $unittest (StrInStr("1","ABCDEFGH1234567890"),  8);
    $unittest (StrInStr("123","ABCDEFGH1234567890"),  8);

    $unittest (StrInStr("123","1234567890"),  0);
    $unittest (StrInStr("9","1234567890"),  8);
    $unittest (StrInStr("90","1234567890"),  8);
    $unittest (StrInStr("901","1234567890"),  -1);

    $unittest (StrInStr("123456789","12341234567892"),  4);

    $unittest (StrInStr("1234567890","123412345678902"),  4);

    $unittest (StrInStr("123","123412345678902"),  0);
    $unittest (StrInStr("ABC","ABACABADABACABA"),  -1);

    $unittest (StrInStr("ABC","1ABC12345678902"),  1);

    $unittest (StrInStr("DABCFAB","ABACABADABACABA"),  -1);

    $unittest (StrInStr ("AB", "AB"), 0);
    $unittest (StrInStr ("AB", "ABCAB"), 0);

    $unittest (StrInStr ("AB", "ABCBCC"), 0);

    $unittest (StrInStr ("AB", "BCBBBABCCABCABC"), 5);

    $unittest (StrInStr ("qw", "qede dqw"), 6);

    $unittest (StrInStr (" qw", "qwde qwd"), 4);

    $unittest (StrInStr ("", "qw"), 0);
    $unittest (StrInStr ("", ""), 0);
    $unittest (StrInStr ("qw", ""), -1);
    $unittest (StrInStr ("qw", "ewewq"), -1);
    $unittest (StrInStr ("88", "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567788"), 98);

    $unittest (StrInStr ("DABA", "ABACABADABACABA"), 7);
    $unittest (StrInStr ("DABA", "ABACABADABCCABADABAA"), 15);
    $unittest (StrInStr ("DABA", "ABACABADABCCABADABADABA"), 15);

    $unittest (StrInStr ("DABA", "ABACABADABCCABADABAABACACD"), 15);

    $unittest (StrInStr ("при", "Василий, привет!"), 9);
    $unittest (StrInStr ("ЛИЦ", "ПОЛИЦИЯ"), 2);

    $unittest (StrInStr ("корова", "ковкорова"), 3);

    $unittest (StrInStr ("korova", "kovkorova"), 3);
    $unittest (StrInStr ("world", "worlrworlrworld"), 10);
    $unittest (StrInStr ("world", "worlrworldworld"), 5);
    $unittest (StrInStr ("world", "worldworldworld"), 0);

    }

  /*
0123                            *
DABA                            *
  >*
>>>*
                                *
таблица сдвигов
ABCDEFGH                        *
44444444
34444444  - последняя A
32444444        B
12444444       A
01434444       D                *

0000000000111111111122222222223333333333
0123456789012345678901234567890123456789
ABACABCADABACABA
DABA  :|  :           +1
   ^  :|  :
    DABA  :
       ^  :
       DABA
        DABA          -1




 $p пауза

  */


// Длина строки
int LenS (const char Str[])
    {
    int d = 0;

    while (Str[d] != '\0') d++;

    return d;
    }

