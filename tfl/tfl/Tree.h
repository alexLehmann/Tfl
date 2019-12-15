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
	int Parm;//����������� ����������
	DATA_TYPE Type_Funct = TYPE_UNKNOWN;
	
	
public:
	static Tree * Cur; // ������� ������� ������
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
	int DupControl(Tree *Addr, TypeLex a);// �������� �������������� � �� ��������� �������� ������ �����
	void SetCur(Tree * a) ;	// ���������� ������� ���� ������
	Tree * GetCur(void);// �������� �������� �������� ���� ������
	Tree * SemInclude(TypeLex a, DATA_TYPE t,TScaner *s);// ��������� �������������� a � ������� � ����� t
	void SemSetType(Tree *Addr, DATA_TYPE t);// ���������� ��� t ��� ���������� �� ������ Addr
	Tree * SemGetType(TypeLex a,TScaner *s);// ����� � ������� ���������� � ������ a � ������� ������ �� ��������������� ������� ������
	void SemSetParam(Tree *Addr,int num);//����������� ����������
	void SemControlParam(TypeLex a,Tree *Addr, int num,TScaner *s);//�������� �� �����������
	Tree * SemGetFunct(TypeLex a,TScaner *s);	// ����� � ������� ������� � ������ a � ������� ������ �� ��������������� ������� ������
	DATA_TYPE Type(TypeLex t,TScaner *s);//���������� ��� ������� t
	DATA_TYPE Type_PR(DATA_TYPE fir, DATA_TYPE sec, int a, TScaner *s, TypeLex l);
	void SetTypeFunct(DATA_TYPE t);//������ ��� ����� �������� ��������
	DATA_TYPE GetTypeFunct();//�������� ��� ������������� ��������
	DATA_TYPE getDT();//�������� ���
	Tree* Sem(Tree* v);//������ �� ���������� ��� ������ �������

};

