/***************************************************************************

  PROGRAM  : ROBY.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.01
  DATE     : 16-Nov-92
  PURPOSE  : Fischer-Technik Roboter
  REMARKS  : LABcom mode 0
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK     : Use Unicom
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/
 /*
    Bemerkungen zum mechanisch/elektrischen Aufbau:

    Arm noch oben/unten   :   kleinere/grîssere Werte von zeige_vertikal()
    Arm nach rechts/links :   kleinere/grîssere Werte von zeige_horizontal()

    Man verwendet:   - 2 Analog-Input-Module
                     - 1 Digital-Input-Module
                     - Power-Output-Modul
    die mit dem Flachband-Kabel verbunden werden.
 */



/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <process.h>
#include <conio.h>
#include <unicom.h>

/* -------------------------- Defines -----------------------------------*/
#define FALSE 0
#define TRUE !FALSE

/* Motor/Magnet */
#define M_AUF      4
#define M_AB       8
#define M_EIN     32
#define M_RECHTS  64
#define M_LINKS  128

/* Tasten */
#define T_KEINE      0
#define T_AUF        1
#define T_AB         2
#define T_RECHTS     4
#define T_LINKS      8
#define T_EIN       16
#define T_AUS       32
#define T_SPEICHERN 64
#define T_RUN      128

/* -------------------------- Typedefs -----------------------------------*/
typedef unsigned char byte;

typedef struct {
   byte vertikal;
   byte horizontal;
   byte magnet;
   } zustandstype;

/* -------------------------- Prototypes ---------------------------------*/
void drehe_auf(void);
void drehe_ab(void);
void drehe_rechts(void);
void drehe_links(void);
void magnet_ein(void);
void magnet_aus(void);
void halte_an(void);

byte zeige_vertikal(void);
byte zeige_horizontal(void);
byte zeige_tasten(void);

void speichere(void);
void fahre_vertikal(byte);
void fahre_horizontal(byte);
void fahre_ab(int);

/* -------------------------- Globals ------------------------------------*/
byte befehl = 0;
zustandstype zliste[200];
int znum = 0;

/**************************** Main ****************************************/
void main(void)
{
byte tasten_wert;
int gespeichert;

   if ( !initcom() ) exit(1);

   printf("\nROBY V1.01\n");
   printf("Positionen mit Tasten anfahren und speichern.\n");
   printf("Beenden mit der RUN-Taste.\n\n");

   do {
      tasten_wert = zeige_tasten();
      switch ( tasten_wert ) {
         case T_KEINE     : gespeichert = FALSE; halte_an(); break;
         case T_AUF       : drehe_auf();    break;
         case T_AB        : drehe_ab();     break;
         case T_LINKS     : drehe_links();  break;
         case T_RECHTS    : drehe_rechts(); break;
         case T_EIN       : magnet_ein();   break;
         case T_AUS       : magnet_aus();   break;
         case T_SPEICHERN : if ( !gespeichert ) {
                               gespeichert = TRUE;
                               speichere();
                            }
      }
   }
   while ( tasten_wert != T_RUN );
   printf("\aRUN gedrÅckt...\n");
   while ( !kbhit() ) fahre_ab(znum);
   printf("Gute Arbeit geleistet, lieber ROBY!\n");
}

/* -------------------------- Functions ----------------------------------*/

void drehe_auf(void)
/* Arm nach oben bewegen */
{
   befehl = befehl | M_AUF;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

void drehe_ab(void)
/* Arm nach unten bewegen */
{
   befehl = befehl | M_AB;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

void drehe_links(void)
/* Arm nach links bewegen (von oben gesehen) */
{
   befehl = befehl | M_LINKS;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

void drehe_rechts(void)
/* Arm nach rechts bewegen (von oben gesehen) */
{
   befehl = befehl | M_RECHTS;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

void magnet_ein(void)
/* Magnet einschalten */
{
   befehl = befehl | M_EIN;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

void magnet_aus(void)
/* Magnet ausschalten */
{
   befehl = befehl & ~M_EIN;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

void halte_an(void)
/* Motoren ausschalten */
{
   befehl = befehl & ~M_AUF & ~M_AB & ~M_LINKS & ~M_RECHTS;
   txcharw(befehl);
   rxcharw(); rxcharw(); rxcharw();
}

byte zeige_vertikal(void)
/* Vertikale Position zurÅckgeben */
/* Es werden immer 3 Positionen: Vertikal, Horizonal, Tasten geliefert */
{
byte vpos;

   txcharw(befehl);
   vpos = rxcharw();
   rxcharw();
   rxcharw();
   return(vpos);
}

byte zeige_horizontal(void)
/* Horizontale Position zurÅckgeben */
/* Es werden immer 3 Positionen: Vertikal, Horizonal, Tasten geliefert */
{
byte hpos;

   txcharw(befehl);
   rxcharw();
   hpos = rxcharw();
   rxcharw();
   return(hpos);
}

byte zeige_tasten(void)
/* Tastenstellung zurÅckgeben */
/* Es werden immer 3 Positionen: Vertikal, Horizonal, Tasten geliefert */
{
byte tpos;

   txcharw(befehl);
   rxcharw();
   rxcharw();
   tpos = rxcharw();
   tpos = ~tpos;    /* Invertiere alle Bits */
   return(tpos);
}

void speichere(void)
/* Momentane Position in Datenstruktur speichern */
{
   zliste[znum].vertikal   = zeige_vertikal();
   zliste[znum].horizontal = zeige_horizontal();
   zliste[znum].magnet     = befehl & M_EIN;
   printf("\aSpeichere POS %d: VERTIKAL: %d HORZONTAL: %d MAGNET %d\n",
             znum,
             zliste[znum].vertikal,
             zliste[znum].horizontal,
             zliste[znum].magnet);
   znum++;
}

void fahre_vertikal(byte sollwert)
/* Mit Vertikalmotor auf Sollwert fahren */
{
byte istwert;
byte hysterese = 2;

   istwert = zeige_vertikal();

   if ( istwert < sollwert ) {
      drehe_ab();
      do
         istwert = zeige_vertikal();
      while ( istwert < sollwert - hysterese );
   }
   else {
      drehe_auf();
      do
         istwert = zeige_vertikal();
      while ( istwert > sollwert + hysterese );
   }
   halte_an();
}

void fahre_horizontal(byte sollwert)
/* Mit Horizontalmotor auf Sollwert fahren */
{
byte istwert;
byte hysterese = 2;

   istwert = zeige_horizontal();
   if ( istwert < sollwert ) {
      drehe_links();
      do
         istwert = zeige_horizontal();
      while ( istwert < sollwert - hysterese );
   }
   else {
      drehe_rechts();
      do
         istwert = zeige_horizontal();
      while ( istwert > sollwert + hysterese );
   }
   halte_an();
}

void fahre_ab(int zmax)
/* Gespeicherte Positionen durchlaufen */
{
int schritt;
byte vpos, hpos;

   printf("\n\n\aNeuer Durchlauf...mit irgendeiner Taste beenden\n");
   for ( schritt = 0; schritt < zmax; schritt++ ) {

      if ( zliste[schritt].magnet )
         befehl = befehl | M_EIN;
      else
         befehl = befehl & ~M_EIN;

      vpos = zeige_vertikal();
      if ( vpos != zliste[schritt].vertikal )
         fahre_vertikal(zliste[schritt].vertikal);

      hpos = zeige_horizontal();
      if ( hpos != zliste[schritt].horizontal )
         fahre_horizontal(zliste[schritt].horizontal);

      printf("POS %d: VERTIKAL: %d HORIZONTAL: %d MAGNET: ",
              schritt, zliste[schritt].vertikal, zliste[schritt].horizontal);
      if ( zliste[schritt].magnet ) printf("EIN\n");
      else printf("AUS\n");
   }
}
