//remove comments
#include<stdio.h>
extern char file[50];
//void main(int argc,char **argv)
void comments(void)
{
	FILE *fs,*fd;
	char ch;
	char z[20];
	int i=0;
	/*if(argc!=3)
	{
		printf("usage:./a.out fname fname.i\n");
		return;
	}*/
	//fs=fopen(argv[1],"r");
	fs=fopen(file,"r");
	for(i=0;file[i]!='.';i++)
	z[i]=file[i];
	z[i]=file[i];
	z[++i]='i';
	printf("%s",z);
	fd=fopen(z,"w");
	//fd=fopen(argv[2],"w");
	while((ch=fgetc(fs))!=-1)
	{
		if(ch=='/')
		{
			ch=fgetc(fs);
			if(ch=='/')
			{
				while((ch=fgetc(fs))!='\n');
			}
			else if(ch=='*')
			{
				while(1)
				{
					while((ch=fgetc(fs))!='*');
					ch=fgetc(fs);
					if(ch=='/')
						break;
					else
						continue;
				}
			}
			else
			{
			fseek(fs,-2,SEEK_CUR);
			ch=fgetc(fs);
			fputc(ch,fd);
			ch=fgetc(fs);
			fputc(ch,fd);
			}
		}
		else
		{
		fputc(ch,fd);
		}
	}
remove(file);
fclose(fd);
}
