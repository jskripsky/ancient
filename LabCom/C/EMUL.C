/***************************************************************************

  PROGRAM  : EMUL.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.02
  DATE     : 14-Oct-92
  PURPOSE  : Simple terminal emulation.
  REMARKS  :
  COMPILE  : Turbo C, Version 2.0, large memory model
  LINK     : Unigraph, Unicom
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <stdio.h>
#include <bios.h>
#include <conio.h>
#include <process.h>
#include <unicom.h>

/* -------------------------- Defines ------------------------------------*/
#define FALSE   0
#define TRUE    !FALSE

/* -------------------------- Typedefs -----------------------------------*/
typedef union
   { unsigned short w;
     struct
	{ char lo;
	  char hi;
	} b;
   } wordbyte;

/* -------------------------- Globals ------------------------------------*/
int down = 0;
FILE *outfp;

/* --------------------- Function  definitions --------------------------*/
void upload(void)
{
FILE *infp;
char filename[24];
int c;

   printf("\nEnter filename: ");
   scanf("%s",filename);
   infp = fopen(filename,"r");

   while ( (c = getc(infp)) != EOF ) {
      if ( c == 10 ) txcharw(13);  /* include <CR> */
      txcharw(c);
   }
   fclose(infp);
   printf("\nUpload successful.\n");
}

void start_down(void)
{
char filename[24];

   printf("\nAlt-E to close the capture file.");
   printf("\nEnter filename: ");
   scanf("%s",filename);
   outfp = fopen(filename,"w");
   down = TRUE;
}

void end_down(void)
{
   fclose(outfp);
   printf("\nCapture file closed.\n");
}

/* ------------------------- Main program --------------------------------*/
main(void)

{
int ch;
wordbyte key;

   if ( !initcom() ) {
      printf("Press any key...");
      getch();
      exit(1);
   }

   printf("\nEMUL V1.0\n\n");
   printf("\nAlt-X to quit.\n");
   printf("Alt-T to upload  ASCII file.\n");
   printf("Alt-C to capture ASCII file.\n");
   printf("\nEnter terminal emulation now... (no echo)\n");

   do {
      key.w = bioskey(1);
      if ( key.w ) {
	 key.w = bioskey(0);
	 if ( key.b.lo != NULL ) {                 /* normal  char */
	    switch (key.b.lo) {
	       case 17 : send_ctrlq(); break;
	       case 19 : send_ctrls(); break;
               default : if ( !tx_queue_full() ) {
                           txchar(key.b.lo); break;
                         }
                         else break;
            }
         }
         else {                               /* special char */
            switch (key.b.hi) {
               case 45 : exit(0); break;      /* Alt-X */
               case 20 : upload(); break;     /* Alt-T */
               case 46 : start_down(); break; /* Alt-C */
	       case 18 : end_down(); break;   /* Alt-E */
	       default : printf("\n\nIllegal key.\n"); break;
            }
         }
      }
   if ( !rx_queue_empty() ) {
      ch = rxchar();
      printf("%c",ch);
      if ( down && ( ch != 13) ) putc(ch,outfp);
   }

   }
   while ( TRUE );
}
