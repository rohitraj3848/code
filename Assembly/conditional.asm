section .data
	msg db "the largest digit is :",0xa,0xd
	len equ $-msg
	num1 dd '47'
	num2 dd '22'
	num3 dd '31'

section .bss
	largest resb 2


section .text
	global _start
	_start:
		mov ecx,[num1]
		cmp ecx,[num2]
		jg  check_third_sum
		mov ecx,[num2]

	check_third_sum:
		cmp ecx,[num3]
		jg  _exit
		mov ecx,[num3]

	_exit:
		mov [largest],word ecx
		mov ecx,msg
		mov edx,len
		mov ebx,1
		mov eax,4
		int 0x80

		mov ecx,largest
		mov edx,2
		mov eax,4
		mov ebx,1
		int 0x80
