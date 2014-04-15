/***************************************************************************

  PROGRAM  : KOZOOM.C
  COPYRIGHT: (c) 1992 University of Berne, Switzerland, Computerlab KL
  REVISION : 1.1
  DATE     : 16-Oct-92
  PURPOSE  : Storage cathode ray oscilloscope simulation with
	     with LABcom interface external trigger (Mode 2)
	     Zoom possibilities with mouse
  REMARKS  :
  COMPILE  : Borland C++, Version 2.0, large memory model
  LINK     : Use UNILIB: Unigraph, RS232DRV, PCHRT
  USAGE    : First load driver RS232DRV from command line

 **************************************************************************/

/* -------------------------- Includes -----------------------------------*/
#include <dos.h>
#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <ctype.h>
#include <unigraph.h>
#include <unicom.h>
#include <unitimer.h>

/* -------------------------- Defines ------------------------------------*/
#define FALSE    0
#define TRUE     !FALSE
#define PI 3.14159
#define CTRL_C 3
#define MAXDATA 4096
#define MINDATA 1900
#define XTRIGGER 2046

unsigned _stklen = 8000;

/**************************** Hauptprogramm ********************************/
void main(void)

{
int xmin, xmax, ymin, ymax;
int x, xlold, xrold;
float xf, yf;
unsigned event;
int dragleft, dragright, leftset, rightset, do_zoom, do_reset;
int do_newrun = FALSE;
char ans, ch;
unsigned char data[MAXDATA+1];
int i;
FILE *out;
char filename[20];

   if ( !initcom() ) {
      printf("Press any key to quit.\n");
      getch();
      exit(1);
   }

   gdefinescreen(EGAVGA);
   ginit();

   mouse_init();
   mouse_defevent( MOUSE_MOVE
		 | MOUSE_LPRESS
		 | MOUSE_RPRESS
		 | MOUSE_LRELEASE
		 | MOUSE_RRELEASE
		 | MOUSE_LCLICK
		 | MOUSE_LDCLICK
		 | MOUSE_RDCLICK );


   ans = 'm';

   if ( ! rx_queue_empty() ) {
      printf("\aOld data in buffer.\nFlushing old data...\n");
      txchar(CTRL_C);
      delay(200);
      flush_rx_queue();
   }

   do {
      gclearscreen();
      gframe(RED);

      if ( toupper(ans) == 'M' ) {
	 xmin = MINDATA; xmax = MAXDATA; ymin = 0; ymax = 255;
	 i = 0;
	 if ( do_newrun ) {
	    gotoxy(1,20);
	    printf("\aGot new data...");
	 }

	 ans = ' ';
	 gotoxy(1,10);
	 printf("Wait for trigger\n");
	 printf("(Press any key\n");
	 printf(" to quit)\n");

	 while ( i <= MAXDATA ) {
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
	    i++;
	 }
	 txchar(CTRL_C);
	 delay(200);
	 flush_rx_queue();

	 gotoxy(1,10);
	 printf("                \n");
	 printf("                \n");
	 printf("                \n");
      }

      leftset = FALSE;
      rightset = FALSE;
      dragleft = FALSE;
      dragright = FALSE;
      do_zoom = FALSE;
      do_reset = FALSE;
      do_newrun = FALSE;

      gotoxy(1,1);
      printf("Mouse:\n");
      printf("L_press: low bound\n");
      printf("R_press: high bound\n");
      printf("L_click: zoom\n");
      printf("L_D_click: unzoom\n");
      printf("R_D_click: file\n\n");
      printf("Press:\n");
      printf("M: New messure\n");
      printf("Q: Quit\n");

      gwindow(xmin,xmax,ymin,ymax);
      xlold = xmin; xrold = xmax;

      gcolor(BLUE);
      gpos(xmin,128); gdraw(xmax,128);
      gpos(XTRIGGER,0); gdraw(XTRIGGER,255);

      gcolor(WHITE);
      i = xmin;
      gpos(i,data[i]);

      for ( i = xmin; i <= xmax; i++)
	 gdraw(i, data[i]);

      while ( !kbhit() && !do_zoom && !do_reset && !do_newrun ) {
	 if ( !rx_queue_empty() ) {
	    do_newrun = TRUE;
	    ans = 'm';
	 }
	 event = mouse_event(&xf, &yf); /* reports xf,yf even when no event */
	 x = (int)xf;
	 gotoxy(1,15);
	 printf("Actual = %5d", x);

	 switch ( event ) {
	    case MOUSE_LPRESS:
	       if ( x > xrold ) {
		  printf("\a");
		  break;
	       }
	       gcolor(YELLOW);
	       gxor(XOR_PUT);
	       if ( leftset ) {
		  gpos(xlold,0); gdraw(xlold,255);
	       }
	       gpos(x,0); gdraw(x,255);
	       xlold = x;
	       dragleft = TRUE;
	       break;

	    case MOUSE_RPRESS:
	       if ( x < xlold ) {
		  printf("\a");
		  break;
	       }
	       gcolor(GREEN);
	       gxor(XOR_PUT);
	       if ( rightset ) {
		  gpos(xrold,0); gdraw(xrold,255);
	       }
	       gpos(x,0); gdraw(x,255);
	       xrold = x;
	       dragright = TRUE;
	       break;

	    case MOUSE_LRELEASE:
	       if ( x > xrold ) {
		  printf("\a");
		  break;
	       }

	       dragleft = FALSE;
	       gxor(COPY_PUT);
	       leftset = TRUE;
	       gotoxy(1,16);
	       printf("Left   = %5d", xlold);
	       break;

	    case MOUSE_RRELEASE:
	       if ( x < xlold ) {
		  printf("\a");
		  break;
	       }
	       dragright = FALSE;
	       gxor(COPY_PUT);
	       rightset = TRUE;
	       gotoxy(1,17);
	       printf("Right  = %5d", xrold);
	       break;

	    case MOUSE_MOVE:
	       if ( dragleft ) {
		  if ( x > xrold ) {
		     printf("\a");
		     break;
		  }
		  gpos(xlold,0); gdraw(xlold,255);
		  gpos(x,0); gdraw(x,255);
		  xlold = x;
		  gotoxy(1,16);
		  printf("Left   = %5d", xlold);
	       }

	       if ( dragright ) {
		  if ( x < xlold ) {
		     printf("\a");
		     break;
		  }
		  gpos(xrold,0); gdraw(xrold,255);
		  gpos(x,0); gdraw(x,255);
		  xrold = x;
		  gotoxy(1,17);
		  printf("Right  = %5d", x);
	       }
	       break;

	    case MOUSE_LCLICK:
	       do_zoom = TRUE;
	       break;

	    case MOUSE_LDCLICK:
	       do_reset = TRUE;
	       break;

	    case MOUSE_RDCLICK:
	       gotoxy(1,20);
	       printf("Filename:\n");
	       scanf("%s",filename);

	       if ((out = fopen(filename, "wt")) == NULL)
		   fprintf(stderr, "Cannot open output file.\n");
	       else {
		  printf("Writing file...");
		  for ( i = xmin; i <= xmax; i++ )
		     fprintf(out, "%d\n", data[i]);
		  fclose(out);
		  printf("done.\n");
	       }
	       break;
	 }
      }
      if ( !do_zoom && !do_reset && !do_newrun ) ans = getch();
      if ( do_reset)
	 { xmin = MINDATA; xmax = MAXDATA; }
      else
	 { xmin = xlold; xmax = xrold; }
   }
   while ( toupper(ans) != 'Q' );

   mouse_end();
   gend();
}

