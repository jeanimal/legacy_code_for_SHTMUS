/* backup file */

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

/* backup file */


#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "llist.h"
#include "fillcueorders.h"




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
{

long             i,
               *Cue_Order_Recorder;
double         *Ex_Cv_Ar_Cpy,
                hi_val,
               *hi_cue_pos_ptr,
               *dblptr,
               *Cv_Ptr;

long				*Ss_Cue_Order_Array;
double			*External_Cv_Array;

	Ss_Cue_Order_Array= alg_var->ss_cue_order_array;
	External_Cv_Array= alg_var->cue_validity_array; 
	

	/* init array -- malloc */
	Ex_Cv_Ar_Cpy= (double *) malloc( (num_cues+1) * sizeof(double) );

   /* Make a copy of External_Cv_Array which can be damaged */
   dblptr = Ex_Cv_Ar_Cpy;
   for (i = 0; i <= num_cues; i++)
      *dblptr++ = *External_Cv_Array++;
   /* Set the first position to the index of recgn cue */
   *Ss_Cue_Order_Array = 0;

   /*
    * start with done=1 since recognition cue is always
        first; only the other  cues are ordered by validity
    */
for (Cue_Order_Recorder = Ss_Cue_Order_Array + 1; Cue_Order_Recorder - Ss_Cue_Order_Array <= num_cues; Cue_Order_Recorder++)
   {
   hi_cue_pos_ptr=NULL;
   hi_val = -1;
      for (Cv_Ptr = Ex_Cv_Ar_Cpy + 1; Cv_Ptr - Ex_Cv_Ar_Cpy <= num_cues;
 Cv_Ptr++)
      {
         if (*Cv_Ptr > hi_val)
         {
            hi_val = *Cv_Ptr;
            hi_cue_pos_ptr = Cv_Ptr;
         }
      }
      if (!hi_cue_pos_ptr)
      {
         printf("no high cue found!");
         exit(1);
      }
      *hi_cue_pos_ptr = -1;
      *Cue_Order_Recorder = hi_cue_pos_ptr - Ex_Cv_Ar_Cpy;
   }

   free(Ex_Cv_Ar_Cpy);

}









void Fill_Ss_Cue_Order_Array_RND(long *Ss_Cue_Order_Array, long num_cues)
{
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

