#pragma once
#ifndef __Scaner
#define __Scaner
#include "defs.h"

class TScaner
{
private :
	TypeMod t; //�������� �����
	int uk; //��������� ��� �������
	int line;//������� ������
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
