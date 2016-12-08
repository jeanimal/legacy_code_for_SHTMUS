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
 * file: getsiminfo.c
 * purpose: get simulation info from user, e.g. inference algs to use
 *            (major parameters are set in variables.h)
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h> 
#include "main.h"
#include "getsiminfo.h"
#include "variables.h"

/* Get sim info: Routines for getting the parameters from the user*/

void Get_Sim_Info(struct sim_info_struct *AStruct, struct
useful_variables_struct useful) 
{

float tempfloat;
long templong;
long max_num_quest;


printf ("\nPlease select an algorithm\n");
printf ("1 = PMM\n");
printf ("2 = Tallying\n");
printf ("3 = Weighted Tallying\n");
printf ("4 = Unit weighted linear model\n");
printf ("5 = Real weighted linear model\n");
printf ("6 = Multiple regression\n");
printf ("7 = Random cue algorithm\n");
printf ("8 = Take the last algorithm\n");
printf ("9 = Most Frequent cue algorithm\n");
printf("10= PMM w/ 2nd chance actvn.\n");
printf("11= RND w/ 2nd chance actvn.\n");
printf("12= REC w/ 2nd chance actvn. \n");
printf("13= FRE w/ 2nd chance actvn. \n");
printf("14= PMM w/ weak actvn (take the best)\n");
printf("15= RND w/ weak actvn (minimalist)\n");
printf("16= REC w/ weak actvn\n");
printf("17= FRE w/ weak actvn\n");
printf("18= RND w/weak, re-rand every inf.\n");
printf("19= real weighted linear w/ -.5\n");
printf("20= simple bayes\n");
printf(": ");
scanf ("%ld",&(AStruct->Algchoice));

switch (AStruct->Algchoice) {
case 1: strcpy(AStruct->Algstr,"PMM.");break;
case 2: strcpy(AStruct->Algstr,"Tal.");break;
case 3: strcpy(AStruct->Algstr,"WTal.");break;
/* TEMP CHANGE */
case 4: strcpy(AStruct->Algstr,"ULinT.");break;
case 5: strcpy(AStruct->Algstr,"WLin.");break;
case 6: strcpy(AStruct->Algstr,"Reg.");break;

/*
case 7: strcpy(AStruct->Algstr,"P.RND.");break;
*/

case 8: strcpy(AStruct->Algstr,"P.REC.");break;

/*
case 9: strcpy(AStruct->Algstr,"P.FRE.");break;
case 10: strcpy(AStruct->Algstr,"PMM2.");break;
case 11: strcpy(AStruct->Algstr,"RND2.");break;
case 12: strcpy(AStruct->Algstr,"REC2.");break;
case 13: strcpy(AStruct->Algstr,"FRE2.");break;
*/

case 14: strcpy(AStruct->Algstr,"PMMw.");break;
case 15: strcpy(AStruct->Algstr,"RNDw.");break;
case 16: strcpy(AStruct->Algstr,"RECw.");break;
case 17: strcpy(AStruct->Algstr,"FREw.");break;
case 18: strcpy(AStruct->Algstr,"RND3.");break;
case 19: strcpy(AStruct->Algstr,"WLn5.");break;
case 20: strcpy(AStruct->Algstr,"BAY.");break;
}



/* recognition is currently always on, so this is temporarily disabled */
/*
printf ("\n0 = Recognition principle off\n");
printf ("1 = Recognition principle on\n");
scanf ("%ld",&(AStruct->RPchoice));
if (AStruct->RPchoice) strcpy(AStruct->RPstr,"RP.");
else strcpy(AStruct->RPstr,"NRP.");
*/


printf("CROSSVALIDATE= %ld\n", CROSSVALIDATE);


printf("\nType the # of reps\n:");
scanf("%ld",&(AStruct->Repchoice));


/* CHANGE 042897 jfc */
/* to make input easier for common case of full info */

printf("\nRun under full information? (1=yes, 0=no)\n:");
scanf("%ld", &templong);
if (templong == 1)
{
	AStruct->CVchoice=(double)1;
	AStruct->Start_per_choice= useful.num_percents-1;
	if (!CROSSVALIDATE)
		AStruct->Start_city_choice= useful.num_cities;
	else
		AStruct->Start_city_choice= useful.actual_num_cities/2;

}
else
{

	printf("\nEnter recognition cue validity\n:");
	scanf("%f",&tempfloat);
	AStruct->CVchoice=(double)tempfloat;


	printf("\nType the percent cues index to begin with: 0 through %ld\n:", 
  	 useful.num_percents-1);
	scanf("%ld",&(AStruct->Start_per_choice));
    if (AStruct->Start_per_choice > useful.num_percents-1)
    {
        printf("ERROR: value too large\n");
        exit(1);
    }


	if (!CROSSVALIDATE)
		printf("\nType the city to begin with: 0 through %ld\n:",
	 	 useful.num_cities);
	else
		printf("\nType the city to begin with: 0 through %ld\n:",
         useful.actual_num_cities/2);
	scanf("%ld", &(AStruct->Start_city_choice));
	if (AStruct->Start_city_choice > useful.num_cities)
	{
		printf("ERROR: value too large\n");
		exit(1);
	}	

} /* end else not full info */





	printf("\nDo you want the full question array? (1=yes, 0=no)\n:");
	scanf("%ld", &templong);


	if (!CROSSVALIDATE)
		max_num_quest= useful.num_cities*(useful.num_cities-1)/2;
	else
		max_num_quest= (useful.actual_num_cities/2)*
						(useful.actual_num_cities/2-1)/2;


	if (templong==1)
    	AStruct->Questchoice= max_num_quest;
	else
	{
		printf("\nType # of questions; %ld is exhaustive:\n", max_num_quest);
		scanf("%ld",&(AStruct->Questchoice));
		if (AStruct->Questchoice > useful.num_cities*(useful.num_cities-1)/2   )
		{
  			printf("Value too large");
  			exit(0);
 		}
	} /* end else of (templong==1) */



printf("\nType 1 to count the average number of lookups per question");
printf("\nType 0 to skip this process\n");
scanf("%ld",&(AStruct->Lookupchoice));


printf("\nType 1 to count the number of guesses made");
printf("\nType 0 to skip this process\n");
scanf("%ld",&(AStruct->Guesschoice));


if (ASKSAMPLING) {
	printf("\nSAMPLING ON\n");
	if (!CROSSVALIDATE) {
		printf("sampling makes no sense without crossval!\n");
		exit(1);
	}
	printf("If your sample is an absolute number, type 0\n");
	printf("If your sample number is a percent, type 1\n");
	scanf("%ld", &(AStruct->Samplingtype));
	if (AStruct->Samplingtype != 0 && AStruct->Samplingtype != 1) {
		printf("Sampling type %ld unrecognized\n", 
		  AStruct->Samplingtype);
		exit(1);
	}
	printf("Enter sample N: ");
	scanf("%lf", &(AStruct->SampleN));
}



} /* end function */






void Make_Output_File_Names(struct sim_info_struct *AStruct)
{

    sprintf (AStruct->Correctfilename,"%s%s.%ld.%ld.%ld",AStruct->Algstr,
     AStruct->Filecode,(int)(AStruct->CVchoice*100),AStruct->Questchoice,
     AStruct->Repchoice);

    sprintf (AStruct->Datafilename,"DAT.%s%s.%ld.%ld.%ld",AStruct->Algstr,
     AStruct->Filecode,(int)(AStruct->CVchoice*100),AStruct->Questchoice,
     AStruct->Repchoice);


    if (AStruct->Lookupchoice)
        sprintf (AStruct->Lookupfilename,"%s%s.%ld.%ld.%ld.lu",AStruct->Algstr,
         AStruct->Filecode,(int)(AStruct->CVchoice*100),AStruct->Questchoice,
         AStruct->Repchoice);


    if (AStruct->Guesschoice)
        sprintf (AStruct->Guessfilename,"%s%s.%ld.%ld.%ld.gu",AStruct->Algstr,
         AStruct->Filecode,(int)(AStruct->CVchoice*100),AStruct->Questchoice,
         AStruct->Repchoice);

    if(CROSSVALIDATE)
    {
        strcat(AStruct->Correctfilename, ".CV");
        strcat(AStruct->Datafilename, ".CV");
        strcat(AStruct->Lookupfilename, ".CV");
        strcat(AStruct->Guessfilename, ".CV");
    }



}


