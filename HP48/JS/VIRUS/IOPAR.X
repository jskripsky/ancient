%%HP: T(3)A(D)F(.);
\<<
   BLACK.ROSE
   TYPE
   IF
      0
      \=/
   THEN
      DEPTH
      DUP
      IF
         0
         >
      THEN
         1
         SWAP
         START
            DUP
            TYPE
            DUP
            IF
               0 ==
               SWAP
               12 ==
               OR
            THEN
               RAND
               0.1 *
               0.95 +
               *
            END
            DEPTH
            ROLL
         NEXT
      ELSE
         DROP
      END
   END
\>>
