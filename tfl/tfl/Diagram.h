#pragma once
#ifndef __DIAGRAM
#define __DIAGRAM
#include "Scaner.h"
#include "Tree.h"

class TDiagram
{
private:
	TScaner *sc;
	Tree *Root;
public:
	TDiagram(TScaner *s,Tree *r){
		sc = s;
		Root = r;
	}	
	~TDiagram(void){}
	
	void Q(); //класс Main
	void W(DATA_TYPE typ); //переменная
	void E(Tree * v); //оператор
	void R(); //одно описание
	void T(); //данные
	void Y(); //функция
	void U(); //список
	void I(Tree * v); //составной оператор
	int O(); //список формальных параметров
	void P(Tree *v); //While
	void A(); //вызов функции
	DATA_TYPE S(); //выражение
	DATA_TYPE D(); //слагаемое
	DATA_TYPE F(); //множитель
	DATA_TYPE G(); //элементарное выражение
	
};
#endif