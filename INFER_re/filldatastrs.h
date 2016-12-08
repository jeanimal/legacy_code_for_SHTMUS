/***** filldatastrs.h *******/

                 
/* Function Prototypes */
void
Fill_Question_Array(struct question_pair_struct *Quest_Point, long num_cities);

void 
Fill_Ss_Knowledge_Array(long *known_cities, long num_cities_known, double proportion_cues_known, struct world_array_struct *world, struct world_array_struct *s_knowledge, struct useful_variables_struct useful);

double
Calc_Cue_Validity_Fast(struct world_array_struct *world_struct, long 
which_cue, struct useful_variables_struct);

double
Calc_Cue_Validity_Old(struct world_array_struct *world_struct, long 
which_cue, struct useful_variables_struct);


void
Fill_External_Cv_Array(struct alg_var_struct *alg_var, struct world_array_struct
 *this_struct, double recognition_validity, struct useful_variables_struct
useful);


void Reverse_This_Cue(struct world_array_struct *world_struct, long
which_cue, struct useful_variables_struct useful);


void Check_For_Reverse(double *validity, struct world_array_struct
*world_struct, struct useful_variables_struct useful);

/* score matrix never used in montec b/c perfect information */
void 
Init_Score_Matrix(struct score_matrix_struct *score_matrix, struct
useful_variables_struct useful);


/* below is another version of cue validity proposed by Laura. 
 * it's currently inactive.  
 */
double
Calc_Cue_Validity_Suc (struct world_array_struct *world_struct, long cue_num, long
 num_cities);


