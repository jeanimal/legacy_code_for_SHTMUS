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
 * file: pmmutils.c
 * purpose: utilities for the PMM inference heuristics, e.g. Take The Best
 */


#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "pmmutils.h"
#include "umacros.h"
#include "pprint.h"

/* leave set to 1.0 until incorporated into cue validity counting */
#define MULTDIFF 1.0



long
Compare_Cues(struct world_array_struct *Ss_Knowledge_Array, long city1, long city2, long cue_num)
 /* activates if one city has positive cue and other does not */
/* assumes the only possible cue values are 1, 0, -1. */
{

	if(DEBUG)printf("cue %ld tried:", cue_num );
	if(DEBUG)printf(" %lf vs. %lf \n", Ss_Knowledge_Array[city1].cue[cue_num], 
	 Ss_Knowledge_Array[city2].cue[cue_num]);

/* TEMP CHANGE FOR REAL VALUES!! */

/*
   if (POS_CUEVAL(Ss_Knowledge_Array[city1].cue[cue_num]) &&
	NON_POS_CUEVAL(Ss_Knowledge_Array[city2].cue[cue_num]))
		return city1;
   else
   		if ( POS_CUEVAL(Ss_Knowledge_Array[city2].cue[cue_num]) &&
		 NON_POS_CUEVAL(Ss_Knowledge_Array[city1].cue[cue_num]))
      		return city2;
   		else
      		return -1;
*/

	if (Ss_Knowledge_Array[city1].cue[cue_num] >
	   MULTDIFF*Ss_Knowledge_Array[city2].cue[cue_num])
		return city1;
	else
	if (Ss_Knowledge_Array[city2].cue[cue_num] >
       MULTDIFF*Ss_Knowledge_Array[city1].cue[cue_num])
		return  city2;
	else
		return -1; 

}






                         
long
Compare_Recognition(struct world_array_struct *Ss_Knowledge_Array,
                    long city1, long city2)
/* for this algorithm, happens to work same as cues */
{
long             temp;


        if ( (Ss_Knowledge_Array[city1].cue[0] == 1) ||
        (Ss_Knowledge_Array[city2].cue[0] == 1) )
                temp = Compare_Cues(Ss_Knowledge_Array, city1, city2, 0);
        else
                temp= -666;  /* will guess city shortly
*/

        return temp;

}
 






long
Pick_City_PMM(struct world_array_struct *Ss_Knowledge_Array, long
*Ss_Cue_Order_Array, long city1, long city2, long *guess, long *cues_used,
long num_cues)
{

long             valid_cntr;
long             activated;
/* -1 if not activated and city# of chosen city if activated */
/* if don't recognize either city, activated= -666 until guess city
 later */

   /* first do recognition cue */

   valid_cntr = 0;

/* recognition not used for MONTEC */
/* 

   activated = Compare_Recognition(Ss_Knowledge_Array,
                                   city1, city2);

*/

	activated= -1;
   /* now do other cues as necessary */
   while ((activated == -1) && (valid_cntr < num_cues ))
   {
      valid_cntr++;
      if (DEBUG) Print_long_Array(Ss_Cue_Order_Array, num_cues+1);
      activated = Compare_Cues(Ss_Knowledge_Array, city1,
        city2, Ss_Cue_Order_Array[valid_cntr] );
   }

   *cues_used= 2 * (valid_cntr+1);


   /*
    * next take care of case where no cue activated, which results in 
	* randomly picking a city.  Also do random if neither city had been
    * recognized before.
    */
 
   *guess = 0;
   if  (activated < 0)
   {
      activated = (New_Rand(2)) ? city1 : city2;
     if(DEBUG)printf("_____________________________ only GUESSED!\n");
      *guess = 1;
   }
   return activated;

}








