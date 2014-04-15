// ****************************
// ***	 Exportfile Conv.   ***
// ****************************
// ***			    ***
// ****************************

#include <process.h>

#define JSFILEIDMARKE		"TMS Exportfile, JS Format"
#define JSFILEGRVERSION 	1
#define JSFILEKLVERSION 	0

#define JSTMPFILENAME		"JSFile.Tmp"
#define COMPRESSPROGNAME	"Arj.Exe"
#define DECOMPRESSPROGNAME	"Arj.Exe"
#define COMPRESSPARAMS		"a"
#define DECOMPRESSPARAMS	"e -y"

#define ARCHIVEFILENAMETEMPL	"0000"
#define DATAFILENAMETEMPL	"00.Dat"

#define UNKONTROLLIERT		1
#define ABGEBROCHEN		2

#define TMSFILE_INV_LENGTH	1
#define TMSFILE_OLD_VERSION	2

#define TMSFILE_DOS_ERROR	11
#define JSFILE_DOS_ERROR	12

#define COMPRESS_SWITCH		4

#define MONATJAHR		0
#define ANZPERSONTAG		1

#define PERSON			10
#define TAG			11

// *** Vartypes	***************
struct SatzAnfang
    {
    CHAR		    Flag;
    CHAR		    Personalnummer[9];
    CHAR		    Name[30];
    CHAR		    Anstellung[6];
    CHAR		    Austritt[6];
    CHAR		    Beschaeftigungsgrad[3];
    CHAR		    Jahresplan[3];
    CHAR		    Funktion[5];
    CHAR		    Beschreibung[30];
    CHAR		    Felder[7][5];
    CHAR		    Zeitkonti[20][7];
    CHAR		    Frei[154];
    CHAR		    Schlusszeichen;
    CHAR		    ASCIISchlusszeichen[2];
    };

struct SatzMitte
    {
    CHAR		    Flag;
    CHAR		    Stempelung[2];
    CHAR		    Monat_Vormonat[1];
    CHAR		    Stempelungen[20][5];

    struct
	{
	CHAR		    Code[3];
	CHAR		    Typ;
	CHAR		    Herkunft[1];
	CHAR		    Dauer[4];
	}		    Begruendungen[21];

    CHAR		    Zeitkonti[20][5];
    CHAR		    Monat[2];
    CHAR		    Jahr[2];
    CHAR		    Kontrolle[3];
    CHAR		    Tagesplan[3];
    CHAR		    Frei[19];
    CHAR		    Schlusszeichen;
    CHAR		    ASCIISchlusszeichen[2];
    };

struct SatzEnde
    {
    CHAR		    Flag;

    CHAR		    PseudoFrei[147];

    CHAR		    Frei[274];
    CHAR		    Schlusszeichen;
    CHAR		    ASCIISchlusszeichen[2];
    };
