#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int l=0;
int sym_loc=0;

typedef struct MOT
{
		char mne[7];
		int code;
		int size;
		char type[3];
}MOT;

typedef struct T
{
		char name[5];
		int add;
}T;

T sym[50],lit_table[50]; //lit_pool is literal table
int lit_table_index=0,lit=0; //lit_pool_index is literal table index and lit_loc is pool index

MOT m[10]={{"add",1,5,"IS"},{"sub",2,7,"IS"},{"mul",3,10,"IS"},{"div",4,12,"IS"},{"bc",5,0,"IS"},{"dc",1,1,"DL"},{"ds",2,0,"DL"},{"ltorg",1,1,"AD"},{"end",0,0,"AD"},{"equ",2,0,"AD"}};
MOT reg[4]={{"areg",1,0,""},{"breg",2,0,""},{"creg",3,0,""},{"-",0,0,""}};


int search_reg(char str[])
{
		int j=-1;
		for(j=0; j<4; j++)
		{
			if(strcmp(reg[j].mne,str)==0)
				break;
		}
		return j;
}

void label_handle(char str1[])
{
    int k;
    for(k=0; k<sym_loc; k++)
    {
        if(strcmp(sym[k].name,str1)==0)
            break;
    }
    if(k==sym_loc)
    {
        strcpy(sym[k].name,str1);
        sym[k].add=l;
        sym_loc++;
    }
}

void lit_handle(char str4[])
{
    int k;
    for(k=lit; k<lit_table_index; k++)
    {
        if(strcmp(str4,lit_table[k].name)==0)
            break;
    }
    if(k==lit_table_index)
    {
        strcpy(lit_table[lit_table_index].name,str4);
        lit_table[lit_table_index].add=0;
        lit_table_index++;
    }
}

void sym_handle(char str4[])
{
    int k;
    for(k=0; k<sym_loc; k++)
    {
        if(strcmp(sym[k].name,str4)==0)
            break;
    }
    if(k==sym_loc)
    {
        strcpy(sym[k].name,str4);
        sym[k].add=-1;
        sym_loc++;
    }
}

void is_handler(char str1[],char str2[],char str3[],char str4[],int i)
{
		FILE *fp1;
		fp1=fopen("Intermediate_code.txt","a");
		int j;
		j=search_reg(str3);

		if(strcmp(str1,"-")!=0)
            label_handle(str1);

		int len;
		len=strlen(str4);
		if(strcmp(str4,"-")!=0)
		{
		    if(str4[1]=='\'' && str4[len-1]=='\'' && str4[0]=='=')
		    {
                lit_handle(str4);
		    	fprintf(fp1,"%d\t(%s,%d)\t(R,%d)\t(L,%s)\n",l,m[i].type,m[i].code,reg[j].code,str4);
		    }
		    else if((str4[0]>=65 && str4[0]<=91) || (str4[0]>=97 && str4[0]<=122))
		    {
                sym_handle(str4);
				fprintf(fp1,"%d\t(%s,%d)\t(R,%d)\t(S,%d)\n",l,m[i].type,m[i].code,reg[j].code,sym_loc-1);
		    }
		    else if(isdigit(str4[0]))
		    {
		        fprintf(fp1,"%d\t(%s,%d)\t(R,%d)\t(C,%s)\n",l,m[i].type,m[i].code,reg[j].code,str4);
		    }
		    else
		    {
		    	printf("Error : Invalid operand 2\n");
		    	return;
		    }
		}
		l=l+m[i].size;
		fclose(fp1);
}


void dl_handler(char str1[],char str2[],char str3[],char str4[],int i)
{
		FILE *fp1;
		fp1=fopen("Intermediate_code.txt","a");
		int k;
		if(strcmp(str1,"-")==0)
		{
		    printf("Error : No symbol found!\n");
		    return;
		}
		if(strcmp(str3,"-")!=0)
		{
		    printf("Error : Register not allowed\n");
		    return;
		}
		for(k=0; k<sym_loc; k++)
		{
		    if(strcmp(sym[k].name,str1)==0)
		    {
		        if(sym[k].add==-1)
		            sym[k].add=l;
		        else
		            printf("Error : Duplicate entries!\n");
		        break;
		    }
		}
		if(k==sym_loc)
		{
		    strcpy(sym[sym_loc].name,str1);
		    sym[sym_loc].add=l;
		    sym_loc++;
		}
		fprintf(fp1,"%d\t(%s,%d)\t---\t(C,%s)\n",l,m[i].type,m[i].code,str4);
		if(strcmp(m[i].mne,"ds")==0)
		{
		    int a;
		    a=atoi(str4);
		    l=l+a;
		}
		l=l+m[i].size;
		fclose(fp1);
}


void ad_handler(char str1[],char str2[],char str3[],char str4[],int i)
{
		FILE *fp1;
		fp1=fopen("Intermediate_code.txt","a");
		int j;
		if(strcmp(str2,"ltorg")==0)
		{
			fprintf(fp1,"%d\t(%s,%d)\t---\t---\n",l,m[i].type,m[i].code);
			l++;
			for(j=lit; j<lit_table_index; j++)
			{
				fprintf(fp1,"%d\t---\t---\t%s\n",l,lit_table[j].name);
				lit_table[j].add=l;
				l++;				
			}			
			lit=lit_table_index;
		}
		else if(strcmp(str2,"end")==0)
		{
			for(j=lit; j<lit_table_index; j++)
			{
				lit_table[j].add=l;
				l++;
			}
			fprintf(fp1,"---\t---\t---\t---\n");
		}
		else if(strcmp(str2,"equ")==0)
		{
		    for(j=0; j<sym_loc; j++)
		    {
		        if(strcmp(str1,sym[j].name)==0)
		        {
		            sym[j].add=atoi(str4);
		            break;
		        }
		    }
		    if(j==sym_loc)
		    {
		        strcpy(sym[sym_loc].name,str1);
		        sym[sym_loc].add=atoi(str4);
		        sym_loc++;
		    }
		}
		fclose(fp1);
}


int check_start(char str[])
{
		if(strcmp(str,"START")!=0)
		{
			printf("\nError!!\nNo START found!\n\n");
			exit(0);
		}
		return 1;
}


int search_mnemonic(char str[])
{
		int i=-1;
		for(i=0; i<11; i++)
		{
			if(strcmp(m[i].mne,str)==0)
				break;
		}
		if(i==11)
		    return -1;
		return i;
}


int main()
{
		FILE *fp,*fp1,*fp2;

		fp1=fopen("Intermediate_code.txt","w");
		fclose(fp1);

		int i;
		char str1[5],str2[5],str3[5],str4[10];
		fp=fopen("sample.txt","r");
		fscanf(fp,"%s %d",str1,&l);
		if(check_start(str1))
		{
			while(fscanf(fp,"%s %s %s %s",str1, str2, str3, str4)!=EOF)
			{
				i=search_mnemonic(str2);
				if(i==-1)
				{
					printf("\nError : Mnemonic missing!\n");
					continue;
				}

				if(strcmp(m[i].type,"IS")==0)
					is_handler(str1, str2, str3, str4,i);
				else if(strcmp(m[i].type,"DL")==0)
					dl_handler(str1, str2, str3, str4,i);
				else if(strcmp(m[i].type,"AD")==0)
					ad_handler(str1, str2, str3, str4,i);
			}
		}
		fclose(fp);

		fp1=fopen("Intermediate_code.txt","r");
		printf("Intermediate code:\n");
		char c = fgetc(fp1);
		while (c != EOF)
		{
		    printf ("%c", c);
		    c = fgetc(fp1);
		}
		fclose(fp1);

		fp2=fopen("Symbol_table.txt","w");
		printf("\n\nSymbol Table:\n");
		for(i=0; i<sym_loc; i++)
		{
			printf("%s\t%d\n",sym[i].name,sym[i].add);
			fprintf(fp2,"%s\t%d\n",sym[i].name,sym[i].add);
		}
		fclose(fp2);
		
		fp2=fopen("Literal_table.txt","w");

		printf("\n\nLiteral Table:\n");
		for(i=0; i<lit_table_index; i++)
		{
			fprintf(fp2,"%s\t%d\n",lit_table[i].name,lit_table[i].add);
			printf("%s\t%d\n",lit_table[i].name,lit_table[i].add);
		}
		fclose(fp2);
}
