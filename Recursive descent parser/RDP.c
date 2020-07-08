/*Grammar is : 
E->iE'
E'->+iE'/$*/


#include<stdio.h>
#include<string.h>

char l,str[20];
int loc=0;

void Edash()    
{ 
	int i;
    	if (l == '+') 
    	{
   		loc++;
   		l=str[loc];
	   	if(l=='i')
   		{
   			loc++;
   			l=str[loc];
   			Edash();
   		}
   		else
   			return;	   			
    	} 
    	else
	   	return;
} 

void E() 
{ 
    if(l == 'i') 
    {
		loc++;
		l=str[loc];
		Edash();
    }
} 


int main()
{
	int len;
	printf("Enter string to match : ");
	scanf("%s",str);
	
	len=strlen(str);
	str[len]='$';
	
	printf("\n\nGrammar is : \nE->iE'\nE'->+iE'/$\n\n");
	
	l=str[loc];
	
	E();
	
	if (l == '$')
     	printf("Parsing Successful\n");
     else
     	printf("Parsing Unsuccessful\n");
	return 0;
}

