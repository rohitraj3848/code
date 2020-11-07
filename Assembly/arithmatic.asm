segment .data
msg1 db "Enter a digit ",0xa,0xd
len1 equ $-msg1

msg2 db "please enter a second digit",0xa,0xd
len2 equ $-msg2

msg3 db "the sum is:-"
len3 equ $-msg3

msg4 db "the diff is:-"
len4 equ $-msg4

segment .bss
	num1 resb 2
	num2 resb 2
	sum resb 1

segment .text
	global _start
	_start:
		mov eax,4
		mov ebx,1
		mov ecx,msg1
		mov edx,len1
		int 0x80

		mov eax,3
		mov ebx,0
		mov ecx,num1
		mov edx,2
		int 0x80

		mov eax,4
		mov ebx,1
		mov ecx,num1
		mov edx,2
		int 0x80


		mov eax,4
		mov ebx,1
		mov ecx,msg2
		mov edx,len2
		int 0x80


		mov eax,3
		mov ebx,0
		mov ecx,num2
		mov edx,2
		int 0x80

		mov eax,4
		mov ebx,1
		mov ecx,num2
		mov edx,len2
		int 0x80


		mov eax,[num1]
		sub eax,'0'
		mov ebx,[num2]
		sub eax,'0'

		add eax,ebx
		add eax,'0'
		mov [sum],eax

		mov eax,4
		mov ebx,1
		mov ecx,msg3
		mov edx,len3
		int 0x80


		mov eax,4
		mov ebx,1
		mov ecx,sum
		mov edx,1
		int 0x80

		mov eax,1
		int 0x80

