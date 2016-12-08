
double Average_long(long *array, long len);

double Average_Double(double *array, long len);

double Covariance_long(long *array1, long *array2, long len);
double Variance_long(long *array, long len);

double Covariance_Double(double *array1, double *array2, long len);
double Variance_Double(double *array, long len);

double Correlation_long(long *array1, long *array2, long len);

double Correlation_Double(double *array1, double *array2, long len);


void Extract_Cue_Vector(struct world_array_struct *world,
long num_cases, long which_cue, double *cue_vector);

void Extract_Target_Vector(struct world_array_struct *world,
long num_cases, double *cue_vector);

long Count_1s(double *array, long len);

double abs_real (double abs_me);

