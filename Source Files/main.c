#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "..\Header Files\semen.h"
#include "..\Header Files\naive_bayes.h"

//extern float** semen_array;

int main()
{
    clock_t endT;
    clock_t startT = clock();
    
    printf("P2 Group 8 Assignment 1\n");
    InitFile();
    PrintData(0);
    Init_Probablity(semen_array);

    endT = clock();
    printf("\nElapsed Time: %f seconds\n", (double)(endT - startT) / CLOCKS_PER_SEC);

    return 0;
}