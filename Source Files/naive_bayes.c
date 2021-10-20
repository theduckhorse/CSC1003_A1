// implment your functions here
#include "..\Header Files\naive_bayes.h"
#include "..\Header Files\semen.h"
#include <stdio.h>

//probablity for being altered or normal
float altered_probablity = 0;
float normal_probablity = 0;

//store the caculated probablities into these structs
//struct Probablity altered;
//struct Probablity normal;

//this will take full array size regarless
float Init_Probablity(float** semen)
{
    for (int i = 0; i < s_row; i++)
    {
        if (semen[i][s_col-1] == 1.0f) //assume last rows = results
            altered_probablity++;
        else
            normal_probablity++;
    }
    altered_probablity /= s_row;
    normal_probablity /= s_row;
    
    //right now its only total count
    printf("\nap: %f, np: %f", altered_probablity, normal_probablity);

    printf("\nProb of Winter: %f",  Prob_Season(winter));
}

float Prob_Season(enum Season e)
{
    float probability = 0.f;
    for (int i = 0; i < s_row; i++)
    {
        switch (e)
        {
        case winter:
            if (semen_array[i][0] == -1.0f)
                probability++;
            break;
        case spring:
            if (semen_array[i][0] == -0.33f)
                probability++;
            break;
        case summer:
            if (semen_array[i][0] == 0.33f)
                probability++;
            break;
        case fall:
            if (semen_array[i][0] == 1.0f)
                probability++;
            break;
        default:
            break;
        }
    }
    probability /= s_row;
    return probability;
}