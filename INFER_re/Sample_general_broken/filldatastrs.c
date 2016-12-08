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
 * file: filldatastrs.c
 * purpose: fill data structures, e.g. question array, knowledge array
 */

#include <stdlib.h>
#include <stdio.h>
#include "main.h"
#include "filldatastrs.h"
#include "umacros.h"
#include "llist.h"
#include "string.h"
#include "pprint.h"


/* Data Structure Filling Routines */

void
Fill_Question_Array(struct question_pair_struct *Quest_Point, long num_cities)
{
long *Array_Point;
long i;
long temp;
long *Temp_Arr;

	/* init array -- malloc */
	Temp_Arr= (long *)malloc( (num_cities*num_cities-num_cities) * sizeof(long) );

	Draw_Wo_Replacement(Temp_Arr, num_cities*num_cities-num_cities);

	Array_Point=Temp_Arr;
	for (i=0;i<(num_cities*(num_cities-1)/2);i++)
	{
		do 
		{
     		Quest_Point->obj1=(*Array_Point)/num_cities;
     		Quest_Point->obj2=(*Array_Point)%num_cities;
     		Array_Point++;
     	}
  		while (Quest_Point->obj1>=Quest_Point->obj2);

  		if (New_Rand(2))
        {
        	temp=Quest_Point->obj1;
        	Quest_Point->obj1=Quest_Point->obj2;
        	Quest_Point->obj2=temp;
        }
		Quest_Point++;
 	} /* end for i */

	free(Temp_Arr);

} /* end function Fill_Question_Array */










void 
Fill_Ss_Knowledge_Array(long *known_cities, long num_cities_known,
double proportion_cues_known, struct world_array_struct *world,
struct world_array_struct *s_knowledge, struct useful_variables_struct
useful)
{

/* fills in "proportion_cues_known" of the cues from known cities.
 * e.g. if 2 cities known, each with 10 cues, then there are 20
 * potentially known cues.  if 0.6 is proportion known, then this
 * function will randomly assign 0.6*20= 12 of the cues to be
 * known and the rest (8 cues) to be unknown. */

long city_cntr,
  cue_cntr;
long array_cntr;
long total_cues,
  chosen_cues,
  tot_chosen;
long test_city,
  test_cue;


	if(DEBUG2) {
		printf("on entering fill Ss, here is world:");
	            Print_World_Array_Struct(world, useful.num_cities,
                useful.num_cues);
	}


/* first initialize the subject's knowledge struct */
/* if few cues known, initialize as know nothing because then few need
to be changed to their known values; if many cues known, initialize as
with the known cities filled in with data and then eliminate the few
unknown cues.  In each case the "changes" will be indicated by the
"chosen" cues */

	for (city_cntr=0; city_cntr < useful.num_cities; city_cntr++)
	{ 
		strcpy(s_knowledge[city_cntr].name, world[city_cntr].name);
		s_knowledge[city_cntr].rank= world[city_cntr].rank;
		s_knowledge[city_cntr].pop= world[city_cntr].pop;
		s_knowledge[city_cntr].cue[0]= 0; /* city unrecognized */
		for (cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++)
		{
			s_knowledge[city_cntr].cue[cue_cntr]= -1;
			/* all cues are ? (don't know) by default */
		}
	}

    if (proportion_cues_known > 0.5)
	{ 
    	for (array_cntr=0; array_cntr < num_cities_known; array_cntr++) 
		{
        	s_knowledge[known_cities[array_cntr]].cue[0]= 1;
        	for (cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++) 
			{
				s_knowledge[known_cities[array_cntr]].cue[cue_cntr]=
				  world[known_cities[array_cntr]].cue[cue_cntr];
            } /* end for cue_cntr */
        } /* end for array_cntr */
    } else /* contra if proportion_cues_known > 0.5 */
	{
        for (array_cntr=0; array_cntr < num_cities_known; array_cntr++) 
		{
            s_knowledge[known_cities[array_cntr]].cue[0]= 1;
        }
    } /* else proportion_cues_known */


/* now make the changes on the "chosen" cues */
/* Recall the two cases (low and high proportion cues known) are
 * initialized differently and so must be changed differently.  For low
 * known, an empty matrix has info added to it; for hi known, a full matrix
 * (at least for the recognized cities) has info deleted from it. 
 */
    total_cues= num_cities_known * useful.num_cues;
    chosen_cues= 0;

		if (proportion_cues_known <= 0.5) {
            tot_chosen= (long)(.5+(proportion_cues_known * (double)total_cues));
            for (chosen_cues=0; chosen_cues <tot_chosen; chosen_cues++)
			{
                do 
				{
                	test_city= known_cities[New_Rand(num_cities_known)];
                	test_cue= 1 + New_Rand(useful.num_cues);
                } while (s_knowledge[test_city].cue[test_cue]+1 > MYERR);
        /* keep searching till find -1, which is a "don't know" and
         * can be filled with knowledge. */
                s_knowledge[test_city].cue[test_cue]= 
				  world[test_city].cue[test_cue];
            } /* for chosen_cues */
        } else /* contra if proportion_cues_known <= 0.5 */ 
		{
            tot_chosen=(long)(.5 +
			  ( (1-proportion_cues_known)*(double)total_cues));
            for (chosen_cues=0; chosen_cues <tot_chosen; chosen_cues++)
			{
                do 
				{
                	test_city= known_cities[New_Rand(num_cities_known)];
                	test_cue= 1 + New_Rand(useful.num_cues);
                } while (s_knowledge[test_city].cue[test_cue]+1 < MYERR);
        /* keep searching till find something other than -1 (which is
        a "don't know") so that can find known cue info and erase it */
                s_knowledge[test_city].cue[test_cue]= -1;
        	} /* for chosen_cues */
        } /* else proportion_cues_known */

		if(DEBUG2) 
		{
			printf("at end of function, here is world:\n");
			Print_World_Array_Struct(world, useful.num_cities,
				useful.num_cues);
			printf("what the subject knows in Fill_Ss_Knowledge\n");
			Print_World_Array_Struct(s_knowledge, useful.num_cities,
				useful.num_cues);
		}

}








double
Calc_Cue_Validity_Fast(struct world_array_struct *world_struct, long which_cue,
struct useful_variables_struct useful) 
/* Cue validity = correct / (correct + incorrect)
 * where, of course, only discriminating cases are at issue.
 */
/* Instead of trying all pairs of objects, this version just finds
 * the discriminating cases. */
/* this means it's faster BUT it MUST have binary (0-1) input,
 * i.e. the old version, though slower, is broader in scope */

{
long num_correct=0;
long num_wrong=0;
long num_zero_so_far=0;
long num_one_so_far=0;
long object_cntr;
double validity;

	if(useful.categorize)
	{
	printf("WARNING: you're using fast cue validity calculation");
	printf(" although this is a categorization task!\n\n");
	}

	for (object_cntr=0; object_cntr < useful.num_cities; object_cntr++)
	{
		if (world_struct[object_cntr].cue[which_cue]==1) {
			num_wrong+= num_zero_so_far;
			num_one_so_far++;
		}

		if (world_struct[object_cntr].cue[which_cue]==0) {
			num_correct+= num_one_so_far;
			num_zero_so_far++;
		}
	}

	validity= (num_correct + num_wrong > 0)  
	  ? ((double) num_correct / (double) (num_correct + num_wrong) )
	  : 0.5 ; 
	/* i.e. if no discriminating cases, then do as well as chance [0.5] */

	return validity;

}









double
Calc_Cue_Validity_Old (struct world_array_struct *world_struct, long which_cue,
struct useful_variables_struct useful)
/* Cue validity = correct / (correct + incorrect)
 * where, of course, only discriminating cases are at issue.
 */
/* this is the OLD version that literally tries all pairs of objects */
/* CHANGES:
 * 30 Aug 96- if target variable (population) equal for a pair, then
 * scored as a guess */
{

double correct,
	total;  /* CHANGEd to doubles for 30 Aug 96 */

long city1,
	city2;

double return_me;


	if(DEBUG)printf("num_cities= %ld, cue_num= %ld  ", useful.num_cities, 
	which_cue);
    
	  correct = total = 0;
    
	  for (city1 = 0; city1 < useful.num_cities; city1++)
      {
         for (city2 = city1 + 1; city2 < useful.num_cities; city2++)
         {
            if ( REAL_GREATER(world_struct[city1].cue[which_cue],
                world_struct[city2].cue[which_cue]) )
            {
               	total++;
               	if (world_struct[city1].pop > world_struct[city2].pop) 
				{
                  correct++;
				} 
				else if (useful.categorize && 
				REAL_EQUAL(world_struct[city1].pop, world_struct[city2].pop) )
				{
					correct+= 0.5;  /* scored as a "guess"- not wrong */
				}
            } 
            else if ( REAL_GREATER(world_struct[city2].cue[which_cue], 
                   world_struct[city1].cue[which_cue]) )
            {
               total++;
               if (world_struct[city2].pop > world_struct[city1].pop)
               {
				correct++;
		       }
				else if (useful.categorize &&
                REAL_EQUAL(world_struct[city1].pop, world_struct[city2].pop) )
                {
                    correct+= 0.5;  /* scored as a "guess"- not wrong */
                }
            } /* else if */

         }  /* for city2 */

      }  /* for city1 */

	if(DEBUG)printf("correct= %lf, total= %lf\n", correct, total);

      return_me= (total > 0) ?
         correct / total : 0.5;
    /* i.e. if no discriminating cases, then do as well as chance [0.5] */


      return return_me;


}







void 
Fill_External_Cv_Array(struct alg_var_struct *alg_var, struct world_array_struct
 *this_struct, double recognition_validity, struct useful_variables_struct 
useful) 
{
 
   /*
    * if correct / total is 0 / 0, then the cue validity for that
    * cue is set to 0.5.  Also, validity for cue[0], 
    * the recognition cue, is
    * not computed because it is pre-set.  
    */

long            which_cue,
                city1,
                city2,
                correct,
                total;


   (alg_var->cue_validity_array)[0]= recognition_validity;


	/* must count to num_cues + 1 because recognition takes up position 0
	*   and so the rest of the cues are shifted up 1 spot. */
   for (which_cue = 1; which_cue < useful.num_cues + 1; which_cue++)
   {

      (alg_var->cue_validity_array)[which_cue]= 
		Calc_Cue_Validity_Old(this_struct, which_cue, useful);

   }/* for cue_num */


}/* function */







/* CHANGE in the program-- added function */
void Reverse_This_Cue(struct world_array_struct *world_struct, long
which_cue, struct useful_variables_struct useful)
/* for all of cue cue_num, turns 1's to 0's and 0's to 1's.
*   WARNING: assumes no -1's  (don't know's) are there!!    */
{

long citycntr;

    for(citycntr=0; citycntr<useful.num_cities; citycntr++)
    {
        world_struct[citycntr].cue[which_cue]= 1 -
            world_struct[citycntr].cue[which_cue];
    }

}






/* CHANGE in the program-- added function */
void Check_For_Reverse(double *validity, struct world_array_struct 
*world_struct, struct useful_variables_struct useful)
/* Should be called only if CUEREVERSE equals 1 (cue reversing is on).
 * The purpose of this function is to make all cues "point in the
 * right direction", i.e. so that on the average a 1 means a bigger
 * city.
 * The function searches for cues with validity below 0.5.  When
 * such a cue is found, function Reverse is called, which changes
 * 1's to 0's and 0's to 1's in the cue, with the end result that
 * the validity is now above 0.5.  
 * DOES NOT calculate the new validity for you.
 * I removed this aspect because it was confusing under
 * cross-validation (when there are two possible worlds).
 */
{
long which_cue;

    for (which_cue=1; which_cue < useful.num_cues+1; which_cue++) {
                                         
        if(DEBUG)printf("old validity= %lf;", validity[which_cue]);
        if (validity[which_cue] < 0.5)
        {
            Reverse_This_Cue(world_struct, which_cue, useful);
		/* CUEVALIDITY CHANGES */
                /* CHANGE AFTER TORSTEN */
	/* do 1-oldval because of crossval case.  cueval should
	 * be calculated ONLY on the modelling world, but
	 * Reverse was passed the whole world, b/c whole world
	 * needs cue reversed if it points the wrong way. 
	 */
            validity[which_cue]= 1-validity[which_cue];
/*  BELOW IS WRONG because we calc validity on the whole world!
            validity[which_cue]= Calc_Cue_Validity_Old(world_struct, which_cue,
             useful);
*/

            if(DEBUG)printf("new validity= %lf;", validity[which_cue]);
        } /* end if validity < 0.5 */

    } /* end for cue_num */

}
   




void
Init_Score_Matrix(struct score_matrix_struct *score_matrix, struct 
useful_variables_struct useful)
{

long per_cntr,
  city_cntr;


        for (city_cntr=0; city_cntr< useful.num_cities+1; city_cntr++) {
                for (per_cntr=0; per_cntr<useful.num_percents; per_cntr++) {
               		score_matrix[ city_cntr * useful.num_percents  +
                      per_cntr ].correct=0;
		   	score_matrix[ city_cntr * useful.num_percents  +
                      per_cntr ].lookups=0;
                    score_matrix[ city_cntr * useful.num_percents  +
                      per_cntr ].guesses=0;
                }
        }


}










double
Calc_Cue_Validity_Suc (struct world_array_struct *world_struct, long cue_num, long
 num_cities)
{



/*  success_rate(C) = (#correct_inferences + #undecided/2)/#pairs  */
/*
* All pairs of cities are tested.  A cue indicates a correct inference
* when the city with the larger population (lower rank in the world)
* has a 1 while the other city has a zero.  The cue is undecided if
* it has the same value for both cities-- both have 1's or both have
* zeroes.  Since the algorithm then guesses and has a 50/50 chance of
* guessing correctly, this scores half a point on average, so we
* divide by 2.  #pairs is of course n*(n-1)/2 where n=#cities.
*   This formula was developed as an alternative to cue validity
* by Laura Martignon.
*/



long correct,
    undecided,
    pairs,
    city1,
    city2;
double return_me;


      correct = undecided = pairs = 0;
      for (city1 = 0; city1 < num_cities; city1++)
      {
         for (city2 = city1 + 1; city2 < num_cities; city2++)
         {
            if (world_struct[city1].cue[cue_num] -
                world_struct[city2].cue[cue_num] > MYERR)
            {
                if (world_struct[city1].pop > world_struct[city2].pop)
                {
                  correct++;
                }
            } else
               if (world_struct[city2].cue[cue_num] -
                   world_struct[city1].cue[cue_num]
                   > MYERR)
            {
               if (world_struct[city2].pop > world_struct[city1].pop)
               {
                correct++;
               }
            }
            else
            {
                undecided++;
            }
            pairs++;

        }

    }



    if(pairs != num_cities*(num_cities-1)/2) {
        printf("ERROR: pairs= %ld when should be %ld in cue success rate\n",
         pairs, num_cities*(num_cities-1)/2 );
    }

	if(DEBUG)printf("correct= %ld, undecided=%ld, pairs=%ld\n", correct, undecided, pairs);
    return_me= ( (double) correct + ((double) undecided)/2 ) / (double) pairs;

    return return_me;



}





