program Pi_Approximation;


   var Counter    : Integer;

        XPos       : Real;
        YPos       : Real;
        CenterDist : Real;

        Hits       : Integer;
        RelHits    : Real;
        PiApprox   : Real;


begin

     Randomize;

     Hits:= 0;

     for Counter := 0 to 10000 do
     begin
          XPos := Random( 10001 ) / 10000;  XPos := XPos * XPos;
          YPos := Random( 10001 ) / 10000;  YPos := YPos * YPos;
          CenterDist := XPos + YPos;

          if (CenterDist <= 1) then  Hits := Hits + 1;
     end;

     RelHits := Hits / Counter;
     PiApprox := Relhits * 4;

     WriteLn( 'PI-Naeherungswert: ', PiApprox:0:4 );


end.
