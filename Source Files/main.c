#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "..\Header Files\semen.h"
#include "..\Header Files\naive_bayes.h"

// Total data size; 100
#define data_size 100
// 80:20 (Training Set : Testing Set)
#define training_set 80
#define testing_set 20

int main()
{
    clock_t endT;
    clock_t startT = clock();
    double **training_res;
    double **testing_res;
    char *name1 = "Training Set Probability of Error Graph";
    char *name2 = "Testing Set Probability of Error Graph";

    InitFile();
    Init_Probability(semen_array);

    training_res = Make_Predict(0, training_set, training_set);     // Init prediction for training set (80)
    Plot_Graph(0, name1, training_set, training_res); // Plot error probability graph for training set
    free(*training_res);
    free(training_res);

    testing_res = Make_Predict(training_set, data_size, testing_set); // Init prediction for testing set (20)
    Plot_Graph(1, name2, testing_set, testing_res);      // Plot error probability graph for testing set
    free(*testing_res);
    free(testing_res);

    endT = clock();
    printf("\nElapsed Time: %f seconds\n", (double)(endT - startT) / CLOCKS_PER_SEC);

    return 0;
}
