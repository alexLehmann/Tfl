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
	
	void Q(); //����� Main
	void W(DATA_TYPE typ); //����������
	void E(Tree * v); //��������
	void R(); //���� ��������
	void T(); //������
	void Y(); //�������
	void U(); //������
	void I(Tree * v); //��������� ��������
	int O(); //������ ���������� ����������
	void P(Tree *v); //While
	void A(); //����� �������
	DATA_TYPE S(); //���������
	DATA_TYPE D(); //���������
	DATA_TYPE F(); //���������
	DATA_TYPE G(); //������������ ���������
	
};
#endif