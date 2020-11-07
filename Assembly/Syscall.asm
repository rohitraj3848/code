section .data
	userMsg db 'Please enter a number :'
	lenUsrMsg equ $-userMsg
	DispMsg db 'you have entered: '
	lenDispMsg equ $-DispMsg

section .bss
	num resb 5

section .text
	global _start
	_start:
	mov eax,4
	mov ebx,1
	mov ecx,userMsg
	mov edx,lenUsrMsg
	int 0x80


	;read and store the user input
	mov eax,3
	mov ebx,2
	mov ecx,num
	mov edx,5
	int 0x80

	;output the message
	mov eax,4
	mov ebx,1
	mov ecx,DispMsg
	mov edx,lenDispMsg
	int 0x80

	;output the numbered entered
	mov eax,4
	mov ebx,1
	mov ecx,num
	mov edx,5
	int 0x80

	;exit code
	mov eax,1
	mov ebx,0
	int 0x80