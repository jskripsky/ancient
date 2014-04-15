/* ----------------- Prototypes of UNICOM functions ---------------- */
/* Version 1.0, 23-Apr-1992, A. Pluess */

/* unmangle names if C++ */

#ifdef __cplusplus
    extern "C" {
#endif

extern int far initcom(void);
/* Search for communication driver and return communicaton port number */
/* or 0 if not found */
/* INT 14h function 0h */

extern int far txchar(int ch);
/* If TXBUF is not full put ch in TXBUF otherwise return error code */
/* INT 14 function 1h */

extern int far txcharw(int ch);
/* Wait until TXBUF is not full put ch in TXBUF */
/* INT 14 function 1h */

extern int far rxchar(void);
/* Return a character from receive queue if available, otherwise zero */
/* INT 14h function 2h */

extern int far tx_queue_full(void);
/*  Return TRUE if tx-queue is full */
/* INT 14 function 3h */

extern int far rx_queue_empty(void);
/*  Return TRUE if rx-queue is empty */
/* INT 14h function 4h */

extern void far send_ctrls(void);
/* Put ctrl/s in transmit buffer and send it, clear ctrl/s-flag */
/* INT 14 function 5h */

extern void far send_ctrlq(void);
/* Check if ctrl/s-flag is cleared and send ctrl/q */
/* INT 14 function 6h */

extern void far deact_rts(void);
/* Deactivate RTS-signal */
/* INT 14h function 7h */

extern void far act_rts(void);
/* Activate RTS-signal */
/* INT 14h function 8h */

extern int far carrier_detect(void);
/* Return TRUE if carrier detect */
/* INT 14h function 9h */

extern void far deact_dtr(void);
/* Deactivate DTR-signal */
/* INT 14h function 0Ah */

extern void far act_dtr(void);
/* Activate RTS-signal */
/* INT 14h function 0Bh */

extern int far rxcharw(void);
/* Wait until char in receive queue and return char */

extern void far flush_rx_queue(void);
/* Flush receiver buffer */

#ifdef __cplusplus
	}
#endif
