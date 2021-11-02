/* declare your functions here */
#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H
#define SEASON_ALPHA 4;
#define D_T_S_ALPHA 2; //Disease, Accident, Surgery aplhas
#define F_S_ALPHA 3; //Fever, Smoking aplhas
#define ALCOHOL_ALPHA 5;

#define M_PI 3.14159265358979323846

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

//assume that collumns are always the same data.

//setup initial probability for altered and normal | float** is a 2d array
float Init_Probability(float **semen);

//takes in array | will output probality for input data
//float probability(float *semen, int alpha);

//calculate mean for guassisan distribution | takes in which collumn to avg. 
void Mean(int column, float mean[]);

//calculate Std Dev for guassisan distribution | takes in which collumn to avg. 
void Standard_Deviation(int column, float mean[], float sd[]);

//calculate probability of both age and sitting and return age * probability
float Gaussian_Probability(float data[], struct probability probability);

//calculate posterior probability based on the conditional probability
double Posterior_Probability(int i, struct probability probability);

//prediction based on conditional probability
int NB_Prediction(double normal_p, double altered_p);

//makes final calculations for a given dataset from start_count to end_count
double** Make_Predict(int start_count, int end_count, int size);

//plot probability of error graph
void Plot_Graph(int terminal, char *name, int size, double** prob_error_arr);

//use (results*100)/total data to get scoring 
//calculate the score for the naive bayes algo
float Scoring();

//enum class
enum Season{winter, spring, summer, fall};
enum Fever{less_than_three_months_ago = -1, more_than_three_months_ago, No};
enum Alcohol_Consumption{several_times_a_day, every_day, several_times_a_week, once_a_week, hardly_ever_or_never};
enum Smoking_Habit{never = -1, occasional, daily};

//functions prototype for calculating probability
void Prior_Probability();
void Prob_Season();
void Prob_Age();
void Prob_Childish_Disease();
void Prob_Accident();
void Prob_Surgical_Intervention();
void Prob_Fever();
void Prob_Alcohol_Consumption();
void Prob_Smoking();
void Prob_Sitting();

#endif