/* crossval.h */

void Copy_World(struct world_array_struct *into_me,
struct world_array_struct *copy_me, long num_cases, long num_cues);

void Copy_World_Guided(struct world_array_struct *into_me,
struct world_array_struct *copy_me, long begin, long end, long *case_array,
long num_cues);

void Crossval_Split(struct world_array_struct *world, struct world_array_struct *actual_world, struct world_array_struct *modelling_world, struct useful_variables_struct useful);

