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
 * Most of the code comes from Namir C. Shammas' book,
 * C/C++ Mathematical Algorithms for Scientists and Engineers/
 * Book and Disk.  (I think that's the one!)
 * JFC copied it and then modified it.
 */

/* INFER is for comparing the accuracy and frugality of
 * different inference (prediction) heuristics.
 *
 * The task is to infer which of two objects drawn from a population has
 * a higher value on a criterion variable based on several
 * numeric or binary variables.
 *
 * file: mlreg.c
 * purpose: after all data structures set up and filled, implements the "guts" of regression
 *          (regression.c is the interface to the rest of INFER)
 */

/* this is the stuff I copied from a book and slightly modified.  Too bad I didn't write down
 * what damn book it was.  Anyway, it still crashes about 1 in 100,000 times.
 * must run stuff in regression.c before calling this stuff.  lots of set-up needed.
 * regression.c is the interface with the rest of the INFER program.
 * JFC Feb 98 
 */

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "global.h"

#include "mlreg.h"

#include "statlib.h"

#include "main.h"


void InitializeMLR(MLRegrec* r,

                   long NumTerms,

                   double (*Fx[MLREG_MAX_TERM+1])(double),

                   double (*InvFy)(double),

                   longVector VarsIndex,

                   long HasMissingData,

                   double MissingCode)



{

  long i, j, n;

if(DEBUG_REG)printf("begin init MLR\n");
fflush(stdout);

  r->numTerms = (NumTerms > MLREG_MAX_TERM) ?

                             MLREG_MAX_TERM : NumTerms;


  n = r->numTerms + 1;


  newlongVect(&r->Index, n);

  newMat(&r->A, n, n);
  newMat(&r->S, n, n);
  newVect(&r->TCalc, n);
  newVect(&r->StdErSlope, n);
  newVect(&r->B, n);
  newVect(&r->Mean, n);

  for (i = 0; i < n; i++) {

    /* initialize summations */

    for (j = 0; j < n; j++)

      MAT(r->A, i, j) = 0;

    VEC(r->B, i) = 0;

    /* assign function pointers and indices */

    r->fx[i] = Fx[i];

    VEC(r->Index, i) = VEC(VarsIndex, i);

  }


  r->invfy = InvFy;

  r->sumYY = 0;

  r->hasMissingData = HasMissingData;

  r->missingCode = MissingCode;

if(DEBUG_REG)printf("end init MLR\n");
fflush(stdout);
}






void CalcSumMLR(Matrix DataMat, MLRegrec* r, long NData)

{

  long i, j, k;

  long n = r->numTerms + 1;

  Vector Ttrnsf;

  Vector Torig;

  double Yt;

  long OK;


if(DEBUG_REG)printf("begin calcsum\n");
fflush(stdout);

  newVect(&Ttrnsf, n);

  newVect(&Torig, n);



  for (i = 0; i < NData; i++) {

    /* copy data to local array Torig */

    for (j = 0; j < n; j++) {

      k = VEC(r->Index, j);

      VEC(Torig, j) = MAT(DataMat, i, k);

    }


    /* set ok flag */

    OK = TRUE;



    /* are there any possible missing data? */

    if (r->hasMissingData) {

      /* search for missing data */

      j = 0;

      while (j < n && OK)

       if (VEC(Torig, j) > r->missingCode)

         j++;

       else

         OK = FALSE;

    }


    if (OK) {

       /* now transform the data */

       /* first transform Torig[] into Ttrnsf[] */

       for (j = 0; j < n; j++)

         VEC(Ttrnsf, j) = (*r->fx[j])(VEC(Torig, j));



       Yt = VEC(Ttrnsf, 0);

       VEC(Ttrnsf, 0) = 1;

       r->sumYY += SQR(Yt);

       for (k = 0; k < n; k++) {

         VEC(r->B, k) += VEC(Ttrnsf, k) * Yt;

         for (j = 0; j < n; j++)

           MAT(r->A, j, k) += VEC(Ttrnsf, j) * VEC(Ttrnsf, k);

       }

    }

  }

  deleteVect(&Ttrnsf);

  deleteVect(&Torig);

if(DEBUG_REG)printf("end calcsum\n");
fflush(stdout);
}






void CalcMultiReg(MLRegrec* r)

{

  double Diag, tempo, DegF, MS;

  long i, j, k;

  long n = r->numTerms + 1; 
/* numTerms+1 because all loops begin with 1; target is in position 0 */


if(DEBUG_REG)printf("begin calc multi reg\n");
fflush(stdout);
  r->sum = MAT(r->A, 0, 0);

if(DEBUG_REG)
{
printf("1 ");
fflush(stdout);
}

  r->sumY = VEC(r->B, 0);

if(DEBUG_REG)
{
printf("2 ");
fflush(stdout);
}

  /* Form the A and S Matrices */

  for (i = 1; i < n; i++) {

    MAT(r->A, i, 0) = VEC(r->B, i) - r->sumY *

                      MAT(r->A, 0, i) / r->sum;

    for (j = 1; j <= i; j++) {

      MAT(r->A, j, i) -= MAT(r->A, 0, i) *

                         MAT(r->A, 0, j) / r->sum;

      /* Make a copy of the matrix A */

      MAT(r->S, j, i) = MAT(r->A, j, i);

    }

  }

if(DEBUG_REG)
{
printf("3 ");
fflush(stdout);
}

  /* Clear the matrix S inversion flag */

  r->Inverted_S = FALSE;



  r->sumYY -= SQR(r->sumY) / r->sum;

  r->sumY /= r->sum;


if(DEBUG_REG)
{
printf("4 ");
fflush(stdout);
}

  for (i = 1; i < n; i++) {

    MAT(r->A, 0, i) /= r->sum;

    /* Make copies of the mean and std error vectors */

    VEC(r->Mean, i) = MAT(r->A, 0, i);

    VEC(r->StdErSlope, i) = MAT(r->A, i, i);

  }

if(DEBUG_REG)
{
printf("5 ");
fflush(stdout);
}


  /* Form correlation matrix */

  for (i = 1; i < n; i++) {

    MAT(r->A, i, 0) /= sqrt(r->sumYY * VEC(r->StdErSlope, i));

    for (j = 1; j < i; j++)

      MAT(r->A, j, i) /= sqrt(VEC(r->StdErSlope, i) *

                              VEC(r->StdErSlope, j));

    MAT(r->A, i, i) = 1.0;

  }


if(DEBUG_REG)
{
printf("6 ");
fflush(stdout);
}

  /* Complete symmetric part of the matrix */

  for (i = 2; i < n; i++)

    for (j = 1; j < i; j++)

      MAT(r->A, i, j) = MAT(r->A, j, i);


if(DEBUG_REG)
{
printf("7 ");
fflush(stdout);
}


  /* Start solving the simultaneous equations */

  for (j = 1; j < n; j++) {

    Diag = MAT(r->A, j, j);

if(Diag < 0.001)
{
  printf("Reassigning unstable\n");
  fflush(stdout);
  Diag= 0.001;
}
    MAT(r->A, j, j) = 1;

    for (k = 1; k < n; k++)

      MAT(r->A, j, k) /= Diag;


    for (k = 1; k < n; k++)

      if (j != k) {

        tempo = MAT(r->A, k, j);

        MAT(r->A, k, j) = 0;

        for (i = 1; i < n; i++)

          MAT(r->A, k, i) -= MAT(r->A, j, i) * tempo;

      }

  }

if(DEBUG_REG)
{
printf("8 ");
fflush(stdout);
}

  r->R2 = 0;

  r->Intercept = 0;

  for (i = 1; i < n; i++) {
if(DEBUG_REG)printf("i=%ld ", i); fflush(stdout);
    VEC(r->B, i) = 0;

    for (j = 1; j < n; j++)
    {
if(DEBUG_REG)printf("j=%ld ", j); fflush(stdout);
      VEC(r->B, i) += MAT(r->A, j, 0) * MAT(r->A, j, i);
	}
if(DEBUG_REG)printf("\n"); fflush(stdout);

    r->R2 += VEC(r->B, i) * MAT(r->A, i, 0);

    VEC(r->B, i) *= sqrt(r->sumYY / VEC(r->StdErSlope, i));

    r->Intercept += VEC(r->B, i) * MAT(r->A, 0, i);
if(DEBUG_REG)printf("and the rest\n"); fflush(stdout);

  }


if(DEBUG_REG)
{
printf("9 ");
fflush(stdout);
}

/*
  r->Intercept = r->sumY - r->Intercept;

  DegF = r->sum - r->numTerms - 1;

  MS = (1 - r->R2) * r->sumYY / DegF;

  for (i = 1; i < n; i++) {

    VEC(r->StdErSlope, i) = sqrt(MS * MAT(r->A, i, i) /

                       VEC(r->StdErSlope, i));

    VEC(r->TCalc, i) = VEC(r->B, i) / VEC(r->StdErSlope, i);


  }

*/

/*
  r->R2adj = 1 - (1 - r->R2) * r->sum / DegF;

  r->ANOVA.Total_df =  r->numTerms + 1;

  r->ANOVA.Total_SS = r->sumYY;

  r->ANOVA.Reg_df = r->numTerms;

  r->ANOVA.S2 = MS;

  r->ANOVA.Reg_SS = r->sumYY - r->ANOVA.S2;

  r->ANOVA.Residual_df = DegF;

  r->ANOVA.Residual_SS = r->ANOVA.S2 * DegF;

  r->ANOVA.F = DegF / r->numTerms * r->R2 / (1 - r->R2);
*/

if(DEBUG_REG)printf("end calc multi reg\n");
fflush(stdout);
}



void yHatCI(MLRegrec* r, double probability,

                double* X,

                double* yHatLow,

                double* yHat,

                double* yHatHigh)

{

  double diff, p, df, tableT, traceMat, pivot, tempo;

  long i, j, k, m;

  Matrix XX;

  Matrix prodMat;

  long n = r->numTerms + 1;

  Vector Xcopy;


if(DEBUG_REG)printf("begin yHat\n");
fflush(stdout);

  newMat(&XX, n, n);

  newMat(&prodMat, n, n);

  newVect(&Xcopy, n);



  if (probability > 1)

    p = 0.5 - probability / 200;

  else

    p = 0.5 - probability / 2;

  df = r->sum - (r->numTerms + 1);

  tableT = TInv(p, df);



  if (!r->Inverted_S) { /* Invert matrix S */

    r->Inverted_S = TRUE;

    for (j = 1; j < n; j++) {

      pivot = MAT(r->S, j, j);

      MAT(r->S, j, j) = 1;

      for (k = 1; k < n; k++)

        MAT(r->S, j, k) /= pivot;



      for (k = 1; k < n; k++)

        if (k != j ) {

          tempo = MAT(r->S, k, j);

          MAT(r->S, k, j) = 0;

          for (m = 1; m < n; m++)

            MAT(r->S, k, m) -= MAT(r->S, j, m) * tempo;

        }

     }

  }



  /* Calculate yHat */

  *yHat = r->Intercept;

  for (i = 1; i < n; i++) {

    VEC(Xcopy, i) = (*r->fx[i])(X[i]);

    *yHat += VEC(r->B, i) * VEC(Xcopy, i);

  }



  /* Form standarized vector */

  for (i = 1; i < n; i++)

    VEC(Xcopy, i) -= VEC(r->Mean, i);



  /* Form X X' matrix */

  for (k = 1; k < n; k++)

    for (j = 1; j < n; j++)

      MAT(XX, j, k) = 0;



  for (k = 1; k < n; k++) {

    for (j = 1; j < n; j++)

      MAT(XX, j, k) += VEC(Xcopy, j) * VEC(Xcopy, k);

  }



  /* Multiply S_Inverse and XX' */

  for (i = 1; i < n; i++) {

    for (j = 1; j < n; j++) {

      MAT(prodMat, i, j) = 0;

      for (k = 1; k < n; k++)

        MAT(prodMat, i, j) += MAT(r->S, i, k) *

                              MAT(XX, k, j);

    }

  }



  /* Calculate trace of prodMat */

  traceMat = 1.;

  for (i = 1; i < n; i++)

    traceMat *= MAT(prodMat, i, i);



  diff = tableT * sqrt(r->ANOVA.S2 * (1 + 1/r->sum + traceMat));

  *yHatLow  = *yHat - diff;

  *yHatHigh = *yHat + diff;



  *yHat = (*r->invfy)(*yHat);

  *yHatLow = (*r->invfy)(*yHatLow);

  *yHatHigh = (*r->invfy)(*yHatHigh);



  deleteMat(&XX);

  deleteMat(&prodMat);

  deleteVect(&Xcopy);

if(DEBUG_REG)printf("end yHat\n");
fflush(stdout);
}



void MultiRegCoefCI(MLRegrec* r, double probability,

                    double* slopeHi,

                    double* slopeLow)

{

  double diff, p, df, tableT;

  long j;

  long n = r->numTerms + 1;

if(DEBUG_REG)printf("begin coef\n");
fflush(stdout);
  if (probability > 1)

    p = 0.5 - probability / 200;

  else

    p = 0.5 - probability / 2;

  df = r->sum - (r->numTerms + 1);

  tableT = TInv(p, df);

  for (j = 1; j < n; j++) {

   diff = tableT * VEC(r->StdErSlope, j);

   slopeHi[j] = VEC(r->B, j) + diff;

   slopeLow[j] = VEC(r->B, j) - diff;

  }

if(DEBUG_REG)printf("end coeff\n");
fflush(stdout);
}





void MLR_Slope_T_test(MLRegrec* r, double probability,

              double testValue, long termNum,

              double* calcT, double* tableT,

              long* passTest)

{

 double p, df;

if(DEBUG_REG)printf("begin slope t-test\n");
fflush(stdout);
  if (probability > 1)

    p = 0.5 - probability / 200;

  else

    p = 0.5 - probability / 2;

  df = r->sum - (r->numTerms + 1);

  *tableT = TInv(p, df);

  *calcT = (VEC(r->B, termNum) - testValue) /

            VEC(r->StdErSlope, termNum);

  *passTest = (fabs(*calcT) <= *tableT) ? TRUE : FALSE;

if(DEBUG_REG)printf("end slope t-test\n");
fflush(stdout);
}





void MLR_R2_T_Test(MLRegrec* r, double probability,

           double* calcT, double* tableT,

           long* passTest)

/* test hypothesis H0 : R^2 = 0 */

{



  double p, df;

if(DEBUG_REG)printf("begin other test\n");
fflush(stdout);
  if (probability > 1)

    p = 0.5 - probability / 200;

  else

    p = 0.5 - probability / 2;

  df = r->sum - (r->numTerms + 1);

  *tableT = TInv(p, df);

  *calcT = sqrt(r->R2 * df /(1 - r->R2));

  *passTest = (*calcT <= *tableT ) ?  FALSE : TRUE;

if(DEBUG_REG)printf("end other test\n");
fflush(stdout);
}



void deleteMLRegrec(MLRegrec* r)

{
if(DEBUG_REG)printf("begin delete\n");
fflush(stdout);
  deletelongVect(&r->Index);

  deleteMat(&r->A);

  deleteMat(&r->S);

  deleteVect(&r->TCalc);

  deleteVect(&r->StdErSlope);

  deleteVect(&r->B);

  deleteVect(&r->Mean);

if(DEBUG_REG)printf("end delete\n");
fflush(stdout);
}

