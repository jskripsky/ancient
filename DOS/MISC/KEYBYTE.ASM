	TITLE   Keyboard Status Byte Reader

	DOSSEG
	.MODEL  small

	.CODE
start:  mov ah, 02h
	int 16h

	and al, 0Fh

	mov ah, 4Ch
	int 21h

	END start
