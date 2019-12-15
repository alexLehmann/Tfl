#pragma once
#include "defs.h"
#include "Scaner.h"

enum DATA_TYPE { TYPE_UNKNOWN =1, TYPE_INTEGER,
	TYPE_BOOL, TYPE_FUNCT};

class Tree
{
private:
	TypeLex id;
	DATA_TYPE DataType;
	Tree *Up, *Left, *Right;
	int Parm;//колличество переменных
	DATA_TYPE Type_Funct = TYPE_UNKNOWN;
	
	
public:
	static Tree * Cur; // текущий элемент дерева
	Tree(Tree * l, Tree * r, Tree * u, TypeLex aid,DATA_TYPE aDataType);
	Tree(void);
	~Tree(void);
	void SetLeft (Tree * Data);
	void SetRight(Tree * Data);
	void SetLeft (TypeLex aid,DATA_TYPE aDataType);
	void SetRight(TypeLex aid,DATA_TYPE aDataType);
	Tree * FindUp (Tree * From, TypeLex id);
	Tree * FindUpOneLevel (Tree * From, TypeLex id);
	Tree * FindUp (TypeLex id);
	Tree * FindRightLeft (Tree * From, TypeLex id);
	Tree * FindRightLeft (TypeLex id);
	void Print(void);
	int DupControl(Tree *Addr, TypeLex a);// проверка идентификатора а на повторное описание внутри блока
	void SetCur(Tree * a) ;	// установить текущий узел дерева
	Tree * GetCur(void);// получить значение текущего узла дерева
	Tree * SemInclude(TypeLex a, DATA_TYPE t,TScaner *s);// занесение идентификатора a в таблицу с типом t
	void SemSetType(Tree *Addr, DATA_TYPE t);// установить тип t для переменной по адресу Addr
	Tree * SemGetType(TypeLex a,TScaner *s);// найти в таблице переменную с именем a и вернуть ссылку на соответствующий элемент дерева
	void SemSetParam(Tree *Addr,int num);//колличество параметров
	void SemControlParam(TypeLex a,Tree *Addr, int num,TScaner *s);//контроль за параметрами
	Tree * SemGetFunct(TypeLex a,TScaner *s);	// найти в таблице функцию с именем a и вернуть ссылку на соответствующий элемент дерева
	DATA_TYPE Type(TypeLex t,TScaner *s);//Определяет тип лексемы t
	DATA_TYPE Type_PR(DATA_TYPE fir, DATA_TYPE sec, int a, TScaner *s, TypeLex l);
	void SetTypeFunct(DATA_TYPE t);//задать тип возвр значения функцией
	DATA_TYPE GetTypeFunct();//получить тип возвращаемого значения
	DATA_TYPE getDT();//получить тип
	Tree* Sem(Tree* v);//проход по параметрам при вызове функции

};

