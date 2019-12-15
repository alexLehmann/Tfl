// tfl.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "defs.h"
#include "Scaner.h"
#include "Diagram.h"
#include "Tree.h"



int main(int argc, char* argv[])
{
	setlocale( LC_ALL, "Russian");

		
	TScaner *sc;
	int type; 
	TypeLex l;

	if(argc <= 1) sc = new TScaner("input.txt");
	else sc = new TScaner(argv[1]);
	
	Tree* Root = new Tree(NULL,NULL,NULL,"КОРЕНЬ",TYPE_UNKNOWN);
	Root->SetCur(Root);

	TDiagram *dg = new TDiagram(sc,Root);
	dg->Q();

	type = sc->Scaner(l);
	if(type == Tend)
		printf("Синтаксических ошибок не обнаружено. \n");
	else 
		sc->PrintError("Лишний текст в конце программы.","");

	return 0;
}

