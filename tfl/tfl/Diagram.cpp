#include "stdafx.h"
#include "Diagram.h"
#include "Diagram.h"
#include "Tree.h"

void TDiagram::Q()
{
	TypeLex l; int t, uk1, line1;
	t = sc->Scaner(l);
	if (t != TClass) sc->PrintError("�������� ������ class",l);
	t = sc->Scaner(l);
	if(t != TMain) sc->PrintError("�������� ������ Main",l);
	Root->SemInclude(l,TYPE_UNKNOWN,sc);
	t = sc->Scaner(l);
	if(t != Tfls) sc->PrintError("�������� ������ {",l);

	uk1 = sc->GetUK();
	line1 = sc->GetLine();

	t = sc->Scaner(l);
	sc->PutUK(uk1);
	sc->SetLine(line1);

	bool flag = true;
	if (t==Tfps)
	{
		flag = false;
	}
	else if((t != Tint) && (t != Tboolean))	
	{
		flag =false;
		sc->PrintError("������",l);
	}
	
	

	while(flag)
	{
		R();// ���� ��������
		uk1 = sc->GetUK();
		line1 = sc->GetLine();
		t = sc->Scaner(l);
		sc->PutUK(uk1);
		sc->SetLine(line1);

		if((t != Tint) && (t != Tboolean))	
		{
			flag =false;
			if(t != Tfps)
			{				
				sc->PrintError("������",l);
			}
		}		
	}
	t = sc->Scaner(l);
	if(t != Tfps) 
		sc->PrintError("�������� ������ }",l);
	Root->Print();
}
//���� ��������
void TDiagram::R()

{
	TypeLex l; int t, uk1, line1;
	uk1 = sc->GetUK(); 
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	if (t == Tint || t == Tboolean)
	{
		t = sc->Scaner(l);
		if (t == Tident)
		{
			t = sc->Scaner(l);
			sc->PutUK(uk1);
			sc->SetLine(line1);
			if(t == Tls) Y();//������� 
			else  T();//������			
		}

	}

}

//�������
void TDiagram::Y()
{
	DATA_TYPE typ;
	

	bool flag = true;
	TypeLex l; int t;
	t = sc->Scaner(l);
	if(t != Tint && t != Tboolean)
		sc->PrintError("�������� ��� ������",l);
	else
	{
		 typ = Root->Type(l,sc);
	}
	
		t = sc->Scaner(l);
		if(t != Tident)
			sc->PrintError("�������� �������������",l);
		


		Tree * v=Root->SemInclude(l,TYPE_FUNCT,sc);//������ �������
		//������ ��� ������������� ��������
		v->SetTypeFunct(typ);


		int i=0;
		t = sc->Scaner(l);
		if(t != Tls)
			sc->PrintError("�������� ������ (",l);
		//t = sc->Scaner(l);
		i = O();//������ � �����
		t = sc->Scaner(l);
		if(t != Tps)
			sc->PrintError("�������� ������ )",l);
		Root->SemSetParam(v,i);//�� ���������
		E(v);//��������
		Root->SetCur(v);//����������� ������� � ������
	
}

//������
/*void TDiagram::U()
{
	TypeLex l; int t, uk1;
	do
	{
		W();//����������
		t = sc->Scaner(l);
	} while (t == Tzpt);
}*/

//����������
void TDiagram::W(DATA_TYPE typ)
{
	
	DATA_TYPE type1;
	
	TypeLex l; int t, uk1, line1;
	t = sc->Scaner(l);
	if(t != Tident)
		sc->PrintError("�������� �������������",l);
	//������ �������������
	Root->SemInclude(l,typ,sc);
	
	uk1 = sc->GetUK();
	line1 = sc->GetLine();

	t = sc->Scaner(l);
	if (t == Tsave)
	{
		type1 = S();//���������

		type1 = Root->Type_PR(typ,type1,t,sc,l);


		uk1 = sc->GetUK();
		line1 = sc->GetLine();

		//t = sc->Scaner(l);
	}
	sc->PutUK(uk1);
	sc->SetLine(line1);
}

//������
void TDiagram::T()
{
	bool flag = true;
	TypeLex l; int t;
	t = sc->Scaner(l);
	if((t != Tint) && (t != Tboolean))
		sc->PrintError("�������� ��� ������",l);
	else
	{
		DATA_TYPE typ = Root->Type(l,sc);
	
		do
		{
			W(typ);//����������
			t = sc->Scaner(l);
		} while (t == Tzpt);

		if(t != Ttzpt)
			sc->PrintError("�������� ������ ;",l);
	}
}

//���������
DATA_TYPE TDiagram::S()
{
	DATA_TYPE type = TYPE_UNKNOWN;
	DATA_TYPE type1;
	TypeLex l; int t, uk1, line1;
	uk1 = sc->GetUK(); 
	line1 = sc->GetLine();

	t = sc->Scaner(l);
	if(t != Tnot)
	{
		sc->PutUK(uk1);
		sc->SetLine(line1);
		type = D();//���������
	}
	else
	{
		type = D();//���������
		type = TYPE_BOOL;
	}
	
	uk1 = sc->GetUK(); 
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	while((t <= Tneq) && (t >= Tand))
	{
		type1 = D();//���������
		//�������� �����
		type = Root->Type_PR(type,type1,t,sc,l);

		uk1 = sc->GetUK();
		line1 = sc->GetLine();
		t = sc->Scaner(l);
	}
	sc->PutUK(uk1);
	sc->SetLine(line1);
	return type;	
}



//���������
DATA_TYPE TDiagram::D()
{
	DATA_TYPE type = TYPE_UNKNOWN;
	DATA_TYPE type1;

	bool flag = false;
	TypeLex l; int t, uk1, line1;	
	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	if((t != Tplus) && (t != Tminus))
	{
		sc->PutUK(uk1);
		sc->SetLine(line1);
	}
	else 
		flag = true;

	type = F();//���������

	if (flag)
	{
		//������������� �������� �� ������������ ������� ��������
	}

	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	while ((t == Tplus) || (t == Tminus))
	{
		type1 = F();//���������
		//������������� ��������

		type = Root->Type_PR(type,type1,t,sc,l);

		uk1 = sc->GetUK();
		line1 = sc->GetLine();
		t = sc->Scaner(l);
	}
	sc->PutUK(uk1);
	sc->SetLine(line1);
	return type;
}

//���������
DATA_TYPE TDiagram::F()
{
	DATA_TYPE type = TYPE_UNKNOWN;
	DATA_TYPE type1;

	TypeLex l; int t, uk1, line1;
	type = G();//����. ���������



	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	while ((t == Tdiv) || (t == Tmult) ||(t == Tmod))
	{
		type1 = G();//����.���

		//semant prov

		type = Root->Type_PR(type,type1,t,sc,l);

		uk1 = sc->GetUK();
		line1 = sc->GetLine();
		t = sc->Scaner(l);
	}
	sc->PutUK(uk1);
	sc->SetLine(line1);

	return type;
}

//����.����������
DATA_TYPE TDiagram::G()
{
	
	DATA_TYPE type = TYPE_UNKNOWN;
	int uk1, line1;
	
	TypeLex l; int t;


	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	if((t == Tconst10) || (t == Tconst16))
	{
		type = TYPE_INTEGER;
	}		
	else if(t == Tls)
	{
		type = S();//���������
		t = sc->Scaner(l);
		if(t != Tps)
			sc->PrintError("�������� ������ )",l);
		
	}
	else if((t == Ttrue) || (t == Tfalse))
		type = TYPE_BOOL;
	else if (t == Tident)
	{
		//������� �� ��� 
		Tree * tp = Root->SemGetType(l, sc);
		type = tp->getDT();
		if (type == TYPE_FUNCT)
		{
			
			//t = sc->Scaner(l);
			//t = sc->Scaner(l);

			sc->PutUK(uk1);
			sc->SetLine(line1);

			A();

			type = tp->GetTypeFunct();
			
		}
		

	}		
	else 
		sc->PrintError("�������� �������������", l);
		
	/*else if((t != Tconst10) && (t != Tconst16) && (t != Tls) 
		&& (t != Tident) && (t != Ttrue) && (t != Tfalse) && (t != Tzpt))
		sc->PrintError("��������� ���������",l);
	*/
	return type;
}

//��������
void TDiagram::E(Tree * v)
{
	TypeLex l; int t,uk1, line1;
	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	if(t == Ttzpt) return;
	
	if (t == Twhile)
	{
		sc->PutUK(uk1);
		sc->SetLine(line1);
		P(v);//While
		return;
	}
	if (t == Treturn)
	{
		
		DATA_TYPE typ = v->GetTypeFunct();
		DATA_TYPE typ1;
				
		typ1 = S();//���������

		typ = Root->Type_PR(typ,typ1,t,sc,l);

		t = sc->Scaner(l);
		if(t != Ttzpt)
			sc->PrintError("�������� ������ ;",l);
		return;
	}
	if (t == Tfls)
	{
		sc->PutUK(uk1);
		sc->SetLine(line1);
		I(v);//��������� ��������
		return;
	}
	t = sc->Scaner(l);
	sc->PutUK(uk1);
	sc->SetLine(line1);
	

	DATA_TYPE type;
	DATA_TYPE type1;
	if (t == Tsave)
	{
		
		t = sc->Scaner(l);
		if(t != Tident)
			sc->PrintError("�������� �������������",l);

		//������� �� ��� 
		Tree * tp = Root->SemGetType(l, sc);
		type = tp->getDT();


		t = sc->Scaner(l);
		if(t != Tsave)
		{
			sc->PrintError("�������� ������ =",l);
		}
		type1 = S();//���������

		type = Root->Type_PR(type,type1,t,sc,l);

		t = sc->Scaner(l);
		if(t != Ttzpt)
			sc->PrintError("�������� ������ ;",l);
	}
	else 
	{		
		A();//����� �������
	}	
	
}



//����� �������
void TDiagram::A()
{
	TypeLex l; int t, uk1, line1;
	t = sc->Scaner(l);
	if(t != Tident)
		sc->PrintError("�������� �������������",l);

	Tree * v= Root->SemGetFunct(l,sc); // ����� ����� ������� � �������
	Tree * h = v;
	int num=0; // ����� ����������� ����������
	t = sc->Scaner(l);
	if(t != Tls)
		sc->PrintError("�������� ������ (",l);
	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	
	if(t == Tps)
	{
		Root->SemControlParam(l,v, num,sc);
		return;
	}

	sc->PutUK(uk1);
	sc->SetLine(line1);
	
	h = v->Sem(h);


	DATA_TYPE type;
	DATA_TYPE type1;

	do
	{
		h = h->Sem(h);
		num++;
		
		type = h->getDT();
		type1 = S();//���������

		type = Root->Type_PR(type,type1,t,sc,l);

		uk1 = sc->GetUK();
		line1 = sc->GetLine();
		t = sc->Scaner(l);				
	} while (t == Tzpt);



	Root->SemControlParam(l,v, num,sc);
	sc->PutUK(uk1);
	sc->SetLine(line1);


	t = sc->Scaner(l);
	if(t != Tps)
		sc->PrintError("�������� ������ )",l);

	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	if (t >= Tnot && t<= Tsave)
	{
		sc->PutUK(uk1);
		sc->SetLine(line1);
	}
	else if (t != Ttzpt)
	{

		sc->PrintError("�������� ������ ;", l);
	}
	else
	{
		sc->PutUK(uk1);
		sc->SetLine(line1);
	}
		


}

//��������� ��������
void TDiagram::I(Tree * v)
{
	TypeLex l; int t, t1, uk1 ,line1;

	Tree *k = Root->SemInclude("----", TYPE_UNKNOWN,sc);
	
	

	t = sc->Scaner(l);
	if(t != Tfls)
		sc->PrintError("�������� ������ {",l);
			
	bool flag = true;
	
	while (flag == true)
	{
		uk1 = sc->GetUK();
		line1 = sc->GetLine();
		t = sc->Scaner(l);		
		t1 = sc->Scaner(l);

		
		if ((t == Ttzpt) || (t == Twhile) ||
			(t == Treturn) || (t == Tfls) ||
			(t1 == Tsave) || (t1 == Tls))
		{
			sc->PutUK(uk1);
			sc->SetLine(line1);
			E(v);//��������
		}else if ((t == Tint) || (t == Tboolean))
		{
			sc->PutUK(uk1);
			sc->SetLine(line1);
			T(); //������
		}else if(t == Tfps)
 		{
			sc->PutUK(uk1);
			sc->SetLine(line1);
			flag = false;	
			Root->SetCur(k);
		}		
		else sc->PrintError("������",l);

		
	}

	t = sc->Scaner(l);
	if(t != Tfps)
		sc->PrintError("�������� ������ }",l);	
}

//While
void TDiagram::P(Tree *v)
{
	DATA_TYPE type = TYPE_BOOL;
	DATA_TYPE type1;

	TypeLex l; int t;
	t = sc->Scaner(l);
	if(t != Twhile)
		sc->PrintError("�������� ������ while",l);
	t = sc->Scaner(l);
	if(t != Tls)
		sc->PrintError("�������� ������ (",l);

	type1 = S();//���������	
	type = Root->Type_PR(type, type1, t, sc,l);

	t = sc->Scaner(l);	
	if(t != Tps)
		sc->PrintError("�������� ������ )",l);
	E(v);
}

//������ ���������� ����������
int TDiagram::O()
{
	TypeLex l; int t, uk1, line1;
	int k=0;
	uk1 = sc->GetUK();
	line1 = sc->GetLine();
	t = sc->Scaner(l);
	sc->PutUK(uk1);
	sc->SetLine(line1);
	if(t == Tint || t == Tboolean )
	{
		
		do
		{
			k++;
			t = sc->Scaner(l);
			if((t != Tint) && (t != Tboolean))
				sc->PrintError("�������� ��� ������",l);
			DATA_TYPE typ = Root->Type(l,sc);
			t = sc->Scaner(l);
			if(t != Tident)
				sc->PrintError("�������� �������������",l);
			Root->SemInclude(l,typ,sc);//������ �������� � �����
			uk1=sc->GetUK();
			line1 = sc->GetLine();
			t=sc->Scaner(l);
		} while (t == Tzpt);
		sc->PutUK(uk1);
		sc->SetLine(line1);
	}
	return k;
}

