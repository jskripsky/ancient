#include "Compiler.H"

/***************************************************************************

  PROGRAM  : UNICOM.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE	   : 23-Apr-92
  PURPOSE  : Subroutines to be used with resident
	     communication driver RS232DRV
  REMARKS  :
  COMPILE  :
  LINK	   :

 **************************************************************************/
/***************************************************************************

  REV	  DATE	     BY 		PURPOSE
 -----	 --------   ---------		----------------------------------
 1.00	 23-Apr-92  A. Pluess		Adapted from SUBDRV.C
 **************************************************************************/

#include <unicom.h>
#include <dos.h>
#include <stdio.h>

static union REGS regs;

extern int far initcom(void)
/* Search for communication driver and return communicaton port number */
/* or 0 if not found */
/* INT 14h function 0h */

{
   regs.h.ah = 0;
   int86(0x14,&regs,&regs);
   if ( regs.x.bx != 0x1234 ) {
      printf("\nError in routine initcom:-- Driver not found.\n");
      return(0);
   }
   return(regs.h.al);
}


extern int far txchar(int ch)
/* If TXBUF is not full put ch in TXBUF otherwise return error code */
/* INT 14 function 1h */

{
    regs.h.al = ch;
    regs.h.ah = 1;
    int86(0x14,&regs,&regs);
    return(regs.h.ah);
}

extern int far txcharw(int ch)
/* Wait until TXBUF is not full put ch in TXBUF */
/* INT 14 function 1h */

{
    while ( tx_queue_full() ) {};
    regs.h.al = ch;
    regs.h.ah = 1;
    int86(0x14,&regs,&regs);
    return(regs.h.ah);
}

extern int far rxchar(void)
/* Return a character from receive queue if available, otherwise zero */
/* INT 14h function 2h */

{
   regs.h.ah = 2;
   int86(0x14,&regs,&regs);
   if ( regs.h.ah ) return(0);	 /* no character */
   else return(regs.h.al);
}

extern int far tx_queue_full(void)
/* Return TRUE if tx-queue is full */
/* INT 14 function 3h */

{
   regs.h.ah = 3;
   int86(0x14,&regs,&regs);
   return(regs.h.ah);
}

extern int far rx_queue_empty(void)
/*  Return TRUE if rx-queue is empty */
/* INT 14h function 4h */

{
   regs.h.ah = 4;
   int86(0x14,&regs,&regs);
   return(regs.h.ah);
}

extern void far send_ctrls(void)
/* Put ctrl/s in transmit buffer and send it, clear ctrl/s-flag */
/* INT 14 function 5h */

{
   regs.h.ah = 5;
   int86(0x14,&regs,&regs);
}

extern void far send_ctrlq(void)
/* Check if ctrl/s-flag is cleared and send ctrl/q */
/* INT 14 function 6h */

{
   regs.h.ah = 6;
   int86(0x14,&regs,&regs);
}

extern void far deact_rts(void)
/* Deactivate RTS-signal */
/* INT 14h function 7h */

{
   regs.h.ah = 7;
   int86(0x14,&regs,&regs);
}

extern void far act_rts(void)
/* Activate RTS-signal */
/* INT 14h function 8h */

{
   regs.h.ah = 8;
   int86(0x14,&regs,&regs);
}

extern int far carrier_detect(void)
/* Return TRUE if carrier detect */
/* INT 14h function 9h */

{
   regs.h.ah = 9;
   int86(0x14,&regs,&regs);
   return(regs.h.ah);
}

extern void far deact_dtr(void)
/* Deactivate DTR-signal */
/* INT 14h function 0Ah */

{
   regs.h.ah = 10;
   int86(0x14,&regs,&regs);
}

extern void far act_dtr(void)
/* Activate RTS-signal */
/* INT 14h function 0Bh */

{
   regs.h.ah = 11;
   int86(0x14,&regs,&regs);
}

extern int far rxcharw(void)
/* Wait until char in receive queue and return char */
{
   while ( rx_queue_empty() );
   return(rxchar());
}

extern void far flush_rx_queue(void)
/* Flush receiver buffer */
{
   delay(100);
   while ( !rx_queue_empty() ) {
      while ( !rx_queue_empty() ) rxchar();
      delay(100);   /* Wait 100 ms */
   }
}
