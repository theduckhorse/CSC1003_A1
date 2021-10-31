#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "..\Header Files\semen.h"
#include "..\Header Files\naive_bayes.h"

//extern float** semen_array;

void Plot_Graph();

int main()
{
    clock_t endT;
    clock_t startT = clock();
    
    InitFile();
    Init_Probablity(semen_array);
    // Plot_Graph();
    
    endT = clock();
    printf("\nElapsed Time: %f seconds\n", (double)(endT - startT) / CLOCKS_PER_SEC);

    return 0;
}

void Plot_Graph()
{
    float x,y;
    //output file
    FILE *fp = NULL;
    //stream for gnupipe
    FILE *gnupipe = NULL;
    char *GnuCommands [] = {"set title \"UOG SPERM BANK\"", "plot 'data.tmp'"};
    size_t gnuCommands_size = sizeof GnuCommands / sizeof *GnuCommands;

    //'w' if the file does not exist, it will create a new file
    fp = fopen("data.tmp", "w");
    gnupipe = _popen("gnuplot -persistent", "w");

    //plots a nice curve
    for (x=-3.14159; x<=3.13159; x+=0.1)
    {
        y = sin(x);
        //writes the coordinate to the output file
        fprintf(fp, "%f %f\n", x,y);
    }

    for (int i = 0; i < gnuCommands_size; i++){
        fprintf(gnupipe, "%s\n", GnuCommands[i]);
    }
}