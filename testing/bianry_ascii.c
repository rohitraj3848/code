#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	char a = 0b11110110;
	printf("%c\n", a);
	unsigned char data[] = "34567890";
	unsigned char data_str[32];
	memcpy(data_str, data, sizeof(data));
	printf("%ld\n", sizeof(data));
	printf("%c\n", data[3]);
	printf("%s\n", data);
	printf("%s\n", data_str);
}