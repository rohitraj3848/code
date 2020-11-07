stdin equ 0
stdout equ 1
SYS_WRITE equ 4
SYS_EXIT  equ 1

section .data
msg1 db 'hello ,programmmers!',0xA,0xD
len1 equ $-msg1
msg2 db 'welcome to the world of,',0xA,0xD
len2 equ $-msg2
msg3 db 'Linux assembly programming ! '
len3 equ $-msg3

section .text
	global _start
	_start:
			mov eax,SYS_WRITE
			mov ebx,stdout
			mov edx,len1
			mov ecx,msg1
			int 0x80

			mov eax,SYS_WRITE
			mov ebx,stdout
			mov edx,len2
			mov ecx,msg2
			int 0x80

			mov eax,SYS_WRITE
			mov ebx,stdout
			mov edx,len3
			mov ecx,msg3
			int 0x80

			mov eax,SYS_EXIT
			int 0x80