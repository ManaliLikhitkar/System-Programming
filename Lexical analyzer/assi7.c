#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

typedef struct kt
{
	char name[10];
	int brk;
	char token[5];
}kt;

kt KT[29]={{"if",0,"key1"},{"else",0,"key2"},{"while",0,"key3"},{"for",0,"key4"},{"int",0,"key5"},{"char",0,"key6"},{"stdio.h",0,"key7"},{"stdlib.h",0,"key8"},{"string.h",0,"key9"},{"include",0,"key10"},{"(",1,"("},{")",1,")"},{"{",1,"{"},{"}",1,"}"},{"[",1,"["},{"]",1,"]"},{"=",1,"="},{"\"",1,"\""},{"'",1,"'"},{";",1,";"},{" ",1," "},{"+",1,"+"},{"-",1,"-"},{"*",1,"*"},{"/",1,"/"},{"%",1,"%"},{"#",1,"#"},{"<",1,"<"},{">",1,">"}};


typedef struct ust
{
	char name[10];
	char table;
	int pos;
}ust;
ust UST[50];
int UST_ind=0;


typedef struct tab
{
	char id[10];
	char token[5];
}tab;
tab sym_tab[20],lit_tab[20];
int sym_tab_ind=0,lit_tab_ind=0;


int search_ter(char c)
{
	int i;
	for(i=10; i<29; i++)
	{
		if(c==KT[i].name[0])
			return 1;
	}
	return 0;
}

int search(char key[])
{
	int i;
	for(i=0; i<29; i++)
	{
		if(strcmp(KT[i].name,key)==0)
			return i;
	}
	return -1;
}

void put_UST(char key[], int pos, char table)
{
	strcpy(UST[UST_ind].name,key);
	UST[UST_ind].table=table;
	UST[UST_ind].pos=pos;
	UST_ind++;
}

void put_symbol(char key[])
{
	int i;
	
	if(!search(key))
	for(i=1; key[i]!='\0'; i++)
	{
		if(isalpha(key[i]) || isdigit(key[i]))
			continue;
		else
		{
			printf("Invalid token : %s",key);
			return;
		}
	}
	char tok[5]="ID";
	char no[5];
	sprintf(no,"%d",sym_tab_ind+1);
	strcat(tok,no);
	
	for(i=0; i<sym_tab_ind; i++)
	{
		if(strcmp(sym_tab[i].id,key)==0)
			break;
	}
	
	if(i==sym_tab_ind)
	{
		strcpy(sym_tab[sym_tab_ind].id,key);
		strcpy(sym_tab[sym_tab_ind].token,tok);			
		sym_tab_ind++;
	}
	put_UST(key,sym_tab_ind-1,'S');	
}

void put_literal(char key[])
{	
	int i;
	if(isdigit(key[0]))
	{
		for(i=0; key[i]!='\0'; i++)
		{
			if(!isdigit(key[i]))
			{
				printf("Invalid token : %s",key);
				return;
			}			
		}
	}
	char tok[5]="L";
	char no[5]="";
	sprintf(no,"%d",lit_tab_ind+1);
	strcat(tok,no);
	
	for(i=0; i<lit_tab_ind; i++)
	{
		if(strcmp(lit_tab[i].id,key)==0)
			break;
	}
	
	if(i==lit_tab_ind)
	{
		strcpy(lit_tab[lit_tab_ind].id,key);
		printf("\n%s",lit_tab[lit_tab_ind].id);
		strcpy(lit_tab[lit_tab_ind].token,tok);	
	
		lit_tab_ind++;
	}
	put_UST(key,lit_tab_ind-1,'L');	
}

void handler(char buf[])
{
	int pos=-1,flag=1;
	int fp=0,bp=0;
	int i,j=0;
	char key[10];
	while(buf[fp]!='\0')
	{
		j=0;
		flag=1;
		if(buf[fp]=='/' && buf[fp+1]=='/')
			return;
		if(search_ter(buf[fp]))
		{
			if(buf[fp]=='"')
				flag=0;
			if(bp<fp)
			{			
				for(i=bp; i<fp; i++)
				{
					key[j]=buf[i];
					j++;
				}
				key[j]='\0';
			}
			else
			{
				key[0]=buf[fp];
				key[1]='\0';
				fp++;
			}
			if(key[0]!='"' && flag==0)
			{
				put_literal(key);
				bp=fp;
			}
			else
			{
				pos=search(key);
				if(pos!=-1)
				{
					if(key[0]!=' ')
						put_UST(key,pos,'K');				
				}
				else
				{
					if(isalpha(key[0]))
					{
						put_symbol(key);		
					}
					else if(isdigit(key[0]))
					{
						put_literal(key);
					}	
				}
				bp=fp;
			}
			
		}
		else
			fp++;
	}
}

int main()
{
	int i;
	char buf[30];	
	FILE *fp;
	fp=fopen("Input_code.txt","r");	
	while(fgets(buf,30,fp)!=NULL)
	{
		handler(buf);
	}
	fclose(fp);
	
	printf("\n\nUniform Symbol Table:\n\n");
	for(i=0; i<UST_ind; i++)
	{
		printf("%s\t %c\t%d\n",UST[i].name,UST[i].table,UST[i].pos);
	}
	
	printf("\n\nSymbol Table:\n\n");
	for(i=0; i<sym_tab_ind; i++)
	{
		printf("%s\t%s\n",sym_tab[i].id,sym_tab[i].token);
	}
	
	printf("\n\nLiteral Table:\n\n");
	for(i=0; i<lit_tab_ind; i++)
	{
		printf("%s\t%s\n",lit_tab[i].id,lit_tab[i].token);
	}
}
