/* declare your functions here */
#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

#define ALPHA 20; 

extern float altered_probablity, normal_probablity;
struct Probablity
{
    //alpha 4 
    float winter_probablity, spring_probablity, summer_probablity, fall_probablity;
    float age_mean, age_standard_deviation;
    //alpha 2
    float disease_probablity, no_disease_probablity;
    //alpha 2
    float trauma_probablity, no_trauma_probablity;
    //alpha 2
    float surgery_probablity, no_surgery_probablity;
    //alpha 2
    float fever_probablity, no_fever_probablity;
    //alpha 5
    float alcohol_several_day_probablity, alcohol_everyday_probablity;
    //alpha 5
    float alcohol_several_week_probablity, alcohol_once_week_probablity, alcohol_hardly_probablity;
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
float Probablity(float *semen, int alpha);

//calculate mean for guassisan distribution
float Mean();

//calculate Std Dev for guassisan distribution
float Standard_Deviation();

//calculate probablity from normal 
float Gaussian_Probablity();

//use (results*100)/total data to get scoring 
//calculate the score for the naive bayes algo
float Scoring();

#endif