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
 * file: stats.c
 * purpose: a library of very simple statistics on arrays of longs
 */


/* stats.c */

/* some simple, useful statistics */
/* created with hillclimbing in mind, but useful for other stuff */


#include <stdio.h>
#include <math.h>
#include "main.h"
#include "stats.h"


double Average_long(long *array, long len)
{
long cntr;
long sum_so_far= 0;

	for(cntr=0; cntr<len; cntr++)
		sum_so_far+= array[cntr];

	return ( (double) sum_so_far / (double) len);


}



double Average_Double(double *array, long len)
{
long cntr;
double sum_so_far= 0;

    for(cntr=0; cntr<len; cntr++)
        sum_so_far+= array[cntr];

    return ( sum_so_far / (double) len);


}




double Covariance_long(long *array1, long *array2, long len)
/* note: arrays must be of same length */
{

long cntr;
double sum_so_far= 0;
double average1, average2;

	average1= Average_long(array1, len);
    average2= Average_long(array2, len);

    for(cntr=0; cntr<len; cntr++)
        sum_so_far+= ((double)array1[cntr]-average1) * ((double)array2[cntr]-average2);

    return ( sum_so_far / (double) len);

}



double Variance_long(long *array1, long len)
{
	return (Covariance_long(array1, array1, len));
}





double Covariance_Double(double *array1, double *array2, long len)
/* note: arrays must be of same length */
{

long cntr;
double sum_so_far= 0;
double average1, average2;

    average1= Average_Double(array1, len);
    average2= Average_Double(array2, len);

    for(cntr=0; cntr<len; cntr++)
        sum_so_far+= (array1[cntr]-average1) * (array2[cntr]-average2);

    return ( sum_so_far / (double) len);


}


double Variance_Double(double *array, long len)
{
	return(Covariance_Double(array, array, len));
}




double Correlation_long(long *array1, long *array2, long len)
{
double cov, var1, var2;

	cov= Covariance_long(array1, array2, len);
	var1= Variance_long(array1, len);
	var2= Variance_long(array2, len);


    if (var1*var2 == 0)
        return 2;
    else
		return ( cov / sqrt(var1*var2) );

}





double Correlation_Double(double *array1, double *array2, long len)
/* if correlation doesn't exist, we return 2 */
{
double cov, var1, var2;

    cov= Covariance_Double(array1, array2, len);
    var1= Variance_Double(array1, len);
    var2= Variance_Double(array2, len);

	if (var1*var2 == 0)
		return 2;
	else
		return ( (cov) / sqrt(var1*var2) );

}



/*-----------------*/
/*
 * now some functions more specific to ttb vs. wl.
 *
 */
/*-----------------*/


void Extract_Cue_Vector(struct world_array_struct *world,
long num_cases, long which_cue, double *cue_vector)
/* WARNING sufficient space should already be malloc'ed */
{
long case_cntr;

	for(case_cntr= 0; case_cntr < num_cases; case_cntr++)
		cue_vector[case_cntr]= world[case_cntr].cue[which_cue];

}


void Extract_Target_Vector(struct world_array_struct *world,
long num_cases, double *cue_vector)
{
long case_cntr;

    for(case_cntr= 0; case_cntr < num_cases; case_cntr++)
        cue_vector[case_cntr]= (double) (world[case_cntr].pop);

}

long Count_1s(double *array, long len)
{
long cntr;
double sum= 0;

	for(cntr=0; cntr < len; cntr++)
		sum+= array[cntr];

	return (long)sum;

}


double abs_real(double abs_me)
{
	if (abs_me < 0)
		return (-abs_me);
	else
		return abs_me;

}


