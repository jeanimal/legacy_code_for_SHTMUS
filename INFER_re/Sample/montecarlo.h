

void Build_World_Basics(struct world_array_struct *world,
struct useful_variables_struct useful);

void Build_World_Binomial(struct world_array_struct *world,
struct useful_variables_struct useful);


void Build_World_Planar(struct world_array_struct *world,
struct useful_variables_struct useful);

void Build_World_Uniform(struct world_array_struct *world,
struct useful_variables_struct useful);


void Print_Just_Cues(struct world_array_struct *this_struct,
long num_cities, long num_cues);

/* MONTEC FILESTUFF */
void Print_Just_Cues_To_File(struct world_array_struct *this_struct,
long num_cities, long num_cues);


/* MONTEC FILESTUFF */
void Print_Montec_Score(struct score_struct *score_ptr1, 
struct score_struct *score_ptr2,
struct useful_variables_struct useful, struct sim_info_struct sim_info,
char *out_file_name, long num_quest);



/* MONTEC FILESTUFF */
/*
void Print_Just_One_Score(struct score_matrix_struct *score_matrix,
long curr_per_index, long curr_city, long Questchoice, long Repchoice);
*/




