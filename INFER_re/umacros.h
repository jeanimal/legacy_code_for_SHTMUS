/* umacros.h */

/*   Useful Marcos */

/* drand48 is not available on MacOS */
/*
#define New_Rand(x) (long int)(x*drand48())
*/
#ifndef random
#include <stdlib.h>
#endif

#include <limits.h>
#define New_Rand(x) (long int)(x*((double)random()/(double) LONG_MAX))


#define XOR(t1,t2) ( ( (t1) && !(t2) ) || ( !(t1) && (t2) ) ) 


#define ACTIVATION(a,b) ( XOR (POS_CUEVAL(A), POS_CUEVAL(B) )
#define RECOGNITION(a,b) ( XOR (POS_CUEVAL(A), POS_CUEVAL(B) )

#define REAL_EQUAL(a,b) ( ((a)-(b))*((a)-(b)) <= MYERR*MYERR )
#define REAL_GREATER(a,b) ( (a)-(b) ) > MYERR
	/* i.e. returns non-zero if first variable (a) is greater than second */
	

/* below are new versions of these defines.  had to be made
 * compatible with real-valued (double) cue values (even if they
 * happen to have values 1 and 0).  
*/	
#define POS_CUEVAL(a)  (REAL_GREATER((a),0))
#define NON_POS_CUEVAL(a) (!REAL_GREATER((a),0))
#define NEG_CUEVAL(a)  ( (REAL_GREATER(0,(a))) || ((a)==0) )
#define UNK_CUEVAL(a)  (REAL_EQUAL(a,-1))
/* UNK should NEVER be called! it's not in working order for real valued! */


/* old version of macros for real-valued cues.  shoddy! */
/*
#define POS_CUEVAL(a)  (REAL_EQUAL(a,1))
#define NON_POS_CUEVAL(a) (!REAL_EQUAL(a,1))
#define NEG_CUEVAL(a)  (REAL_EQUAL(a,0))
#define UNK_CUEVAL(a)  (REAL_EQUAL(a,-1))
*/

/* original versions, designed for binary cues 
#define POS_CUEVAL(a)  ((a)==1)
#define NON_POS_CUEVAL(a) ((a)!=1)
#define NEG_CUEVAL(a)  ((a)==0)
#define UNK_CUEVAL(a)  ((a)==-1)
*/



