#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char a = 0x23;
	printf("%d\n", a);
	unsigned char b[2];
	b[0] = (b[0] | (a  & 0x0F)) + '0';
	b[1] = (b[1] | ((a >> 4) & 0x0F)) + '0';
	printf("%c\n", b[0]);	
	printf("%c\n", b[1]);
	
        return 0;	
}
