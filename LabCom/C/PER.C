/***************************************************************************

  PROGRAM  : PER.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE     : 24-Apr-92
  PURPOSE  : Periodisches Einlesen von Eingangsmodulwerten
  REMARKS  : LABcom mode 0
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK     : Use Unitimer, Unicom
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <unitimer.h>
#include <unicom.h>

/* -------------------------- Defines -----------------------------------*/
#define EMAX  0      /* Maximaler Index der Eingangsmodule */
#define AMAX -1      /* Maximaler Index der Ausgangsmodule */
#define SYNCHBYTE 0

/* -------------------------- Prototypes ---------------------------------*/
void lab_aktual(void);

/* -------------------------- Globals ------------------------------------*/
unsigned char awert[8], ewert[8];

/**************************** Main ****************************************/
void main(void)
{

   initcom();

   t_start();            /* Initialisiere Timer-Software */
   t_alarm_start();      /* Initialize Alarm-Uhr */
   delaytime = 1000000L; /* Periodendauer in us */

   printf("\nPER V1.0\n");

   t_alarm_set(0,delaytime,T_ONCE);
   do {
      do ; while ( t_alarm_check(0) == 0 );
      t_alarm_set(0,delaytime,T_ONCE);

      lab_aktual();
      printf("Wert: %d\n", ewert[0]);
   } while ( !kbhit() );

   t_stop();   /* Desinstalliere Timer */
}

/* -------------------------- Functions ----------------------------------*/
void lab_aktual(void)
{
int i;

   if ( AMAX == -1 ) txcharw(SYNCHBYTE);
   else for ( i = 0; i <= AMAX; i++ ) txcharw(awert[i]);

   for ( i = 0; i <= EMAX; i++ ) ewert[i] = rxcharw();
}
