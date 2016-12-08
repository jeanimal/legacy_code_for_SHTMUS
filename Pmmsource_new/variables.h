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
 * file: variables.h 
 * purpose: holds major parameters of the simulation.  must recompile if changed.
 */

/* variables.h */

/* for ease of adjusting the values of major program
 * parameters, they are held here.  This file should be
 * included in main.c and main.c only.  In main() they
 * are immediately loaded into local variables and then
 * passed into functions as needed-- nice and modular!
 */

#define NUMPERCENTS     6
#define CUEREVERSE      1 /* if =1, cues will  be reversed
                            when their validities are below 0.5 */
                          /* "reversed" means for that cue, all 1-values
                          will be changed to 0's, and all 0's to 1's */

#define CROSSVALIDATE	0 /* if =1, data will be split into two;
						   * one half will be used to calculate
						   * weights and validities, and these will
						   * be applied to predictions in other half.
						   * WARNING: if this is ON, you must use
						   * Calc_Cue_Validity_Old rather than _Fast.
						   * It is also safer to turn OFF CUEREVERSE.
						   */


/* NOT YET IMPLEMENTED */
/*
#define CATEGORIZE      0 */
						  /* if =1, then discriminating cues that have
                           * same target variable (populations) will be
                           * scored as 0.5 rather than 0 (wrong) in the
                           * cue validity calculation (must be Old version,
                           * not Fast version for this to work).  This
                           * situation comes up only in categorization
                           * tasks.   */




