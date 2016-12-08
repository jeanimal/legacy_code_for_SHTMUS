

long No_Variation(struct world_array_struct *world, long this_cue, long num_cases);

long No_Variation_Target(struct world_array_struct *world, long num_cases);

long Collinear_With_Earlier(struct world_array_struct *world, long this_cue,
                 long num_cases, struct longVectTag Index, long Index_size);

void Fill_External_Cv_Array_Reg(struct alg_var_struct *alg_var, struct
world_array_struct *world, double recognition_validity,
struct useful_variables_struct useful);


double linear(double);


