#include<stdio.h>
int main()
{
	FILE *fp;
	char ch;
	fp=fopen("123","r");
	while((ch=fgetc(fp))!=EOF)
	{
		printf("%d\n",ch);
	}
}