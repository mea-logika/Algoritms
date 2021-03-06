#include "TXLib.h"

typedef unsigned long long THesh (const char Str[], int LenStr, int Bits );
typedef void TSkip (unsigned long long* Value, char CharOut, char CharAdd, int Bits , unsigned long long HideSeek = 0);

THesh HeshSumm;
THesh HeshSS;

TSkip SkipHeshSumm;
TSkip SkipHeshSS;

void RunTest  (THesh*, TSkip*, int Bits);
int LenS (const char Str[]);
bool IsFind  (const char Ps[], const char Str[], int start);

int StrInStr (THesh*, TSkip*, const char Ps[], const char Str[], int Bits );

unsigned long long Maska (int len);

int main()
    {

    int Bits = 4; // ���������� �������� ��������� ��� ������ �������
    //$(HeshSS("ABC",3, Bits));
    RunTest (&HeshSS, &SkipHeshSS, Bits);
    }

// ����������� ��� �������� ������. ����� ����� ��������.
unsigned long long HeshSumm (const char Str[], int LenStr, int Bits )
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

void SkipHeshSumm (unsigned long long* Value, char CharOut, char CharAdd, int Bits, unsigned long long HideSeek)
    {
     *Value -= CharOut;
     *Value += CharAdd;
    }

void SkipHeshSS   (unsigned long long* Value, char CharOut, char CharAdd, int Bits, unsigned long long HideSeek)
   {
    *Value = (*Value << Bits) + (CharAdd & Maska(Bits));
    *Value = *Value & HideSeek;
   }

// ���������� ������ ��������� ��������� � ������. ���� ���������� ���, �� ���������� -1
int StrInStr(THesh* Hesh, TSkip* Skip, const char Ps[], const char Str[], int Bits)
    {
    int i = 0;
    int start = 0;
    int number = -1;

    int LenPs = LenS(Ps);
    int LenStr = LenS(Str);

    unsigned long long HeshPs = (*Hesh) (Ps, LenPs, Bits);
    unsigned long long HeshInclude = (*Hesh) (Str, LenPs, Bits);

    unsigned long long Hide = Maska (LenPs * Bits);

    while (start <= LenStr - LenPs)
        {
        if (HeshPs == HeshInclude)
            {
            if (IsFind (Ps, Str, start)) return start;

            }
        else
            {
            (*Skip) (&HeshInclude, Str[start], Str[start + LenPs], Bits, Hide);
            };
        start++;
        }

    return -1;
    }


// ����������� ��� �������� ������. ������ ������ ���������.
unsigned long long HeshSS (const char Str[], int LenStr, int Bits)
    {
    unsigned long long result = 0;
    int i = 0;

    while ((Str[i] != '\0') && (i<LenStr))
        {
        result = (result << Bits) + (Str[i] & Maska (Bits));
        i++;
        }
    return result;
    }


// ��������� ��������� �� ��������� � ������ ������, ������� � ������� start
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

// ���� ������ �������
void RunTest (THesh* Hesh, TSkip* Skip, int Bits)
    {

    $unittest (StrInStr(Hesh, Skip, "", "abc", Bits),      0);

    $unittest (StrInStr(Hesh, Skip,"a", "abc", Bits),     0);
    $unittest (StrInStr(Hesh, Skip,"b", "abc", Bits),     1);
    $unittest (StrInStr(Hesh, Skip,"c", "abc", Bits),     2);
    $unittest (StrInStr(Hesh, Skip,"123","123", Bits),  0);

    $unittest (StrInStr(Hesh, Skip,"bcd", "abcd", Bits),  1);
    $unittest (StrInStr(Hesh, Skip,"bcd", "abct", Bits), -1);
    $unittest (StrInStr(Hesh, Skip,"bcd", "abcd", Bits),  1);
    $unittest (StrInStr(Hesh, Skip,"bcd", "abc", Bits),  -1);

    $unittest (StrInStr(Hesh, Skip,"ABCDEFGH1234567890", "123", Bits),  -1);
    $unittest (StrInStr(Hesh, Skip,"1","ABCDEFGH1234567890", Bits),  8);
    $unittest (StrInStr(Hesh, Skip,"123","ABCDEFGH1234567890", Bits),  8);

    $unittest (StrInStr(Hesh, Skip,"123","1234567890", Bits),  0);
    $unittest (StrInStr(Hesh, Skip,"9","1234567890", Bits),  8);
    $unittest (StrInStr(Hesh, Skip,"90","1234567890", Bits),  8);
    $unittest (StrInStr(Hesh, Skip,"901","1234567890", Bits),  -1);

    $unittest (StrInStr(Hesh, Skip,"123456789","12341234567892", Bits),  4);
    $unittest (StrInStr(Hesh, Skip,"1234567890","123412345678902", Bits),  4);

    }

// ��������� ��������� len ����� 1
unsigned long long Maska (int len)
    {


    if (len < 64) return (  1LLU << len) - 1;
        else      return ( ~0LLU );
    }

// ����� ������
int LenS (const char Str[])
    {
    int d = 0;

    while (Str[d] != '\0') d++;

    return d;
    }

