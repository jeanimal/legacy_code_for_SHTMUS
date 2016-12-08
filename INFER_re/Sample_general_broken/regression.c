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
 * file: regression.c
 * purpose: interface between Shammas' regression module and INFER
 */

/* regression module for the Fast & Frugal contest */

/* added by Jean Czerlinski, frueh Mai 1997 */

/* currently uses the regression module of Namir C. Shammas to
 * calculate the beta weights; from there on it's as if weighted
 * linear were called (from main).
 */


#include <stdlib.h>
#include <stdio.h>

#include "main.h"
#include "umacros.h"
#include "math.h"
#include "stats.h"
#include "pprint.h"
#include "mlreg.h"
#include "global.h"
#include "arrays.h"
#include "regression.h"
#include "llist.h"

long No_Variation(struct world_array_struct *world, long this_cue, long num_cases)
/* tests if cue # this_cue is all 1's or all 0's, in which case 1 is returned,
 * else 0.
 */
{
double *this_cue_vector;
double var;



    this_cue_vector= (double *) malloc(num_cases * sizeof(double));
	Extract_Cue_Vector(world, num_cases, this_cue, this_cue_vector); 

	var= Variance_Double(this_cue_vector, num_cases);

	free(this_cue_vector);  /* must do this before returns! */

	if ( var < MIN_VAR_ALLOWED )
	{
        if (DEBUG)
            printf("***    cue %ld found to be No_Var\n", this_cue);
		return 1;
	}
	else
		return 0;


}



long No_Variation_Target(struct world_array_struct *world, long num_cases)
/* tests if cue # this_cue is all 1's or all 0's, in which case 1 is returned,
 * else 0.
 */
{
double *this_cue_vector;
double var;



    this_cue_vector= (double *) malloc(num_cases * sizeof(double));
    Extract_Target_Vector(world, num_cases, this_cue_vector);

    var= Variance_Double(this_cue_vector, num_cases);

    free(this_cue_vector);  /* must do this before returns! */

    if ( var < MIN_VAR_ALLOWED )
    {
        if (DEBUG)
            printf("***    TARGET found to be No_Var\n");
        return 1;
    }
    else
        return 0;


}



long Collinear_With_Earlier(struct world_array_struct *world, long this_cue,
				long num_cases, struct longVectTag Index, long Index_size)
/* returns 1 if current vector is collinear 
 * --i.e. has abs correlation > MAX_CORREL_VALUE, set in the header file--
 * with any cue considered and already included in the regression matrix,
 * indicated by being in the Index vector before position Index_size.  
 * (It is then assumed this
 * current vector will be excluded from the model at some later time.)
 */
{
long Index_cntr;
double *this_cue_vector,
	*already_included_cue_vector;
double correl=0;



if(DEBUG)printf("/// collinearity test for cue %ld\n", this_cue); 


	this_cue_vector= (double *) malloc(num_cases * sizeof(double));
	already_included_cue_vector= (double *) malloc(num_cases * sizeof(double));
	/* former will stay fixed; latter will wander over each previous
	 * cue already in the model-- for each pair we will calculate correl
	 */
	
	Extract_Cue_Vector(world, num_cases, this_cue, this_cue_vector);


    Index_cntr= 1; /* recall position 0 is the target */

    while( (Index_cntr < Index_size) && (abs_real(correl) <= MAX_CORREL_VALUE) )
    {

		Extract_Cue_Vector(world, num_cases, VEC(Index,Index_cntr), 
		 already_included_cue_vector);

		correl= Correlation_Double(this_cue_vector, already_included_cue_vector,
		 num_cases);

if(DEBUG)printf("comparing against cue %ld, correl is %lf\n", VEC(Index,Index_cntr), correl);

		Index_cntr++;
    }


	free(this_cue_vector);  /* must do this before returns! */
	free(already_included_cue_vector);

    if((abs_real(correl) > MAX_CORREL_VALUE))
    {
		if(DEBUG)
			printf("*** cue %ld excluded because of collinearity\n", this_cue);
        return 1;
    }
    else
        return 0;


}







void Fill_External_Cv_Array_Reg(struct alg_var_struct *alg_var, struct
world_array_struct *world, double recognition_validity, 
struct useful_variables_struct useful)
{

long cue_cntr,
	cue_cntr2,
	case_cntr;
long drop_this;
long cueorder[useful.num_cues];

  Matrix mat;
  MLRegrec r;
  longVector Index;
  double (*fx[MLREG_MAX_TERM+1])(double);
  double probability;
  double testValue, calcT, tableT;
  double yHat, yHatLow, yHatHigh;
  long i, numTerms, numData;
  long passTest;
  long zero = 0;


  /* if no variation in the target value, make all weights zero
   * and return-- nothing more to model! 
   */
  if(No_Variation_Target(world, useful.num_cities))
  {

    for (cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++)
        (alg_var->cue_validity_array)[cue_cntr]= 0;

	return;

  }

  numData = useful.num_cities;
  numTerms = useful.num_cues;


  /* initialize array fx with default values-- point to function linear,
   * which leaves variables untransformed.
   */

  for (i = 0; i <= MLREG_MAX_TERM; i++)

    fx[i] = linear;



/* matrix will be target variable plus cues, BUT NOT YET RECOGNITION.
 * thus we need num_cues+1 columns. We will indicate in the
 * vector Index which columns are target and which cues (first
 * will be target, others will be cues in RANDOM order)
 */
  newMat(&mat, useful.num_cities, useful.num_cues+1);
  newlongVect(&Index, useful.num_cues+1);

	if(DEBUG)printf("initialized reg matrices & vects\n");

/* below is not the most efficient way to do things, but it's clear. */

/* copy in target values */
    for (case_cntr=0; case_cntr<useful.num_cities; case_cntr++)
        MAT(mat, case_cntr, 0)= world[case_cntr].pop;

/* copy in cues */
    for (case_cntr=0; case_cntr<useful.num_cities; case_cntr++)
	for (cue_cntr=1; cue_cntr<useful.num_cues+1; cue_cntr++)
	    MAT(mat, case_cntr, cue_cntr)= 
		 world[case_cntr].cue[cue_cntr];
/* ignore recognition for now */
	
	if(DEBUG)printf("data successfully copied\n");


/* set Index vector-- 0 indicates target variable, all others are just cues
 * in a certain order which usually doesn't matter. Note that we currently
 * exclude vectors that are all 1's or all 0's, and we exclude those
 * that are collinear (correlation 1) with some other vector */

/* the easy way is below, but then doesn't check for problems
for (cue_cntr=0; cue_cntr<useful.num_cues+1; cue_cntr++)
	VEC(Index, cue_cntr)= cue_cntr;
*/

    VEC(Index, 0)= 0;
    cue_cntr2= 1;
    for (cue_cntr=1; cue_cntr<useful.num_cues+1; cue_cntr++)
        if ( !No_Variation(world, cue_cntr, useful.num_cities)
          && !Collinear_With_Earlier(world, cue_cntr, useful.num_cities,
                                      Index, cue_cntr2)   )
        {
            VEC(Index, cue_cntr2)= cue_cntr;
            cue_cntr2++;
        }

	numTerms= cue_cntr2-1;

	if(DEBUG_REG)printf("set index vector; %ld cues used\n", numTerms);

	/* only count the number of cues NOT excluded, but don't count target */

	/* if rows < columns+1, then drop some columns until okay.
	 */
	while(numData <= numTerms+1)
	{
		/* functions by setting pointer of cue drop_this to last cue, 
		 * and then ignoring pointer to last cue. */
		if(DEBUG_REG)printf("NOTICE: "); fflush(stdout);
		drop_this= New_Rand(numTerms)+1;
		if(DEBUG_REG)printf("dropping cue %ld of %ld ", drop_this, numTerms);
			fflush(stdout); 
		VEC(Index,drop_this)= VEC(Index,numTerms);
		numTerms--;
		if(DEBUG_REG)printf(" simulation modified.\n"); fflush(stdout);
	}




/*************************************/
/*  below we call the JEWELS to do   */
/*  the work after set-up above      */
/*************************************/

  InitializeMLR(&r, numTerms, fx, linear, Index, FALSE, 0);
if(DEBUG)printf("initialized MLR\n"); fflush(stdout);
  CalcSumMLR(mat, &r, numData);
if(DEBUG)printf("CalcSumMLRed\n"); fflush(stdout);
  CalcMultiReg(&r);
if(DEBUG)printf("CalcedMultiReg\n"); fflush(stdout);

/************************************/


    (alg_var->cue_validity_array)[0]= recognition_validity;
	/* recall no recognition for now */

	/* first call all 0, then change the ones that were used
	 * in the regression; which ones were used were in Index 
	 */
    for (cue_cntr=1; cue_cntr < useful.num_cues+1; cue_cntr++)
		(alg_var->cue_validity_array)[cue_cntr]= 0;

    for (cue_cntr=1; cue_cntr < numTerms+1; cue_cntr++)
        (alg_var->cue_validity_array)[VEC(Index,cue_cntr)]= VEC(r.B, cue_cntr);


	if(DEBUG_REG)
	{
		printf("all %ld weights are:\n", useful.num_cues); fflush(stdout);
		Print_Double_Array((alg_var->cue_validity_array), useful.num_cues+1);
		fflush(stdout);
	}




  /* now clean up memory, keeping it all as tidy as a kitty keeps
   * her litter box.... (Bury your shit!)
   */


  deleteMat(&mat);

  deletelongVect(&Index);

  deleteMLRegrec(&r);



} 





double linear(double x)
/* this just effects a linear transformation of the variables.  Other
 * transformations such as squared, exponential, are possible.  Use
 * them in the f functions.  
 */
{

  return x;

}





