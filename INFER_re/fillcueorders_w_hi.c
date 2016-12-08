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


	Ss_Cue_Order_Array= alg_var->ss_cue_order_array;
	External_Cv_Array= alg_var->cue_validity_array; 

	cue_val_ord= (struct cue_val_ord_struct *) malloc( (num_cues+1)
	  * sizeof(struct cue_val_ord_struct) );

	/* copy into my other form, for passing into qsort */
	for (i= 0; i < num_cues+1; i++) {
		cue_val_ord[i].cv= External_Cv_Array[i];
		cue_val_ord[i].ord= i;	
	}
	
	/* TO DO: randomize first */

	/* sort, but keep recognition cue first! */
	
	/* copy back to structs external caller will see */
	for (i= 0; i < num_cues+1; i++) {
		External_Cv_Array[i]= cue_val_ord[i].cv;
		Ss_Cue_Order_Arry[i]= cue_val_ord[i].ord;	
	}


	/* init array -- malloc */
	Ex_Cv_Ar_Cpy= (double *) malloc( (num_cues+1) * sizeof(double) );
        /* whenever you do a malloc, be sure to do a free at the end! */

   /* Make a copy of External_Cv_Array which can be damaged */
   dblptr = Ex_Cv_Ar_Cpy;
   for (i = 0; i <= num_cues; i++)
      *dblptr++ = *External_Cv_Array++;
   /* Set the first position to the index of recgn cue */
   *Ss_Cue_Order_Array = 0;

   last_hi_val= 9999;  /* first time so there is no last hi */

for (Cue_Order_Recorder = Ss_Cue_Order_Array + 1; Cue_Order_Recorder - Ss_Cue_Order_Array <= num_cues; Cue_Order_Recorder++)
{
   hi_val = -1;

  for (Cv_Ptr = Ex_Cv_Ar_Cpy + 1; Cv_Ptr - Ex_Cv_Ar_Cpy <= num_cues; Cv_Ptr++)
  {
      /* find the cue or cues which have the next highest validity */
         if ( (*Cv_Ptr > hi_val) && (*Cv_Ptr < last_hi_val) )
         {
            hi_val = *Cv_Ptr;
            hi_cue_pos_ptr[0] = Cv_Ptr; /* store address of cue */
            if(DEBUG)
               printf("assigned hi to cv %lf\n", *(hi_cue_pos_ptr[0]) );
            num_eq_valid= 1;
         }
         else if (REAL_EQUAL (*Cv_Ptr, hi_val) )
         {
            hi_cue_pos_ptr[num_eq_valid] = Cv_Ptr;
            if(DEBUG)
              printf("  an equal hi\n");
            num_eq_valid++;
         }
  } /* end for Cv_Ptr */

/*
      if ((hi_cue_pos_ptr[0] < Cv_Ptr) || (hi_cue_pos_ptr[0] > (Cv_Ptr+num_cues)))
      {
         printf("no high cue found! pointing to %lf \n", *(hi_cue_pos_ptr[0]) );
         exit(1);
      }
*/

      /* now record the hi cues found into the  order array */

      /* if more than 1 cue, choose the next cue recorded randomly */
      while (num_eq_valid > 1)
      {
        which= New_Rand(num_eq_valid);
        /* subtract the addresses to get the cue number for cue order */
        *Cue_Order_Recorder = hi_cue_pos_ptr[which] - Ex_Cv_Ar_Cpy; 
        /* shove everything over one spot to fill the hole */
        for (cntr= which; cntr < num_eq_valid-1; cntr++)
          hi_cue_pos_ptr[cntr]= hi_cue_pos_ptr[cntr+1];
        num_eq_valid--;

        /* ALSO INCREMENT FOR LOOP HERE!! */
        Cue_Order_Recorder++;

      }

      /* by now, num_eq_valid should be == 1 , only 1 cue left */
      if (num_eq_valid == 1)
        *Cue_Order_Recorder = hi_cue_pos_ptr[0] - Ex_Cv_Ar_Cpy;
      else
        printf("ERROR: num_eq_valid = %d\n", num_eq_valid);

      last_hi_val= hi_val;

} /* end for Cue_Order_Recorder */

   free(Ex_Cv_Ar_Cpy);

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

