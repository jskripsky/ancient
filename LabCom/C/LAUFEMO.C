/***************************************************************************

  PROGRAM  : LAUFEMO.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.00
  DATE	   : 24-Apr-92
  PURPOSE  : Anlaufen einer Achsposition
  REMARKS  : LABcom mode 0
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK	   : Use Unicom
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
void drehe_rechts(void);
void drehe_links(void);
void halte_an(void);
unsigned char lese_istwert(void);
void laufe(unsigned char);

/* -------------------------- Globals ------------------------------------*/
unsigned char awert[8], ewert[8];

/**************************** Main ****************************************/
void main(void)
{
unsigned char sollwert;

   initcom();
   printf("\nLAUFEMO V1.0\n");
   printf("Gebe Sollwert ein (0..255) : ");
   scanf("%d", &sollwert);

   laufe(sollwert);
}

/* -------------------------- Functions ----------------------------------*/
void lab_aktual(void)
{
int i;

   if ( AMAX == -1 ) txcharw(SYNCHBYTE);
   else for ( i = 0; i <= AMAX; i++ ) txcharw(awert[i]);

   for ( i = 0; i <= EMAX; i++ ) ewert[i] = rxcharw();
}

void drehe_links(void)
{
   awert[0] = awert[0] | 0x01;
   awert[0] = awert[0] & 0xFD;
   lab_aktual();
}

void drehe_rechts(void)
{
   awert[0] = awert[0] | 0x02;
   awert[0] = awert[0] & 0xFE;
   lab_aktual();
}

void halte_an(void)
{
   awert[0] = awert[0] | 0x01;
   awert[0] = awert[0] | 0x02;
   lab_aktual();
}

unsigned char lese_istwert(void)
{
   lab_aktual();
   printf("\nIstwert = %d", ewert[0]);
   return ewert[0];
}

void laufe(unsigned char sollwert)
{
unsigned char istwert;

   do {
      istwert = lese_istwert();
      if ( istwert > sollwert ) drehe_links();
      if ( istwert < sollwert ) drehe_rechts();
   } while ( istwert != sollwert );

   halte_an();
}

