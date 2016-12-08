#ifndef _MLREG_H_

#define _MLREG_H_



/*

        Copyright (c) 1995 Namir C. Shammas



    Version 1.0                                Date 7/1/94



    C module which performs the following multiple linear

    regression operations:



        + Basic multiple regression

        + Confidence interval of slopes

        + Student-t test for regression slopes

        + Student-t test for regression coefficient

*/



#include "arrays.h"



#define MLREG_MAX_TERM 100

#define MLREG_BIG 1.0E+30



struct MLR_ANOVAtag {

  double Reg_df;

  double Reg_SS;

  double Residual_df;

  double Residual_SS;

  double Total_df;

  double Total_SS;

  double S2;

  double F;

};



typedef struct MLR_ANOVAtag MLR_ANOVA;



struct MLRegtag {

  long numTerms;

  longVector Index;

  double (*fx[MLREG_MAX_TERM+1])(double);

  double (*invfy)(double);

  /* summation block */

  double sum;

  double sumY;

  double sumYY;

  Matrix A;

  Matrix S;

  Vector TCalc;

  Vector StdErSlope;

  Vector B;

  Vector Mean;

  long hasMissingData;

  double missingCode;

  long Inverted_S;

  double Intercept;

  double R2;

  double R2adj;

  MLR_ANOVA ANOVA;

};



typedef struct MLRegtag MLRegrec;



void InitializeMLR(MLRegrec* r,

                   long NumTerms,

                   double (*Fx[MLREG_MAX_TERM+1])(double),

                   double (*InvFy)(double),

                   longVector VarsIndex,

                   long HasMissingData,

                   double MissingCode);



void CalcSumMLR(Matrix DataMat, MLRegrec* r, long NData);



void CalcMultiReg(MLRegrec* r);



void yHatCI(MLRegrec* r, double probability,

            double* X,

            double* yHatLow,

            double* yHat,

            double* yHatHigh);



void MultiRegCoefCI(MLRegrec* r, double probability,

                    double* slopeHi,

                    double* slopeLow);



void MLR_Slope_T_test(MLRegrec* r, double probability,

                      double testValue, long termNum,

                      double* calcT, double* tableT,

                      long* passTest);



void MLR_R2_T_Test(MLRegrec* r, double probability,

                   double* calcT, double* tableT,

                   long* passTest);



void deleteMLRegrec(MLRegrec* r);



#endif

