#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct T
{
	char name[5];
	int add;
}T;

T sym[50],lit[50];
int sym_ind=0,lit_ind=0;

int search_add(char str[])
{
	char addr[3];
	int i,j=0;
	for(i=3; str[i]!=')' ; i++)
	{
		addr[j]=str[i];
		j++;
	}
	int ad;
	ad=atoi(addr);
	return ad;
}

int search_lit_add(char str[])
{
	char literal[5];
	int i,j=0;
	for(i=3; str[i]!=')' ; i++)
	{
		literal[j]=str[i];
		j++;
	}
	literal[j]='\0';
	for(i=0; i<lit_ind; i++)
	{
		if(strcmp(literal,lit[i].name)==0)
			break;
	}
	return i;
}

void is_handler(int l,char str1[],char str2[],char str3[])
{
	int i;
	FILE *fp;
	fp=fopen("Final_code.txt","a");
	fprintf(fp,"%d\t+",l);
	for(i=4; i<strlen(str1); i++)
	{
		if(str1[i]==')')
			break;
		fprintf(fp,"%c",str1[i]);
	}
	fprintf(fp,"\t%c\t",str2[3]);
	
	//printf("%s\n",str3);
	
	if(str3[1]=='S')
	{
		i=search_add(str3);
		fprintf(fp,"%d\n",i);
	}
	else if(str3[1]=='C')
	{
		fprintf(fp,"%c\n",str3[3]);
	}
	else
	{
		i=search_lit_add(str3);
		fprintf(fp,"%d\n",lit[i].add);
	}
	fclose(fp);	
}


void dl_handler(int l,char str1[],char str2[],char str3[])
{
	FILE *fp;
	fp=fopen("Final_code.txt","a");
	if(str1[4]=='1')
	{
		fprintf(fp,"%d\t00\t00\t%c\n",l,str3[3]);
	}
	else if(str1[4]=='2')
	{
		fprintf(fp,"%d\t00\t00\t00\n",l);
	}
	fclose(fp);
}

void l_handler(int l,char str3[])
{
	FILE *fp;
	int i;
	fp=fopen("Final_code.txt","a");
	fprintf(fp,"%d\t00\t00\t",l);
	i=2;
	while(str3[i]!='\'')
	{
		fprintf(fp,"%c",str3[i]);
		i++;
	}
	fprintf(fp,"\n");
	fclose(fp);
}

void copy_symbol_table()
{
	int l;
	char str1[10];
	FILE *fp;
	fp=fopen("Symbol_table.txt","r");
	while(fscanf(fp,"%s\t%d",str1,&l)!=EOF)
	{
		strcpy(sym[sym_ind].name,str1);
		sym[sym_ind].add=l;
		sym_ind++;
	}
	fclose(fp);
}

void copy_literal_table()
{
	int l;
	char str1[10];
	FILE *fp;
	fp=fopen("Literal_table.txt","r");
	while(fscanf(fp,"%s\t%d",str1,&l)!=EOF)
	{
		strcpy(lit[lit_ind].name,str1);
		lit[lit_ind].add=l;
		lit_ind++;
	}
	fclose(fp);
}

int main()
{
	int l,i;
	char str1[50],str2[50],str3[50];
	
	copy_symbol_table();
	copy_literal_table();
	
	FILE *fp1,*fp2;
	fp1=fopen("Final_code.txt","w");
	fclose(fp1);
	
	fp2=fopen("Intermediate_code.txt","r");
	
	while(fscanf(fp2,"%d\t%s\t%s\t%s",&l,str1, str2, str3)!=EOF)
	{		
		if(str1[1]=='A')
			continue;
		else if(str1[1]=='I')
			is_handler(l,str1,str2,str3);
		else if(str1[1]=='D')
			dl_handler(l,str1,str2,str3);
		else if(str1[1]=='-' && l!=00)
			l_handler(l,str3);
	}	
	fclose(fp2);
	
	/*fp2=fopen("Final_code.txt","r");
	while(fscanf(fp2,"%d\t%s\t%s\t%s",&l,str1, str2, str3)!=EOF)
	{
		printf("%d\t%s\t%s\t%s",l,str1, str2, str3);
	}
	fclose(fp2);*/
}
