rem Start Demo-Emulator
rem You may type RS232DRV without any paramters 
rem to get more information about using the serial driver

rem Use COM1,1200 baud,no parity,8 data bits,1 stop bit,software handshake
   rs232drv com1:12,n,8,1,s
   emul
