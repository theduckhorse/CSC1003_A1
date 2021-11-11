/* declare your functions here */
#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H
#define SEASON_ALPHA 4;
#define D_T_S_ALPHA 2; //Disease, Accident, Surgery aplhas
#define F_S_ALPHA 3; //Fever, Smoking aplhas
#define ALCOHOL_ALPHA 5;

#define M_PI 3.14159265358979323846
#define s_col 10 //s_col (Amount of variables for semen)
//extern int s_row;
extern float altered_probability, normal_probability;

struct probability
{
    //alpha 4 
    float winter_probability, spring_probability, summer_probability, fall_probability;
    //alpha 
    float age_mean, age_standard_deviation;
    //alpha 2
    float disease_probability, no_disease_probability;
    //alpha 2
    float trauma_probability, no_trauma_probability;
    //alpha 2
    float surgery_probability, no_surgery_probability;
    //alpha 3
    float fever_less3m_probability, fever_more3m_probability, no_fever_probability;
    //alpha 5
    float alcohol_several_day_probability, alcohol_everyday_probability, alcohol_several_week_probability, alcohol_once_week_probability, alcohol_hardly_probability;
    //alpha 3
    float smoke_never_probability, smoke_occasional_probability, smoke_daily_probability;
    float sitting_mean, sitting_standard_deviation;
    float prior_probability;
};
extern struct probability altered;
extern struct probability normal;

//assume that columns are always the same data.

//setup initial probability for altered and normal | float** is a 2d array
float Init_Probability(float **semen, int s_row);

//takes in array | will output probality for input data
//float probability(float *semen, int alpha);

//calculate mean for guassisan distribution | takes in which collumn to avg. 
void Mean(int column, float mean[], float **s_arr, int s_row);

//calculate Std Dev for guassisan distribution | takes in which collumn to avg. 
void Standard_Deviation(int column, float mean[], float sd[], float **s_arr, int s_row);

//calculate probability of both age and sitting and return age * probability
float Gaussian_Probability(float data[], struct probability probability);

//calculate posterior probability based on the conditional probability
double Posterior_Probability(int i, struct probability probability, float **s_arr);

//prediction based on conditional probability
int NB_Prediction(double normal_p, double altered_p);

//makes final calculations for a given dataset from start_count to end_count
double** Make_Prediction(int start_count, int end_count, int size, float **s_arr);

//calculate confusion matrix values
int *Compute_Confusion_Matrix(double **data_arr, int size);

//use (results*100)/total data to get scoring 
//calculate the score for the naive bayes algo
double Scoring(int tn_count, int tp_count, int total);

//functions prototype for calculating probability
void Prior_Probability(float **arr, int s_row);
void Prob_Season(float **arr, int s_row);
void Prob_Age(float **arr, int s_row);
void Prob_Childish_Disease(float **arr, int s_row);
void Prob_Accident(float **arr, int s_row);
void Prob_Surgical_Intervention(float **arr, int s_row);
void Prob_Fever(float **arr, int s_row);
void Prob_Alcohol_Consumption(float **arr, int s_row);
void Prob_Smoking(float **arr, int s_row);
void Prob_Sitting(float **arr, int s_row);

#endif