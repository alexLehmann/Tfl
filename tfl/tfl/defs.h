#pragma once
#include"stdafx.h"

#ifndef __DEFS
#define __DEFS

#define MAX_TEXT 10000 //максимальна€ дл€ина текста
#define MAX_LEX 100 //максимальна€ длина лексемы
#define MAX_KEYW 8 //число ключевых слов

typedef char TypeLex[MAX_LEX];
typedef char TypeMod[MAX_TEXT];

//ключевые слова
#define TClass 0
#define TMain 1
#define Tint 2
#define Tboolean 3
#define Twhile 4
#define Ttrue 5
#define Tfalse 6
#define Treturn 7
//идентефикаторы
#define Tident 11

#define Tconst10 20
#define Tconst16 21
//—пециальные знаки
#define Tzpt 30
#define Ttzpt 31
#define Tls 32
#define Tps 33
#define Tfls 34
#define Tfps 35
//«наки операций
#define Tnot 40
#define Tand 41
#define Tor 42
#define Tlt 43
#define Tle 44
#define Tgt 45
#define Tge 46
#define Teq 47
#define Tneq 48
#define Tplus 49
#define Tminus 50
#define Tmult 51
#define Tdiv 52
#define Tmod 53
#define Tsave 54
#define Tend 100
#define Terr 200
#endif