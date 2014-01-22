#include<stdio.h>
#include<string.h>
 
struct tu
{
  char s[30];
  int i[100];
  int j;
  int z;
};
 
struct tu2
{
  char s[30];
};

void viethoa(char s[])
{
  int z,j;
  
  j=strlen(s);
  for(z=0;z<j;z++)
    {
      s[z]=tolower(s[z]);
    }
}

int locchuhoa(struct tu2 db3[],int i)
{
  int z;
  
  if(i>0){
    z=strlen(db3[i-1].s);
    if(!islower(db3[i].s[0]))
      {
	if(db3[i-1].s[z-1]=='.') return 1;
	else return 0;
      }
    else return 1;
  }
  else return 1;
}

void loaibo(char s[])
{
  int i;
  i=strlen(s);
  if(isalpha(s[i-1])==0)s[i-1]='\0';
}

int loaibo2(char s[])
{
  int i,j,z;
  z=0;
  i=strlen(s);
  for(j=0;j<i;j++)
    {
      if(isalpha(s[j]))z++;
    }
  if(z==i)return 1;
  else return 0;
}

int kiemtra(struct tu db[],struct tu2 db3[],struct tu2 db2[],int n,int m)
{
  int i,j,x,z;
  int x1,x2;
  z=0;
  
  for(i=0;i<n;i++)
    {
      x1=1;x2=1;
      x=locchuhoa(db3,i);
      loaibo(db3[i].s);
      for (j=0;j<z;j++)
	{
	  viethoa(db3[i].s);
	  if(strcmp(db[j].s,db3[i].s)==0) {x1=0; break;}
	}
      for(j=0;j<m;j++)
	{
	  viethoa(db3[i].s);
	  if(strcmp(db2[j].s,db3[i].s)==0) {x2=0;break;}
	}
      if(i==0 && x2==1 )
	{
	  loaibo(db3[i].s);
	  viethoa(db3[i].s);
	  strcpy(db[0].s,db3[i].s);
	  z++;
	}
      else {
	if(x1==1 && x2==1 &&x==1 &&loaibo2(db3[i].s)==1)
	  {
	    loaibo(db3[i].s);
	    viethoa(db3[i].s);
	    strcpy(db[z].s,db3[i].s);
	    z++;
	  }
      }
      //printf("%s %d \n",db3[i].s,x1);
    }
return z;
}

void sapxep(struct tu db3[],int n)
{
  int j,z;
  char s[30];
  for(j=0;j<n;j++)
    {
      for(z=0;z<n;z++)
	{
	  if(strcmp(db3[j].s,db3[z].s)==-1)
	    {
	      strcpy(s,db3[j].s);
	      strcpy(db3[j].s,db3[z].s);
	      strcpy(db3[z].s,s);
	    }
	}
    }
}

void main()
{
  FILE *f1,*f2,*f3;
  struct tu db[15000];
  struct tu2 db2[15000],db3[15000],db4[15000];
  char s[30],s2[81];
  int i,m,n,j,z,p,q,h;
  char * pch;
  
  f1=fopen("unnikatha.txt","r");
  f2=fopen("stopw.txt","r");
  f3=fopen("kqbt1.txt","w+");
  
  if(f1!=NULL && f2!=NULL)
    {
      i=-1;
      while(fscanf(f2,"%s",s)!=EOF)
	{
	  i+=1;
	  strcpy(db2[i].s,s);
	  //printf("%s\n",db2[i].s);
	};
      m=i+1;
      i=0;
      while(fscanf(f1,"%s",s)!=EOF)
	{
	  strcpy(db3[i].s,s);
	  i++;
	}
      n=i;
      z=kiemtra(db,db3,db2,n,m);
      sapxep(db,z);
      for(j=0;j<z;j++)
	{
	  db[j].j=0;
	  db[j].z=0;
	}
      
      rewind(f1);
      h=1;
      while(fgets (s2, 80, f1) != NULL)
	{
	  i=0;
	  pch=strtok(s2," ,.()");
	  while(pch != NULL)
	    {
	      viethoa(pch);
	      strcpy(db4[i].s,pch);
	      //printf("%s \n",db4[i].s);
	      i++;
	      pch=strtok(NULL," ,.()");
	    }
	  for(j=0;j<z;j++)
	    {
	      p=0;
	      for(q=0;q<=i;q++)
		{
		  if(strcmp(db[j].s,db4[q].s)==0)
		    {
		      if(p==0)
			{
			  db[j].i[db[j].z]=h;
			  db[j].z++;
			  db[j].j++;
			  p=1;
			}
		      else db[j].j++;
		    }
		}
	    }
	  h++;
	}
    }
   for(j=0;j<z;j++)
    {
      printf("%s    so lan: %d   ",db[j].s,db[j].j);
      printf("Dong : ");
      for(i=0;i<db[j].z;i++)printf("%d ",db[j].i[i]);
      printf("\n\n");
      }
}
