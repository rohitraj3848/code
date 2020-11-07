#include<stdio.h>

int read_str(void){
	char buff[128];
	int i;
	fgets(buff);
	i=atoi(buff);
	return i;
}

int main(int ac,char **argv){
	int x=read_str();
	printf("x=%d\n",x);
}