/* A statistical library copied from somewhere. */

#include <math.h>

#include "statlib.h"

#include "global.h"





double Q(double x)

/* Function that returns the "Normal"

	probability distribution integral */

{

  const double twoPi = 6.283185308;



  double result;

  double sum; /* summation */

  double xp; /* x raised to an integer power */

  double tempo;

  /* Array of coefficients */

  double b[5] = { 0.319381530, -0.356563782,

						1.781477937, -1.821255978,

						1.330274429 };



  long i;



  tempo = 1.0 / ( 1.0 + 0.2316419 * fabs(x));

  /* Initialize summation */

  sum = 0.0;

  xp = 1.0;

  /* Loop to obtain summation term */

  for (i = 0; i < 5; i++) {

	 xp *= tempo; /* Update power factor */

	 sum += b[i] * xp;

  }

  /* Calculate result */

  result = (exp(-x * x / 2.0) / sqrt(twoPi) * sum);

  result = (x >= 0.0) ? 1.0 - result : result;

  return result;

}



double QInv(double x)

/*  calculate the inverse normal. */

{

  double result;

  double sum1, sum2; /* Two summations used */

  double tempo, xp;

  long i;

  /* First and second coefficient array */

  double c[4] = { 2.515517, 0.802853,

						0.010328, 0.0 };

  double d[4] = { 1.0, 1.432788, 0.189269, 0.001308 };



	 /* Check limits of x */

	 if (x <= 0.0)

		x = 0.0001;

	 if (x >= 1.0)

		x = 0.9999;



	 if (x <= 0.5)

		tempo = sqrt(log(1.0/SQR(x)));

	 else

		 tempo = sqrt(log(1.0/SQR(1.0 - x)));



	 /* Initialize summations */

	 sum1 = 0.0;

	 sum2 = 0.0;

	 xp = 1.0;

	 /* Start loop to calculate summations */

	 for (i = 0; i <4; i++) {

		  sum1 += c[i] * xp;

		  sum2 += d[i] * xp;

		  xp *= tempo; /* Update power factor */

	 }

	 /* Calculate the result */

	 result = tempo - sum1 / sum2;

	 result = (x > 0.5) ? -result : result;

	 return result; /* Return sought value */

}



double T(double x, double df)

/* Function will return the probability of

  obtaining a student-t statistic, x, at

  df degrees of freedom.                       */



{

  double xt;



  xt = x * (1.0 - 0.25 / df) /

		 sqrt(1.0 + SQR(x) / 2.0 / df);

  return (1.0 - Q(xt));

}



double TInv(double x, double df)

/* double will return the value of student-t statistic for a

	given probability, x, and df degrees of freedom.          */



{

	 double sum, xp, xq;

	 double Pwr[10]; /* Array of powers of xq */

	 double term[5]; /* Array of terms */

	 long i;



	 /* Check limits of x */

	 if (x <= 0.0)

		x = 0.0001;

	 if (x >= 1.0)

		x = 0.9999;



	 xq = QInv(x);

	 Pwr[1] = xq;

	 /* Loop to obtain the array of powers */

	 for (i = 2; i <= 9; i++)

		  Pwr[i] = Pwr[i-1] * xq;



	 /* Calculate the four terms */

	 term[1] = 0.25 * (Pwr[3] + Pwr[1]);

	 term[2] = (5*Pwr[5] + 16*Pwr[3] + 3*Pwr[1])/96;

	 term[3] = (3*Pwr[7] + 19*Pwr[5] + 17*Pwr[3] -

					15*Pwr[1])/384;

	 term[4] = (79*Pwr[9] + 776*Pwr[7] + 1482*Pwr[5] -

					1920*Pwr[3] - 945*Pwr[1])/92160.0;

	 /* Initialize summation and power factor */

	 sum = xq;

	 xp = 1;

	 /* Loop to add terms */

	 for (i = 1; i <= 4; i++) {

		  xp *= df; /* Update df power factor */

		  sum += term[i] / xp;

	 }

	 return sum;

}



double Chi(double x, double df)

/* Function will return the probability of obtaining a

  chi-squared statistic, x, at df degrees of freedom.  */

{

  double k, xq;



  k = 2.0 / 9.0 / df;

  xq = (pow((x/df), 0.33333) - (1.0 - k))/ sqrt(k);

  return (1.0 - Q(xq));

}



double ChiInv(double x, double df)

/* double will return the value of chi-squared statistic for a */

/* given probability, x, and df degrees of freedom.              */



{

	 double k, tempo, xq;



	 /* Check limits of x */

	 if (x <= 0.0)

		x = 0.0001;

	 if (x >= 1.0)

		x = 0.9999;



	 k = 2.0 / 9.0;

	 xq = QInv(x);

	 tempo = 1.0 - k / df + xq * sqrt(k / df);

	 tempo = df * CUBE(tempo);

	 return tempo; /* Return sought value */



}





double F(double x, double df1, double df2)

/* Function will return the probability of obtaining an

	F statistic, x, at df degrees of freedom.             */



{

  double f1, f2, k;



  k = 2.0 / 9.0;

  f1 = pow(x, 0.333334) * (1 - k / df2) - (1 - k / df1);

  f2 = sqrt(k / df1 + pow(x, 0.666667) * k / df2);

  return 1.0 - Q(f1 / f2);

}





double FInv(double x, double df1, double df2)

/* Function will return the value of the F statistic for a

  given probability, x, and df degrees of freedom.        */



{

  double alpha, beta, gamma, delta,

			A, B, C, k, result, xq;



  /* Check limits of x */

  if (x <= 0.0 )

	 x = 0.0001;

  if (x >= 1.0 )

	 x = 0.9999;



  k = 2.0 / 9.0;

  xq = QInv(x);

  alpha = (1 - k / df2);

  beta = (1 - k /df1);

  gamma = 1.0 - (1 - k / df1);

  delta = 1.0 - (1 - k / df2);

  A = SQR(alpha) - SQR(xq) * delta;

  B = -2.0 * alpha * beta;

  C = SQR(beta) - SQR(xq) * gamma;



  result = (-1.0 * B + sqrt(B * B - 4.0 * A * C))/(2.0 * A);

  return CUBE(result);

}

