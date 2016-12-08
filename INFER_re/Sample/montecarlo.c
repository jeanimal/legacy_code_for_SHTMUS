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
 * file: montecarlo.c
 * purpose: instead of reading real data, you can generate it randomly
 */


/* montecarlo routines, set up for PMM programs *
/* written Dec 95 / Jan 96 */

#include <stdio.h>
#include <stdlib.h>

#include "main.h"
#include "mathutils.h"
#include "bitutils.h"
#include "montecarlo.h"
#include "filldatastrs.h"
#include "umacros.h"



void Build_World_Basics(struct world_array_struct *world,
struct useful_variables_struct useful)
/* fills in the info common to all build world functions,
 * like the ranks and all that. 
 */
{
long case_cntr;
long cue_cntr;
long BIG= 10000; 


	if(useful.num_cities > BIG)
		printf("WARNING: num cities > %ld\n", BIG);


    for (case_cntr=0; case_cntr < useful.num_cities; case_cntr++)
    {
		world[case_cntr].name[0]= 'x';
		world[case_cntr].name[1]= '\0';
		world[case_cntr].rank= case_cntr;
		world[case_cntr].pop= BIG-case_cntr;
         /* first "cue" is actually recognition or not--
          *   used in knowledge array, here simply 1 */		
		world[case_cntr].cue[0]= 1;
	}

}






void Build_World_Binomial(struct world_array_struct *world,
struct useful_variables_struct useful)
/* fills in world cues (not recognition) with a p=50% chance of
 * being 1 or 0, making a binomial distribution of 1's and 0's.
 * Another version could be written to input the value of p. 
 */
{
long case_cntr;
long cue_cntr;


	Build_World_Basics(world, useful);


	/* now for the cues... (besides recognition at position 0) */

	for(case_cntr=0; case_cntr < useful.num_cities; case_cntr++)
	{
		for(cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++)
		{
			/* randomly (50%) set the cue to be 0 or 1 */
			if (rand() % 2 == 0) 
				world[case_cntr].cue[cue_cntr]= 0;
			else
				world[case_cntr].cue[cue_cntr]= 1;

			/* below is a fast but less flexible version:
			 * world[case_cntr].cue[cue_cntr]= (double)  New_Rand(2); 
			 */
		}
	}

	/* awfully easy, eh?  I should have done this years ago! */


}
 




void Build_World_Planar(struct world_array_struct *world,
struct useful_variables_struct useful)
/* fills in world cues (not recognition) with a p=50% chance of
 * being 1 or 0, making a binomial distribution of 1's and 0's.
 * Another version could be written to input the value of p.
 */
/* Criterion is (1^l)*cue1 + (2^l)*cue2 + (3^l)*cue3 + ..+ noise.
 *  currently l is set to 1. 
 */
{
long case_cntr,
	 cue_cntr,
	temp_pop;


    Build_World_Basics(world, useful);

    /* now for the cues... (besides recognition at position 0) */

    for(case_cntr=0; case_cntr < useful.num_cities; case_cntr++)
    {
		temp_pop= 0;
        for(cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++)
        {
            /* randomly (50%) set the cue to be 0 or 1 */
            if (rand() % 2 == 0)
                world[case_cntr].cue[cue_cntr]= 0;
            else
                world[case_cntr].cue[cue_cntr]= 1;
			temp_pop+= cue_cntr * (long) (world[case_cntr].cue[cue_cntr]);
        }
/*
		temp_pop+= rand() % (useful.num_cues) - (useful.num_cues) / 2; 
*/
		world[case_cntr].pop= temp_pop;
    }


}





void Build_World_Uniform(struct world_array_struct *world,
struct useful_variables_struct useful)
/* fills in world cues such that each combo is equally likely.
 * This is done by first randomly (uniformly) selecting an
 * integer from 0 to 2^(num_cities)-1 and then converting it
 * into its appropriate bit string.
 * (This is truly uniform, allowing repeats, unlike Laura's
 *  ideas used in the pattern matching algorithm.)
 * NOTE: other uniform distributions could be used, e.g.
 * uniform across the cues of each city or uniform across
 * the whole matrix of cities x cues.	
 * WARNING: This function won't work well if 2^(num_cities)-1
 * gets too close to RANDMAX.  Randomness will be compromised.
 */
{
long case_cntr;
long cue_cntr;

long this_vector;
long vector_max;


	Build_World_Basics(world, useful);


	/* now for the cues... (besides recognition at position 0) */

	vector_max= power2_long( (long) useful.num_cities) - 1;

	for(case_cntr=0; case_cntr < useful.num_cities; case_cntr++)
	{
		for(cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++)
		{
			/* choose a number from 0 to vector_max;
		     * to make this inclusive of vector_max, must add 1.
			 * (I know, this undoes the 1 I subtracted but is clearer.) 
			 */ 
			this_vector= New_Rand(vector_max+1);
			Convert_To_City_Array(this_vector, cue_cntr, world,
			 useful.num_cities);
		}
	}
	


}







void Print_Just_Cues(struct world_array_struct *this_struct,
long num_cities, long num_cues)
/* prints population (target variable) followed by * for a 1
 * and blank for a zero.  Recognition cue not included. */
{

long data_num;
long cue_num;

    for (data_num=0; data_num < num_cities; data_num++) {
		if(DEBUG)printf("%8ld : ", this_struct[data_num].pop);
        for (cue_num=1; cue_num < num_cues+1; cue_num++)
        {
            if ( REAL_EQUAL(this_struct[data_num].cue[cue_num], 1.0) )
            {
                printf("* ");
            }
            else
                printf("  ");
        }
        printf("\n");
    }

}











void Print_Just_Cues_To_File(struct world_array_struct *this_struct, 
long num_cities, long num_cues)
{

long data_num;
long cue_num;
FILE *mc;

    mc= fopen("montec_out", "a");

    if(DEBUG)printf("printing cues to montec_out\n");
    for (data_num=0; data_num < num_cities; data_num++) {
        for (cue_num=1; cue_num < num_cues+1; cue_num++)
        {
            if(DEBUG)printf("%lf.", this_struct[data_num].cue[cue_num]);
            if ( REAL_EQUAL(this_struct[data_num].cue[cue_num], 
             this_struct[data_num].cue[cue_num]) )
            {
                fprintf(mc, "  ");
            }
            else
                fprintf(mc, "* ");
        }
        fprintf(mc, "\n");
        if(DEBUG)printf("\n");
    }

    fclose(mc);

}





void Print_Montec_Score(struct score_struct *score_ptr1,
struct score_struct *score_ptr2, 
struct useful_variables_struct useful, struct sim_info_struct sim_info, 
char *out_file_name, long num_quest)
{
FILE *outptr;
double divider;

	outptr= fopen(out_file_name, "a");
	if (outptr == NULL)
	{
		printf("failed to open score output file!\n");
		exit(1);
	}

    divider= (double) num_quest * (double) sim_info.Repchoice;

	fprintf(outptr, "%5ld %5ld: %12.1lf %12.1lf    %8ld %12.6lf %12.6lf\n", 
	 useful.num_cities, useful.num_cues, 
	 (score_ptr1->correct), (score_ptr2->correct), 
	 num_quest, 
	((score_ptr1->correct)/divider), ((score_ptr2->correct)/divider) );

	fclose(outptr);

}







/*
void Print_Just_One_Score(struct score_matrix_struct *score_matrix,
long curr_per_index, long curr_city, long Questchoice, long Repchoice)
{
FILE *mc;
double divider;

    mc= fopen("montec_out", "a");

    divider= (double) Questchoice * (double) Repchoice;
    if(DEBUG)printf("divider= %lf\n", divider);

    if(DEBUG)printf("curr_per_index= %ld, curr_city= %ld\n", curr_per_index,
        curr_city);

    if(DEBUG)printf("correct= %lf\n",
        score_matrix[ curr_city * num_percents  +
          curr_per_index ].correct);
    fprintf(mc, "%lf\n", score_matrix[ curr_city * useful.num_percents  +
        curr_per_index  ].correct / divider);

    fclose(mc);

}

*/



