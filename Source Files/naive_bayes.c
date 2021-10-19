// implment your functions here
#include "..\Header Files\naive_bayes.h"
#include "..\Header Files\semen.h"
#include <stdio.h>

//probablity for being altered or normal
float altered_probablity = 0;
float normal_probablity = 0;

//store the caculated probablities into these structs
struct Probablity altered;
struct Probablity normal;

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
    printf("\nap%f, np%f", altered_probablity, normal_probablity);
}
