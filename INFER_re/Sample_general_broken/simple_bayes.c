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
 * file: simple_bayes.c
 * purpose: implements naive bayes inference heuristic
 */


#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "allalgutils.h"
#include "pmmutils.h"
#include "umacros.h"
#include "simple_bayes.h"


/* written March, 1999, by Jean Czerlinski,
 * at Laura Martignon's suggestion   
*/


long
Simple_Bayes(struct world_array_struct *ss_knowledge_array,
struct world_array_struct *world_array,
long city1, long city2, long curr_per_index, long curr_city,
struct score_matrix_struct *score_matrix_ptr,
struct useful_variables_struct useful,
struct alg_var_struct alg_var)

/*
 * Determines whether it is more likely that city1 or city2 has the
 * higher criterion, given the cue validities in alg_var.cue_validity_array 
 *
 * if an object (city) has a higher value for a given cue, its likelihood
 * gets multiplied by the cue validity of the cue while the other 
 * object's likelihood is multiplied by one minus the cue validity.
 */

{

double		likelihood1, /* running product-- likelihood city 2 bigger */
		likelihood2; /* running product-- likelihood city 2 bigger */
long             guess=0; /* set to 1 in rare case that likelihoods  equal */
long             chosen;
long             correct;
long 		cue_cntr;



   likelihood1= likelihood2= 1;
   /* do not use 0 as a start because we will be multiplying! */

   for (cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++) 
   {
      if (world_array[city1].cue[cue_cntr] > 
          world_array[city2].cue[cue_cntr]   )
      {
         likelihood1*= alg_var.cue_validity_array[cue_cntr];
         likelihood2*= (1 - alg_var.cue_validity_array[cue_cntr]);
      }
      else if (world_array[city2].cue[cue_cntr] >
               world_array[city1].cue[cue_cntr]   )
      {
         likelihood1*= (1 - alg_var.cue_validity_array[cue_cntr]);
         likelihood2*= alg_var.cue_validity_array[cue_cntr]; 
      }
      /* else (i.e. if cues equal) leave likelihood alone */

   }

        if ( REAL_EQUAL(likelihood1, likelihood2) )
        {
                chosen= (New_Rand(2)) ? city1 : city2;
                guess= 1;
                if(DEBUG)printf("____________simple Bayes only GUESSED!\n");
        }
        else if (likelihood1 > likelihood2)
                chosen= city1;
        else if (likelihood2 > likelihood1)
                chosen= city2;
        if(DEBUG)printf("likelihood1= %lf, likelihood2= %lf\n", 
          likelihood1, likelihood2);
        if(DEBUG)printf("SO city %ld chosen\n", chosen);


        correct= Correct_City(world_array, city1, city2);

        Universal_Scorer(score_matrix_ptr, curr_per_index, curr_city, chosen, 
         correct, guess, useful.num_percents);




   /* the function used to return guess but now simply adds it in to
    * the score_matrix (in the Universal_Scorer).
    * So now nothing is returned-- do not
    * panic */


}
                         
