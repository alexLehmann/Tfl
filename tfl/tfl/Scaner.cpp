#include "stdafx.h"
#include "Scaner.h"
#include "defs.h"



TScaner::TScaner(char *FileName)
{
	GetData(FileName);
	SetLine(1);
	PutUK(0);
}

void TScaner::SetLine(int value){line = value;}

int TScaner::GetLine(){return line;}

//�������� �����
TypeLex Keyword[MAX_KEYW] = { "class", "Main", "int", "boolean" , 
							 "while", "true", "false", "return"};


int IndexKeyword[MAX_KEYW] = { TClass, TMain, Tint, Tboolean,
							   Twhile, Ttrue, Tfalse, Treturn};

void TScaner::PutUK(int i){uk = i;} 

int TScaner::GetUK(void){return uk;}

void TScaner::PrintError(char *err, char *a)
{
	if(a[0] == '\0')
		printf("������ : %s %s\n", err, a);
	else 
		printf("������ : %s. �������� ������ %s  ������ %d\n ", err, a, line);
	exit(0);
}

void TScaner::GetData(char *FileName)
{
	char aa;
	FILE *in = fopen(FileName,"r");
	if(in == NULL) {
		PrintError("����������� ������� ����","");
		exit(1);
	}
	int i=0;
	while (!feof(in))
	{
		fscanf(in, "%c", &aa);
		if(!feof(in)) t[i++] = aa;
		if (i > MAX_TEXT-1)
		{
			PrintError("������� ������� ������ ��������� ������","");
			break;
		}
	}
	t[i]='\0';
	fclose(in);
}

int TScaner::Scaner(TypeLex l)
{
	int i; //������� ���� �������
	for (i = 0; i < MAX_LEX; i++) 
		l[i]=0;
	i=0;

while(true)
{

	while ((t[uk] == ' ') || (t[uk] == '\n') || (t[uk] == '\t'))
	{
		if(t[uk] == '\n') SetLine(GetLine()+1);
		uk++;
	}
	//�������� �� ���������� � ������� �� \n
	if ((t[uk] =='/') && (t[uk+1] == '/'))
	{
		uk=uk+2;
		while((t[uk] !='\n') && (t[uk] != '\0'))
		{
			uk++;
		}
		if(t[uk] == '\n')
		{
			//SetLine(GetLine()+1);
				//uk++;
		}
				
		continue;
	}
	break;
}
	//�������� �� �����
	if(t[uk] =='\0') 
	{
		l[0]='#';
		return Tend;
	}
	//�������� �� ��������
	if((t[uk] <= '9') && (t[uk] >= '0'))
	{
		if(t[uk] == '0' && (t[uk+1] == 'x' || t[uk+1] == 'X'))
		{
			l[i++] = t[uk++];
			l[i++] = t[uk++]; 
			while(((t[uk] <= '9') && (t[uk] >= '0')) || 
				(t[uk] <= 'F') && (t[uk] >= 'A'))
			if(i < MAX_LEX-1) 
				l[i++] = t[uk++];
			else uk++;
			
			return Tconst16;
		}
		else if (t[uk] == '0')
		{
			l[i++] = t[uk++]; 
			return Tconst10;
		}
		else
		{
			l[i++] = t[uk++];
			while ((t[uk] <= '9') && (t[uk] >= '0'))		
				if(i < MAX_LEX - 1) 
					l[i++] = t[uk++];
				else uk++;		
			
			return Tconst10;		
		}
	}	
	//�������� �� �������������
	else if ((t[uk] >= 'a') && (t[uk] <= 'z') ||
			(t[uk] >= 'A') && (t[uk] <= 'Z'))
	{ 
		//�������������
		bool flag = true;
		l[i++] = t[uk++];
		while((t[uk] <= '9') && (t[uk] >= '0') ||
			(t[uk] >= 'a') && (t[uk] <= 'z') ||
			(t[uk] >= 'A') && (t[uk] <= 'Z'))
			if(i < MAX_LEX-1)
				l[i++] = t[uk++];
			else 
			{
					uk++;
					flag = false;
			}

		int j; //�������� �� ���� �����
		for (j = 0; j < MAX_KEYW; j++)
			if(strcmp(l,Keyword[j])==0)
				return IndexKeyword[j];
		if(!flag)
			printf("������������� �������!\n");
		return Tident;

		//�������� �� ���� ����� � �������
	}else if (t[uk] == ',')
	{
		l[i++] = t[uk++];
		return Tzpt;
	}
	else if (t[uk] == ';')
	{
		l[i++] = t[uk++];
		return Ttzpt;
	}
	else if (t[uk] == '(')
	{
		l[i++] = t[uk++];
		return Tls;
	}
	else if (t[uk] == ')')
	{
		l[i++] = t[uk++];
		return Tps;
	}
	else if (t[uk] == '{')
	{
		l[i++] = t[uk++];
		return Tfls;
	}
	else if (t[uk] == '}')
	{
		l[i++] = t[uk++];
		return Tfps;
	}
	else if (t[uk] == '+')
	{
		l[i++] = t[uk++];
		return Tplus;
	}
	else if (t[uk] == '-')
	{
		l[i++] = t[uk++];
		return Tminus;
	}else if (t[uk] == '*')
	{
		l[i++] = t[uk++];
		return Tmult;
	}
	else if (t[uk] == '/')
	{
		l[i++] = t[uk++];
		return Tdiv;
	}
	else if (t[uk] == '%')
	{
		l[i++] = t[uk++];
		return  Tmod;
	}
	else if (t[uk] == '<')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=')
		{
			l[i++] = t[uk++];
			return Tle;
		}
		return Tlt;
	}
	else if (t[uk] == '>')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=')
		{
			l[i++] = t[uk++];
			return Tge;
		}
		return Tgt;
	}
	else if (t[uk] == '!')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=')
		{
			l[i++] = t[uk++];
			return Tneq;
		}
		return Tnot;
	}
	else if (t[uk] == '=')
	{
		l[i++] = t[uk++];
		if (t[uk] == '=')
		{
			l[i++] = t[uk++];
			return Teq;
		}
		return Tsave;
	}
	else if (t[uk] == '&' && t[uk+1] == '&')
	{
		l[i++] = t[uk++];
		l[i++] = t[uk++];
		return Tand;
	}
	else if (t[uk] == '|' && t[uk+1] == '|')
	{
		l[i++] = t[uk++];
		l[i++] = t[uk++];
		return Tor;
	}
	else
	{
		l[i]=t[uk];
		PrintError("�������� ������", l);
		uk++;
		return Terr;
	}

	
}