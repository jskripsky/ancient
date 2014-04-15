TITLE RS232DRV Ver 1.07 (c) 1992 University of Berne, Switzerland, Lab_KL
;
;*****************************************************************************
;									     *
; PROGRAM  : RS232DRV.ASM						     *
; COPYRIGHT: (c) 1992 University of Berne, Switzerland			     *
; REVISION : 1.07							     *
; DATE	   : 5-May-92							     *
; PURPOSE  : Driver to communicate with COM-ports from most HLL via INT 14h  *
;	     Interrupt driven with hardware or software handshake option     *
; REMARKS  : COM3 and COM4 ports only with XT-type bus (IRQ4,IRQ3 resp.)     *
; COPYRIGHT: Parts from IBMCOM.PAS by Pascalaholics Anonymous, CIS	     *
;*****************************************************************************
;*****************************************************************************
;									     *
; REV	  DATE	     BY 		PURPOSE 			     *
; -----   --------   ---------		----------------------------------   *
; 1.00	   12-Jun-90  A. Pluess 	Adapted from RS232UNI (no INT 14h)   *
; 1.01	   16-Jun-90  A. Pluess 	No CTRL/S at intall time	     *
; 1.02	   30-Aug-90  A. Pluess 	STI at begin of int.routine	     *
; 1.03	    1-Mar-91  A. Pluess 	Include DTR handling		     *
; 1.04	    5-Mar-92  A. Pluess 	Bug: RTS remained inactive	     *
; 1.05	   29-Mar-92  A. Pluess 	At init: RTS,DTR active, don't send ^Q *
;					At installation: RTS, DTR active     *
; 1.06	   14-Apr-92  A. Pluess 	Minor syntax modificatins	     *
; 1.07	    5-May-92  A. Pluess 	Baud rate option for midi baudrate   *
;*****************************************************************************
; INTERFACE:								     *
; All request are done with INT 14. On entry the function number is in AH    *
; Characters to send or receive are in AL				     *
; All other registers are preserved (exept Function 0)			     *
; The port is initialized by installing the driver			     *
;									     *
; Functions:								     *
; ---------								     *
; ----------------- Function 00h ------------------------------------------- *
; AH 00    AL --      : Search for communication driver at port 1,..,4	     *
;			If found clear TXBUF & RXBUF and		     *
;			activate RTS and DTR
; return:								     *
; AL  comm.port 1,..,4 (where driver is found)				     *
; BX  1234h   Driver identification code				     *
; If BX does not contain this value, the driver is (probably) not present    *
;									     *
; ----------------- Function 01h ------------------------------------------- *
; AH 01    AL char    : Wait until TXBUF is not full, put it in TXBUF	     *
; return:		and transmit it 				     *
; AH 00h   no error (character in TXBUF)
; AH 01h   TXBUF full (character lost)
;									     *
; ----------------- Function 02h ------------------------------------------- *
; AH 02    AL --      : Return last char from RXBUF if available	     *
; return:								     *
; AL character received 						     *
; AH 00h   no error							     *
;    01h   no character available					     *
;									     *
; ----------------- Function 03h ------------------------------------------- *
; AH 03    AL --       : Test if TXBUF is full				     *
; return:								     *
; AH 00    TXBUF is not full						     *
; AH 01    TXBUF is full						     *
;									     *
; ----------------- Function 04h ------------------------------------------- *
; AH 04    AL --       : Test if RXBUF is empty 			     *
; return:								     *
; AH 00    RXBUF is not empty						     *
; AH 01    RXBUF is empty						     *
;									     *
; ----------------- Function 05h ------------------------------------------- *
; AH 05    AL --       : Wait until TXBUF is not full, put CTRL/S in TXBUF,  *
; return:  --		 send it and clear CTRL/S-flag			     *
;									     *
; ----------------- Function 06h ------------------------------------------- *
; AH 06    AL --       : Check if CTRL/S-flag is cleared, wait until TXBUF   *
; return:  --		 is not full, put CTRL/Q in TXBUF and send it	     *			     *
;									     *
; ----------------- Function 07h ------------------------------------------- *
; AH 07    AL --       : Desactivate RTS				     *
; return:  --								     *
;									     *
; ----------------- Function 08h ------------------------------------------- *
; AH 08    AL --       : Activate RTS					     *
; return:  --								     *
;									     *
; ----------------- Function 09h ------------------------------------------- *
; AH 09    AL --       : Detect carrier 				     *
; return:								     *
; AH 00    No carrier present						     *
; AH 01    Carrier detect						     *
;
; ----------------- Function 0Ah ------------------------------------------- *
; AH 0A    AL --       : Desactivate DTR				     *
; return:  --								     *
;									     *
; ----------------- Function 0Bh ------------------------------------------- *
; AH 0B    AL --       : Activate DTR					     *
; return:  --								     *
;									     *
;------------------ End of INT 14 functions ---------------------------------
;
%NOINCL
%NOMACS
%LINUM 4
%BIN 8
; -----------------------------------------------------------------------
;
; Summary of IBM-PC Asynchronous Adapter Registers.  From:
;    Compute!'s Mapping the IBM PC and PCjr, by Russ Davis
;    (Greensboro, North Carolina, 1985: COMPUTE! Publications, Inc.),
;    pp. 290-292.
;
;  Addresses given are for COM1 and COM2, respectively.  The names given
;  in parentheses are the names used in this module.
;
;
;  3F8/2F8 (uart_data) Read: transmit buffer.  Write: receive buffer, or baud
;  rate divisor LSB if port 3FB, bit 7 = 1.
;
;  3F9/2F9 (uart_ier) Write: Interrupt enable register or baud rate divisor
;  MSB if port 3FB, bit 7 = 1.
;  PCjr baud rate divisor is different from other models;
;  clock input is 1.7895 megahertz rather than 1.8432 megahertz.
;  Interrupt enable register:
;      bits 7-4  forced to 0
;      bit 3	 1=enable change-in-modem-status interrupt
;      bit 2	 1=enable line-status interrupt
;      bit 1	 1=enable transmit-register-empty interrupt
;      bit 0	 1=data-available interrupt
;
;  3FA/2FA (uart_iir) Interrupt identification register (prioritized)
;	bits 7-3  forced to 0
;	bits 2-1  00=change-in-modem-status (lowest)
;	bits 2-1  01=transmit-register-empty (low)
;	bits 2-1  10=data-available (high)
;	bits 2-1  11=line status (highest)
;	bit 0	  1=no interrupt pending
;	bit 0	  0=interrupt pending
;
;  3FB/2FB (uart_lcr) Line control register
;	bit 7  0=normal, 1=address baud rate divisor registers
;	bit 6  0=break disabled, 1=enabled
;	bit 5  0=don't force parity
;	       1=if bit 4-3=01 parity always 1
;		 if bit 4-3=11 parity always 0
;		 if bit 3=0 no parity
;	bit 4  0=odd parity,1=even
;	bit 3  0=no parity,1=parity
;	bit 2  0=1 stop bit
;	       1=1.5 stop bits if 5 bits/character or
;		 2 stop bits if 6-8 bits/character
;	bits 1-0  00=5 bits/character
;		  01=6 bits/character
;		  10=7 bits/character
;		  11=8 bits/character
;
;	bits 5..3: 000 No parity
;		   001 Odd parity
;		   010 No parity
;		   011 Even parity
;		   100 No parity
;		   101 Parity always 1
;		   110 No parity
;		   111 Parity always 0
;
;
;  3FC/2FC (uart_mcr) Modem control register
;	bits 7-5  forced to zero
;	bit 4	  0=normal, 1=loop back test
;	bits 3-2  all PCs except PCjr
;	bit 3	  1=interrupts to system bus, user-designated output: OUT2
;	bit 2	  user-designated output, OUT1
;	bit 1	  1=activate rts
;	bit 0	  1=activate dtr
;
;  3FD/2FD (uart_lsr) Line status register
;	bit 7  forced to 0
;	bit 6  1=transmit shift register is empty
;	bit 5  1=transmit hold register is empty
;	bit 4  1=break received
;	bit 3  1=framing error received
;	bit 2  1=parity error received
;	bit 1  1=overrun error received
;	bit 0  1=data received
;
;  3FE/2FE (uart_msr) Modem status register
;	bit 7  1=receive line signal detect
;	bit 6  1=ring indicator (all PCs except PCjr)
;	bit 5  1=dsr
;	bit 4  1=cts
;	bit 3  1=receive line signal detect has changed state
;	bit 2  1=ring indicator has changed state (all PCs except PCjr)
;	bit 1  1=dsr has changed state
;	bit 0  1=cts has changed state
;
;   B3FF/2FF (uart_spr) Scratch pad register
; --------------------- End of initial comment --------------------------
;
	INCLUDE DOSMAC.INC
; for testing purposes only:
	INCLUDE UTIL.INC
;
; --------------------- Constants ----------------------------------------
ID_CODE_LOW	EQU 1358h		; ID to check if program is loaded
ID_CODE_HIGH	EQU 0FCA8h		;
;
CTRL_Q		EQU	11h		; ^Q
CTRL_S		EQU	13h		; ^S
MIN_CHAR	EQU	5		; # of char in rx_queue to send ^Q
MAX_CHAR	EQU	60		; # of char in rx_queue to send ^S
;
INT_14		EQU	14h		; BIOS Interrupt 14h
; ********************* Program Section *********************************
CODE		SEGMENT
		ASSUME CS:CODE
		ORG 100H
START:		JMP INIT		; Jump to start of code
;
INT_NUM 	DB  ?			; Interrupt number of port
I8259LEVEL	DB  ?			; Interrupt controller level of port
COM_PORT	DB  ?			; Number of communication port (1..4)
PROG_ID 	DW  ?			; Place to store the program ID
		DW  ?			;
;
; UART 8259 addresses for selected port
UART_BASE	DW  ?			; Base address of UART
UART_DATA	DW  ?			; Transmit/Receive buffer
UART_IER	DW  ?			; Interrupt enable
UART_IIR	DW  ?			; Interrupt identification
UART_LCR	DW  ?			; Line control
UART_MCR	DW  ?			; Modem control
UART_LSR	DW  ?			; Line status
UART_MSR	DW  ?			; Modem status
UART_SPR	DW  ?			; Scratch pad
;
; Original content to restore UART to whatever it was before
OLD_IER 	DB  ?			; Value of IER before installation
OLD_MCR 	DB  ?			; Value of MCR before installation
;
OLD_VECTOR	DW  2 DUP (?)		; Original interrupt vector
;
OLD_I8259_MASK	DB  ?			; Original int.contr.mask
;
I8259_BIT	DB  ?			; Bit mask for i8259 controller
;
HANDSHAKE	DW  0			; Indicate handshake option:
					; 0: no handshake
					; 1: hardware handshake (CTS/RTS)
					; 2: software handshake (^Q/^S)
;
RTS_FLAG	DW  0			; Flag for hardware handshake
					; to prevent rx-queue overflow
					; 0: normal case (RTS active)
					; 1: not used
					; 2: Host waiting (RTS passive)
					; 3: not used
;
CTRL_S_FLAG	DW  0			; Flag for ^Q/^S handshake
					; to prevent rx-queue overflow
					; 0: normal case
					; 1: ^S pending (must be sent)
					; 2: Host waiting (^S has been sent)
					; 3: ^Q pending (must be sent)
;
WAIT_TRM_FLAG	DW  0			; Flag for host handshake
					; 0: transmit to host
					; 1: wait for transmission to host
;
TEST_B0 	DW  0			; For testing purposes
TEST_B1 	DW  0			; idem
;
; Receive queue
RX_QUEUE_SIZE	EQU 120 		; Size in chars of receive queue
RX_HEAD 	DW  ?			; Address of where to retrieve next char
RX_TAIL 	DW  ?			; Address of where to store next char
RX_BUF		DW  RX_QUEUE_SIZE DUP (?)  ; Buffer start
RX_BUF_END	LABEL WORD		; One step beyond the end
RX_CHARS	DW  ?			; Number of chars in queue
;
; Transmit queue
TX_QUEUE_SIZE	EQU 32			; Size in chars of trmit queue
TX_HEAD 	DW  ?			; Address of where to retrieve next char
TX_TAIL 	DW  ?			; Address of where to store next char
TX_BUF		DW  TX_QUEUE_SIZE DUP (?) ; Buffer start
TX_BUF_END	LABEL WORD		; One step beyond the end
TX_CHARS	DW  ?			; Number of chars in queue
;
;
OLD_VECTOR_14	DW  2 DUP (?)		; Old interrupt vector of INT 14
;
; ************* Interrupt routine for hardware interrupt *******************
;
COM_INT 	PROC
		PUSH DS 		; Save registers
		PUSH SI
		PUSH DI
		PUSH DX
		PUSH CX
		PUSH BX
		PUSH AX
;
; On entry, DS points to something unknown, all memory references
; must be addressed with new DS
; (Alternative: ASSUME DS:NOTHING will force to use segment prefix whenever
;  memory is referenced.)
;
	ASSUME DS:CODE
		MOV DX,CS
		MOV DS,DX
; The following line may be included or not whether you want enable
; other interrupts or not
		STI			; Enable interrupts from other sources.
					; Interrupts with nr higher than
					; this comm.port are still inhibited
					; because int.contr. will no serve them
; Identify interrupt and get character
AGAIN:		MOV DX,UART_IIR 	; Get interrupt identification
		IN  AL,DX		;
		TEST AL,1		; Is another interrupt to handle?
		JE  DO_PROCESS		; Yes--> process it
		JMP QUIT_COM_INT	; otherwise quit

DO_PROCESS:	SHR AL,1		; get rid of first bit
		CMP AL,10B		; was IIR=100 (from receiver) ?
		JNE INT_L1		; no-->continue
		JMP GET_CHAR		; Yes--> get char
INT_L1: 	CMP AL,01B		; was IIR=010 (from transmitter) ?
		JNE INT_L101		; no-->continue
		JMP SEND_CHAR		; Yes--> transmit char
INT_L101:	CMP AL,00B		; was IIR=000  (from modem status) ?
		JNE INT_L1001		; no-->continue
		JMP  CHANGE_MODEM	; (should not happen) Yes--> reset it
INT_L1001:	JMP  CHANGE_LINE	; it was IIR=110  (from line status)
					; (should not happen) -->reset it
;
GET_CHAR:	MOV DX,UART_DATA	; Prepare for data
		IN  AL,DX		; Take char in AL
		CMP HANDSHAKE,2 	; Check handshake option
		JNE NOSOFT		; No software handshake
		CMP AL,CTRL_S		; Is it a ^S to stop transmission?
		JE  GOT_CTRLS		; yes-->we got a ^S
		CMP AL,CTRL_Q		; Is it a ^Q to resume transmission?
		JE  GOT_CTRLQ		; yes-->we get a ^Q
;
NOSOFT: 	INC RX_CHARS		; Increase char count
		MOV DI,RX_TAIL		; Get pointer
		MOV [DI],AL		; Store char
		INC RX_TAIL		; Advance "Tail"
		CMP RX_TAIL,OFFSET RX_BUF_END ; Passed the end of buffer?
		JNE BETWEEN		; no--> simple case
		MOV RX_TAIL,OFFSET RX_BUF ; set "Tail" at begin of buffer
;
BETWEEN:	CMP HANDSHAKE,0 	; Check handshake option
		JNE DO_HANDSHAKE	; 0--> no handshake
		JMP AGAIN		; and see if another interrupt waiting
;
DO_HANDSHAKE:	CMP RX_CHARS,MAX_CHAR	    ; Have we to stop host?
		JE  STOP_HOST		; yes-->do it
		JMP AGAIN		; no-->see if another interrupt waiting
;
STOP_HOST:	CMP HANDSHAKE,1 	; Is hardware handshake selected?
		JNE SOFT_HAND_SEL	; no-->software handshake
		MOV DX,UART_MCR 	; Prepare address
		IN  AL,DX		; to get MCR
		AND AL,0FDh		; Clear bit #1 (lower RTS)
		OUT DX,AL		; and out it goes
		MOV RTS_FLAG,2		; Mark host is waiting (RTS passive)
		JMP AGAIN		; See if anogher interrupt waiting
;
SOFT_HAND_SEL:	MOV CTRL_S_FLAG,1	; Mark pending ^S
		MOV DX,UART_LSR 	; Prepare to get LSR
		IN  AL,DX		; into AL
		TEST AL,00100000B	; Test if bit #5 is set(hold reg. empty)		 JNE INT_L10		 ; yes-->send char immediately
		JNE INT_L10		; yes-->transmit ^S immediately
		JMP AGAIN		; no--> transmit on next tx interrupt
INT_L10:	MOV AL,CTRL_S		; Prepare
		MOV DX,UART_DATA	; for data
		OUT DX,AL		; and send it to UART
		MOV CTRL_S_FLAG,2	; Mark we have sent a ^S to stop trmit
		JMP AGAIN		; see if another interrupt waiting
;
GOT_CTRLS:	MOV WAIT_TRM_FLAG,1	; Mark to stop transmission
		JMP AGAIN		; see if another interrupt waiting
;
GOT_CTRLQ:	MOV WAIT_TRM_FLAG,0	; Mark to resume transmission
		MOV DX,UART_IER 	; Prepare to
		IN  AL,DX		; get IER
		OR  AL,2h		; set bit #1 (transmit-empty interrupt)
		OUT DX,AL		; enable transmit interrupt
		JMP QUIT_COM_INT
;
SEND_CHAR:	CMP WAIT_TRM_FLAG,1	; Is wait flag set?
		JE  DO_NOT		; yes-->do not transmit
		MOV AX,TX_HEAD		; Is transmit queue empty?
		CMP AX,TX_TAIL		; Head = Tail?
		JNZ TRANSMIT		; no-->transmit char
DO_NOT: 	MOV DX,UART_IER 	; Prepare to get IER
		IN  AL,DX		; to disable interrupt
		AND AL,11111101B	; clear interrupt enable bit
		OUT DX,AL		; and write it into IER
		JMP AGAIN		; See if another interrupt waiting
;
TRANSMIT:
; The test of the line-status-register is to see if the transmit
; holding register is truly empty.
		MOV DX,UART_LSR 	; Prepare to get LSR
		IN  AL,DX		; into AL
		TEST AL,00100000B	; Test if bit #5 is set
		JNE INT_L2		; yes-->continue
		JMP AGAIN		; no--> transmit hold register not empty
;
INT_L2: 	CMP CTRL_S_FLAG,1	; see if pending ^S
		JNE CONT1		; no-->continue
		MOV AL,CTRL_S		; Prepare
		MOV DX,UART_DATA	; for data and
		OUT DX,AL		; send ^S to UART
		MOV CTRL_S_FLAG,2	; mark we have sent a ^S to stop trmit
		JMP AGAIN		; see if another interrupt waiting

CONT1:		CMP CTRL_S_FLAG,3	; see if pending ^Q
		JNE CONT2		; no-->continue
		MOV AL,CTRL_Q		; Prepare
		MOV DX,UART_DATA	; for data and
		OUT DX,AL		; send ^Q it to UART
		MOV CTRL_S_FLAG,0	; reset ^S flag
		JMP AGAIN		; see if another interrupt waiting
;
CONT2:		DEC TX_CHARS		; Decrease char count
		MOV SI,TX_HEAD		; Get address of character
		MOV AL,[SI]		; and fetch it
		MOV DX,UART_DATA	; Prepare for data
		OUT DX,AL		; and send it to UART
		INC TX_HEAD		; Advance "Head"
		CMP TX_HEAD,OFFSET TX_BUF_END ; Passed the end of buffer?
		JNE BETWE		; no--> simple case
		MOV TX_HEAD,OFFSET TX_BUF  ; set "Head" at begin of buffer
BETWE:		JMP AGAIN		; see if there is another interrupt
;
CHANGE_MODEM:	MOV DX,UART_MSR 	; Read MSR
		IN  AL,DX
		TEST AL,1		; Is bit #1 set?
		JNE CTS_CHANGE		; yes-->CTS changed state
		JMP AGAIN		; no-->do nothing
;
CTS_CHANGE:	TEST AL,10h		; Is bit #4 set (CTS active)?
		JNE CTS_UP		; yes-->resume transmission
		MOV WAIT_TRM_FLAG,1	; otherwise mark stop of transmission
		JMP AGAIN		; and see if there is another interrupt
CTS_UP: 	MOV WAIT_TRM_FLAG,0	; Mark to resume transmission
		MOV DX,UART_IER 	; Prepare to
		IN  AL,DX		; get IER
		OR  AL,2h		; Set bit #1 (transmit-empty int)
		OUT DX,AL		; and out it goes
		JMP QUIT_COM_INT
;
CHANGE_LINE:	MOV DX,UART_LSR 	; Read LSR
		IN  AL,DX
		JMP AGAIN		; and do nothing
;
; Tell the interrupt controller this interrupt is served
QUIT_COM_INT:
		MOV AL,20h		;
		OUT 20h,AL		;
;
		POP AX			; Restore registers
		POP BX
		POP CX
		POP DX
		POP DI
		POP SI
		POP DS
		IRET			; Return from interrupt
;
COM_INT 	ENDP
; ///////////////////// End of hardware interrupt routine /////////////////
;
; *************** Interrupt  routine for INT 14 **********************
BIOS_INT	PROC
		PUSH DS 		; Save registers
		PUSH ES
		PUSH SI
		PUSH DI
		PUSH DX
		PUSH CX
		PUSH BX
; On entry DS points to something unknown, initialize DS to code segment
	ASSUME DS:CODE
		MOV DX,CS
		MOV DS,DX
;
		CMP AH,5		; Function HIGH? (binary search)
		JGE FUNC_HIGH
		CMP AH,0		; Function 0?
		JE  FUNC_0
		CMP AH,1		; Function 1?
		JE  FUNC_1
		CMP AH,2		; Function 2?
		JE  FUNC_2
		CMP AH,3		; Function 3?
		JE  FUNC_3
		CMP AH,4		; Function 4?
		JE  FUNC_4
		JMP FUNC_ILLEGAL
FUNC_HIGH:
		CMP AH,5		; Function 5?
		JE  FUNC_5
		CMP AH,6		; Function 6?
		JE  FUNC_6
		CMP AH,7		; Function 7?
		JE  FUNC_7
		CMP AH,8		; Function 8?
		JE  FUNC_8
		CMP AH,9		; Function 9?
		JE  FUNC_9
		CMP AH,0Ah		; Function 0Ah?
		JE  FUNC_0A
		CMP AH,0Bh		; Function 0Bh?
		JE  FUNC_0B
		JMP FUNC_ILLEGAL
;
FUNC_0: 	CALL COM_INIT
		POP DX			; Take BX from stack
		PUSH BX 		; and replace it with new value
		JMP QUIT_BIOS_INT
;
FUNC_1: 	CALL COM_TX
		JMP QUIT_BIOS_INT
;
FUNC_2: 	CALL COM_RX
		JMP QUIT_BIOS_INT
;
FUNC_3: 	CALL COM_TX_FULL
		JMP QUIT_BIOS_INT
;
FUNC_4: 	CALL COM_RX_EMPTY
		JMP QUIT_BIOS_INT
;
FUNC_5: 	CALL COM_SEND_CTRLS
		JMP QUIT_BIOS_INT
;
FUNC_6: 	CALL COM_SEND_CTRLQ
		JMP QUIT_BIOS_INT
;
FUNC_7: 	CALL COM_LOWER_RTS
		JMP QUIT_BIOS_INT
;
FUNC_8: 	CALL COM_RAISE_RTS
		JMP QUIT_BIOS_INT
;
FUNC_9: 	CALL COM_CARRIER
		JMP QUIT_BIOS_INT
;
FUNC_0A:	CALL COM_LOWER_DTR
		JMP QUIT_BIOS_INT
;
FUNC_0B:	CALL COM_RAISE_DTR
		JMP QUIT_BIOS_INT
;
FUNC_ILLEGAL:	MOV AX,0FFFFh		; Indicate error
;
QUIT_BIOS_INT:	POP BX			; Restore registers
		POP CX
		POP DX
		POP DI
		POP SI
		POP ES
		POP DS
		IRET			; Return from interrupt
;
BIOS_INT	ENDP
; ///////////////////// End of interrupt routine ////////////////////////
;
; Resident procedures:
;
; --------------------- Initialize driver ---------------------------
COM_INIT	PROC NEAR
		CALL COM_FLUSH_RX	; Flush RXBUF
		CALL COM_FLUSH_TX	; Flush TXBUF
		CALL COM_RAISE_RTS	; Activate RTS
		CMP HANDSHAKE,0 	; Is handshake selected?
		JE QUIT_COM_INIT	; no-->all done
		CMP HANDSHAKE,1 	; Is hardware handshake selected?
		JE  QUIT_COM_INIT	; yes-->all done
QUIT_COM_INIT:	MOV BX,1234h		; Return identification
		MOV AL,COM_PORT 	; Return communication port number
		RET
COM_INIT	ENDP
;
; --------------------- Return AH=1 if receive buffer is empty ------
COM_RX_EMPTY	PROC NEAR
		CMP RX_CHARS,0		; See if buffer empty
		JNE NOTEMPTY		; no-->indicate 'not empty'
		MOV AH,1		; Set flag to indicate 'empty'
		RET
NOTEMPTY:	MOV AH,0		; set flag to indicate 'not empty'
		RET
COM_RX_EMPTY	ENDP
;
; --------------------- Get a character in AL from receive queue --------
COM_RX		PROC NEAR
		CMP RX_CHARS,0		; Are there any chars?
		JE NOCHAR		; no-->indicate 'no character'
; First check handshake option
		CMP HANDSHAKE,0 	; Have we handshake selected?
		JE  TAKE_CHAR		; no-->don't worry about handshake
		CMP HANDSHAKE,1 	; Have we hardware handshake selected?
		JNE RX_SOFT		; no-->software handshake
;
		CMP RX_CHARS,MIN_CHAR	; Have we to reactivate host?
		JNE TAKE_CHAR		; no--> take char from queue
		CMP RTS_FLAG,2		; Is host waiting for reactivtion?
		JNE TAKE_CHAR		; no--> take char from queue
		CALL COM_RAISE_RTS	; Resume host transmission
		MOV RTS_FLAG,0		; Reset RTS flag
		JMP TAKE_CHAR		; and get char
;
RX_SOFT:	CMP RX_CHARS,MIN_CHAR	; Have we a ^Q to send?
		JNE TAKE_CHAR		; no--> take char from queue
		CMP CTRL_S_FLAG,2	; Is transmitter waiting for ^Q?
		JNE TAKE_CHAR		; no--> take char from queue
		MOV CTRL_S_FLAG,3	; Mark pending ^Q
		MOV DX,UART_LSR 	; Prepare to get LSR
		IN  AL,DX		; into AL
		TEST AL,00100000B	; Test if bit #5 is set (hold reg. epty)
		JE  TAKE_CHAR		; no-->send it on next interrupt
		MOV AL,CTRL_Q		; Prepare
		MOV DX,UART_DATA	; for data and
		OUT DX,AL		; send ^Q it to UART
		MOV CTRL_S_FLAG,0	; reset ^S flag
;
TAKE_CHAR:	CLI			; Disable interrupts
		MOV SI,RX_HEAD		; Get address of 'Head'
		MOV AL,[SI]		; Get char
		INC RX_HEAD		; Adjust pointer
		CMP RX_HEAD,OFFSET RX_BUF_END ; passed end of buffer?
		JNE BTWEN		; no-->simple case
		MOV RX_HEAD,OFFSET RX_BUF ; set 'Head' to begin of buffer
BTWEN:		DEC RX_CHARS		; Decrease number of chars
		STI			; Enable interrupts
		MOV AH,0		; Indicate no error
		RET			; and return
NOCHAR: 	MOV AH,1		; Indicate error
		RET			; and return
COM_RX		ENDP
;
; --------------------- Return AH=1 if transmit buffer is full ---------
COM_TX_FULL	PROC NEAR
		CMP TX_CHARS,TX_QUEUE_SIZE ; see if buffer full
		JE  TX_FULL		; yes-->indicate 'full'
		MOV AH,0		; Set flag to indicate 'not full'
		RET
TX_FULL:	MOV AH,1		; Set flag to indicate 'TXBUFF_FULL'
		RET
COM_TX_FULL	ENDP
;
; --------------------- Send a character in AL -------------------------
; Send a character.  If TXBUF is not full,  put it in TXBUF;
; otherwise return error code.
; The interrupt driver will send the character
; once the character is at the head of the transmit queue and a transmit
; interrupt occurs
COM_TX		PROC NEAR
		CALL COM_TX_FULL	; Check if buffer is not full
		CMP AH,1		; return value in AH
		JE  FULL		; Not ready for transmission
		CLI			; Disable interrupts
		MOV DI,TX_TAIL		; Get index of char
		MOV [DI],AL		; Store char
		INC TX_TAIL		; Adjust pointer
		CMP TX_TAIL,OFFSET TX_BUF_END ; passed end of buffer?
		JNE BTWEEN		; no-->simple case
		MOV TX_TAIL,OFFSET TX_BUF ; set 'Tail' to begin of buffer
BTWEEN: 	INC TX_CHARS		; Increase number of chars
		MOV DX,UART_IER 	; Prepare to
		IN  AL,DX		; get IER
		OR  AL,2h		; set bit #1 (transmit-empty interrupt)
		OUT DX,AL		; enable transmit interrupt
		STI			; enable all interrupts
		MOV AH,0		; Indicate no error
		RET
;
FULL:		MOV AH,1		; Indicate character lost
		RET
COM_TX		ENDP
;
; --------------------- Send Ctrl/Q immediately ------------------------
QUICKSEND_CTRLQ PROC NEAR
		MOV DX,UART_LSR 	; Prepare to get LSR
		IN  AL,DX		; into AL
SEND_LOOP:	TEST AL,00100000B	; Test if bit #5 is set(hold reg. empty)
		JE  SEND_LOOP		; no-->wait until ready
		MOV AL,CTRL_Q		; Prepare
		MOV DX,UART_DATA	; for data and
		OUT DX,AL		; send ^Q it to UART
		RET
QUICKSEND_CTRLQ ENDP
;
; --------------------- Desactivate DTR (Pin 20) ---------------------------
COM_LOWER_DTR	PROC NEAR
		CLI
		MOV DX,UART_MCR 	; Prepare address
		IN  AL,DX		; Get present state
		AND AL,0FEh		; Clear bit #0
		OUT DX,AL		; and out it goes
		STI
		RET
COM_LOWER_DTR	ENDP
;
; --------------------- Activate DTR (Pin 20) ---------------------------
COM_RAISE_DTR	PROC NEAR
		CLI
		MOV DX,UART_MCR 	; Prepare address
		IN  AL,DX		; Get present state
		OR  AL,1		; Set Bit #0
		OUT DX,AL		; and out it goes
		STI
		RET
COM_RAISE_DTR	ENDP
;
; --------------------- Desactivate RTS (Pin 4) ---------------------------
COM_LOWER_RTS	PROC NEAR
		CLI
		MOV DX,UART_MCR 	; Prepare address
		IN  AL,DX		; Get present state
		AND AL,0FDh		; Clear bit #1
		OUT DX,AL		; and out it goes
		STI
		RET
COM_LOWER_RTS	ENDP
;
; --------------------- Activate RTS (Pin 4) ---------------------------
COM_RAISE_RTS	PROC NEAR
		CLI
		MOV DX,UART_MCR 	; Prepare address
		IN  AL,DX		; Get present state
		OR  AL,2		; Set Bit #1
		OUT DX,AL		; and out it goes
		STI
		RET
COM_RAISE_RTS	ENDP
; --------------------- Flush Receiver Buffer ---------------------------
COM_FLUSH_RX	PROC NEAR
		CLI
		MOV BX,OFFSET RX_BUF	; Get start address
		MOV RX_HEAD,BX		; Initialize
		MOV RX_TAIL,BX		;
		MOV RX_CHARS,0		; Number of chars is zero
		STI
		RET
COM_FLUSH_RX	ENDP
;
; --------------------- Flush Transmitter Buffer ------------------------
COM_FLUSH_TX	PROC NEAR
		CLI
		MOV BX,OFFSET TX_BUF	; Get start address
		MOV TX_HEAD,BX		; Initialize
		MOV TX_TAIL,BX		;
		MOV TX_CHARS,0		; Number of chars is zero
		STI
		RET
COM_FLUSH_TX	ENDP
;
; --------------------- Return AH=1 if carrier is present --------------
COM_CARRIER	PROC NEAR
		MOV DX,UART_MSR 	; Prepare to
		IN AL,DX		; get MSR
		TEST AL,10000000B	; is bit #7 set?
		JE  NOCARRIER		; no-->set flag to 0
		MOV  AH,1		; otherwise set flag to 1
		RET			; and leave
NOCARRIER:	MOV  AH,0		; Clear flag
		RET
COM_CARRIER	ENDP
;
; --------------------- Send CTRL/S and clear CTRL/S flag --------------
COM_SEND_CTRLS	PROC NEAR
		MOV AL,CTRL_S		; Put CTRL/S in AL and send it
		CALL COM_TX		; in TXBUFF
		MOV CTRL_S_FLAG,0	; Clear CTRL/S flag
		RET
COM_SEND_CTRLS	ENDP
;
;-------------- Check if CTRL-flag is cleared and send CTRL/Q -----------
COM_SEND_CTRLQ	PROC NEAR
		CMP CTRL_S_FLAG,0      ; Check CTRL/S flag
		JNE DO_NOT_SEND
		MOV AL,CTRL_Q		; Put CTRL/Q in AL and send it
		CALL COM_TX		; in TXBUFF
DO_NOT_SEND:	RET
COM_SEND_CTRLQ	ENDP
;
; ********************* Main program ************************************
;
INIT:					; Setup routine
		JMP BEGIN		; Jump over data block
;
TEST_MSG	DB  'Test-Message is executed.',13,10,'$'
MSG1_MAIN	DB  'RS232DRV-Driver V1.07 (Univ. of Berne-Switzerland, KL)',13,10,'$'
MSG4_MAIN	DB  'No handshake selected.',13,10,'$'
MSG5_MAIN	DB  'Hardware handshake (CTS/RTS) selected.',13,10,'$'
MSG6_MAIN	DB  'Software handshake (CTRL/Q-CTRL/S) selected.',13,10,'$'
;
MSG3_MAIN	DB  'Replacement of BIOS INT 14.',13,10,10
		DB	13,10,' Usage:   RS232DRV COMn:bb,p,d,s,h'
		db	13,10,'               n = com port 1, 2, 3 or 4'
		db	13,10,'              bb = baud rate (see table below)'
		db	13,10,'               p = parity   N, E or O'
		db	13,10,'               d = databits 8, 7, 6 or 5'
		db	13,10,'               s = stopbits 1 or 2'
		db	13,10,'               h = handshake option N, H or S'
		db	13,10,'                   (None, Hardware: RTS/CTS, Software: ^Q/^S)'
		db	13,10
		db	13,10,'                  50 = 50      75 = 75      110 = 11'
		db	13,10,'                 134 = 13     150 = 15      300 = 30'
		db	13,10,'                 600 = 60    1200 = 12     1800 = 18'
		db	13,10,'                2000 = 20    2400 = 24     3600 = 36'
		db	13,10,'                4800 = 48    7200 = 72     9600 = 96'
		db	13,10,'               19200 = 19   38400 = 38    57600 = 57'
		db	13,10,'               31250 = 31   MIDI interface (4MHz clk)'
		db	13,10,'               (use no parity, 8 databits, 1 stopbit)'
		db	13,10
		db	13,10,' To deinstall call it a second time.'
		db	13,10,'$'
;
;-----------------------------------------------------------------------------
BEGIN:
		DISP MSG1_MAIN		; Startup message
		CALL SET_PORT		; Setup port parameters/deinstall
		CALL COM_INSTALL	; Install communication driver
		CALL INT14_INSTALL	; Install replacement of BIOS INT 14
		CALL COM_RAISE_DTR	; Raise DTR
		CMP  HANDSHAKE,0	; Check handshake option:
		JNE  NOT_ZERO		; handshake selected
		DISP MSG4_MAIN		; Say handshake option
		JMP  MAKE_RES		; and continue
NOT_ZERO:	CMP  HANDSHAKE,1	; Check handshake option:
		JNE  SOFT_HAND		; software handshake selected
		DISP MSG5_MAIN		; Say handshake option
		JMP  MAKE_RES		; and continue
SOFT_HAND:	DISP MSG6_MAIN		; Say handshake option
MAKE_RES:	KEEP_PROCESS 0 INIT	; Make programm TSR with errorcode 0
; ///////////////////// End of main program /////////////////////////////
;
; ********************* Procedure definitions ***************************
;
INT14_INSTALL		PROC NEAR
		GET_VECTOR INT_14	; Get old interrupt vector in ES:BX
		MOV OLD_VECTOR_14,BX	; and store it
		MOV OLD_VECTOR_14 + 2,ES
		SET_VECTOR INT_14,BIOS_INT ; Set new interrupt vector
		RET
INT14_INSTALL	ENDP
;
; --------------------- Test if driver is already installed -------------
; if yes, deinstall it, called by proc SET_PORT
;
ALREADY_INSTALLED	PROC NEAR
		GET_VECTOR INT_NUM	; Get actual interrupt vector
		MOV AX,ES:[PROG_ID]	; Get program id lowword
		CMP AX,ID_CODE_LOW	; Is key correct?
		JNE INSTALL		; no-->not yet installed
		MOV AX,ES:[PROG_ID + 2] ; Get program id highword
		CMP AX,ID_CODE_HIGH	; Is key correct?
		JNE INSTALL		; no-->not yet installed
		CALL COM_DEINSTALL	; Resume old context
		MOV BX,ES:[2Ch] 	; Get address of environment block
		MOV CX,ES		; Get address of program block
		FREE_MEMORY BX		; Release memory of environment
		FREE_MEMORY CX		; Release memory of program
		END_PROCESS 1		; Exit to DOS
;					; Quit to DOS with errorlevel 1
INSTALL:	RET			; Return to caller
ALREADY_INSTALLED ENDP
;
; --------------------- Install communication driver --------------------
COM_INSTALL	PROC NEAR
		JMP  BEGIN_COM_INSTALL
MSG1_COM_INSTALL DB  'Communication-Driver installed.',13,10,'$'
MSG2_COM_INSTALL DB  13,10,'Error:--- Cannot install Communication-Driver.'
		 DB  'UART not present.$'
;
BEGIN_COM_INSTALL:
		MOV AX,ID_CODE_LOW	; Get program id lowword
		MOV DS:[PROG_ID],AX	; Store it
		MOV AX,ID_CODE_HIGH	; Get program id high
		MOV DS:[PROG_ID+2],AX	; Store it
;
		MOV AL,1		; Set bit #0 to
		MOV CL,I8259LEVEL	; Prepare for shift left to
		SHL AL,CL		; produce the appropriate int.bit
		MOV I8259_BIT,AL
; Save old status
		MOV DX,UART_IER 	; Prepare to
		IN  AL,DX		; get old IER
		MOV OLD_IER,AL		; and save it
		MOV AL,0		; Try to set IER
		OUT DX,AL		; to zero
		NOP			; Wait a while
		NOP
		NOP
		IN  AL,DX		; Read it back
		CMP AL,0		; Is it zero?
		JE  PRESENT		; yes-->UART present
		DISP MSG2_COM_INSTALL	; no--> display message
		JMP QUIT_COM_INSTALL	; and leave

PRESENT:
; Disable COM-port interrupt in interrupt controller
		CLI			; Disable hardware interrupt
		IN  AL,21h		; Get mask from interrupt controller
		MOV OLD_I8259_MASK,AL	; and save it
		OR  AL,I8259_BIT	; Set appropriate bit
		OUT 21h,AL		; Inhibit interrupt from COM-port
		STI			; enable hardware interrupt
;
		CALL COM_FLUSH_TX	; Clear transmit buffer
		CALL COM_FLUSH_RX	; Clear receive buffer
;
		GET_VECTOR INT_NUM	; Get old interrupt vector in ES:BX
		MOV OLD_VECTOR,BX	; and store it
		MOV OLD_VECTOR + 2,ES	;
;
		SET_VECTOR INT_NUM,COM_INT ; Set new interrupt vector
;
; Set parity to none, turn off BREAK and make sure we are not addressing
; the baud rate register
		MOV DX,UART_LCR 	; Prepare
		MOV AL,3		;
		OUT DX,AL		; UART LCR
; Read register to reset the UART
		MOV DX,UART_DATA
		IN  AL,DX
		IN  AL,DX		; again
; Save original contents UART_MSR  of modem control register, then enable
; interrupts to system bus and activate DTR and RTS
		CLI
		MOV DX,UART_MCR 	; Prepare
		IN  AL,DX		; Get MCR
		MOV OLD_MCR,AL		; and save it
		MOV AL,11		; Set bits to interrupt system bus
					; and activate DTR and RTS
		OUT DX,AL		; and out it goes
		STI
; Enable interrupt of UART
		MOV DX,UART_IER 	; Prepare  address
		MOV AL,1		; to set bit 0 (int on data available)
		CMP HANDSHAKE,1 	; Is hardware handshake selected?
		JNE SOFT_SHAKE1 	; no-->continue
		OR  AL,8		; yes-->set bit #3 (int on modem lines)
SOFT_SHAKE1:	OUT DX,AL		; and out it goes
; Enable interrupt of controller
		CLI			;
		IN  AL,21h		; Get mask from interrupt controller
		MOV AH,I8259_BIT	; Get appropriate bit
		NOT AH			; Inverting bit
		AND AL,AH		; Clear appropriate bit
		OUT 21h,AL		; Enable interrupt
		STI
		DISP MSG1_COM_INSTALL	; Say everything ok
QUIT_COM_INSTALL:
		RET
COM_INSTALL	ENDP
;
; --------------------- Deinstall communication driver -------------------
COM_DEINSTALL	PROC NEAR
; On entry ES points to segment of installed driver
;
		JMP  BEGIN_COM_DEINSTALL
MSG1_COM_DEINSTALL DB  13,10,'Communcation-Driver removed.$'
;
BEGIN_COM_DEINSTALL:
		MOV AL,ES:[OLD_MCR]	     ; Restore MCR
		MOV DX,ES:[UART_MCR]	     ;
		OUT DX,AL		;
		MOV AL,ES:[OLD_IER]	     ; Restore IER
		MOV DX,ES:[UART_IER]
		OUT DX,AL
;
; Restore mask of interrupt controller
		CLI			; Inhibit interrupts
		MOV AL,ES:[OLD_I8259_MASK] ; Get old mask
		OUT 21h,AL		; Store it and
		STI			; enable interrupts
;
; first hardware interrupt vector
		PUSH DS 		; Save DS
		MOV AX,ES:[OLD_VECTOR]	     ; Get old interrupt vector offset
		MOV BX,ES:[OLD_VECTOR + 2]   ; Get old interrupt vector segment
		XOR CX,CX		; Clear CX
		MOV CL,INT_NUM		; Get interrupt number
		SHL CX,1		; Multiply by 4 to get address
		SHL CX,1
		MOV SI,CX		; For indirect addressing
		MOV DX,0		; Prepare to address
		MOV DS,DX		; vector segment
		MOV [SI],AX		; Restore offset
		MOV [SI+ 2],BX		; Restore segment
		POP DS			; Restore DS
; now INT 14
		PUSH DS 		; Save DS
		MOV AX,ES:[OLD_VECTOR_14]     ; Get old interrupt vector offset
		MOV BX,ES:[OLD_VECTOR_14 + 2] ; Get old interrupt vector segment
		XOR CX,CX		; Clear CX
		MOV CL,INT_14		; Get interrupt number
		SHL CX,1		; Multiply by 4 to get address
		SHL CX,1
		MOV SI,CX		; For indirect addressing
		MOV DX,0		; Prepare to address
		MOV DS,DX		; vector segment
		MOV [SI],AX		; Restore offset
		MOV [SI+ 2],BX		; Restore segment
		POP DS			; Restore DS
;
		DISP MSG1_COM_DEINSTALL
		RET
COM_DEINSTALL	ENDP
;
; --------------------- Set the transmission parameters ------------------
; This part of code comes from	FMODE ver 1.00à (c) 1987 lyman & associates
; Modifications in uppercase
SET_PORT	PROC NEAR
		JMP  BEG_SET_PORT
;
port		dw	001 dup (00h)		; 0=com1 2=com2 4=com3 6=com4
baud		dw	001 dup (00h)		; baud rate divisor
lcr		db	001 dup (00h)		; line control register
;						;
;-----------------------------------------------------------------------------
BEG_SET_PORT:	call	getparms		; see if we got any parameters
		call	getport 		; get the port number to set
		CALL	ALREADY_INSTALLED	; check if driver is installed
		call	chkport 		; check the validity of the port
		call	getbaud 		; get the desired baud rate
		call	getparity		; get the parity requirements
		call	getdata 		; get the requested number of databits
		call	getstop 		; and lastly get the stopbits
		CALL	GETHAND 		; get the handshake option
		call	setport 		; set the port as specified
		RET
SET_PORT	ENDP
;
; --------------------- Read Command Line Parameters from PSP ------------
GETPARMS	proc	near			;
		mov	si, 82h 		; first char in PSP
		mov	bx, 80h 		;
		cmp	byte ptr [bx], 0	; param count in PSP
		jne	getparms1		;
		call	help			; and exit
getparms1:	ret				;
getparms	endp				;
;						;
;-----------------------------------------------------------------------------
GETPORT 	proc	near			;
getport1:	lodsb				; get a character
		cmp	al, 20h 		; get rid of leading spaces
		je	getport1		;
		call	uppercase		;
						;
		cmp	al, 'C'                 ; this is klugy, but it will do
		jne	getport3		;
						;
		lodsb				;
		call	uppercase		;
		cmp	al, 'O'                 ;
		jne	getport3		;
						;
		lodsb				;
		call	uppercase		;
		cmp	al, 'M'                 ;
		jne	getport3		;
						;
		lodsb				; get the port number
		cmp	al, '1'                 ; is it COM1 ??
		jne	getport2		;
		mov	port, 00h		;
		MOV	UART_BASE,03F8h 	; Base for UART COM1
		MOV	INT_NUM,0Ch		; Interrupt number COM1
		MOV	I8259LEVEL,4h		; Interrupt level COM1 (IRQ4)
		MOV	COM_PORT,1		; Comport number
		jmp	short getport6		;
						;
getport2:	cmp	al, '2'                 ; is it COM2 ??
		jne	getport3		;
		mov	port, 02h		;
		MOV	UART_BASE,02F8h 	; Base for UART COM2
		MOV	INT_NUM,0Bh		; Interrupt number COM2
		MOV	I8259LEVEL,3h		; Interrupt level COM2 (IRQ3)
		MOV	COM_PORT,2		; Comport number
		jmp	short getport6		;
						;
getport3:	cmp	al, '3'                 ; is it COM3 ??
		jne	getport4		;
		mov	port, 04h		;
		MOV	UART_BASE,03E8h 	; Base for UART COM3
		MOV	INT_NUM,0Ch		; Interrupt number COM3
		MOV	I8259LEVEL,4h		; Interrupt level COM3 (IRQ4)
		MOV	COM_PORT,3		; Comport number
		jmp	short getport6		;
						;
getport4:	cmp	al, '4'                 ; or COM4 ??
		jne	getport5		; if not, giv'em help
		mov	port, 06h		;
		MOV	UART_BASE,02E8h 	; Base for UART COM4
		MOV	INT_NUM,0Bh		; Interrupt number COM4
		MOV	I8259LEVEL,3h		; Interrupt level COM4	(IRQ3)
		MOV	COM_PORT,4		; Comport number
		jmp	short getport6		;
						;
getport5:	call	help			;
						;
getport6:	MOV    AX,UART_BASE
		MOV    UART_BASE+2,AX
		ADD    AX,1
		MOV    UART_BASE+4,AX
		ADD    AX,1
		MOV    UART_BASE+6,AX
		ADD    AX,1
		MOV    UART_BASE+8,AX
		ADD    AX,1
		MOV    UART_BASE+10,AX
		ADD    AX,1
		MOV    UART_BASE+12,AX
		ADD    AX,1
		MOV    UART_BASE+14,AX
		ADD    AX,1
		MOV    UART_BASE+16,AX
		ret
getport 	endp				;
;						;
;-----------------------------------------------------------------------------
CHKPORT 	proc	near			;
		int	11h			; get equipment list
		mov	cl, 09h 		; set up for shifter
		shr	ax, cl			; shift it
		and	ax, 00000111b		; get number of ports
		shl	ax, 1			; multiply by 2
		sub	ax, 2			; normalize for 00h offset
		cmp	port, ax		; and check for valid port
		jle	chkport1		; lees than or equal o.k.
		call	help1			; otherwise give'em help
chkport1:	ret				;
chkport 	endp				;
;						;
;-----------------------------------------------------------------------------
GETBAUD 	proc	near			;
		lodsb				;
		cmp	al, ':'                 ; check for delimiter
		je	getbaud1		;
		jmp	getbaud20		;
						;
getbaud1:	lodsb				; get the first digit of desired baud
		sub	al, 30h 		; reduce to binary
		mov	bl, 10			; set up for multiply
		mul	bl			; and do it
		mov	ah, 00h 		; clear AH
		mov	baud, ax		; and save it
		lodsb				; get second digit of baud rate
		sub	al, 30h 		; normalize it to binary
		mov	ah, 00h 		; clear the high half
		add	baud, ax		; and add it in
						;
getbaud2:	cmp	baud, 57		; is this the desired baud
		jne	getbaud3		; no, try the next one
		mov	baud, 002h		; yes, set the baud rate divisor
		jmp	getbaud21		; and exit from routine
						;
getbaud3:	cmp	baud, 38		; ditto
		jne	getbaud4		;
		mov	baud, 003h		;
		jmp	getbaud21		;
						;
getbaud4:	cmp	baud, 19		; ditto
		jne	getbaud5		;
		mov	baud, 006h		;
		jmp	getbaud21		;
						;
getbaud5:	cmp	baud, 96		; ditto
		jne	getbaud6		;
		mov	baud, 00ch		;
		jmp	getbaud21		;
						;
getbaud6:	cmp	baud, 72		; ditto
		jne	getbaud7		;
		mov	baud, 010h		;
		jmp	getbaud21		;
						;
getbaud7:	cmp	baud, 48		; ditto
		jne	getbaud8		;
		mov	baud, 018h		;
		jmp	getbaud21		;
						;
getbaud8:	cmp	baud, 36		; ditto
		jne	getbaud9		;
		mov	baud, 020h		;
		jmp	getbaud21		;
						;
getbaud9:	cmp	baud, 24		; ditto
		jne	getbaud10		;
		mov	baud, 030h		;
		jmp	getbaud21		;
						;
getbaud10:	cmp	baud, 20		; ditto
		jne	getbaud11		;
		mov	baud, 03ah		;
		jmp	getbaud21		;
						;
getbaud11:	cmp	baud, 18		; ditto
		jne	getbaud12		;
		mov	baud, 04h		;
		jmp	getbaud21		;
						;
getbaud12:	cmp	baud, 12		; ditto
		jne	getbaud13		;
		mov	baud, 060h		;
		jmp	getbaud21		;
						;
getbaud13:	cmp	baud, 60		; ditto
		jne	getbaud14		;
		mov	baud, 0c0h		;
		jmp	getbaud21		;
						;
getbaud14:	cmp	baud, 30		; ditto
		jne	getbaud15		;
		mov	baud, 180h		;
		jmp	getbaud21		;
						;
getbaud15:	cmp	baud, 15		; ditto
		jne	getbaud16		;
		mov	baud, 300h		;
		jmp	getbaud21		;
						;
getbaud16:	cmp	baud, 13		; ditto
		jne	getbaud17		;
		mov	baud, 359h		;
		jmp	getbaud21		;
						;
getbaud17:	cmp	baud, 11		; ditto
		jne	getbaud18		;
		mov	baud, 417h		;
		jmp	getbaud21		;
						;
getbaud18:	cmp	baud, 75		; ditto
		jne	getbaud19		;
		mov	baud, 600h		;
		jmp	getbaud21		;
						;
getbaud19:	cmp	baud, 50		; ditto
		jne	getbaudmidi		;
		mov	baud, 900h		;
		jmp	getbaud21		;
						;
getbaudmidi:	cmp	baud, 31		; ditto
		jne	getbaud20		;
		mov	baud, 008h		;
		jmp	getbaud21		;
						;
getbaud20:	call	help			; invalid baud rate exit thru help
						;
getbaud21:	ret				;
getbaud 	endp				;
;						;
;-----------------------------------------------------------------------------
GETPARITY	proc	near			;
		lodsb				;
		cmp	al, ','                 ; check for delimiter
		jne	getparity4		;
						;
		lodsb				; get the character
		call	uppercase		; uppercase it for compare
		cmp	al, 'N'                 ;
		jne	getparity1		;
		or	lcr, 00000b		; set no parity
		jmp	short getparity5	;
						;
getparity1:	or	lcr, 1000b		; parity generated
		cmp	al, 'O'                 ;
		jne	getparity2		;
		or	lcr, 00000b		; odd parity
		jmp	short getparity3	;
						;
getparity2:	cmp	al, 'E'                 ;
		jne	getparity4		;
		or	lcr, 10000b		; even parity
						;
getparity3:	or	lcr, 100000b		; enable stick parity
		jmp	short getparity5	;
						;
getparity4:	call	help			; invalid parity request
						;
getparity5:	ret				;
getparity	endp				;
;						;
;-----------------------------------------------------------------------------
GETDATA 	proc	near			;
		lodsb				;
		cmp	al, ','                 ; check for delimiter
		jne	getdata5		;
						;
getdata1:	lodsb				;
						;
		cmp	al, '8'                 ; 8 data bits ??
		jne	getdata2		;
		or	lcr, 11b		;
		jmp	short getdata6		;
						;
getdata2:	cmp	al, '7'                 ; 7 data bits
		jne	getdata3		;
		or	lcr, 10b		;
		jmp	short getdata6		;
						;
getdata3:	cmp	al, '6'                 ; 6 data bits
		jne	getdata4		;
		or	lcr, 01b		;
		jmp	short getdata6		;
						;
getdata4:	cmp	al, '5'                 ; and the rediculous
		jne	getdata5		;
		or	lcr, 00b		;
		jmp	short getdata6		;
						;
getdata5:	call	help			; invalid request
						;
getdata6:	ret				;
getdata 	endp				;
;						;
;-----------------------------------------------------------------------------
GETHAND 	proc	near			;
		lodsb				;
		cmp	al, ','                 ; check for delimiter
		jne	gethand3		;
						;
		lodsb				; get the character
		call	uppercase		; uppercase it for compare
		cmp	al, 'N'                 ;
		jne	gethand1		;
		mov	handshake,0		; set no handshake
		jmp	short gethand4		;
						;
gethand1:	cmp	al, 'H'                 ;
		jne	gethand2		;
		mov	handshake,1		; hardware handshake
		jmp	short gethand4		;
						;
gethand2:	cmp	al, 'S'                 ;
		jne	gethand3		;
		mov	handshake,2		; software handshake
		jmp	short gethand4		;
						;
gethand3:	call	help			; invalid handshake request
						;
gethand4:	ret				;
GETHAND 	endp				;
;						;
;-----------------------------------------------------------------------------
GETSTOP 	proc	near			;
		lodsb				; get the delimiter
		cmp	al, ','                 ; or else
		jne	getstop3		;
						;
getstop1:	lodsb				;
						;
		cmp	al, '1'                 ; 1 stop bit
		jne	getstop2		;
		or	lcr, 000b		;
		jmp	short getstop4		;
getstop2:	cmp	al, '2'                 ; 2 stop bits, or 1-1/2 if 5 databits
		jne	getstop3		;
		or	lcr, 100b		;
		jmp	short getstop4		;
						;
getstop3:	call	help			; invalid request
						;
getstop4:	ret				;
getstop 	endp				;
;						;
;--------------------------------------------------------------------------------------
SETPORT 	proc	near			;
		mov	ax, 40h 		; set up BIOS Segment
		mov	es, ax			;
		mov	bx, port		; offset of port address
		mov	dx, es:[bx]		; and get it
						;
		add	dx, 3			; offset to line control register
		mov	al, 10000000b		; set bit 7 of lcr to enable baud rate setting
		out	dx, al			; and send it out
		sub	dx, 2			; MSB of baud rate
		mov	ax, baud		; get baud
		mov	al, ah			; put msb in AL
		out	dx, al			; and away it goes
		dec	dx			; LSB of baud rate
		mov	ax, baud		; and set up the lower half
		out	dx, al			; and it's a goner
						;
		mov	al, lcr 		; get the rest of the junk
		add	dx, 3			; and point to the lcr register
		out	dx, al			; and set it
						;
		sub	dx, 2			; set up the interrupt enable register
		mov	al, 0			; disable interrupts fr safety
		out	dx, al			; and it's done
		ret				;
setport 	endp				;
;						;
;-----------------------------------------------------------------------------
HELP		proc	near			;
		DISP MSG3_MAIN			; point to the help msg
		END_PROCESS 1			; and return to DOS with error 1
help		endp				;
;						;
;-----------------------------------------------------------------------------
HELP1		PROC	NEAR			;
		DISP HELP1_MSG			; point to the help msg
		END_PROCESS 2			; and return to DOS with error
HELP1_MSG:	DB  13,10,'Error:--- Serial port not found.$'
HELP1		ENDP				;
;						;
;-----------------------------------------------------------------------------
UPPERCASE	proc	near			;
		cmp	al, 'a'                 ; is it less than an 'a'
		jb	uppercase1		; if so skip it
		cmp	al, 'z'                 ; is it greater than a 'z'
		ja	uppercase1		; if so skip it
		sub	al, 20h 		; otherwise upper case it
uppercase1:	ret				;
uppercase	endp				;
;						;
; ///////////////////// End of part from FMODE ///////////////////////////////
;
CODE		ENDS
       END START
