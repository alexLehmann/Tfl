#pragma once
#ifndef __Scaner
#define __Scaner
#include "defs.h"

class TScaner
{
private :
	TypeMod t; //исходный текст
	int uk; //указатель тек позиции
	int line;//позиция ошибки
public:
	void PutUK(int i);
	int GetUK(void);
	void PrintError(char *, char *);
	int Scaner(TypeLex l);
	void GetData(char *);	
	void SetLine (int value);
	int GetLine ();

	TScaner(char *);
	~TScaner(){}
};
#endif
