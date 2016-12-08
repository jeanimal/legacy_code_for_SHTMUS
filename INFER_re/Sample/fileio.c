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
 * file: fileio.c
 * purpose: file input and output; reading data from file, printing results
 */

#include "main.h"
#include "fileio.h"
#include <stdio.h>
#include <stdlib.h>

void Get_Filename_From_User(char *filename)
{
long cntr=0;


	printf("enter file name from which to read world data\n: ");

	scanf("%c", filename+cntr); /* cntr should still be 0 */

	while (filename[cntr] != '\n')
	{
		cntr++;
		if(cntr>NAMELENGTH)
		{
			printf("ERROR: file name too long\n");
			exit(1);
		}
		scanf("%c", filename+cntr );
	}

	/* note final value of cntr is equal to number of real chars
	 * (i.e. not including the \0), the length of the string.
	 */



	/* below, replace EOL with end-of-string */
	filename[cntr]= '\0';  

	if(DEBUG)printf("filename= %s\n", filename);
/*
temp_name[0]= 'j';
temp_name[1]= 'e';
temp_name[2]= 'a';
temp_name[3]= 'n';
temp_name[4]= '\0';

printf("after assign: temp_name= %s\n", temp_name);
*/

}





void Init_From_Disk(struct useful_variables_struct *useful, struct sim_info_struct *sim_info, char *FILENAME)
{
FILE *Input;

char temp_char;
long data_num;


	printf("opening %s", FILENAME);
    Input= fopen(FILENAME, "r");
	if(Input == NULL) {
		printf("...failed to open file!\n");
		exit(1);
	}        
	printf("\n");

    /* first should be a 3-char string specifying the file name code */
    /* this will be used for the name of the output file */
    fscanf(Input, "%s", (sim_info->Filecode));

    /* next should be two numbers--  num_cities and then num_cues */
    fscanf(Input, "%ld", &(useful->num_cities));  /* let's hope we don't need a tempint */
    fscanf(Input, "%ld", &(useful->num_cues));
    if(DEBUG)printf("expecting %ld cities, %ld cues\n", useful->num_cities,
     useful->num_cues);


	fclose(Input);

}





void Fill_From_Disk(struct world_array_struct *this_struct, struct
useful_variables_struct *useful, char *FILENAME)
{
FILE *Input;
long data_num;
long cue_num;

double double_temp;
char *str_temp[3];
long long_temp;
char temp_char;
float float_temp;

    Input= fopen( FILENAME, "r");
	printf("opening %s", FILENAME);
	if(Input == NULL)printf("...failed to open file!\n");        
	printf("\n");

	/* first get over some irrelevant information */
	/* (should have already been read in Init_From_Disk) */
	fscanf(Input, "%s", str_temp);
	if(DEBUG)printf("Filecode: %s\n", str_temp);
	fscanf(Input, "%ld", &long_temp);
	fscanf(Input, "%ld", &long_temp);


	/* now begin normal data input */


        for (data_num=0; data_num < (long) useful->num_cities; data_num++) 
		{
			if(DEBUG2)printf("about to read case %ld\n", data_num);
                fscanf(Input, "%s", this_struct[data_num].name);
                fscanf(Input, "%ld", &this_struct[data_num].rank);
                fscanf(Input, "%ld", &this_struct[data_num].pop);
                /* first "cue" is actually recognition or not--
                        used in knowledge array, here simply 1 */
                fscanf(Input, "%f", &float_temp);
                this_struct[data_num].cue[0]= (double) float_temp;
                /* now the real cues */
                for (cue_num= 1; cue_num < (long) useful->num_cues+1; cue_num++)
				{ 
                        fscanf(Input, "%f", &float_temp);
                        this_struct[data_num].cue[cue_num]= (double) float_temp;
                }
		/* now read till end of line */
		while(fgetc(Input) != '\n');	

        }

        fclose(Input);

}







void Print_Results_To_File(struct sim_info_struct *sim_ptr,
 struct score_matrix_struct *score_matrix, 
 struct useful_variables_struct useful,
 long Questchoice, long Repchoice)

{


long city_cntr,
  per_cntr;
double divider;
double temp;

double sumC;
double sumCSq;

FILE *fp;




    divider= (double) Questchoice * (double) Repchoice;
    fp= fopen(sim_ptr->Correctfilename, "w+");

	for (city_cntr=0; city_cntr < useful.num_cities+1; city_cntr++) 
	{
    	for (per_cntr=0; per_cntr < useful.num_percents; per_cntr++) 
		{
			/* below is equivalent to
			 *  temp= score_matrix[city_cntr][per_cntr].correct / divider;
			 * but for dynamic memory allocation we're using now.
			 */
        	temp= score_matrix[ city_cntr * useful.num_percents  +
					per_cntr ].correct / divider;
            fprintf(fp, "%lf\t", temp);
        }
        fprintf(fp,"\n");
    }

    fclose(fp);




   if (sim_ptr->Lookupchoice != 0) {

      fp= fopen(sim_ptr->Lookupfilename, "w+");

      for (city_cntr=0; city_cntr < useful.num_cities+1; city_cntr++) 
	  {
        for (per_cntr=0; per_cntr < useful.num_percents; per_cntr++) 
		{
			/* below is equilavent to score_matrix[city_cntr][per_cntr] */
        	temp=  score_matrix[ city_cntr * useful.num_percents  +
                    per_cntr ].lookups / divider;
                        fprintf(fp, "%lf\t", temp);
        }
        fprintf(fp,"\n");
      }

      fclose(fp);


   }

   if (sim_ptr->Guesschoice != 0) {

        fp= fopen(sim_ptr->Guessfilename, "w+");

        for (city_cntr=0; city_cntr < useful.num_cities+1; city_cntr++) 
		{
        	for (per_cntr=0; per_cntr < useful.num_percents; per_cntr++) 
			{
				/* below is equivalent to score_matrix[city_cntr][per_cntr] */
              	temp= score_matrix[ city_cntr * useful.num_percents  +
                    per_cntr].guesses / divider;
                fprintf(fp, "%lf\t", temp);
             }
             fprintf(fp,"\n");
        }

        fclose(fp);


   } /* end if */


} /* end function Print_Results_To_File */




 
