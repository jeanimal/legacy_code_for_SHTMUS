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
 * file: takethebest.c
 * purpose: assuming all data structures filled, implements the Take The Best inference heuristic 
 */


#include <stdio.h>
#include "main.h"
#include "allalgutils.h"
#include "pmmutils.h"
#include "umacros.h"
#include "takethebest.h"



long
Take_The_Best(struct world_array_struct *ss_knowledge_array,
struct world_array_struct *world_array,
long city1, long city2, long curr_per_index, long curr_city,
struct score_matrix_struct *score_matrix_ptr,
struct useful_variables_struct useful,
struct alg_var_struct alg_var)

/*
 * Assumes the cues in alg_var.ss_cue_order_arry have been ordered in decreasing
 * cue validity (except that recognition still comes first).
 * The algorithm works by checking the cues in order (recognition, most
 * valid cue, next most valid cue, ...) until one is found that
 * discriminates.  The inference of which case [city] is bigger is then
 * made on the basis of this one best cue.
 * GUESSING: if neither city is recognized or no cue discriminates,
 * the algorithm guesses.
 * The function then scores number of cues looked up
 * (looking up "one" cue for two cities counts as two lookups),
 * the number of guesses made, and the number of correct
 * inferences. This info is all written to the score_matrix.
 */
/* the Cv array and num_cues are not used by this algorithm, but they
 * must be there for compatibility with the other algies */

{

long             cues_used;
long             guess=0;
long             city_chosen;
long             bigger_city;




   city_chosen = Pick_City_PMM(ss_knowledge_array, alg_var.ss_cue_order_array,
    city1, city2, &guess, &cues_used, useful.num_cues);

   if(DEBUG)printf("between city %ld and %ld,\n", city1, city2);
   if(DEBUG) printf("city %ld chosen\n", city_chosen);


    bigger_city= Correct_City(world_array, city1, city2);
    if(useful.categorize && (bigger_city == -1))
        guess= 1;
    /* score as a guess if equal target variable size */


    Universal_Scorer(score_matrix_ptr, curr_per_index, curr_city, city_chosen,
     bigger_city, guess, useful.num_percents);


    /* below is equivalent to score_matrix[curr_city][curr_per_index] */
    (score_matrix_ptr[ curr_city * useful.num_percents +
        curr_per_index ].lookups)+= cues_used;


   /* the function used to return guess but now simply adds it in to
    * the score_matrix (in the Universal_Scorer).
    * So now nothing is returned-- do not
    * panic */


}
                         
