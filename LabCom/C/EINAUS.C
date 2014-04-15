/***************************************************************************

  PROGRAM  : EINAUS.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE     : 24-Apr-92
  PURPOSE  : Ein- und Ausschalten eines Geraets
  REMARKS  : LABcom mode 0
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK     : Use Unicom
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <unicom.h>

/* -------------------------- Defines -----------------------------------*/
#define EMAX  0      /* Maximaler Index der Eingangsmodule */
#define AMAX  0      /* Maximaler Index der Ausgangsmodule */
#define SYNCHBYTE 0

/* -------------------------- Prototypes ---------------------------------*/
void lab_aktual(void);
void geraetein(void);
void geraetaus(void);

/* -------------------------- Globals ------------------------------------*/
unsigned char awert[8], ewert[8];

/**************************** Main ****************************************/
void main(void)
{
char ch;

   initcom();

   printf("\nEINAUS V1.0\n");
   do {
      ch = getch();
      if ( ch == 'e' ) geraetein();
      if ( ch == 'a' ) geraetaus();
   } while ( ch != 'x' );
}

/* -------------------------- Functions ----------------------------------*/
void lab_aktual(void)
{
int i;

   if ( AMAX == -1 ) txcharw(SYNCHBYTE);
   else for ( i = 0; i <= AMAX; i++ ) txcharw(awert[i]);

   for ( i = 0; i <= EMAX; i++ ) ewert[i] = rxcharw();
}

void geraetein(void)
{
//   awert[0] = awert[0] | 0x01;
   awert[0] = 0xFF;
   lab_aktual();
}

void geraetaus(void)
{
//   awert[0] = awert[0] & 0xFE;
   awert[0] = 0x00;
   lab_aktual();
}
