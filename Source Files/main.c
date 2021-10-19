#include <stdio.h>
#include <stdlib.h>

#include "..\Header Files\semen.h"
//#include <..\Header Files\semen.h>
#include "..\Header Files\naive_bayes.h"

extern float** semen_array;

int main()
{
    printf("Group 8 Assignment 1\n");
    InitFile();
    PrintData(0);
    Init_Probablity(semen_array);
    return 0;
}