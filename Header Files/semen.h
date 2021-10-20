#ifndef SEMEN_H
#define SEMEN_H
#include <stdio.h>
#include <stdlib.h>

//location of data file
#define FILE_NAME "fertility_Diagnosis_Data_Group5_8.txt"

//dynamic array for semen data
extern float** semen_array;
extern int s_row, s_col;

//define functions
void InitFile();
void PrintData(int line);
void FreeArray();

/*struct Semen
{
    float season_of_analysis;
    float age_of_analysis;
    int childish_disease;
    int accident_or_serious_trauma;
    int surgical_intervention;
    int high_fevers_in_last_year;
    float frequency_of_alcohol_consumption;
    int smokin_habit;
    float number_of_hours_spent_sitting_per_day;
};*/

#endif