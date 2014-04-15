/***************************************************************************

  PROGRAM  : KOFAST.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.10
  DATE     : 16-Oct-92
  PURPOSE  : Storage cathode ray oscilloscope simulation with
	     with LABcom interface external trigger (Mode 2)
  REMARKS  :
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK     : Use UNILIB: Unigraph, RS232DRV, PCHRT
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <bios.h>
#include <process.h>
#include <conio.h>
#include <dos.h>
#include <unigraph.h>
#include <unitimer.h>
#include <unicom.h>

/* -------------------------- Defines ------------------------------------*/
#define FALSE   0
#define TRUE    !FALSE
#define CTRL_C  3

/***************************** Main ****************************************/
void main(void)

{
int i;
unsigned char ch;
unsigned char data[3000];
int imin = 1500;
int imax = 2500;

   if ( !initcom() ) {
      printf("Press any key...");
      getch();
      exit(1);
   }

   gdefinescreen(EGAVGA);
   ginit( );
   gwindow(imin,imax,0,255);
   gframe(WHITE);

   printf("KOFAST V1.1\n");
   txchar(CTRL_C);    /* If LABcom already got trigger and waits to send */

   while ( TRUE ) {
      i = 0;
      flush_rx_queue();  /* To be sure we start with clean conditions */
      printf("Wait for trigger\n");
      printf("(Press any key\n");
      printf(" to quit)\n");


      while ( i < 2500 ) {
	 while ( rx_queue_empty() ) {
	    if ( kbhit() ) {
	       txchar(CTRL_C);
	       t_stop();
	       gend();
	       printf("No data received from LABcom\n");
	       exit(0);
	     }
	 }
	 ch = rxchar();
	 data[i] = ch;

	 i++;
      }

   gclearscreen();
   gotoxy(1,1);
   gframe(RED);
   gcolor(GREEN);
   gpos(imin,128); gdraw(imax,128);
   gcolor(YELLOW);
   gpos(2048,0); gdraw(2048,255);
   gcolor(WHITE);

   gpos(imin,data[imin]);
   for ( i = imin; i < imax; i++ ) gdraw(i,data[i]);
   txchar(CTRL_C);          /* Stop output from LABcom */
   printf("Wait until ready\n");
   delay(5000);            /* Wait LABcom to get ready */
   flush_rx_queue();       /* To get rid of characters after delayed stop */    }
   gend();
}

