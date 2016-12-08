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
 * file: allalgutils.c 
 * purpose: utilities for all inference algorithms, e.g. scoring answers 
 */



#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "allalgutils.h"
#include "umacros.h"


long Correct_City (struct world_array_struct *World_Array, long city1,
long city2)
{
long bigger;


    if(DEBUG)printf("pop of city%ld= %ld.  pop of city%ld= %ld.\n",
        city1, World_Array[city1].pop, city2, World_Array[city2].pop);


    if (World_Array[city1].pop > World_Array[city2].pop)
        bigger= city1;
    else if (World_Array[city1].pop < World_Array[city2].pop)
        bigger= city2;
    else 
	{
		bigger= (New_Rand(2)) ? city1: city2;
	}	

/* FIX ME? make sure guess-score works right even when
 * a random bigger city returned.  probably should
 * return -1 or something like that when equal cities */

/* LONDON CHANGE */
/*
        printf("\n\nERROR-- cities %ld and %ld have same population\n\n", 
		 city1, city2);
        exit(1);
*/

	if(DEBUG2)printf("finished correct city\n");

return bigger;


}





void
Universal_Scorer(struct score_matrix_struct *score_matrix, 
long curr_per_index, long curr_city, long chosen, long correct, long guess,
long num_percents)
{
    /* fills in the correct and guess info  in the score matrix */

    /* chosen should be the number of the city chosen by the algorithem
    * in its inference.  guess should be 0 if didn't guess, 1 if did. */

    /* Adds 1 to the guess part if it was a guess. */
    /* Checks the chosen city against the correct city and
    * if the chosen one was correct, add one point to correct 
    * UNLESS two things:
    *   - GUESSCNT is set to 1, which means guesses are scored differently
    *   - and you did indeed guess (guess is 1).
    * In this exceptional case, 0.5 is added to correct without checking
    * what correct city is; i.e. the expectation is added on. */
    /* Does NOT score lookups since these apply only to a few algorithms */



    if (GUESSCNT && guess) {
        /* below are equivlaent to score_matrix[curr_city][curr_per_index] */
        (score_matrix[curr_city * num_percents + curr_per_index].guesses)++;
        (score_matrix[curr_city * num_percents + curr_per_index].correct)+= 0.5;

        if(DEBUG)printf("and this was GUESS SCORED\n");
    } else 
	{
        if (chosen == correct) 
		{
          /* below is equivlaent to score_matrix[curr_city][curr_per_index] */
          (score_matrix[curr_city * num_percents + curr_per_index].correct)++;
          if(DEBUG)printf("and this was CORRECT************\n");
        }
    	else if(DEBUG)printf("and this was INCORRECT____________\n");
    }

	if(DEBUG2)printf("finished universal scorer\n");

}
   





