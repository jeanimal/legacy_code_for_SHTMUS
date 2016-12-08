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
 * file: weighted.c
 * purpose: after data structures filled, implements the (cue-validity) weighted linear inference heuristic
 */




#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "umacros.h"
#include "allalgutils.h"
#include "linutils.h"
#include "weightedlinear.h"



/* weighted linear algorithm
* for the Fast & Frugal contest */

/* Under the directorship of DANimal Goldstein
* and programmed by 'imal and his trusty sidekick
* Mean-Jean-tha-Programming-Machine. */

/* October 1995 */





long
Weighted_Linear(struct world_array_struct *ss_knowledge_array,
struct world_array_struct *world_array,
long city1, long city2, long curr_per_index, long curr_city,
struct score_matrix_struct *score_matrix_ptr,
struct useful_variables_struct useful,
struct alg_var_struct alg_var)

{

double weight1, /* total weight for city1 */
 weight2; /* total weight for city2 */
long cue_cntr;
long chosen;
long correct;
long guess=0;
	
	if (DEBUG)printf("\n\nbetween cities %ld and %ld...\n", city1, city2);

	weight1= weight2=0;

	/* no recognition so just don't check that cue for now, so
	 * start with cue 1 */

/* TEMP CHANGE FOR REAL VALUES!! */

	for (cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++) {
		weight1 += 
/* (double)Get_Cue_Type(ss_knowledge_array, city1, cue_cntr) * */
world_array[city1].cue[cue_cntr] *
(alg_var.cue_validity_array[cue_cntr] );
        weight2+= 
/* (double)Get_Cue_Type(ss_knowledge_array, city2, cue_cntr) * */
world_array[city2].cue[cue_cntr] *
(alg_var.cue_validity_array[cue_cntr] );
	}
        if ( REAL_EQUAL(weight1, weight2) )
        {
			chosen= (New_Rand(2)) ? city1 : city2;
			guess= 1;
        	if(DEBUG)printf("______________weighted linear only GUESSED!\n");
        }
	else if (weight1 > weight2)
		chosen= city1;
	else if (weight2 > weight1)
		chosen= city2;
	if(DEBUG)printf("weight1= %lf, weight2= %lf\n", weight1, weight2);
	if(DEBUG)printf("SO city %ld chosen\n", chosen);

    correct = Correct_City(world_array, city1, city2);
    Universal_Scorer(score_matrix_ptr, curr_per_index, curr_city, chosen, correct, guess, useful.num_percents);


}










long
Weighted_Linear_5(struct world_array_struct *ss_knowledge_array,
struct world_array_struct *world_array,
long city1, long city2, long curr_per_index, long curr_city,
struct score_matrix_struct *score_matrix_ptr,
struct useful_variables_struct useful,
struct alg_var_struct alg_var)
{

double weight1, /* total weight for city1 */
 weight2; /* total weight for city2 */
long cue_cntr;
long chosen;
long correct;
long guess= 0;


        if (DEBUG)printf("\n\nbetween cities %ld and %ld...\n", city1, city2);

        weight1= weight2=0;
        for (cue_cntr=0; cue_cntr < useful.num_cues+1; cue_cntr++) {
        	weight1 += (double)Get_Cue_Type(ss_knowledge_array, city1,
                 cue_cntr) * (alg_var.cue_validity_array[cue_cntr] - .5);
        	weight2+= (double) Get_Cue_Type(ss_knowledge_array, city2,
                 cue_cntr) * (alg_var.cue_validity_array[cue_cntr] - .5);
        }
        if (REAL_EQUAL(weight1,weight2))
        {
        	chosen= (New_Rand(2)) ? city1 : city2;
			guess= 1;
        	if(DEBUG)printf("______________weighted linear only GUESSED!\n");
        }
        else if (weight1 > weight2)
                chosen= city1;
        else if (weight2 > weight1)
                chosen= city2;
        if(DEBUG)printf("weight1= %lf, weight2= %lf\n", weight1, weight2);
        if(DEBUG)printf("SO city %ld chosen\n", chosen);

    correct = Correct_City(world_array, city1, city2);
    Universal_Scorer(score_matrix_ptr, curr_per_index, curr_city, chosen, correct, guess, useful.num_percents);


}



