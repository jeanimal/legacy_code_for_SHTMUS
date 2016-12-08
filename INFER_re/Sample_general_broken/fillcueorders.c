/*
 *            INFER SOFTWARE
 *
 *    Copyright (c) 1999 Jean Czerlinski & Dan Goldstein.
 *            All Rights Reserved
 *
 *
 * This software is confidential and proprietory information of the
 * above copyright holders. You shall not disclose such Confidential
 * Information and shall use it only in accordance with the terms of the
 * license agreement you entered into the above copyright holders.
 *
 */

/* INFER is for comparing the accuracy and frugality of
 * different inference (prediction) heuristics.
 *
 * The task is to infer which of two objects drawn from a population has
 * a higher value on a criterion variable based on several
 * numeric or binary variables.
 *
 * file: fillcueorders.c
 * purpose: for PMM inference heuristics, make array with cue order
 */


#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "llist.h"
#include "fillcueorders.h"


/* 
 * UPDATE May 20, 1999
 *
 * for Fill cue order by Validity,
 * if cues are equal validity, put in random order
 *  (rather than using the order they are already in).
 */


void
Fill_Ss_Cue_Order_Array_01234(long *Ss_Cue_Order_Array, long num_cues)
{
long cnt;

    for(cnt=0;cnt< num_cues+1;cnt++)
    {
        Ss_Cue_Order_Array[cnt]=cnt;

    }


}



/* we want to sort in descending order,
 * so if a < b, we have to return positive, not negative.
 */
int
Compare_cvo(const void *a, const void *b)
{
struct	cue_val_ord_struct	*cvo_a,
				*cvo_b;

	cvo_a= (struct cue_val_ord_struct *) a;
	cvo_b= (struct cue_val_ord_struct *) b;

	/* first case: if a's cv < b's cv */
	if ( REAL_GREATER(cvo_b->cv, cvo_a->cv) )
		return 1;
	else if ( REAL_GREATER(cvo_a->cv, cvo_b->cv) )
		return -1;
	else
		return 0;
}


void
Fill_Ss_Cue_Order_Array_By_Validity(struct alg_var_struct *alg_var, 
 long num_cues)
/* for Take The Best */
/* fills cue order array with numbers of cues (cue 3, cue1, etc.)
 * according to the validity of the cues, most valid first.
 * e.g. if cue 3 is the most valid cue and 1 the 2nd most valid,
 * then the array will have 3 1 ....
 * if cues validities are equal, they are filled in a random
 * order among themselves. (CHANGED Mar. 23, 2001).
 * OLD: for up to 100 equal cues (hi_cue_pos_ptr).
 */
{

long            i, /* a counter */
                /* Cue_Order_Recorder holds the OUTPUT, e.g. 3 1 2 */ 
               *Cue_Order_Recorder,
               /* num cues with equal validity */
		num_eq_valid;
int		which,  /* array index for which cue put in random next */
                cntr;
double         *Ex_Cv_Ar_Cpy,
                hi_val,
                last_hi_val,
               *dblptr,
               *Cv_Ptr;

               /* list of addresses of cues with equal highest validity */
               /* an array of pointers to double (Cv_Ptr) */
double         *hi_cue_pos_ptr[100];

long		*Ss_Cue_Order_Array;
double		*External_Cv_Array;

struct cue_val_ord_struct		*cue_val_ord;
/* for doing initial randomizer */
long		*Initial_Order;


	Ss_Cue_Order_Array= alg_var->ss_cue_order_array;
	External_Cv_Array= alg_var->cue_validity_array; 

	Initial_Order= (long *) malloc((num_cues+1)*sizeof(long));
	cue_val_ord= (struct cue_val_ord_struct *) malloc( (num_cues+1)
	  * sizeof(struct cue_val_ord_struct) );

	/* Make initial order random, so if some cues same value,
	 * so qsort doesn't leave them in the default environ order. 
	 * However, recognition cue is still first. */
	Initial_Order[0]= 0;
	/*
	for (i=1; i<num_cues+1; i++)
		Initial_Order[i]= i;
	*/
	Draw_Wo_Replacement(Initial_Order+1, num_cues);
	/* Draw_Wo fills in from 0 to num_cues-1 and reorders */
	for (i=1; i<num_cues+1; i++)
		Initial_Order[i]++;


	/* copy into my other form, for passing into qsort */
	/* but rather than a straight copy, copy in Initial Order */
	for (i= 0; i < num_cues+1; i++) {
		cue_val_ord[Initial_Order[i]].cv= External_Cv_Array[i];
		cue_val_ord[Initial_Order[i]].ord= i;	
	}
	

	/* sort-- but not recognition cue, which stays first! */
	qsort(cue_val_ord+1, num_cues, sizeof(struct cue_val_ord_struct),
	  Compare_cvo);
	
	/* copy back to structs external caller will see */
	for (i= 0; i < num_cues+1; i++) {
		External_Cv_Array[i]= cue_val_ord[i].cv;
		Ss_Cue_Order_Array[i]= cue_val_ord[i].ord;	
	}
	
	free(Initial_Order);
	free(cue_val_ord);
}









void Fill_Ss_Cue_Order_Array_RND(long *Ss_Cue_Order_Array, long num_cues)
{
/* for minimalist */

long cntr;


	Ss_Cue_Order_Array[0]= 0;  /* recognition first */

	/* then randomly order the rest */
	Draw_Wo_Replacement(Ss_Cue_Order_Array+1, num_cues);

	/* but we're returned an array from 0 to num_cues-1
	 * and we really want from 1 to num_cues, so add 1 to
	 * each. */


	for(cntr=1; cntr<num_cues+1; cntr++)
		Ss_Cue_Order_Array[cntr]++;


	/* Tada, that's all!  Simple enough, ain't it? */

}






void Put_Used_Cue_First(long *Ss_Cue_Order_Array, long last_used)
/* cues should already be in the array.  This function just moves
* (contents of) last_used to position 1 and the others get 
* scooted down one slot.  last_used should be the array position
* of the last cue used.
* Recall position 0 is the recognition cue. */
{
long cntr;
long temp;



	/* first test if there's any work to be done */
	if (last_used != 1) {

		/* store info before shift */
		temp= Ss_Cue_Order_Array[last_used];

		/* now shift right */
		for (cntr= last_used-1; cntr>0; cntr--) {
			Ss_Cue_Order_Array[cntr+1]= Ss_Cue_Order_Array[cntr];
		}

		/* now put the stored value of last_used into first position */
		Ss_Cue_Order_Array[1]= temp;

	}

}

