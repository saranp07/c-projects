#include<stdio.h>
#include<stdlib.h>
#include<string.h>
extern char file1[50];
extern char file[50];
void macro(void)
//void main(int argc,char **argv)
{	
	/*if(argc!=2)
	{
		printf("usage:./a.out filename.c\n\033[31mcompilation terminated\n\033[0m");
		return;
	}*/
	FILE *fp;
	FILE *fd;
	int i,c=0,c1=0,c2=0,j,c3=0,c4=0,c5=0,flag=0,l=0,m=0;
	static int k;
	char ch,ch1=0,name[50];
	char a[10]="#define";
	/*char *filename=__FILE__;//extracting the file name
	  for(i=0;file[i]!='.';i++)
	  z[i]=file[i];
	  z[i++]=file[i];
	  z[i]='i';*/
	fp=fopen(file1,"r");
	fd=fopen(file,"r+");
	if(fp)
	printf("source file is present %s",file1);
	if(fd)
	printf("o/p file is present %s",file);
	fseek(fd,0,SEEK_END);
	//fgets(name,50,fd);
	//printf("%s",name);
	fputc('\n',fd);
	while((ch=fgetc(fp))!=-1)//finding the #define match
	{	
		i=0;
		if(ch==a[i])
		{	if(ch1==0||ch1=='\n'||ch1==' ')//ch1 is a variable  that follow the present character(main clue throughout out the preprocessor)//consider #define only when previous characters are 1)starting of file 2)if prev char is '\n' 3)if prev char is ' '
			{
			while((ch=fgetc(fp))!=-1)
			{
				if(ch!=a[++i])
					break;
			}
			}
		
		}
		if(a[i]=='\0')    //as we don't know sizeof macro first find the size*/
		{
			c2++;
			flag=0;
			while((ch=fgetc(fp))!=-1)
			{	if(flag==0&&ch!=' ')
				{
					c++;
				}
				else if(ch==' '&&flag==0)/*including the						sizeof line continuity '/' */
				{
					flag=1;
				}
				else if(ch!='\\'&&ch!='\n')
				{
					c4++;
				}
				else if(ch=='\\')
				{
					fgetc(fp);
				}
				else if(ch=='\n')
					break;
			}

			if(c>c1)
			{
				c1=c;//finding the size of largest macro						name size
			}
			if(c4>c5)
			{
				c5=c4;//finding the size of largest macro    						body
			}
			c=0;
			c4=0;
		}
		ch1=ch;
	}
	//printf("macros:");
	//printf("%d %d %d\n",c1,c5,c2);
	/////////// allocating memory ////////////////////
	char **p,**q;
	p=malloc(sizeof(char *)*c2);//for macro name
	q=malloc(sizeof(char *)*c2);//for macro body
	for(i=0;i<c2;i++)
	{
		q[i]=calloc(c1+1,sizeof(char));
		p[i]=calloc(c5+1,sizeof(char));
	}
	rewind(fp);
	ch1=0;
	//////// storing #define matches////////////////////
	while((ch=fgetc(fp))!=-1)
	{		i=0;
		if(ch==a[i])/////////////finding #define to exclude
		{
			if(ch1==0||ch1=='\n'||ch1==' ')
			{
			while((ch=fgetc(fp))!=-1)
			{
				if(ch!=a[++i])
					break;
			}
			}
		}
		if(a[i]=='\0')//once if #define match is found with above					condition 
		{	j=0;	
			fscanf(fp,"%s",q[k]);//extracting macro name
			ch=fgetc(fp);
			while((ch=fgetc(fp))!=-1)
			{	

				if(ch!='\n'&&ch!='\\')
					p[k][j++]=ch;//extracting macro body 					to the corresponding macro name index
				else if(ch=='\\')
				{	
					fgetc(fp);
				}
				else if(ch=='\n')
				{
					p[k++][j]='\0';
					break;
				}
			}
		}
		ch1=ch;
	}
	//printf("%s%s\n%s\n%s\n%s\n%s\n",q[0],p[0],q[1],p[1],q[2],p[2]);
	printf("%s %s",q[0],p[0]);
	/////////////replacing macros////////////////
	rewind(fp);
	k=j=0;
	ch1=0;
	while((ch=fgetc(fp))!=-1)//finding and removing preprocessor directives
	{	
		i=0;
		if(ch==a[i])
		{
			if(ch1==0||ch1=='\n'||ch1==' ')
			{
				while((ch=fgetc(fp))!=-1)
				{
					if(ch=='\\')
					{
						fgetc(fp);
					}
					else if(ch=='\n')
						break;
				}
			}
			else
			fputc(ch,fd);//for including'#'Ex:printf("#define");
		}
		else			//find the macro name and replacing with macro body
		{	
			if(!((ch1>='a'&&ch1<='z')||(ch1>='A'&&ch1<='Z')))//these condt is replace a macro name if previous char is not an alphabet      Ex:if pf is macro name,printpf here pf should not replace
			{
				for(c=0,k=0;k<c2;k++)//checking every char for macroname match;
				{
					for(j=0;j<(c1+1);j++)
					{
						if(ch!=q[k][j])	
							break;
						else{
							c++;
							ch=fgetc(fp);
						}
					}
					if(q[k][j]=='\0'&&(!((ch>='a'&&ch<='z')||(ch>='A'&&ch<='Z'))))//if macro name matched and prev char is not aplhabet then replace it with corresponding index macro body
					{j=0;
						while(p[k][j]!='\0')
						{
							//printf("%c",p[k][j]);	
							fputc(p[k][j],fd);
							j++;
						}
						//printf("%c",ch);
						fputc(ch,fd);
						break;
					}
					else if(c>0)//if macroname is half matched then we want to retrive filepointer to back we use this condt
					{
						fseek(fp,-(c+1),SEEK_CUR);
						ch=fgetc(fp);
						c=0;
					}
				}
			}
			if(k==c2)//if character not matched we are coping itinto our file
			{
				//printf("%c",ch);
				fputc(ch,fd);
			}
		}
		if(ch=='"')//excluding the " "part from checking for macro name
		{
			while((ch=fgetc(fp))!='"')
				//printf("%c",ch);
				//printf("%c",ch);
				fputc(ch,fd);
			fputc(ch,fd);
		}
		ch1=ch;//catching present char,before it loaded with new char
	}
	fclose(fd);
	//remove(a);
}
