/***************************************************************************

  PROGRAM  : RCCHARGE.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.0
  DATE	   : 30-Dec-92
  PURPOSE  : Demonstration of charging and discharching a capacitor
  REMARKS  : Mode 2, binary format, 10 kHz samling rate, 19 kBaud,
	     Trigger on 128 (equal)
	     R = 10 kOhm, C = 10 uF with 5 V from Analog Input Module
	     Stores data in array to be processed in any way
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK	   : Use UNILIB: Unigraph, Unicom
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <bios.h>
#include <process.h>
#include <conio.h>
#include <dos.h>
#include <unigraph.h>
#include <unicom.h>

/* -------------------------- Defines ------------------------------------*/
#define CTRL_C	3

unsigned _stklen = 60000U;

/***************************** Main ****************************************/
void main(void)

{
int i;
unsigned char ch;
unsigned char data[16000];
int imin = 0;
int imax = 16000;

   if ( !initcom() ) {
      printf("Press any key...");
      getch();
      exit(1);
   }

   gdefinescreen(EGAVGA);
   ginit( );
   gwindow(imin,imax,0,255);
   txchar(CTRL_C);   /* To stop LabCom if already triggered */

   while ( 1 ) {
      flush_rx_queue();  /* To be sure we start with clean conditions */
      gotoxy(1,10);
      printf("Wait for trigger\n");
      printf("(Press any key\n");
      printf(" to quit)\n");

      i = imin;
      while ( i < imax ) {
	 while ( rx_queue_empty() ) {
	    if ( kbhit() ) {
	       txchar(CTRL_C);
	       gend();
	       printf("No data received from LABcom\n");
	       exit(0);
	     }
	 }
	 ch = rxchar();
	 data[i] = ch;
	 if ( i == imin ) {
	    gclearscreen();
	    gframe(GREEN);
	    gcolor(GREEN);
	    for ( i = imin; i <= imax; i += 2000 ) {
	       gpos(i,0); gdraw(i,255);
	    }

	    for (i = 0; i <=255; i += 20 ) {
	       gpos(imin,i); gdraw(imax,i);
	    }
	    gcolor(WHITE);
	    gpos(imin,data[imin]);
	 }
	 else gdraw(i,data[i]);
	 i++;
      }

      txcharw(CTRL_C);
      delay(7000);	      /* Wait LabCom to get ready */
      flush_rx_queue();       /* Drop any characters after stop */
   }
}
