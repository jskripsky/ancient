/***************************************************************************

  PROGRAM  : SPEICHKO.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE	   : 24-Apr-92
  PURPOSE  : Erfassung von schnellen Signalen
  REMARKS  : LABcom Modus 2, Externe Triggerung auf Signal
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK	   : Use Unicom, Unigraph
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <unicom.h>
#include <unigraph.h>

* -------------------------- Defines -----------------------------------*/
#define CTRL_C 3

/**************************** Main ****************************************/
void main(void)
{
int i;
unsigned char wert;

   initcom();
   ginit();
   gwindow(0,4000,0,255);

   printf("\nSPEICHKO V1.0\n");

   for ( i = 1; i <= 4000; i++ ) {
      wert = rxcharw();
      if ( i == 1) gpos(i,wert);
      else gdraw(i,wert);
   }

   txchar(CTRL_C);
   printf("Drcke Taste..."); getch();
   gend();
}

