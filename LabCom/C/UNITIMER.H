/* UNITIMER.H */
/* -------------------------------------------------------------------------- */
/*  Allowed memory models: LARGE                                              */
/* -------------------------------------------------------------------------- */
#if !defined( __LARGE__ )
#error Must use LARGE memory model with UNITIMER.
#endif

/*---------------------------------------------------------------------------
 |  PCHRT.H                                                                 |
 |                                                                          |
 |  Compiler independant header module for PCHRT in a C environment.        |
 |                                                                          |
 |  (c)1988,1991 Ryle Design, P.O. Box 22, Mt. Pleasant, MI 48804           |
 |                                                                          |
 |  V4.10                                                                   |
 ---------------------------------------------------------------------------*/

#ifndef T_TRUE
    #define T_TRUE    1
    #define T_FALSE   0
#endif

#define T_NUMVEC        10              /* # of BIOS interrupts we can profile  */

#define T_CRT10         1               /* BIOS timer bitmask switches        */
#define T_DISK          2
#define T_COM           4
#define T_KEYBD         8
#define T_PRT           16
#define T_DOS21         32
#define T_MOUSE         64
#define T_EMS           128
#define T_USER          256
#define T_HARDUSER      512

#define T_INTS_ON       1               /* timer modes - default with interrupts on             */
#define T_NO_INTS_ON    2               /* short duration with interrupts off                   */
#define T_NESTED        3               /* nested timer mode                                    */
#define T_DEF_NUMTIMERS 10              /* default number of timers - override with t_request() */

#define T_CONTROL_PORT  0x43            /* 8253 control registers */
#define T_DATA_PORT     0x40

#define T_HIGHWATER     0               /* timer report type specifiers */
#define T_NONZERO       1

#define T_TIMERSTACK    100             /* size of BIOS timer stack     */
#define T_NESTSTACK     256

#define T_CLOCK_TIME    0.054925        /* DOS timer tick length        */

#define T_LAST          0               /* t_check_timer qualifiers     */
#define T_TOTAL         1

#define     T_ONCE      0               /* alarm types                  */
#define     T_RESTART   1
#define     T_AUTO      2


typedef char tname[21];                 /* timer name data type         */

typedef struct                                                  /* hires timestamp              */
{
        unsigned int    ticks;                          /* 8253 838ns "ticks"           */
        unsigned int    tocks;              /* BIOS TOD 54.925 ms "tocks"   */
}
pchrt_type;


typedef struct
{
    long unsigned   entry;              /* timer entry count         */
    long unsigned   elapsed;            /* timer elapsed time count  */
    tname           timername;          /* timer name                */
    pchrt_type      tstart;             /* timer entry timestamp     */
    pchrt_type      tstop;              /* timer exit timestamp      */
}
pchrt_data;


typedef struct                                  /* bios timer data structure             */
{
    int             which_int;                  /* interrupt vector timer               */
    char            int_name[31];               /* description of interrupt functionality  */
    int             enabled;                    /* interrupt timer state flag            */
    tname           func_name[256];             /* interrupt function name                 */
    long unsigned   entry[256];                 /* # of activations for each timer         */
    long unsigned   elapsed[256];               /* total elapsed for each timer            */
    pchrt_type      bstart[256];                /* entry timestamps                        */
    pchrt_type      bstop[256];                 /* exit timestamps                         */
}
tbios_data;


typedef struct                                  /* data structure for delay function */
{
    int     inner;                              /* inner loop count */
    int     outer;                              /* outer loop count */
}
tdelay_type;


typedef struct                                  /* stack for BIOS interrupt timers */
{
    char unsigned   func;
    tbios_data      *iptr;
}
tbios_timer_stack;


typedef struct                                  /* alarm data structure */
{
    int             alarm_type;                 /* type                 */
    long unsigned   alarm_len;                  /* requested length     */
    long unsigned   act_time;                   /* actual length        */
    pchrt_type      alarm_start;                /* start timestamp      */
}
t_alarm_type;


/*---------------------------------------------------------------------------
 |                        global variable definitions                       |
 ---------------------------------------------------------------------------*/

extern pchrt_data   *tdata;                     /* timer data struct       */
extern tbios_data   *i10data;                   /* INT 10h timer data      */
extern tbios_data   *i13data;                   /* INT 13h timer data      */
extern tbios_data   *i14data;                   /* INT 14h timer data      */
extern tbios_data   *i16data;                   /* INT 16h timer data      */
extern tbios_data   *i17data;                   /* INT 17h timer data      */
extern tbios_data   *i21data;                   /* INT 21h timer data      */
extern tbios_data   *i33data;                   /* INT 33h timer data      */
extern tbios_data   *i67data;                   /* INT 67h timer data      */
extern tbios_data   *iuserdata;                 /* user int timer data     */
extern tbios_data   *huserdata;                 /* user hardware int timer data */

extern tbios_timer_stack    tbios_stack[T_TIMERSTACK];

extern char         pchrt_fname[67];            /* default report file name */
extern char         pchrt_title[81];            /* default report title     */

extern char         tbios_fname[67];            /* default bios report file name                            */
extern char         tbios_title[81];            /* default bios report title                                */
extern char         tbios_user_file[67];        /* file containing user interrupt function descriptions     */
extern char         tbios_hard_file[67];
extern char         tbios_path[67];             /* path to interrupt description files */

extern int          t_timermode;                /* flag for timer mode - INTS_ON or NO_INTS_ON  */
extern int          t_maxtimer;                 /* # of timers available                        */
extern int          t_maxentry;                 /* timer highwater mark                         */
extern int          t_report_type;              /* timer report type                            */
extern int          tbios_user_int;             /* user specified bios interrupt timer          */
extern int          tbios_hard_int;
extern int          tbios_mask;                 /* global bios timer mask                       */
extern int          t_valid;                    /* timer data valid flag                        */
extern int          tbios_valid;                /* bios timer data valid flag                   */
extern int          tbios_stackptr;             /* bios timer stack                             */
extern int          t_stkptr;                   /* nested timer stack                           */
extern int          t_ttm_valid;                /* ttm state flag                               */

extern int unsigned t_nstack[T_NESTSTACK];      /* NEST mode timer stack                */
extern int unsigned t_8253_load;                /* 8253 load word                       */
extern int unsigned t_08svc_count;              /* interrupt 08 time since last service */
extern int unsigned t_08svc_alarm;              /* interrupt 08 service alarm           */

extern long unsigned    t_iohead;               /* overhead in INTS_ON mode     */
extern long unsigned    t_noint_iohead;         /* overhead in NOINTS_ON mode   */
extern long unsigned    tdelay_ohead;           /* t_delay calling overhead     */
extern long unsigned    tdelay_inner;           /* t_delay inner loop time      */
extern long unsigned    tdelay_outer;           /* t_delay outer loop time      */
extern long unsigned    t_dos_tick;             /* DOS tod timer tick value (usec)         */
extern long unsigned    t_1Csvc_count;          /* interrupt 1C time since last activation */
extern long unsigned    t_1Csvc_alarm;          /* interrupt 1C service alarm              */
extern long unsigned    t_8253_tick;                    /* 8253 period                  */

extern double           tdelay_ff;              /* t_delay "fudge factor"           */
extern double           t_8253_period;          /* 8253 interrupt rate (usec)       */
extern double           t_8253_hz;              /* 8253 interrupt rate (hertz)      */
extern double           t_1C_period;            /* interrupt 1C rate (usec)         */
extern double           t_1C_hz;                /* interrupt 1C rate (hertz)        */
extern double           t_ttm_error;            /* DOS clock error from ttm         */


/*---------------------------------------------------------------------------
 |                            function prototypes                           |
 ---------------------------------------------------------------------------*/

/* unmangle names if C++ */

#ifdef __cplusplus
    extern "C" {
#endif

/* timer kernel functions */

void          t_request(int numtimer);
int           t_start(void);
void          t_get(pchrt_type* timestamp);
void          t_stop(void);
void          t_hires_entry(pchrt_type *timestamp);
void          t_hires_exit(pchrt_type *timestamp);
void          t_setmode(int modetype);
long unsigned t_diff(pchrt_type *start, pchrt_type *stop);
void          t_calib(void);
void          t_entry(int timernum);
void          t_exit(int timernum);
void          t_reset(int tnum);
void          t_ask_timer(int tnum, long unsigned *hits, long unsigned *elapsed);
long unsigned t_ask_elapsed(int tnum);
long unsigned t_ask_count(int tnum);
long unsigned t_check_timer(int tnum, int howmuch);
void          t_suspend(int tnum);
void          t_resume(int tnum);

/* timer report functions */

void          t_name(int timernum, char* timername);
void          t_set_report(int whichkind);
void          t_report(int whereto);
char *        t_cvt_time(unsigned long usecs, char *time_string);
void          t_fname(char *filename);
void          t_rname(char *report_title);

/* bios timer functions */

int  t_bios_start(int biosmask);
void t_bios_stop(void);
void t_bios_suspend(int biosmask);
void t_bios_resume(int biosmask);
void t_bios_report(int whereto);
void t_bios_ask(int whichint, int whichfunc, unsigned long *hits, unsigned long *elapsed);
void t_bios_reset(int whichint, int whichfunc);
void t_bios_fname(char *fname);
void t_bios_rname(char *rname);
void t_bios_set_user(int user_int);
void t_bios_hard_user(int user_int);
void t_bios_set_file(char *user_int_file);
void t_bios_hard_file(char *user_int_file);
void t_bios_set_path(char *path);
void t_bios_load_desc(int whichint, char *data_file);
void t_bios_entry(int whichint, int whichfunc);
void t_bios_exit(void);
void t_hook_int(int int_no);
void t_unhook_int(int int_no);

/* delay functions */

void            t_delay_calib(void);
double          t_calc_delay_ff(unsigned long how_long, int ints_or_not);
double          t_get_delay_ff(void);
void            t_set_delay_ff(double delay_ff);
void            t_ask_delay(long unsigned usec, tdelay_type *dp);
long unsigned   t_min_delay(void);
long unsigned   t_res_delay(void);
void            t_do_delay(tdelay_type *delay_params);
void            t_do_delay_wints(tdelay_type *delay_params);

/* timer tick manager functions */

void                t_ttm_init(double hz);
int                 t_ttm_start(void);
void                            t_ttm_stop(void);
void                            t_ttm_1C_set(double hz);

/* alarm functions */

void          t_alarm_request(int num_alarms);
int           t_alarm_start(void);
void          t_alarm_set(int alarm_num, unsigned long alarm_time, int action);
long unsigned t_alarm_check(int alarm_num);
void          t_alarm_stop(void);


#ifdef __TURBOC__
    void interrupt      t_new_08(void);
#else
    void interrupt far  t_new_08(void);
#endif

#ifdef __cplusplus
    }
#endif

/*---------------------------------------------------------------------------
                                  end pchrt.h
 ---------------------------------------------------------------------------*/
