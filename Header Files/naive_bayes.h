/* declare your functions here */
#ifndef NAIVE_BAYES_H
#define NAIVE_BAYES_H

float altered_probablity; 
float normal_probablity;

enum Season{winter, spring, summer, fall};
enum Fever{less_than_three_months_ago = -1, more_than_three_months_ago, No};
enum Alcohol_Consumption{several_times_a_day, every_day, several_times_a_week, once_a_week, hardly_ever_or_never};
enum Smoking_Habit{never = -1, occasional, daily};


float Init_Probablity(float** semen);
float Final_Probablity();

float Prob_Season(enum Season e);
float Prob_Age(float age);
float Prob_Childish_Disease(int choice);
float Prob_Accident(int choice);
float Prob_Fever(enum Fever e);
float Prob_Alcohol_Consumption(enum Alcohol_Consumption e);
float Prob_Smoking(enum Smoking_Habit e);
float Prob_Sitting(float duration);

#endif