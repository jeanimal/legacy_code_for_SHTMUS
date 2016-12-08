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
 * file: linutils.c
 * purpose: utilities for the linear inference heuristics, e.g. regression
 */

#include <stdio.h>
#include <stdlib.h>
#include "main.h"
#include "umacros.h"
#include "linutils.h"


long Get_Cue_Type(struct world_array_struct *Ss_Knowledge_Array, long city, long cue_num)
/* returns 1 for a positive cue, -1 for a negative cue, and 0 if cue
unknown (negative cue means knowledge state is 0, unknown cue means
knowledge state is -1, so this is sort of confusing) */
{

long type;
double cue_val;


        cue_val= Ss_Knowledge_Array[city].cue[cue_num];

        if (POS_CUEVAL((long)cue_val) > 0)
                type= 1;
        else if (NEG_CUEVAL((long)cue_val) > 0)
                type= -1;
        else if (UNK_CUEVAL((long)cue_val) > 0)
                type= 0;
                                            
 else {
                printf("\n\nERROR: cue type out of range for city %ld, cue %ld\n\n", city, cue_num);
                printf("value is %lf\n\n", cue_val);
                exit(2);
        }

        return type;

}




long Get_Tally(struct world_array_struct *Ss_Knowledge_Array, long
city, long cue_num)
/* returns 1 for known, positive cue; returns 0 otherwise */
{
double cue_val;

        cue_val= Ss_Knowledge_Array[city].cue[cue_num];

	return (POS_CUEVAL((long)cue_val) > 0) ? 1 : 0;

}


