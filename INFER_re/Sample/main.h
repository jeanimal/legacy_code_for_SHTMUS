/* main.h:  all declarations for data structures which
will be passed throughout the program must be made here.
Some source file use local data structures (lists, etc)
and they are not included here for modularity.
Naturally, there should be no function prototypes here */


/* below should really be moved to variables.h, but that requires
 * changing ALL the headers for the algorithms. */
#define GUESSCNT        1 /* if =1, guessing automatically 0.5 correct */

#define NAMELENGTH      60
#define MYERR           0.00001
#define DEBUG           0 
#define DEBUG2          0  /* how deep do you like your debugging? */
#define DEBUG_REG       0  /* debugging regression stuff */

#define MAX_CORREL_VALUE 0.95 /* max correlation between cues to call
							   * something collinear so regression
							   * doesn't crash.
							   */
#define MIN_VAR_ALLOWED 0.01  /* min var for indiv cue-- exclude
							   * cues below this so doesn't crash
							   */


#define HEADPREFIX  (long (*)(struct world_array_struct *, struct world_array_struct *, long, long, long, long, struct score_matrix_struct *, struct useful_variables_struct, struct alg_var_struct) )


struct useful_variables_struct
{
	long	num_cities;
	long	num_cues;
	long	num_percents;

	long	guess_cnt;  /* 1 means guesses count as 0.5 */
	long	cue_reverse; /* 1 means cues w/ below 0.5 validity reversed */
	long	categorize; /* 1 means calc cue validity scores 0.5 for
						 * equal target values */
	long	actual_num_cities; /* used only when CROSSVALIDATE is 1.
								* This is actual value, num_cities is half. */
	long	sample_size;
};


/* below are the further (derived) variables needed to easily
 * run the algorithms (without rederiving all this crap) */

struct alg_var_struct
{
	
	/* cue validities are held here.  
	 * recall cue[0] is the recognition cue and so is handled differently */
	double  *cue_validity_array; 
	
	/* holds the cue order of the current subject */
	long 	*ss_cue_order_array; 


};

/* same as alg_var_struct except grouped the other way.
 * for each cue_val_ord, you have a cue validity and its order.
 * need this for things like qsort.
 */
struct cue_val_ord_struct
{
	double 	cv;
	long	ord;
};



struct score_matrix_struct
{
   double          correct;
   double          lookups;
   double		   guesses;
};





struct question_pair_struct
{
  long obj1;
  long obj2;
};


struct sim_info_struct {
long RPchoice;
long Algchoice;
long Questchoice;
long Lookupchoice;
long Guesschoice;
long Intranschoice;
double CVchoice; /* must read in as float */
long Repchoice;
long Errchoice;
long Start_per_choice;
long Start_city_choice;
char Algstr[7];
char RPstr[5];
char Correctfilename[40];
char Datafilename[40];
char Lookupfilename[40];
char Guessfilename[40];
char Filecode[3];
long TempSampleSize; /* to be copied into useful */
};


struct world_array_struct
{
   char            name[NAMELENGTH];
   long            rank;
   long            pop;
   double          *cue;
};

