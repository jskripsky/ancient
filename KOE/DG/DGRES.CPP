/*****************************************************************************
**                                                                          **
**                                                                          **
**  DOS Dialog Generator - Resource Generation                              **
**  ==========================================                              **
**                                                                          **
**  Version 1.00                                                            **
**                                                                          **
**                                                                          **
**  Copyright (C) 1993 Skribby Soft                                         **
**                                                                          **
** ======================================================================== **
**                                                                          **
**  xxxxxxxxxxx                                                             **
**  -----------                                                             **
**                                                                          **
**  Defined classes:                                                        **
**    - Class xxxxx                                                         **
**                                                                          **
**                                                                          **
**                                                                          **
**  Module Name: DGRES.CPP                                                  **
**                                                                          **
*****************************************************************************/

#include "Compiler.H"

#define Uses_ofpstream
#include "TCard.H"


main()
{
	TCard *card = new TCard();

	card->insert( new CardField( 0x80, 28, "KrankenKassenNamen" ) );
	card->insert( new CardField( 0x81,  7, "KrankenKassenNummer", Numeric ) );
	card->insert( new CardField( 0x82, 12, "Versichertennummer", Numeric ) );
	card->insert( new CardField( 0x83,  4, "VersichertenStatus", Numeric ) );
	card->insert( new CardField( 0x84, 15, "Titel" ) );
	card->insert( new CardField( 0x85, 28, "VorName" ) );
	card->insert( new CardField( 0x86, 15, "NamenZusatz" ) );
	card->insert( new CardField( 0x87, 28, "FamilienName" ) );
	card->insert( new CardField( 0x88,  8, "GeburtsDatum", TTMMJJJJ ) );
	card->insert( new CardField( 0x89, 28, "StrassenName&HausNummer" ) );
	card->insert( new CardField( 0x8A,  3, "WohnsitzLÑnderCode" ) );
	card->insert( new CardField( 0x8B,  7, "PostleitZahl" ) );
	card->insert( new CardField( 0x8C, 22, "OrtsName" ) );
	card->insert( new CardField( 0x8D,  4, "GÅltigkeitsdatum", MMJJ ) );
	card->insert( new CardField( 0x8F,  5, "VKNR", Numeric ) );
	card->insert( new CardField( 0x90,  3, "StatusergÑnzung" ) );

	ofpstream cardFile( "Card.Res", ios::trunc );
	cardFile << card;
	cardFile.close();

	delete card;

	ofpstream charactersFile( "Chars.Res", ios::trunc );
	charactersFile << 128;

	charactersFile.writeString( "00    0  NUL" );
	charactersFile.writeString( "01    1  SOH" );
	charactersFile.writeString( "02    2  STX" );
	charactersFile.writeString( "03    3  ETX" );
	charactersFile.writeString( "04    4  EOT" );
	charactersFile.writeString( "05    5  END" );
	charactersFile.writeString( "06    6  ACK" );
	charactersFile.writeString( "07    7  BEL" );
	charactersFile.writeString( "08    8  BS" );
	charactersFile.writeString( "09    9  HT" );
	charactersFile.writeString( "0a   10  LF" );
	charactersFile.writeString( "0b   11  VT" );
	charactersFile.writeString( "0c   12  FF" );
	charactersFile.writeString( "0d   13  CR" );
	charactersFile.writeString( "0e   14  SO" );
	charactersFile.writeString( "0f   15  SI" );
	charactersFile.writeString( "10   16  DLE" );
	charactersFile.writeString( "11   17  DC1" );
	charactersFile.writeString( "12   18  DC2" );
	charactersFile.writeString( "13   19  DC3" );
	charactersFile.writeString( "14   20  DC4" );
	charactersFile.writeString( "15   21  NAK" );
	charactersFile.writeString( "16   22  SYN" );
	charactersFile.writeString( "17   23  ETB" );
	charactersFile.writeString( "18   24  CAN" );
	charactersFile.writeString( "19   25  EM" );
	charactersFile.writeString( "1a   26  SUB" );
	charactersFile.writeString( "1b   27  ESC" );
	charactersFile.writeString( "1c   28  FS" );
	charactersFile.writeString( "1d   29  GS" );
	charactersFile.writeString( "1e   30  RS" );
	charactersFile.writeString( "1f   31  US" );
	charactersFile.writeString( "20   32  Space" );
	charactersFile.writeString( "21   33  !" );
	charactersFile.writeString( "22   34  \"" );
	charactersFile.writeString( "23   35  #" );
	charactersFile.writeString( "24   36  $" );
	charactersFile.writeString( "25   37  %" );
	charactersFile.writeString( "26   38  &" );
	charactersFile.writeString( "27   39  '" );
	charactersFile.writeString( "28   40  (" );
	charactersFile.writeString( "29   41  )" );
	charactersFile.writeString( "2a   42  *" );
	charactersFile.writeString( "2b   43  +" );
	charactersFile.writeString( "2c   44  ," );
	charactersFile.writeString( "2d   45  -" );
	charactersFile.writeString( "2e   46  ." );
	charactersFile.writeString( "2f   47  /" );
	charactersFile.writeString( "30   48  0" );
	charactersFile.writeString( "31   49  0" );
	charactersFile.writeString( "32   50  0" );
	charactersFile.writeString( "33   51  0" );
	charactersFile.writeString( "34   52  0" );
	charactersFile.writeString( "35   53  0" );
	charactersFile.writeString( "36   54  0" );
	charactersFile.writeString( "37   55  0" );
	charactersFile.writeString( "38   56  0" );
	charactersFile.writeString( "39   57  0" );
	charactersFile.writeString( "3a   58  :" );
	charactersFile.writeString( "3b   59  ;" );
	charactersFile.writeString( "3c   60  <" );
	charactersFile.writeString( "3d   61  =" );
	charactersFile.writeString( "3e   62  >" );
	charactersFile.writeString( "3f   63  ?" );
	charactersFile.writeString( "40   64  @ Paragraph" );
	charactersFile.writeString( "41   65  A" );
	charactersFile.writeString( "42   66  B" );
	charactersFile.writeString( "43   67  C" );
	charactersFile.writeString( "44   68  D" );
	charactersFile.writeString( "45   69  E" );
	charactersFile.writeString( "46   70  F" );
	charactersFile.writeString( "47   71  G" );
	charactersFile.writeString( "48   72  H" );
	charactersFile.writeString( "49   73  I" );
	charactersFile.writeString( "4a   74  J" );
	charactersFile.writeString( "4b   75  K" );
	charactersFile.writeString( "4c   76  L" );
	charactersFile.writeString( "4d   77  M" );
	charactersFile.writeString( "4e   78  N" );
	charactersFile.writeString( "4f   79  O" );
	charactersFile.writeString( "50   80  P" );
	charactersFile.writeString( "51   81  Q" );
	charactersFile.writeString( "52   82  R" );
	charactersFile.writeString( "53   83  S" );
	charactersFile.writeString( "54   84  T" );
	charactersFile.writeString( "55   85  U" );
	charactersFile.writeString( "56   86  V" );
	charactersFile.writeString( "57   87  W" );
	charactersFile.writeString( "58   88  X" );
	charactersFile.writeString( "59   89  Y" );
	charactersFile.writeString( "5a   90  Z" );
	charactersFile.writeString( "5b   91  [ é" );
	charactersFile.writeString( "5c   92  \ ô" );
	charactersFile.writeString( "5d   93  ] ö" );
	charactersFile.writeString( "5e   94  ^" );
	charactersFile.writeString( "5f   95  _" );
	charactersFile.writeString( "60   96  `" );
	charactersFile.writeString( "61   97  a" );
	charactersFile.writeString( "62   98  b" );
	charactersFile.writeString( "63   99  c" );
	charactersFile.writeString( "64  100  d" );
	charactersFile.writeString( "65  101  e" );
	charactersFile.writeString( "66  102  f" );
	charactersFile.writeString( "67  103  g" );
	charactersFile.writeString( "68  104  h" );
	charactersFile.writeString( "69  105  i" );
	charactersFile.writeString( "6a  106  j" );
	charactersFile.writeString( "6b  107  k" );
	charactersFile.writeString( "6c  108  l" );
	charactersFile.writeString( "6d  109  m" );
	charactersFile.writeString( "6e  110  n" );
	charactersFile.writeString( "6f  111  o" );
	charactersFile.writeString( "70  112  p" );
	charactersFile.writeString( "71  113  q" );
	charactersFile.writeString( "72  114  r" );
	charactersFile.writeString( "73  115  s" );
	charactersFile.writeString( "74  116  t" );
	charactersFile.writeString( "75  117  u" );
	charactersFile.writeString( "76  118  v" );
	charactersFile.writeString( "77  119  w" );
	charactersFile.writeString( "78  120  x" );
	charactersFile.writeString( "79  121  y" );
	charactersFile.writeString( "7a  122  z" );
	charactersFile.writeString( "7b  123  { Ñ" );
	charactersFile.writeString( "7c  124  | î" );
	charactersFile.writeString( "7d  125  } Å" );
	charactersFile.writeString( "7e  126  ~ ·" );
	charactersFile.writeString( "7f  127  DEL" );

	charactersFile.close();

	return 0;
}