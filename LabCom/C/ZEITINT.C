/***************************************************************************

  PROGRAM  : ZEITINT.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE     : 24-Apr-92
  PURPOSE  : Bestimmung des Zeitintervalls
  REMARKS  : LABcom mode 5, Lichtschranke (Schalter) an bit 0 und 1 (Modul 0)
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK     : Use Unicom, Unitimer
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <unicom.h>
#include <unitimer.h>

/**************************** Main ****************************************/
void main(void)
{
unsigned char module_nr, ewert = 0;
long dauer;

   initcom();

   t_start();    /* Installiere Timer */

   printf("\nZEITINT V1.0\n");

   while ( (ewert & 0x01) == 0 ) {
      module_nr = rxcharw();
      ewert = rxcharw();
   }

   t_entry(1);   /* Starte Timer */
   printf("\nZeitmessung gestartet...");

   while ( (ewert & 0x02) == 0 ) {
      module_nr = rxcharw();
      ewert = rxcharw();
   }

   t_exit(1);   /* Stoppe Timer */
   dauer = t_ask_elapsed(1);
   printf("Zeitmessung beendet.\n");
   printf("Zeitintervall: %ld us\n", dauer);
   t_stop();   /* Desinstalliere Timer */
}

