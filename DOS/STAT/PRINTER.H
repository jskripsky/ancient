// ****************************
// ***	      Printer	    ***
// ****************************
// ***			    ***
// ****************************



#define DATA			0
#define INIT			1

#define TITLEFONT		10
#define NORMALFONT		11
#define COMPTITLEFONT		20
#define COMPNORMALFONT		21
#define STARTUNDERLINE		40
#define ENDUNDERLINE		41
#define STARTBOLD		60
#define ENDBOLD 		61

#define NEWLINE 		100
#define NEWPAGE 		150

#define SETHPOS 		200

#define LANDSCAPE		0
#define PORTRAIT		1



// *** Vartypes	***************
struct PrinterInfo
    {
    CHAR		    PrinterPort[10];
    CHAR		    PrinterDescription[81];

    BYTE		    ControlCodes[10][40];
    BYTE		    Orientation;

    BYTE		    LinesPerPage;
    };
