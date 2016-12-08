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
 * file: main.c
 * purpose: calls all the other functions-- the framework
 *
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "variables.h"  /* include only in main.c */
#include "main.h"
#include "getsiminfo.h"
#include "ranks.h"
#include "filldatastrs.h"
#include "fileio.h"
#include "pprint.h"
#include "fillcueorders.h"
#include "takethebest.h"
#include "weightedlinear.h"
#include "unitlinear.h"
#include "weightedtally.h"
#include "unittally.h"
#include "minimalist.h"
#include "takethelast.h"
#include "arrays.h"
#include "regression.h"
#include "crossval.h"
#include "simple_bayes.h"



main()
{
/***********************************************
Types and variable declarations
***********************************************/

/* These arrays hold the info read off of the disk,
 and the Ss individual knowledge (varies from S to S)*/

struct world_array_struct *ss_knowledge_array;
struct world_array_struct *world_array;


/* note: if CROSSVALIDATE is true, then world_array will actually
 * hold only the testing half of the world.  The modelling half
 * and actual world are declared below. */

struct world_array_struct *actual_world_array;
struct world_array_struct *modelling_world_array; 





/* Sim_Info are the parameters for running the simulation read
  in from the command line */

struct sim_info_struct sim_info;



/* a struct is just an easier way of passing the matrix */
/* below, an experiment WITHOUT the closet, since now it's
 * all pointers anyway */
struct score_matrix_struct *score_matrix_ptr;



/* holds the pairs of objects asked for each question */

struct question_pair_struct *question_array;



/* useful holds a set of variables about the simulation and about
	world that are often used and often passed into functions */

struct useful_variables_struct useful;



/* alg_var holds variables derived from other information but
 * often needed for running the simulation */

struct alg_var_struct alg_var;



/* This is the set of cities which the current subject recognizes */
long     *ss_rec_cities;



long             Curr_per, /* the actual percent, e.g. 25 */
                Curr_rep,
                Curr_city,
                Curr_quest,
		Curr_per_index=0; /* each percent used (see Curr_per_array)
					   * is assigned an index in the array */
long		Curr_per_array[]={0,10,20,50,75,100};
time_t          t;

long (*algpoint)(struct world_array_struct *, struct world_array_struct *,
 long, long, long, long, struct score_matrix_struct *, 
struct useful_variables_struct, struct alg_var_struct);

char *INFILENAME;


long object_num; /* used only in the malloc section */


/* CHANGE: for recording data to Datafilename */
double  correct_sum_so_far;
double  correct_this_round;
FILE    *dp;  /* for data on each round */



/***************************************************
The main program
****************************************************/

	printf("\n\n-------------------------------------\n");
	printf("\npmmnew running\n\n");




	/*
	 * hello there!  and welcome to the running
	 * annoying commentary of the PMM package!
	 *
	 * first we've got to get through lots of 
	 * yucky boring initialization stuff.  This
	 * takes up the next page or so.
	 *
	 */




    /* init pseudo-random number generation-
     * call ONLY ONCE in the program */
   srand(time(0));


	/* load in some of the most useful variables 
	 * (held as #defines in variables.h file */
	useful.num_percents= NUMPERCENTS;
	useful.guess_cnt= GUESSCNT;
	useful.cue_reverse= CUEREVERSE;
	useful.categorize= 0; /* NOT YET IMPLEMENTED */ 

	INFILENAME= (char *) malloc(NAMELENGTH * sizeof(char) );
	Get_Filename_From_User(INFILENAME);

	/* gets num_cities, num_cues, and a filecode */
   Init_From_Disk(&useful, &sim_info, INFILENAME);
   printf("reading from %s: numcities= %ld, numcues= %ld\n", 
	sim_info.Filecode, useful.num_cities, useful.num_cues);


	/* 
	 * [[]] array inits -- mallocs-- do ONLY ONCE in the program 
	 *    we can do them now that we have num_cities and num_cues 
	 */

		/* the mallocs below are equivalent to
		 *		struct world_array_struct
		 *		{  ...
		 *		   ... 	double	cue[NUMCUES];  
		 *		} world_array[NUMCITIES];
		 */
	world_array= (struct world_array_struct *) 
	  malloc(useful.num_cities * sizeof(struct world_array_struct));
	ss_knowledge_array= (struct world_array_struct *) 
	  malloc(useful.num_cities * sizeof(struct world_array_struct));
	actual_world_array= (struct world_array_struct *)
      malloc(useful.num_cities * sizeof(struct world_array_struct));
	modelling_world_array= (struct world_array_struct *)
      malloc(useful.num_cities * sizeof(struct world_array_struct));
	for(object_num=0; object_num < useful.num_cities; object_num++)
	{
		world_array[object_num].cue= (double *)
			malloc( (useful.num_cues+1) * sizeof(double) );
		ss_knowledge_array[object_num].cue= (double *)
			malloc( (useful.num_cues+1) * sizeof(double) );
		actual_world_array[object_num].cue= (double *)
            malloc( (useful.num_cues+1) * sizeof(double) );
		modelling_world_array[object_num].cue= (double *)
            malloc( (useful.num_cues+1) * sizeof(double) );
	}

	alg_var.cue_validity_array= (double *)
	  malloc( (useful.num_cues+1) * sizeof(double));
	alg_var.ss_cue_order_array= (long *)
	  malloc( (useful.num_cues+1) * sizeof(long));
	ss_rec_cities= (long *) malloc(useful.num_cities * sizeof(long));

	question_array= (struct question_pair_struct *)
	  malloc( (useful.num_cities*(useful.num_cities-1)/2) * 
	  sizeof(struct question_pair_struct) );

	score_matrix_ptr= (struct score_matrix_struct *)
	  malloc( useful.num_percents * (useful.num_cities+1) *
	  sizeof(struct score_matrix_struct) );
	/* 
	 * [[]] end array inits 
	 */





	/* fills world data from disk, then prints to stdout to confirm */
   Fill_From_Disk(world_array, &useful, INFILENAME);
   Print_World_Array_Struct(world_array, useful.num_cities, useful.num_cues);

	/* note: it is important to make these assignments EARLY so that
	 * everything will be initialized properly (number of questions, etc.).
	 */
    if(CROSSVALIDATE)
    {
        useful.actual_num_cities= useful.num_cities;
        useful.num_cities= useful.num_cities/2; /* truncates if odd */

	/* TO DO

	Copy_Useful(useful, useful_fit);
	Copy_Useful(useful, useful_pred);
	useful_fit.num_cities= sample_size;
	Then be careful to give the correct useful to the correct algorithm!
	For input checking, it would be better to not have anything called useful anymore.
	Call it useful_original.

	*/

	}




    /* get info about parameters of simulation from the user (stdin) */
	Get_Sim_Info(&sim_info, useful);
	Make_Output_File_Names(&sim_info);

	if(CROSSVALIDATE)
	{

		Copy_World(actual_world_array, world_array, useful.actual_num_cities, 
		 useful.num_cues);
		Crossval_Split(world_array, actual_world_array, modelling_world_array, useful);

		if (sim_info.Algchoice == 6)
		/* calculates beta weights and soon puts them in the cue_validity_array,
     	 * which is inside alg_var */ 
			Fill_External_Cv_Array_Reg(&alg_var, modelling_world_array, 
			  sim_info.CVchoice, useful);
		else
    	/* calculates cuevalidities and soon puts in the cue_validity_array,
     	* which is inside alg_var */
    		Fill_External_Cv_Array(&alg_var, modelling_world_array, 
			  sim_info.CVchoice, useful);

	}
	else /* no split */
	{
		/* use world array rather than modelling_world_array */
	    if (sim_info.Algchoice == 6)
    	/* calculates beta weights and soon puts them in the cue_validity_array,
     	 * which is inside alg_var */
        	Fill_External_Cv_Array_Reg(&alg_var, world_array,
        	sim_info.CVchoice, useful);
    	else
    	/* calculates cue validities and soon puts them in cue_validity_array,
     	* which is inside alg_var */
        	Fill_External_Cv_Array(&alg_var, world_array,
        	sim_info.CVchoice, useful);

	}

    printf("pre cue validity array for %s:\n", sim_info.Filecode);
    Print_Double_Array(alg_var.cue_validity_array, useful.num_cues + 1);
    if(useful.cue_reverse && (sim_info.Algchoice != 6))
	{
        Check_For_Reverse(alg_var.cue_validity_array, world_array, useful);

/* I had this if-else commented out because Check_For Reverse
 * has a trick for getting the CV of just the modelling world--
 * take 1 - cue validity passed in (which is from modelling world.) */
/*
        if (CROSSVALIDATE)
            Fill_External_Cv_Array(&alg_var, modelling_world_array,
                  sim_info.CVchoice, useful);
        else
            Fill_External_Cv_Array(&alg_var, world_array,
                  sim_info.CVchoice, useful);
*/



    	printf("just after cue_reverse , here is world:");
   	Print_World_Array_Struct(world_array, useful.num_cities, 
            useful.num_cues);
    	printf("cue validity array for %s:\n", sim_info.Filecode);
    	Print_Double_Array(alg_var.cue_validity_array, useful.num_cues + 1);
	}



printf("about to init score matrix\n");
	Init_Score_Matrix(score_matrix_ptr, useful);
	Fill_Question_Array(question_array, useful.num_cities);
printf("filled quest\n");

	/* now set the function pointer to the algorithm to be used */
   switch (sim_info.Algchoice)
    {       /*begin switch */
    case 2:
      algpoint=HEADPREFIX Unit_Tally;
      break;
    case 3:
      algpoint=HEADPREFIX Weighted_Tally;
      break;
    case 4:
      algpoint=HEADPREFIX Unit_Linear;
      break;
    case 5:
	case 6: /* 6 is regression and will use beta weights */
          algpoint=HEADPREFIX Weighted_Linear;
          break;
    case 8:
      algpoint=HEADPREFIX Take_The_Last;
           Fill_Ss_Cue_Order_Array_RND(alg_var.ss_cue_order_array,
                 useful.num_cues);
      break;
    case 14:
      algpoint=HEADPREFIX Take_The_Best;
          Fill_Ss_Cue_Order_Array_By_Validity(&alg_var, useful.num_cues);
          printf("\nSs Cue Order Array: ");
          Print_long_Array(alg_var.ss_cue_order_array, useful.num_cues + 1);
      break;
    case 15:
      algpoint=HEADPREFIX Minimalist;
      break;
    case 19:
      algpoint=HEADPREFIX Weighted_Linear_5;
      break;
    case 20:
      algpoint=HEADPREFIX Simple_Bayes;
      break;
    default:
      printf("Alg not implemented\n");
      exit(1);
      break;   /* as if, ha ha, but good form, no less */
    }       /*end switch  */



printf("set algpoint\n");

if (sim_info.Start_city_choice > useful.num_cities)
	printf("SIMULATION ABANDONED: startcities %ld > num_cities %ld\n", sim_info.Start_city_choice, useful.num_cities); 


	/*
	 * Phew!	
	 * all the set-up and initialization has finally
	 * been completed.
	 *
	 * and so...
	 *
	 * =====>  here the SIMULATION begins <===== 
	 */


   /* for putting data for calculating 95% confidence intervals */
  dp = fopen(sim_info.Datafilename, "w+");
  correct_sum_so_far= 0;

   for (Curr_city= sim_info.Start_city_choice; Curr_city<=useful.num_cities; Curr_city++)
   {
     if (DEBUG)
     printf("\nCurr_city = %ld", Curr_city);

	 for (Curr_per_index=sim_info.Start_per_choice; 
	  Curr_per_index < useful.num_percents; Curr_per_index++)
     {
    	Curr_per = Curr_per_array[Curr_per_index];
    	if (DEBUG) printf("  Curr_per = %ld", Curr_per);
    	
		for (Curr_rep = 0; Curr_rep < sim_info.Repchoice; Curr_rep++)
        {

			if(CROSSVALIDATE)
			{
				Crossval_Split(world_array, actual_world_array, 
				 modelling_world_array, useful);

        		/* use world array rather than modelling_world_array */
        		if (sim_info.Algchoice == 6)
        		/* calculates beta weights and soon puts them in 
				 * the cue_validity_array, which is inside alg_var */
            		Fill_External_Cv_Array_Reg(&alg_var, modelling_world_array,
            	 	 sim_info.CVchoice, useful);
        		else
        		/* calculates cue validities and soon puts them 
				 * in cue_validity_array, which is inside alg_var */
            		Fill_External_Cv_Array(&alg_var, modelling_world_array,
            		 sim_info.CVchoice, useful);


				if(useful.cue_reverse && (sim_info.Algchoice != 6))
        			Check_For_Reverse(alg_var.cue_validity_array, 
					 world_array, useful);

				switch (sim_info.Algchoice)
				{
				case 14:
				Fill_Ss_Cue_Order_Array_By_Validity(&alg_var, 
					 useful.num_cues);
				if(DEBUG)
				{
          			 printf("\ncrossvalidate-Ss Cue Order Array: ");
         			 Print_long_Array(alg_var.ss_cue_order_array, 
				         useful.num_cues + 1);
				}
				break;
				}

			}

            switch (sim_info.Algchoice)
            { 
                case 8:
                Fill_Ss_Cue_Order_Array_RND(alg_var.ss_cue_order_array, 
				 useful.num_cues);
                    /* each subject starts from scratch */
                break;
				
            }
            if (DEBUG) printf("  Curr_rep = %ld \n", Curr_rep);


			if( 1 /* Curr_city < useful.num_cities */ )
			{
            	/* below determine which cities the subject recognizes 
			 	 * and which cues they know of these cities */
				Get_Rank_Order(Curr_city,(sim_info.CVchoice), ss_rec_cities,
			 	 useful);
            	Fill_Ss_Knowledge_Array(ss_rec_cities, Curr_city,
                  (double)Curr_per/100, world_array, ss_knowledge_array,
					useful);
			}

            if (DEBUG)
            {	
				Print_World_Array_Struct(ss_knowledge_array,
             	 useful.num_cities, useful.num_cues);
                printf("recognition validity= %f\n\n",
                 (float) Calc_Cue_Validity_Old(ss_knowledge_array, 0,
                  useful) );
            }


           for (Curr_quest = 0; Curr_quest < sim_info.Questchoice;
            Curr_quest++)
           {

				/*#########################################*
				 THE JEWEL! here is where we finally call the
				 decision algorithm, via the function pointer,
				 to decide on the two cities named by Curr_quest.
				 Pretty unassuming-looking, eh?               
				 *#########################################*/

           		(*algpoint)(ss_knowledge_array, world_array,
                 question_array[Curr_quest].obj1,
                 question_array[Curr_quest].obj2, Curr_per_index,
                 Curr_city, score_matrix_ptr, useful, alg_var);

				/*#########################################*/


                   if (DEBUG)
                    {
                    printf ("Curr_quest = %ld, city1 = %ld city2 = %ld Curr_rep = %ld Curr_per = %ld Curr_city = %ld\n", Curr_quest, question_array[Curr_quest].obj1, question_array[Curr_quest].obj2,Curr_rep,Curr_per,Curr_city);
                    }


               } /* end for Curr_quest */

		/* Data for calculating 95% confidence intervals */
		correct_this_round= 
		  score_matrix_ptr[Curr_city * useful.num_percents + 
		  Curr_per_index].correct   -   correct_sum_so_far; 
		fprintf(dp, "%f\n", correct_this_round / sim_info.Questchoice);
		correct_sum_so_far+= correct_this_round;

            }         /* end for Curr_rep */

	    fprintf(dp, "-------\n");

        }             /* end for Curr_per_index */

	fprintf(dp, "**************\n");


	/* below we record the results from the current number of cities
	 * known to a file. */
	Print_Results_To_File(&sim_info, score_matrix_ptr, useful,
     (sim_info.Questchoice), (sim_info.Repchoice));


   }    /* end for Curr_city */

   fclose(dp);



	/* 
	 * now free up memory-- not totally necessary, but
	 * we want to keep our memory as tidy as a kitten
	 * keeps her litter box.  
	 *
	 */

	free(world_array);
    free(ss_knowledge_array);
    for(object_num=0; object_num < useful.num_cities; object_num++)
    {
        free(world_array[object_num].cue);
        free(ss_knowledge_array[object_num].cue);
    }

    free(alg_var.cue_validity_array);
    free(alg_var.ss_cue_order_array);
    free(ss_rec_cities);

    free(question_array);

    free(score_matrix_ptr);

	free(INFILENAME);

	printf("\n--------------------------------------\n");
	printf("\n\nsimulation successfully completed!\n");
	printf("thank you for using the pmm branch of algorithms\n\n");


} /* end of main */


/*------------------------------------------- The end, folks
 *------------- go home ------------------------------------
 *----- there's no more show.  go home. --------------------*/
