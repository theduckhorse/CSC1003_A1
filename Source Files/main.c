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
    int *training_cm_arr;
    int *testing_cm_arr;
    double **training_res;
    double **testing_res;
    char *title1 = "Training Set";
    char *title2 = "Testing Set";
    char *ylabel = "Error Probability";
    char *xlabel = "Data No.";
    int err_col = 4;

    InitFile();
    Init_Probability(semen_array);

    // Training Set
    training_res = Make_Prediction(0, training_set, training_set);              // Init prediction result for training set (80)
    training_cm_arr = Compute_Confusion_Matrix(training_res, training_set);     // Init confusion matrix results
    Plot_Graph(0, title1, ylabel, xlabel, training_set, training_res, err_col); // Plots error probability graph
    Print_CM_Table(title1, training_cm_arr);                                    // Prints confusion matrix table

    // free up malloc arrays
    free(*training_res);
    free(training_res);

    // Testing Set
    testing_res = Make_Prediction(training_set, data_size, testing_set); // Init prediction result for testing set (20)
    testing_cm_arr = Compute_Confusion_Matrix(testing_res, testing_set);
    Plot_Graph(1, title2, ylabel, xlabel, testing_set, testing_res, err_col);
    Print_CM_Table(title2, testing_cm_arr);

    // free up malloc arrays
    free(*testing_res);
    free(testing_res);

    endT = clock();
    printf("\nElapsed Time: %f seconds\n", (double)(endT - startT) / CLOCKS_PER_SEC);

    return 0;
}
