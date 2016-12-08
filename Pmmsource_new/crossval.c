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
 * file: crossval.c
 * purpose: implements cross-validation when CROSSVALIDATE is 1
 */


/* 
 * functions needed to cross-validate scores.  that is, model is built
 * on a random half of the data and then tested on other half; score is
 * from other half.
 *
 * written April 1997 by JFC
 *
 * have a nice day.
 */


#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "crossval.h"
#include "llist.h"
#include "pprint.h"


void Copy_World(struct world_array_struct *into_me, 
struct world_array_struct *copy_me, long num_cases, long num_cues)
/* space should already be malloc'ed */
{
long cnt_cases,
	 cnt_cues;

	for(cnt_cases=0; cnt_cases< num_cases; cnt_cases++)
	{
		into_me[cnt_cases].rank= copy_me[cnt_cases].rank;
		into_me[cnt_cases].pop= copy_me[cnt_cases].pop;
		for(cnt_cues=0; cnt_cues< num_cues+1; cnt_cues++)
			into_me[cnt_cases].cue[cnt_cues]= copy_me[cnt_cases].cue[cnt_cues];
	/* num_cues+1 because of recognition cue in position 0 */
	}

}



void Copy_World_Guided(struct world_array_struct *into_me,
struct world_array_struct *copy_me, long begin, long end, long *case_array,
long num_cues)
{
long cnt_cases,
     cnt_cues;

    for(cnt_cases= 0; cnt_cases<= end-begin; cnt_cases++)
	{
	    into_me[cnt_cases].rank= copy_me[case_array[cnt_cases+begin]].rank;
        into_me[cnt_cases].pop= copy_me[case_array[cnt_cases+begin]].pop;
        for(cnt_cues=0; cnt_cues< num_cues+1; cnt_cues++)
            into_me[cnt_cases].cue[cnt_cues]= 
			 copy_me[case_array[cnt_cases+begin]].cue[cnt_cues];
	}

}



void Crossval_Split(struct world_array_struct *world, struct world_array_struct *actual_world, struct world_array_struct *modelling_world, struct useful_variables_struct useful)
/* then copies one random half of actual 
world back into world, other random half goes into modelling_world. if odd
number of items, e.g. 35, then 17 go into modelling, 17 into world, and 
one is left out (from this round-- don't worry it'll come back later). */
{
long *itemlist;
long cntr, firsthalf;

	itemlist= (long *) malloc(useful.actual_num_cities*sizeof(long));
	Draw_Wo_Replacement(itemlist, useful.actual_num_cities);
	
	if(DEBUG2)
	{
		printf("numbers guiding split into test and model world:\n");
		Print_long_Array(itemlist, useful.actual_num_cities);
	}

	Copy_World_Guided(world, actual_world, 0, useful.num_cities-1, itemlist, useful.num_cues);     
	Copy_World_Guided(modelling_world, actual_world, useful.num_cities, 2*useful.num_cities-1, itemlist, useful.num_cues);

	if(DEBUG)
	{
printf("\n\nbelow is actual world\n");
Print_World_Array_Struct(actual_world, useful.actual_num_cities, useful.num_cues);
printf("\nbelow is test world\n");
	Print_World_Array_Struct(world, useful.num_cities, useful.num_cues);
printf("\nbelow is modelling world\n");
Print_World_Array_Struct(modelling_world, useful.num_cities, useful.num_cues);
	}

	free(itemlist);

}


