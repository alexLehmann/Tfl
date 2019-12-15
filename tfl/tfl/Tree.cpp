#include "stdafx.h"
#include "Tree.h"
#define max(a,b) a<b? b : a

Tree* Tree::Cur=(Tree*)NULL;

//создаем узел с заданными связямии
Tree::Tree (Tree * l, Tree * r, Tree * u, TypeLex aid,DATA_TYPE aDataType){// конструктор создает узел с заданными связями и данными
	strcpy(id,aid);
	DataType = aDataType;
	Up=u; Left=l; Right=r;
	
}
//создаем узел с пустыми связями и данными
Tree::Tree (void){
	DataType = TYPE_UNKNOWN;
	Up=NULL; Left=NULL; Right=NULL;
	strcpy(id,"*");
}

// назначить левого потомка от текущей вершины this
void Tree::SetLeft (Tree * Data){

	Left=Data; // связали this с вершиной
}

// назначить правого потомка от текущей вершины this
void Tree::SetRight(Tree * Data){

	Right=Data; // связали this с  вершиной
}

// создать левого потомка от текущей вершины this
void Tree::SetLeft (TypeLex aid,DATA_TYPE aDataType){
	Tree *a = new Tree(NULL,NULL,this,aid,aDataType);
	Left = a;	
}
// создать правого потомка от текущей вершины this
void Tree::SetRight(TypeLex aid,DATA_TYPE aDataType){

	Tree *a = new Tree(NULL,NULL,this,aid,aDataType);
	Right = a;
}

// поиск данных в дереве, начиная от текущей вершины this до его корня вверх по связям
Tree* Tree::FindUp(TypeLex id){
	return FindUp(this, id);
}
// поиск данных в дереве от заданной вершины From до его корня вверх по связям
Tree* Tree::FindUp(Tree * From, TypeLex id){
	Tree * i=From; // текущая вершина поиска
	while( (i!=NULL) &&	(strcmp(id, i->id)!=0)){
		i=i->Up; // поднимаемся наверх по связям
	}
	return i;
}

// поиск прямых потомков текущей вершины this
Tree * Tree::FindRightLeft(TypeLex id){
	return FindRightLeft(this, id);
}

// поиск прямых потомков заданной вершины From
Tree * Tree::FindRightLeft(Tree * From, TypeLex id){
	Tree *i=From->Right; // текущая вершина поиска
	while( (i!=NULL) &&(memcmp(id, i->id, max(strlen(i->id),strlen(id)))!=0) ){
		i==i->Left;// обходим только соседей по левым связям
	}
	
	return i;
}
// Поиск элемента id вверх по дереву от текущей вершины From.Поиск осуществляется на одном уровне вложенности по левым связям
Tree * Tree::FindUpOneLevel(Tree * From, TypeLex id){
	Tree * i = From; // текущая вершина поиска
	if(i->Up == NULL) return NULL;

	while( (i!=NULL) &&( i->Up->Right != i)){
		if (memcmp(id, i->id, max(strlen(i->id),strlen(id)))==0){
			return i; // нaшли совпадающий идентификатор
		}
		i=i->Up; // поднимаемся наверх по связям
		if(i->Up == NULL) return NULL;
	}
	return NULL;
}

// Проверка идентификатора а на повторное описание внутри блока. Поиск осуществляется вверх от вершины Addr.
int Tree::DupControl(Tree* Addr, TypeLex a){
	if(a == "----") return 0;
	if (FindUpOneLevel(Addr, a)==NULL){
		return 0;
	}
	return 1;
}
// установить текущий узел дерева  
void Tree::SetCur(Tree * a)
{
	Cur=a;
}
// получить значение текущего узла дерева
Tree * Tree::GetCur(void)
{
	return Cur;
}
// занесение идентификатора a в таблицу с типом t 
Tree * Tree::SemInclude(TypeLex a, DATA_TYPE t, TScaner *s)
{
	if (DupControl(Cur, a)){
		
		s->PrintError("Повторное описание идентификатора ",a);
	}

	Tree * v;
	if (t!= TYPE_FUNCT)
	{
		Cur->SetLeft (a,t);
		Cur = Cur->Left;
		Parm = 0;
		return Cur;
	}
	else
	{
		Cur->SetLeft (a,t); //делаем функцию
		Parm = 0;
		Cur = Cur->Left;
		v=Cur;//точка возврата после выхода изфункции
		Cur->SetRight ("----",TYPE_UNKNOWN); //пустая вершина
		Cur = Cur->Right;
		return v;
	}
}

// установить тип t для переменной по адресу Addr
void Tree::SemSetType(Tree* Addr, DATA_TYPE t)
{
	Addr->DataType=t;
}
//установить число формальных параметров
void Tree::SemSetParam(Tree* Addr, int num)
{
	Addr->Parm = num;
}

void Tree::SemControlParam(TypeLex a,Tree *Addr, int num,TScaner *s)
// проверить равенство числа формальных параметров значению
// n для функции по адресу Addr
{
if (num!=Addr->Parm)
	s->PrintError("Неверное число параметров у функции ",a);
}
// найти в таблице переменную с именем a и вернуть ссылку на соответствующий элемент дерева
Tree * Tree::SemGetType(TypeLex a,TScaner *s){
	Tree *v=FindUp(Cur, a);
	if (v==NULL){
		s->PrintError("Отсутствует описание идентификатора ",a);
	}
	/*
	if (v->DataType==TYPE_FUNCT){
		s->PrintError("Неверное использование вызова функции ",a);
	}*/
	return v;
}
// найти в таблице функцию с именем a и вернуть ссылку на соответствующий элемент дерева.
Tree * Tree::SemGetFunct(TypeLex a,TScaner *s){

	Tree * v=FindUp(Cur, a);
	if (v==NULL){
		s->PrintError("Отсутствует описание функции ",a);
	}
	if (v->DataType!=TYPE_FUNCT){
		s->PrintError("Идентификатор не является функцией ",a);
	}
	return v;
}

DATA_TYPE Tree::Type(TypeLex a,TScaner *s){
	if(strcmp(a,"int") ==0) return TYPE_INTEGER;
	if(strcmp(a,"false") ==0) return TYPE_BOOL;
	if(strcmp(a,"true") ==0) return TYPE_BOOL;
	if (strcmp(a,"boolean") == 0) return TYPE_BOOL;
}

void  Tree::SetTypeFunct(DATA_TYPE t)
{
	Type_Funct = t;
}

DATA_TYPE Tree::GetTypeFunct()
{
	return Type_Funct;
}

DATA_TYPE Tree::Type_PR(DATA_TYPE fir, DATA_TYPE sec, int a, TScaner *s, TypeLex r)
{
	if ((a == Tand)||(a == Tor)||(a == Tlt)||(a == Tle)||(a == Tgt)||(a == Tge) || (a == Teq) || (a == Tneq))
	{
		if (fir == TYPE_INTEGER && sec == TYPE_INTEGER)
		{
			return TYPE_BOOL;
		}
		else 
		if (fir == TYPE_BOOL && sec == TYPE_BOOL)
		{
			return TYPE_BOOL;
		}
		else
		{
			s->PrintError("Невожможно совершить операцию с такими операндами",r );
		}
	}
	if ((a == Tmod) || (a >= Tsave) || (a == Tdiv) || (a == Tmult) || (a == Tminus) || (a == Tplus))
	{

		if (fir == TYPE_INTEGER && sec == TYPE_INTEGER)
		{
			return TYPE_INTEGER;
		}
		else
		if (fir == TYPE_BOOL && sec == TYPE_BOOL)
		{
			return TYPE_BOOL;
		}
		else
		/*if (fir == TYPE_INTEGER && sec == TYPE_BOOL)
		{
			return TYPE_INTEGER;
		}
		else*/
		{
			s->PrintError("Невожможно совершить операцию с такими опреандами",r);
		}
	}
	

	return fir;
}


void Tree::Print (void){
	printf("Вершина %s ----->", id);
	if (Left !=NULL) printf(" слева %s", Left->id );
	if (Right!=NULL) printf(" справа %s", Right->id );
	printf("\n");
	if (Left!=NULL) Left->Print();
	if (Right!=NULL&&Right->DataType!=TYPE_FUNCT) Right->Print();
}

DATA_TYPE Tree::getDT(){
	return DataType;
}

Tree* Tree::Sem(Tree* v)
{
	if (v->Right != NULL)
		v = v->Right;
	else
	{
		v = v->Left;
	}
	return v;
}

Tree::~Tree(void)
{
}
