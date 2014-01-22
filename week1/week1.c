#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct kitu
{
	char tu[50];
};

struct word
{
	int col;
	char wor[25];
};
struct word2
{
	char wor[30];
	int solan;
};
void loaibo(char wor[])
{
int i;
i=strlen(wor);
if(isalpha(wor[i-1])==0)wor[i-1]='\0';
}

int open1(FILE *f,struct word str1[])
{
	int m=0;
	char c;
	char string[25];
	int i,line=1,end_sen=0;
	int k;
while(!feof(f))
	{	i=0;k=0;
	do{
		c=fgetc(f);
		if(c=='.') end_sen=1;
		if((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='-')
		{
		if (end_sen==1 && c>='A' && c<='Z') 
		k=1; end_sen=0;
		string[i]=c;
		i++;
		}
		else
		{
		if(c=='\r') line++;
		string[i]='\0';
		break;
		}
	}while(1);
	
	if(strlen(string)>1)
	{
		if(!(k!=1 && string[0] >='A' && string[0]<='Z'))
		{
            if(string[0]>='A'&& string[0]<='Z') string[0]+=32;
            loaibo(string);
	strcpy(str1[m].wor,string);
	str1[m].col=line;
	m++;}
	}
	}
	return m;
	}


int open2(FILE *f,struct kitu str2[])
{
	char buff[10];
	int n=0,i;
	char c;
	char buf[80];
	while(!feof(f))
	{	i=0;
	do{
		c=fgetc(f);
		if(c!='\n'){
		if((c>='a' && c<='z') || (c>='A' && c<='Z'))
		{
		buff[i]=c;
		i++;
		}
		else
		{
		buff[i]='\0';
		break;
		}}
		}while(1);
		if(strlen(buff)>0)
		{
		loaibo(buff);
		strcpy(str2[n].tu,buff);
		n++;
		}
	}
	return n;
}

int sosanh(struct word str1[],struct word str3[],struct kitu str2[],int m, int n)
{
int i,j,k=0;
int x,x1;
int z=0;
for(i=0;i<m;i++)
{	x=1;
	/*for (j=0;j<z;j++)
	{
	if(strcmp(str2[j].tu,str1[i].wor)==0) {x1=0; break;}
	}*/
	for(j=0;j<n;j++)
	{
		if(strcmp(str2[j].tu,str1[i].wor)==0)
		{x=0;break;}

	}
	if(x==1)
	{strcpy(str3[z].wor,str1[i].wor);
			str3[z].col=str1[i].col;
			z++;}
	
}
return z;
}

void sapxep(struct word str1[], int n)
{

	int i,j;
	struct word tmp;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(strcmp(str1[i].wor,str1[j].wor)<0)
			{
				tmp=str1[i];
				str1[i]=str1[j];
				str1[j]=tmp;
			}
		}
	}
}



int final1(struct word2 str4[],struct word str3[],int m)
{
	int i,j;
	int k=1,z=0;

	for (i = 0; i < m; i++)
	{
			if(strcmp(str3[i].wor,str3[i+1].wor)==0)
			{
				k++;
			}
			else
			{
			strcpy(str4[z].wor,str3[i].wor);
			str4[z].solan=k;
			z++;
			k=1;
			}
	}
	return z;
}


void final(struct word2 str4[],struct word str3[],int m, int n,FILE *f3)
{
	int i,j;
	int dem[100];
	for(i=0;i<m;i++)
	{	
		printf("%s  %d ",str4[i].wor,str4[i].solan);
		fprintf(f3, "%s  %d ",str4[i].wor,str4[i].solan);
		for(j=0;j<n;j++)
		{ 
			if(strcmp(str4[i].wor,str3[j].wor)==0) 
			{
				printf("  %d", str3[j].col);
				fprintf(f3, "  %d", str3[j].col);
			}
		}
		printf("\n");
		fprintf(f3, "\n");
	}
}

int main(void)
{
	FILE *f1,*f2,*f3;
	struct word str1[200];
	struct kitu str2[80];
	struct word str3[200];
	struct word2 str4[200];
	int i,m,z,n,tong;
	int j,k=0,dem;

	f1=fopen("vanban.txt","r");
	f2=fopen("stopw.txt","r");
	f3=fopen("ketqua.txt","w+");
	if(f1==NULL || f2==NULL) 
	{
		printf("File khong ton tai\n");
	}
	z=open2(f2,str2);
	m=open1(f1,str1);
	j=sosanh(str1,str3,str2,m,z);
	sapxep(str3,j);
	tong=final1(str4,str3,j);
	final(str4,str3,tong,j,f3);
	return 0;
	}

