program Heron;

var	Schritte:	Integer;
	Radikand:	Real;
	X, LetztesX:	Real;

begin

	Write( 'Geben Sie bitte den Radikanden ein: ' );
	ReadLn( Radikand );

	X := Radikand;
	Schritte := 0;

	repeat
		LetztesX := X;
		X := (X + (Radikand / X)) / 2;
                Schritte := Schritte + 1;
	until ( X = LetztesX );

	WriteLn( 'Resultat: ', X );
        WriteLn( 'Schritte: ', Schritte );

end.