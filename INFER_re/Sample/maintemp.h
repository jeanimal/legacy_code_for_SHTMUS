/* main.h:  all declarations for data structures which
will be passed throughout the program must be made here.
Some source file use local data structures (lists, etc)
and they are not included here for modularity.
Naturally, there should be no function prototypes here */

/* defines for the whole program*/
#define NUMCITIES       83 
#define NUMCUES         9 
#define NUMPERCENTS	    6
#define MYERR           0.00001
#define NAMELENGTH      60
#define	DEBUG	        0	
#define DEBUG2		    0  /* how deep do you like your debugging? */
#define STARTCITY	   0 	
#define GUESSCNT		1 /* if =1, guessing automatically 0.5 correct */
#define CUEREVERSE      1 /* if =1, cues will  be reversed
                            when their validities are below 0.5 */
						  /* "reversed" means for that cue, all 1-values
						  will be changed to 0's, and all 0's to 1's */

#define HEADPREFIX  (int (*)(struct world_array_struct *, struct world_array_struct *, int *, int, int, int, int,struct score_matrix_struct_closet *,double *,int))

struct score_matrix_struct
{
   double          correct;
   double          lookups;
   double		   guesses;
};

struct score_matrix_struct_closet
{
 struct score_matrix_struct score_matrix[NUMPERCENTS][NUMCITIES + 1];
};

struct question_pair_struct
{
  int obj1;
  int obj2;
};

struct sim_info_struct {
int RPchoice;
int Algchoice;
int Questchoice;
int Lookupchoice;
int Guesschoice;
int Intranschoice;
double CVchoice; /* must read in as float */
int Repchoice;
int Errchoice;
int Startchoice;
char Algstr[7];
char RPstr[5];
char Correctfilename[40];
char Lookupfilename[40];
char Guessfilename[40];
};


struct world_array_struct
{
   char            name[NAMELENGTH];
   int             rank;
   long            pop;
   double          cue[NUMCUES + 1];
};
