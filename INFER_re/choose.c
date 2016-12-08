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
 * file: Choose.c
 * purpose: supplanted by show_choose.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "choose.h"


double Choose (long m, long n) {
double partialtop, partialbottom;
long p;
long i,j,lowerstop,upperstop;
if (n>m) 
        {
        printf ("Cannot choose %ld from %ld", n,m);
        exit(1);
        }
if (
    (m==n) ||
    (m==0) ||
    (n==0) )
return 1;

p=m-n;
if (p>n) {
  lowerstop=m-n+1;
  upperstop=n;
  } else {
  lowerstop=m-p+1;
  upperstop=p;
  }
partialtop=(double)lowerstop++;
for (i=lowerstop;i<=m;i++)
  {
  partialtop*=(double)i;
  }
j=1;
partialbottom=(double)j++;
for (i=j;i<=upperstop;i++)
  {
  partialbottom*=(double)i;
  }
/*printf ("partialtop: %lf partialbottom: %lf\n",partialtop, partialbottom);
*/
return partialtop/partialbottom;

}


/*
main () {
long i,j;
i=84;
for (j=0;j<=i;j++)
printf ("%ld choose %ld is %lf\n",i,j,Choose(i,j));
} */
