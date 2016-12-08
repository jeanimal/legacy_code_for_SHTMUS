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
 * file: main_original.c
 * purpose: replaced by main.c
 */


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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



main()
{
/***********************************************
Types and variable declarations
***********************************************/

/* These arrays hold, the info read off of the disk,
 and the Ss individual knowledge (varies from S to S)*/

struct world_array_struct Ss_Knowledge_Array[NUMCITIES];
struct world_array_struct World_Array[NUMCITIES];

/* cue validities are held here.  recall cue[0] is the recognition cue
and so is handled differently */

double External_Cv_Array[NUMCUES+1];

/* This is the order in which subjects try cues, if need be*/

int             Ss_Cue_Order_Array[NUMCUES + 1];

/* This is the set of cities which the subject recognizes */

int		Rank_Order_Array[NUMCITIES];

/* Sim_Info are the parameters for running the simulation read
  in from the command line */

struct sim_info_struct Sim_Info;

struct score_matrix_struct_closet Score_Closet;

struct question_pair_struct Question_Array[(NUMCITIES*(NUMCITIES-1)/2)];

int             Curr_per, /* the actual percent, e.g. 25 */
                Curr_rep,
                Curr_city,
                Curr_quest,
				Curr_per_index=0; /* each percent used (see Curr_per_array)
						   * is assigned an index in the array */
int		Curr_per_array[]={0,10,20,50,75,100};
time_t          t;
int (*algpoint)(struct world_array_struct *, struct world_array_struct *, int *, int , int , int ,int , struct score_matrix_struct_closet *,double *,int);

/***********************************************
The main program
***********************************************/
 /*  srandom((unsigned) time(&t)); */

   srandom(time(0));

   Fill_From_Disk(World_Array);
   Print_World_Array_Struct(World_Array, NUMCITIES, NUMCUES);
   Get_Sim_Info(&Sim_Info);
   Fill_External_Cv_Array(External_Cv_Array,World_Array,Sim_Info.CVchoice,
	NUMCUES, NUMCITIES);
   if(CUEREVERSE)Check_For_Reverse(External_Cv_Array, NUMCUES, World_Array,
     NUMCITIES);
   Print_World_Array_Struct(World_Array, NUMCITIES, NUMCUES);
   printf("\nExternal_Cv_Array: ");
   Print_Double_Array(External_Cv_Array,NUMCUES+1);
   Init_Score_Closet(&Score_Closet, NUMPERCENTS, NUMCITIES);
   Fill_Question_Array(Question_Array); 
   switch (Sim_Info.Algchoice)
	{		/*begin switch */
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
    	  algpoint=HEADPREFIX Weighted_Linear;
    	  break;
	case 8:
	  algpoint=HEADPREFIX Take_The_Last;
	  break;
   	case 14:
   	  algpoint=HEADPREFIX Take_The_Best;
          Fill_Ss_Cue_Order_Array_By_Validity(Ss_Cue_Order_Array,
	   External_Cv_Array);
          printf("\nSs Cue Order Array: ");
          Print_Int_Array(Ss_Cue_Order_Array,NUMCUES+1);
   	  break;
	case 15:
	  algpoint=HEADPREFIX Minimalist;
	  break;
	case 19:
	  algpoint=HEADPREFIX Weighted_Linear_5;
	  break;
   	default:
   	  printf("Alg not implemented\n");
   	  exit(1);
   	  break;   /* as if, ha ha, but good form, no less */
	} 		/*end switch  */ 
   for (Curr_city = STARTCITY; Curr_city <= NUMCITIES; Curr_city++)
   {
   if (DEBUG)
   printf("\nCurr_city = %d", Curr_city);
   for (Curr_per_index=Sim_Info.Startchoice;Curr_per_index<NUMPERCENTS; Curr_per_index++)
	{
 	Curr_per = Curr_per_array[Curr_per_index];
	if (DEBUG) printf("  Curr_per = %d", Curr_per);
	for (Curr_rep = 0; Curr_rep < Sim_Info.Repchoice; Curr_rep++)
		{
 	    	switch (Sim_Info.Algchoice)
            	{               /*begin switch */
				case 8:
				Fill_Ss_Cue_Order_Array_RND(Ss_Cue_Order_Array, NUMCUES);
		  			/* each subject starts from scratch */
				break;
	    		}
	    	if (DEBUG) printf("  Curr_rep = %d \n", Curr_rep);
	    	Get_Rank_Order(Curr_city,(Sim_Info.CVchoice), Rank_Order_Array);
	    	Fill_Ss_Knowledge_Array(Rank_Order_Array,Curr_city,
	     		  (double)Curr_per/100,World_Array,Ss_Knowledge_Array);
	    	if (DEBUG) Print_World_Array_Struct(Ss_Knowledge_Array, NUMCITIES, NUMCUES);
	    	if (DEBUG) 
			{
                	printf("recognition validity= %f\n\n",
                 	  (float) Calc_Cue_Validity_Old(Ss_Knowledge_Array, 0, 
					  NUMCITIES) );
       		}

		    	for (Curr_quest = 0; Curr_quest < Sim_Info.Questchoice; 
				  Curr_quest++)
	    		{
	    			if (DEBUG)
                	{
	        		printf ("Curr_quest = %d, city1 = %d city2 = %d Curr_rep = %d Curr_per = %d Curr_city = %d\n",Curr_quest,Question_Array[Curr_quest].obj1, Question_Array[Curr_quest].obj2,Curr_rep,Curr_per,Curr_city); 
              	  	}
	    			(*algpoint)(Ss_Knowledge_Array, World_Array,
					  Ss_Cue_Order_Array, Question_Array[Curr_quest].obj1,
					  Question_Array[Curr_quest].obj2, Curr_per_index,
					  Curr_city,&Score_Closet,External_Cv_Array, NUMCUES);

				} /* end for Curr_quest */
			}         /* end for Curr_rep */
		}	          /* end for Curr_per_index */
   Print_Results_To_File(&Sim_Info, &Score_Closet, (long int) NUMCITIES,
     (long int)NUMPERCENTS,(long int)(Sim_Info.Questchoice),(long int)
     (Sim_Info.Repchoice));

   }	/* end for Curr_city */


} /* end of main */


/*------------------------------------------- The end, folks
 *------------- go home ------------------------------------
 *----- there's no more show.  go home. --------------------*/
