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
 * file: pprint.c
 * purpose: print info in data structures in a pretty (readable) way
 */

/* Pretty Printing Routines */
#include <stdio.h>
#include "main.h"
#include "pprint.h"


/* none of these use the useful_variables_struct on the grounds that
these should be routines for *any* type of program, except
Print_World_Array_Struct, which is tailored for this program */


void Print_World_Array_Struct(struct world_array_struct *this_struct, long num_cities, long num_cues)
{

long data_num;
long cue_num;
long char_cntr;

long name_max= 10;



        printf("\n");

        for (data_num=0; data_num < num_cities; data_num++) {
        	for(char_cntr=0; char_cntr < name_max; char_cntr++)
			{
				if(this_struct[data_num].name[char_cntr] == '\0')
					for(; char_cntr < name_max; char_cntr++)
						printf(" ");
				else
		       		printf("%c", this_struct[data_num].name[char_cntr]);
			}
			printf(" : ");
            printf("%4ld ", this_struct[data_num].rank);
            printf("%9ld ", this_struct[data_num].pop);
        
            /* first just the recognition bit (used only for
                        knowledge) */
            printf("<%2.0f> ", this_struct[data_num].cue[0] );
            /* now the other cues */
            for (cue_num=1; cue_num < num_cues+1; cue_num++) 
            	printf("%3lf ", this_struct[data_num].cue[cue_num]);
            printf("\n");
       }


}



void Print_World_Array_Struct_Ord(struct world_array_struct *this_struct, 
long num_cities, long num_cues, long *cue_order)

{
long data_num;
long cue_num;
long char_cntr;

long name_max= 10;



        printf("\n");

        for (data_num=0; data_num < num_cities; data_num++) 
		{

            for(char_cntr=0; char_cntr < name_max; char_cntr++)
            {
                if(this_struct[data_num].name[char_cntr] == '\0')
                    for(; char_cntr < name_max; char_cntr++)
                        printf(" ");
                else
                    printf("%c", this_struct[data_num].name[char_cntr]);
            }
            printf(" : ");
            printf("%4ld ", this_struct[data_num].rank);
            printf("%9ld ", this_struct[data_num].pop);

            /* first just the recognition bit (used only for
                        knowledge) */
            printf("<%2.0lf> ", this_struct[data_num].cue[0] );
            /* now the other cues */
            for (cue_num=1; cue_num < num_cues+1; cue_num++)
                printf("%3.0lf ", this_struct[data_num].cue[cue_order[cue_num]]);
            printf("\n");
       }


}








void Print_Double_Array(double *array, long len)
{
long cntr;

        printf("\n");
        for (cntr=0; cntr < len; cntr++) 
                printf("%lf ", array[cntr]);

        printf("\n");
}




void
Print_long_Array(long *array, long len)
{
long             cntr;

   printf("\n");
   for (cntr = 0; cntr < len; cntr++)
      printf("%ld ", array[cntr]);

   printf("\n");
}





void
Print_Score_Matrix(struct score_matrix_struct *score_matrix,
long numper, long numcities)
{

long per_cntr,
  city_cntr;



        for (city_cntr=0; city_cntr< numcities+1; city_cntr++) 
		{
             printf("num_known %ld:: ", city_cntr);
             for (per_cntr=0; per_cntr<numper; per_cntr++) 
   		 	{
				/* below are equivalent to score_matrix[city_cntr][per_cntr] */
                 printf("%5lf / %5lf |", 
				  score_matrix[ city_cntr * numper  +
        			per_cntr ].correct, 
				  score_matrix[ city_cntr * numper  +
        			per_cntr ].lookups);
             }
             printf("\n");
        }

}
