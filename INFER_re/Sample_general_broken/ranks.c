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
 * file: ranks.c
 * purpose: Dan's cool algorithm for allocating object recognition to come out to a certain recognition validity
 */

/* #include "pmm.h" */
#include <stdlib.h>
#include "main.h"
#include "ranks.h"
#include "choose.h"
#include "show_choose.h"
#include "llist.h"

void
Get_Rank_Order(long n, double cv, long *holder1, 
struct useful_variables_struct useful)
{
   /**********************************************
	Variable Declarations
   ***********************************************/

double          floatpoints,
                choosenum,
                floati;

long        	index3,
		record_hits_array[STOPPOINT],
                min,
                record_hits_index = 0,
                item,
                done,
                *indexarr,
                *roulette,
                max,
                len,
                i,
                cities_drawn,
                goalpoints,
                needed,
                turnsleft,
                sattempt,
                minsum,
                maxsum;
long            *longpoint;

ListType        Orig_Set,
                Picked_Set;



	if (n==0) 
	{
	   for (i=0;i<useful.num_cities;i++)
	    holder1[i] = -1;
 	   return;
        }



	indexarr= (long *) malloc(useful.num_cities * sizeof(long));
	roulette= (long *) malloc(useful.num_cities * sizeof(long));


   Init_List(&Orig_Set);
   Init_List(&Picked_Set);
   minsum = (n * (n + 1)) / 2;
   maxsum = ((useful.num_cities * (useful.num_cities + 1)) / 2)
      - (((useful.num_cities - n) * (useful.num_cities - n + 1)) / 2);
   floatpoints = cv * (double) (maxsum - minsum) + (double) minsum;
   goalpoints = (long) (floatpoints +.5);
   if (DEBUG)
   {
      printf("minsum: %ld maxsum: %ld floatpoints: %lf goalpts: %ld\n", minsum, maxsum, floatpoints, goalpoints);
   }
   /****** Begin outer guarantee a soln looop ***/
   do
   {
      record_hits_index = 0;
      Free_List(&Orig_Set);
      Free_List(&Picked_Set);
      Init_List(&Orig_Set);
      Init_List(&Picked_Set);
      /* Fill Orig_Set set */
      for (i = 1; i < useful.num_cities + 1; i++)
      {
	 Append(i, &Orig_Set);
      }

      needed = goalpoints;

      turnsleft = n;
      cities_drawn = 0;
      done = 0;
      do
      {
	 turnsleft = n - cities_drawn;
	 record_hits_index = 0;
	 if (needed - Top_N(turnsleft - 1, &Orig_Set) > 0)
	    min = needed - Top_N(turnsleft - 1, &Orig_Set);
	 else
	    min = 1;
	 if (needed - Bot_N(turnsleft - 1, &Orig_Set) < useful.num_cities)
	    max = needed - Bot_N(turnsleft - 1, &Orig_Set);
	 else
	    max = useful.num_cities;
	 /* Snip the list at the mins and max */
	 if (Orig_Set.front)
	    Remove_Certain_Items(min, &Orig_Set,
			     (long (*) (void *, void *)) Less_Than_long_Test);
	 if (Orig_Set.front)
	    Remove_Certain_Items(max, &Orig_Set,
			  (long (*) (void *, void *)) Greater_Than_long_Test);
	 /* Be aware of empty lists */
	 len = Length_List(&Orig_Set);
	 if ((!(Orig_Set.front)) || (turnsleft > len))
	 {
	    /*
	     * printf("No or too few items in set in ranks.c\n"); 
	     */
	    Free_List(&Orig_Set);
	    Free_List(&Picked_Set);
	    Init_List(&Orig_Set);
	    Init_List(&Picked_Set);
	    /* Fill Orig_Set set */
	    for (i = 1; i < useful.num_cities + 1; i++)
	    {
	       Append(i, &Orig_Set);
	    }
	    needed = goalpoints;
	    cities_drawn = 0;
	    done = 0;
	    continue;
	 }
	 if (((choosenum = Choose(len, turnsleft)) > STOPPOINT))
	 {
	    item = Remove_Nth(New_Rand(len), &Orig_Set);
	    Append(item, &Picked_Set);
	    needed = needed - item;
	    cities_drawn++;
	 } else
	 {
	    done = 1;
	 }
      } while (!done);
      len = Length_List(&Orig_Set);
      /*
       * Now must transfer Picked_Set to Roulette to determine quickly which
       * sets satisfy sum  
       */
      Copy_To_Array(&Orig_Set, roulette);
      if (DEBUG)
      {
	 printf("Status so far\n");
	 printf("Picked Set\n");
	 Print_List(&Picked_Set);
	 printf("Original Set\n");
	 Print_List(&Orig_Set);
	 if (DEBUG2)
	 {
	    printf("Roulette\n");
	    for (i = 0; i < len; i++)
	    {
	       printf("%ld ", roulette[i]);
	    }
	    printf("\n");
	 }
      }
      /* Enumerate all possible and decide on one */
      for (floati = 0; floati < choosenum; floati++)
	 /* b/c Show_Choose counts from 0 */
      {
	 if (floati == 0)
	 {
	    Show_Choose(indexarr, len, turnsleft, 0, 1, useful);
	 } else
	 {
	    Show_Choose(indexarr, len, turnsleft, 1, 0, useful);
	 }
	 sattempt = 0;
	 for (i = 0; i < turnsleft; i++)
	 {
	    sattempt += roulette[indexarr[i]];
	 }
	 if (sattempt == needed)
	 {
	    if (DEBUG2)
	    {
	       printf("Hit sum of %ld with choice %f\n", sattempt, floati);
	    }
	    record_hits_array[record_hits_index] = (long) floati;
	    record_hits_index++;
	    if (record_hits_index > 32760)
	    {
	       printf("Too many solutions found! ");
	       exit(1);
	    }
	 }
      }				/* End for floati */
      if (DEBUG && record_hits_index == 0)
      {
	 printf("Picking %ld cities: No solution found among %f", n, choosenum);

      }
   }
   while (!record_hits_index);
   if (DEBUG)
   {
      printf("The possible winners are: ");
      for (i = 0; i < record_hits_index; i++)
      {
	 printf("%ld ", record_hits_array[i]);
      }
   }
   if (DEBUG)
   {
      printf("\nThe winner is: ");
   }
   index3 = record_hits_array[New_Rand(record_hits_index)];
   if (DEBUG)
   {
      printf("%ld\n", index3);
      printf("Its members are: ");
   }
   Show_Choose(indexarr, len, turnsleft, index3, 1, useful);

   if (DEBUG)
   {
      longpoint = indexarr;
      for (i = 0; i < turnsleft; i++)
      {
	 printf("%ld ", roulette[*longpoint++]);
      }
   }
   longpoint = indexarr;
   for (i = 0; i < turnsleft; i++)
   {
      Append(roulette[*longpoint++], &Picked_Set);
   }
   if (DEBUG)
   {
      printf("The complete list is:\n");
      Print_List(&Picked_Set);
      printf("and its sum is %ld and goalpts is %ld\n\n", Bot_N(n, &Picked_Set), goalpoints);
   }
   for (i=0;i<useful.num_cities;i++)
	holder1[i]=(-1);
   Copy_To_Array(&Picked_Set,holder1);
   /* reverse the counting for the rest of the program so
	that 0 is the largest city and NUMCITIES -1 is the
	smallest */
   for (longpoint=holder1;longpoint-holder1<n;longpoint++)
 	*longpoint=useful.num_cities-*longpoint;
      Free_List(&Orig_Set);
      Free_List(&Picked_Set);
	free(indexarr);
    free(roulette);   
   
   /********** Comment it all out for debug
	*************/
}
/*
main(long argc, char *argv[])
{
long             arr1[NUMCITIES];
long             i;
float           cv;
long             n;


   srandom((int) time(0));

   for (i = 1; i <= 43; i++)
      Get_Rank_Order(i,.8, arr1);
   for (i = 0; i < 83; i++)
	printf("%ld ",arr1[i]);

}
*/
