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
 * file: show_choose.c
 * purpose: chooses n objects randomly from m (choose in mathematical sense)
 */

#include "main.h"
#include "show_choose.h"
#include <stdio.h>
#include <stdlib.h>

long At_Max(long currposition,long currvalue,long maxposition,long maxvalue)
{
if (currvalue==maxvalue-maxposition+currposition) {
 return 1;
 } else { 
 return 0;
}
}

void Show_Choose(long* retarray,long m, long n, long ith, long empty,
struct useful_variables_struct useful) 
{
/* The flag empty lets you pass in the last soln found, so
  it doesn't have to start from scratch every time */

long *indexset;
long maxvalue=m-1; 
long maxposition=n-1;
long i,j,k,counter=0;
register long currposition;


/* init array -- malloc */
indexset= (long *) malloc(useful.num_cities * sizeof(long));


if (n>m)
        {
        printf ("Cannot choose %ld from %ld", n,m);
        exit(1);
        }

if (empty) 
    for (i=0;i<=maxposition;i++) { indexset[i]=i; }
 else
    for (i=0;i<=maxposition;i++) { indexset[i]=retarray[i]; }

if (ith == 0) {
    for (i=0;i<=maxposition;i++) { 
    retarray[i]=indexset[i];
   /*    printf("%ld ",retarray[i]); */
    }
free(indexset);
return;
    }

do {
counter++;
currposition=maxposition;
while (At_Max(currposition,indexset[currposition],maxposition,maxvalue)) 
 {
 currposition--;
 }
if (currposition >= 0) {

indexset[currposition]++;
j=indexset[currposition]+1;
for (k=currposition+1;k<=maxposition;k++,j++) {
  indexset[k]=j; 
 }

if (counter==ith) {
    for (i=0;i<=maxposition;i++) { 
    retarray[i]=indexset[i];
   /*    printf("%ld ",retarray[i]); */
    }
free(indexset);
return;
}
}
} while (currposition >= 0);

printf ("Index too high error in show_choose\n");

exit(1);

}  /* end of fn Show_Choose */

/*void main() {

long *myarray;
long m=7,n=5,ith,j;

myarray= malloc(NUMCITIES*sizeof(long));

for (ith=0;ith<0300;ith++) {
  printf ("Solution number %ld: ",ith);

  Show_Choose(myarray,m,n,ith);
  for (j=0;j<n;j++) { printf ("%ld ",myarray[j]); }
printf ("\n");
	free(myarray);
  }

} */
