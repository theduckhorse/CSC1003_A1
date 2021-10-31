/* declare your functions here */
#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H
#define SEASON_ALPHA 4;
#define D_T_S_ALPHA 2; //Disease, Accident, Surgery aplhas
#define F_S_ALPHA 3; //Fever, Smoking aplhas
#define ALCOHOL_ALPHA 5;

#define M_PI 3.14159265358979323846

extern float altered_probablity, normal_probablity;

struct Probablity
{
    //alpha 4 
    float winter_probablity, spring_probablity, summer_probablity, fall_probablity;
    //alpha 
    float age_mean, age_standard_deviation;
    //alpha 2
    float disease_probablity, no_disease_probablity;
    //alpha 2
    float trauma_probablity, no_trauma_probablity;
    //alpha 2
    float surgery_probablity, no_surgery_probablity;
    //alpha 3
    float fever_less3m_probablity, fever_more3m_probablity, no_fever_probablity;
    //alpha 5
    float alcohol_several_day_probablity, alcohol_everyday_probablity, alcohol_several_week_probablity, alcohol_once_week_probablity, alcohol_hardly_probablity;
    //alpha 3
    float smoke_never_probablity, smoke_occasional_probablity, smoke_daily_probablity;
    float sitting_mean, sitting_standard_deviation;
};
extern struct Probablity altered;
extern struct Probablity normal;

//assume that collumns are always the same data.

//setup initial probablity for altered and normal | float** is a 2d array
float Init_Probablity(float **semen);

//takes in array | will output probality for input data
//float Probablity(float *semen, int alpha);

//calculate mean for guassisan distribution | takes in which collumn to avg. 
void Mean(int column, float mean[]);

//calculate Std Dev for guassisan distribution | takes in which collumn to avg. 
void Standard_Deviation(int column, float mean[], float sd[]);

//calculate probablity of both age and sitting and return age * probablity
float Gaussian_Probablity(float data[], struct Probablity probablity);

//calculate posterior probability of all the conditions
float Posterior_Probability(int i, struct Probablity probablity);

//make decision based on posterior probability
int NB_Decision(float normal_p, float altered_p);

//use (results*100)/total data to get scoring 
//calculate the score for the naive bayes algo
float Scoring();

//enum class
enum Season{winter, spring, summer, fall};
enum Fever{less_than_three_months_ago = -1, more_than_three_months_ago, No};
enum Alcohol_Consumption{several_times_a_day, every_day, several_times_a_week, once_a_week, hardly_ever_or_never};
enum Smoking_Habit{never = -1, occasional, daily};

//functions prototype for calculating probabiliy
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