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
 * file: takethelast.c
 * purpose: assuming all data structures filled, implements the take the last inference heuristic
 */


#include <stdio.h>
#include "main.h"
#include "allalgutils.h"
#include "pmmutils.h"
#include "takethelast.h"
#include "fillcueorders.h"


long
Take_The_Last(struct world_array_struct *ss_knowledge_array,
struct world_array_struct *world_array,
long city1, long city2, long curr_per_index, long curr_city,
struct score_matrix_struct *score_matrix_ptr,
struct useful_variables_struct useful,
struct alg_var_struct alg_var)
{
/* In the beginning... cues assumed to be randomly ordered.
* But later they will be ordered by recency of use, thus the algorithm
* will take the most recent cue that discriminates ("take the last").
* This is accomplished by taking the cue used on the current pass of
* the algorithm to the beginning of the list (as the first regular
* cue, though recognition comes first).  This function works basically
* like Take_The_Best-- see comments there for more info. */

long             cues_used;
long             guess=0;
long             city_chosen;
long             bigger_city;

   city_chosen = Pick_City_PMM(ss_knowledge_array, alg_var.ss_cue_order_array, 
	city1, city2, &guess, &cues_used, useful.num_cues);

   if(DEBUG)printf("between city %ld and %ld,\n", city1, city2);
   if(DEBUG) printf("city %ld chosen\n", city_chosen);

    bigger_city= Correct_City(world_array, city1, city2);
    Universal_Scorer(score_matrix_ptr, curr_per_index, curr_city, city_chosen, bigger_city, guess, useful.num_percents);
                                                                                

	/* below is equivlaent to score_matrix[cure_city][curr_per_index] */
	(score_matrix_ptr[ curr_city * useful.num_percents +
        curr_per_index ].lookups)+= cues_used;


   /* Now reorder the cues if a cue (not recognition) did discriminate */
   /* cues_used had better be even because comparing 2 cities over 
    * a given cue means two more cues looked up.  subtract 2 to discount
    * the two recognition "cues" looked up.  */

   if( (cues_used>2) && (cues_used<2*(useful.num_cues+1)) ) {
     Put_Used_Cue_First(alg_var.ss_cue_order_array, (cues_used-2)/2);
   }


   /* the function used to return guess but now simply adds it in to
        * the score_matrix.  So now nothing is returned-- do not
        * panic -- do not run for your towel */
 



}


