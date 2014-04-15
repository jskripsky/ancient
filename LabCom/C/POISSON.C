/***************************************************************************

  PROGRAM  : POISSON.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE	   : 24-Apr-92
  PURPOSE  : Histogramm beim radioaktiven Zerfall
  REMARKS  : LABcom Modus 4
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK	   : Use Unicom, Unigraph, Unitimer
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <unicom.h>
#include <unigraph.h>
#include <unitimer.h>

/* -------------------------- Defines -----------------------------------*/
#define SYNCHBYTE 0
#define FALSE 0
#define TRUE !FALSE

/**************************** Main ****************************************/
void main(void)
{
unsigned char zaehlertief, zaehlerhoch, data[256];
long periode = 1000000L;      /* Zeitintervall zwischen Messungen */
int i, start = TRUE;

   initcom();
   ginit();
   gwindow(0,255,0,255);

   t_start();			/* Installiere Timer-Software */
   t_alarm_start();		/* Installiere Alarm-Uhr */
   printf("\nPOISSON V1.0\n");


   for ( i = 0; i <= 255; i++ ) data[i] = 0;
   t_alarm_set(0,periode,T_ONCE);

   do {
      do ; while ( t_alarm_check(0) == 0 );
      t_alarm_set(0,periode,T_ONCE);
      txchar(SYNCHBYTE);
      zaehlertief = rxcharw();
      zaehlerhoch = rxcharw();

      if ( start ) start = FALSE;	 /* Erster Wert unbrauchbar */
      else data[zaehlertief]++;

      gclear();
      for ( i = 0; i <= 255; i++ ) {
	 if ( i == 0 ) gpos(i, data[i]);
	 else gdraw(i, data[i]);
      }
   } while ( !kbhit() );

   t_stop();   /* Desinstalliere Timer */
   printf("\nDrcke Taste..."); getch(); getch();
   gend();
}

