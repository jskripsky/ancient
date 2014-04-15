	TITLE   Weekday Reader

	DOSSEG
	.MODEL  small

	.CODE
start:  mov     ah, 2Ah
	int     21h

	mov     ah, 4Ch
	int     21h

	END     start
