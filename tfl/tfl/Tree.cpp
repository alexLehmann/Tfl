#include "stdafx.h"
#include "Tree.h"
#define max(a,b) a<b? b : a

Tree* Tree::Cur=(Tree*)NULL;

//������� ���� � ��������� ��������
Tree::Tree (Tree * l, Tree * r, Tree * u, TypeLex aid,DATA_TYPE aDataType){// ����������� ������� ���� � ��������� ������� � �������
	strcpy(id,aid);
	DataType = aDataType;
	Up=u; Left=l; Right=r;
	
}
//������� ���� � ������� ������� � �������
Tree::Tree (void){
	DataType = TYPE_UNKNOWN;
	Up=NULL; Left=NULL; Right=NULL;
	strcpy(id,"*");
}

// ��������� ������ ������� �� ������� ������� this
void Tree::SetLeft (Tree * Data){

	Left=Data; // ������� this � ��������
}

// ��������� ������� ������� �� ������� ������� this
void Tree::SetRight(Tree * Data){

	Right=Data; // ������� this �  ��������
}

// ������� ������ ������� �� ������� ������� this
void Tree::SetLeft (TypeLex aid,DATA_TYPE aDataType){
	Tree *a = new Tree(NULL,NULL,this,aid,aDataType);
	Left = a;	
}
// ������� ������� ������� �� ������� ������� this
void Tree::SetRight(TypeLex aid,DATA_TYPE aDataType){

	Tree *a = new Tree(NULL,NULL,this,aid,aDataType);
	Right = a;
}

// ����� ������ � ������, ������� �� ������� ������� this �� ��� ����� ����� �� ������
Tree* Tree::FindUp(TypeLex id){
	return FindUp(this, id);
}
// ����� ������ � ������ �� �������� ������� From �� ��� ����� ����� �� ������
Tree* Tree::FindUp(Tree * From, TypeLex id){
	Tree * i=From; // ������� ������� ������
	while( (i!=NULL) &&	(strcmp(id, i->id)!=0)){
		i=i->Up; // ����������� ������ �� ������
	}
	return i;
}

// ����� ������ �������� ������� ������� this
Tree * Tree::FindRightLeft(TypeLex id){
	return FindRightLeft(this, id);
}

// ����� ������ �������� �������� ������� From
Tree * Tree::FindRightLeft(Tree * From, TypeLex id){
	Tree *i=From->Right; // ������� ������� ������
	while( (i!=NULL) &&(memcmp(id, i->id, max(strlen(i->id),strlen(id)))!=0) ){
		i==i->Left;// ������� ������ ������� �� ����� ������
	}
	
	return i;
}
// ����� �������� id ����� �� ������ �� ������� ������� From.����� �������������� �� ����� ������ ����������� �� ����� ������
Tree * Tree::FindUpOneLevel(Tree * From, TypeLex id){
	Tree * i = From; // ������� ������� ������
	if(i->Up == NULL) return NULL;

	while( (i!=NULL) &&( i->Up->Right != i)){
		if (memcmp(id, i->id, max(strlen(i->id),strlen(id)))==0){
			return i; // �a��� ����������� �������������
		}
		i=i->Up; // ����������� ������ �� ������
		if(i->Up == NULL) return NULL;
	}
	return NULL;
}

// �������� �������������� � �� ��������� �������� ������ �����. ����� �������������� ����� �� ������� Addr.
int Tree::DupControl(Tree* Addr, TypeLex a){
	if(a == "----") return 0;
	if (FindUpOneLevel(Addr, a)==NULL){
		return 0;
	}
	return 1;
}
// ���������� ������� ���� ������  
void Tree::SetCur(Tree * a)
{
	Cur=a;
}
// �������� �������� �������� ���� ������
Tree * Tree::GetCur(void)
{
	return Cur;
}
// ��������� �������������� a � ������� � ����� t 
Tree * Tree::SemInclude(TypeLex a, DATA_TYPE t, TScaner *s)
{
	if (DupControl(Cur, a)){
		
		s->PrintError("��������� �������� �������������� ",a);
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
		Cur->SetLeft (a,t); //������ �������
		Parm = 0;
		Cur = Cur->Left;
		v=Cur;//����� �������� ����� ������ ���������
		Cur->SetRight ("----",TYPE_UNKNOWN); //������ �������
		Cur = Cur->Right;
		return v;
	}
}

// ���������� ��� t ��� ���������� �� ������ Addr
void Tree::SemSetType(Tree* Addr, DATA_TYPE t)
{
	Addr->DataType=t;
}
//���������� ����� ���������� ����������
void Tree::SemSetParam(Tree* Addr, int num)
{
	Addr->Parm = num;
}

void Tree::SemControlParam(TypeLex a,Tree *Addr, int num,TScaner *s)
// ��������� ��������� ����� ���������� ���������� ��������
// n ��� ������� �� ������ Addr
{
if (num!=Addr->Parm)
	s->PrintError("�������� ����� ���������� � ������� ",a);
}
// ����� � ������� ���������� � ������ a � ������� ������ �� ��������������� ������� ������
Tree * Tree::SemGetType(TypeLex a,TScaner *s){
	Tree *v=FindUp(Cur, a);
	if (v==NULL){
		s->PrintError("����������� �������� �������������� ",a);
	}
	/*
	if (v->DataType==TYPE_FUNCT){
		s->PrintError("�������� ������������� ������ ������� ",a);
	}*/
	return v;
}
// ����� � ������� ������� � ������ a � ������� ������ �� ��������������� ������� ������.
Tree * Tree::SemGetFunct(TypeLex a,TScaner *s){

	Tree * v=FindUp(Cur, a);
	if (v==NULL){
		s->PrintError("����������� �������� ������� ",a);
	}
	if (v->DataType!=TYPE_FUNCT){
		s->PrintError("������������� �� �������� �������� ",a);
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
			s->PrintError("���������� ��������� �������� � ������ ����������",r );
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
			s->PrintError("���������� ��������� �������� � ������ ����������",r);
		}
	}
	

	return fir;
}


void Tree::Print (void){
	printf("������� %s ----->", id);
	if (Left !=NULL) printf(" ����� %s", Left->id );
	if (Right!=NULL) printf(" ������ %s", Right->id );
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
