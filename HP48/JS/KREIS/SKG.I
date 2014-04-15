%%HP: T(3)A(D)F(.);
\<<
"Schnitt Kreis, Gerade
---------------------
Axx+Ayy+Bx+Cy+D = 0
Ex + Fy + G = 0

Eingabe: A B C D E F G
Ausgabe: X1 Y1 X2 Y2"
DISPHELP

   \-> A B C D E F G
   \<<
      'A/SQ(F)*(SQ(F)+SQ(E))' EVAL
      'INV(SQ(F))*(2*A*G*E+SQ(F)*B-C*E*F)' EVAL
      'INV(SQ(F))*(A*SQ(G)-C*G*F+D*SQ(F))' EVAL
      QGL
      
      EVAL "X2" \->TAG
      SWAP
      EVAL "X1" \->TAG
      DUP
      E * G + F / NEG
      EVAL "Y1" \->TAG
      ROT
      
      DUP
      E * G + F / NEG
      EVAL "Y2" \->TAG
   \>>
\>>
