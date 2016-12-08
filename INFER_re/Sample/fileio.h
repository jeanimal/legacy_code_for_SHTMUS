

void Get_Filename_From_User(char *filename);

void Init_From_Disk(struct useful_variables_struct *useful, struct sim_info_struct *sim_info, char *FILENAME);


void Fill_From_Disk(struct world_array_struct *this_struct, struct
useful_variables_struct *useful, char *FILENAME); 


void Print_Results_To_File(struct sim_info_struct *sim_ptr,
 struct score_matrix_struct *score_matrix,
 struct useful_variables_struct useful,
 long Questchoice, long Repchoice);


