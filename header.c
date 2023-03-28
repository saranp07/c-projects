//including the header file  //case 1:if #include                <>
//case 2:if duplicate headers are there
#include<stdio.h>
#include<string.h>
//#include<dirent.h>
#include<stdlib.h>
//#define Macro printf
//#include<stdio.h>
char file[50];
char file1[50];
void comments(void);
void macro(void);
void main(int argc,char ** argv)
{
	if(argc!=2)
	{
		printf("usage:./a.out fname\n");
		return;
	}
	strcpy(file1,argv[1]);
	FILE *fp,*fd,*fh;
	char ch,**a,b[10]="#include";
	char ch1=0;
	int i=0,c=0,c1=0,c2=0,flag=0,k,l,m;
	//fp=fopen(argv[1],"r");
	for(i=0;argv[1][i]!='.';i++)
		file[i]=argv[1][i];
	file[i++]=argv[1][i];
	file[i]='s';
	fp=fopen(argv[1],"r");
	if(fp==0)
	{
		printf("source file not present\n");
		return;
	}
	fd=fopen(file,"w");
	while((ch=fgetc(fp))!=-1) //finding the #include match	
	{
		i=0;
		if(ch==b[i])
		{	if(ch1==0||ch1=='\n'||ch1==' ')//match if prev char is met above conditions
			{
				while((ch=fgetc(fp))!=-1)
				{
					if(ch!=b[++i])
						break;
				}
			}

		}
		if(b[i]=='\0')
		{
			if(ch==' ')
			{
				while((ch=fgetc(fp))!='\n')//case 1 satisfied
				{
					if(ch!=' ')
						break;
				}
			}
			if(ch=='<'||ch=='"')
			{
				c2++;		//finding header files count
				while((ch=fgetc(fp))!=-1)
				{	if(ch!='>'&&ch!='"')
					{
						c++;		//finding max size of header
					}
					else
						break;
				}

				if(c>c1)
				{
					c1=c;
				}
				c=0;
			}
		}
		ch1=ch;//holding present character
	}
	rewind(fp);
	ch1=0;
	///////////////////allocating sizes///////////
	a=malloc(sizeof(char *)*c2);
	for(i=0;i<c2;i++)
		a[i]=calloc((c1+1),sizeof(char));
	char d[c1+1];
	//////////////////////////////////////////////
	printf("%d %d\n",c2,c1);

	k=l=0;	
	while((ch=fgetc(fp))!=-1) //finding the #include match	
	{
		i=0;
		if(ch==b[i])
		{	if(ch1==0||ch1=='\n'||ch1==';')
			{
				while((ch=fgetc(fp))!=-1)
				{
					if(ch!=b[++i])
						break;
				}
			}

		}
		if(b[i]=='\0')
		{	
			if(ch==' ')
			{
				while((ch=fgetc(fp))!='\n')
				{
					if(ch!=' ')
						break;
				}
			}
			if(ch=='<'||ch=='"')//taking the header file name into temporary array for finding and avoiding duplicate in the array of header files
			{
				m=0;
				while((ch=fgetc(fp))!=-1)
				{	if(ch!='>'&&ch!='"')
					{
						d[m++]=ch;
						//	printf("%c",ch);
					}
					else
					{
						ch=fgetc(fp);
						d[m]='\0';
						//printf("%d ",k);
						break;
					}
				}
				for(i=0,c=0;i<c2;i++)//checking for duplicates header files
				{
					if(strcmp(a[i],d)==0)
						c++;
				}
				if(c==0)//if not matched update header file name
				{
					strcpy(a[k++],d);
				}
			}
		}
		ch1=ch;
	}	
	//for(i=0;i<k;i++)

	//	printf("%s\n",a[i]);
	char f[c1+20],cp[100];
	for(i=0;i<k;i++)
	{
		sprintf(f,"%s%s","./",a[i]);
		fh=fopen(f,"r");//concating direcory and headerfile name and searching in present working directory
		fseek(fd,0,SEEK_END);
		if(fh)
		{
			while((ch=fgetc(fh))!=-1)
				fputc(ch,fd);
			fputc('\n',fd);
			fclose(fh);
		}
	}
	for(i=0;i<k;i++)
	{
		sprintf(f,"%s%s","/usr/include/",a[i]);
		fh=fopen(f,"r");
		fseek(fd,0,SEEK_END);
		if(fh)
		{
			while((fgets(cp,100,fh)!=NULL))
				fputs(cp,fd);//storing into our o/p file
			fputc('\n',fd);
			fclose(fh);
		}
	}
	fclose(fd);
	fclose(fp);
	macro();//calling macro replacing fun
	comments();//calling comment removal function
}

