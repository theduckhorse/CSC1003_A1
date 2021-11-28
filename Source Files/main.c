#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "..\Header Files\naive_bayes.h"

// Location of data file
#define FILE_NAME "fertility_Diagnosis_Data_Group5_8.txt"

float **InitFile(int *s_row);                                                                                                          // Reads the text file and stores into a dynamic arr, returns array and size of row
void PrintData(float **s_arr, int line);                                                                                               // Prints data based on the row index
void Print_CM_Table(char *title, int *cm_arr);                                                                                         // Prints confusion matrix table
void Plot_Graph(int terminal, char *title, char *dtitle, char *ylabel, char *xlabel, int size, double ydata_arr[], char *xdata_arr[]); // Plots a graph based on data given
void Free_Array_float(float **arr, int row);                                                                                           // Frees float 2D array
void Free_Array_double(double **arr, int row);                                                                                         // Frees double 2D array

int main()
{
    clock_t endT;
    clock_t startT = clock();   // Starts timer
    struct probability altered; // Altered probabilities struct
    struct probability normal;  // Normal probabilities struct
    float **semen_array;        // Dynamic 2D array of data
    int semen_row = 0;          // Amount of data (rows) in semen array
    int *training_cm_arr;
    int *testing_cm_arr;
    double **training_res;
    double **testing_res;
    double training_err_prob_arr[3];
    double testing_err_prob_arr[3];
    char *title1 = "Training Set";
    char *title2 = "Testing Set";
    char *ylabel = "Error Probability";
    char *xlabel = "Training:Testing Set";
    int err_col = 4;
    int num_col = 3;
    int training_set = 80;
    int testing_set = 20;
    char *dtitle = "Error Probability";
    char *xdata_arr[] = {"80:20", "50:50", "90:10"};

    semen_array = InitFile(&semen_row); // Read data from file and store in array

    // Training:Testing Set - 80:20
    // Training Set
    printf("\nTraining:Testing - %d:%d\n", training_set, testing_set);
    printf("Confusion Matrix Table:\n");
    Init_Probability(semen_array, training_set, &altered, &normal);                                // Init Probabilities base on training size
    training_res = Make_Prediction(0, training_set, training_set, semen_array, &altered, &normal); // Init prediction result for training set
    training_cm_arr = Compute_Confusion_Matrix(training_res, training_set);                        // Init confusion matrix results
    Print_CM_Table(title1, training_cm_arr);                                                       // Prints confusion matrix table & accuracy
    training_err_prob_arr[0] = training_res[training_set - 1][err_col];                            // Adds training error probability to array
    printf("Training Error Probability: %f\n", training_err_prob_arr[0]);

    // Testing Set
    testing_res = Make_Prediction(training_set, semen_row, testing_set, semen_array, &altered, &normal); // Init prediction result for testing set
    testing_cm_arr = Compute_Confusion_Matrix(testing_res, testing_set);                                 // Init confusion matrix results
    Print_CM_Table(title2, testing_cm_arr);                                                              // Prints confusion matrix table & accuracy
    testing_err_prob_arr[0] = testing_res[testing_set - 1][err_col];                                     // Adds testing error probability to array
    printf("Testing Error Probability: %f\n", testing_err_prob_arr[0]);

    // Training:Testing Set - 50:50
    training_set = 50;
    testing_set = 50;
    // Training Set
    printf("\nTraining:Testing - %d:%d\n", training_set, testing_set);
    printf("Confusion Matrix Table:\n");
    Init_Probability(semen_array, training_set, &altered, &normal);                                // Init Probabilities base on training size
    training_res = Make_Prediction(0, training_set, training_set, semen_array, &altered, &normal); // Init prediction result for training set
    training_cm_arr = Compute_Confusion_Matrix(training_res, training_set);                        // Init confusion matrix results
    Print_CM_Table(title1, training_cm_arr);                                                       // Prints confusion matrix table & accuracy
    training_err_prob_arr[1] = training_res[training_set - 1][err_col];                            // Adds training error probability to array
    printf("Training Error Probability: %f\n", training_err_prob_arr[1]);

    // Testing Set
    testing_res = Make_Prediction(training_set, semen_row, testing_set, semen_array, &altered, &normal); // Init prediction result for testing set
    testing_cm_arr = Compute_Confusion_Matrix(testing_res, testing_set);                                 // Init confusion matrix results
    Print_CM_Table(title2, testing_cm_arr);                                                              // Prints confusion matrix table & accuracy
    testing_err_prob_arr[1] = testing_res[testing_set - 1][err_col];                                     // Adds testing error probability to array
    printf("Testing Error Probability: %f\n", testing_err_prob_arr[1]);

    // Training:Testing Set - 90:10
    training_set = 90;
    testing_set = 10;
    // Training Set
    printf("\nTraining:Testing - %d:%d\n", training_set, testing_set);
    printf("Confusion Matrix Table:\n");
    Init_Probability(semen_array, training_set, &altered, &normal);                                // Init Probabilities base on training size
    training_res = Make_Prediction(0, training_set, training_set, semen_array, &altered, &normal); // Init prediction result for training set
    training_cm_arr = Compute_Confusion_Matrix(training_res, training_set);                        // Init confusion matrix results
    Print_CM_Table(title1, training_cm_arr);                                                       // Prints confusion matrix table & accuracy
    training_err_prob_arr[2] = training_res[training_set - 1][err_col];                            // Adds training error probability to array
    printf("Training Error Probability: %f\n", training_err_prob_arr[2]);

    // Testing Set
    testing_res = Make_Prediction(training_set, semen_row, testing_set, semen_array, &altered, &normal); // Init prediction result for testing set
    testing_cm_arr = Compute_Confusion_Matrix(testing_res, testing_set);                                 // Init confusion matrix results
    Print_CM_Table(title2, testing_cm_arr);                                                              // Prints confusion matrix table & accuracy
    testing_err_prob_arr[2] = testing_res[testing_set - 1][err_col];                                     // Adds testing error probability to array
    printf("Testing Error Probability: %f\n", testing_err_prob_arr[2]);

    // Free up malloc arrays
    Free_Array_double(training_res, training_set);
    Free_Array_double(testing_res, testing_set);
    Free_Array_float(semen_array, semen_row);

    // Plots Graph
    Plot_Graph(0, title1, dtitle, ylabel, xlabel, num_col, training_err_prob_arr, xdata_arr); // Plots Training error probability graph
    Plot_Graph(1, title2, dtitle, ylabel, xlabel, num_col, testing_err_prob_arr, xdata_arr);  // Plots Testing error probability graph

    endT = clock(); // Stops timer
    printf("\nElapsed Time: %f seconds\n", (double)(endT - startT) / CLOCKS_PER_SEC);

    return 0;
}

// Reads the .txt file and store in a 2D array
float **InitFile(int *s_row)
{
    // 2D dynamic array
    float **s_arr;
    // Pointer to the file
    FILE *fp;
    // Variable to read the content of file
    char c;
    // Variables for semen
    float season_of_analysis;
    float age_of_analysis;
    int childish_disease;
    int accident_or_serious_trauma;
    int surgical_intervention;
    int high_fevers_in_last_year;
    float frequency_of_alcohol_consumption;
    int smokin_habit;
    float number_of_hours_spent_sitting_per_day;
    int semen_diagnosis;

    // Opening a file in r mode
    fp = fopen(FILE_NAME, "r");

    // Check if file exist
    if (fp == NULL)
    {
        printf("Error in opening file \n");
        return NULL;
    }

    printf("Number of lines: %d \n", *s_row);
    // read character by character and check for new line
    while ((c = fgetc(fp)) != EOF)
    {
        if (c == '\n')
            (*s_row)++; // The value pointed at by rows is incremented
    }
    printf("Number of lines: %d \n", *s_row);

    // set dynamic array here
    s_arr = malloc(sizeof(float *) * (*s_row));
    for (int i = 0; i < (*s_row); i++)
    {
        s_arr[i] = malloc(sizeof(float) * s_col);
    }
    printf("Size of semen_array: %llu bytes\n", sizeof(s_arr) + sizeof(s_arr[0]) * (*s_row) + sizeof(float) * (*s_row) * s_col);

    // go back to start of file
    rewind(fp);

    // partition the text file and store the data into dynamic array
    int line = 0;
    while (fscanf(fp, " %f , %f , %d , %d , %d , %d , %f , %d , %f , %d",
                  &season_of_analysis,
                  &age_of_analysis,
                  &childish_disease,
                  &accident_or_serious_trauma,
                  &surgical_intervention,
                  &high_fevers_in_last_year,
                  &frequency_of_alcohol_consumption,
                  &smokin_habit,
                  &number_of_hours_spent_sitting_per_day,
                  &semen_diagnosis) != EOF)
    {
        s_arr[line][0] = season_of_analysis;
        s_arr[line][1] = age_of_analysis;
        s_arr[line][2] = childish_disease;
        s_arr[line][3] = accident_or_serious_trauma;
        s_arr[line][4] = surgical_intervention;
        s_arr[line][5] = high_fevers_in_last_year;
        s_arr[line][6] = frequency_of_alcohol_consumption;
        s_arr[line][7] = smokin_habit;
        s_arr[line][8] = number_of_hours_spent_sitting_per_day;
        s_arr[line][9] = semen_diagnosis;
        line++;
    }
    fclose(fp);
    printf("File closed\n");

    //returns the 2d array
    return s_arr;
}

// prints data based on the row index
void PrintData(float **s_arr, int line)
{
    printf("Semen Data %d \n"
           "Season of analysis: %f \n"
           "Age of analysis: %f \n"
           "Childish disease: %d \n"
           "Accident or serious trauma: %d \n"
           "surgical intervention: %d \n"
           "high fevers in last year: %d \n"
           "frequency of alcohol consumption: %f \n"
           "smokin habit: %d \n"
           "number of hours spent sitting per day: %f \n"
           "semen diagnosis: %d \n",
           line,
           s_arr[line][0],
           s_arr[line][1],
           (int)s_arr[line][2],
           (int)s_arr[line][3],
           (int)s_arr[line][4],
           (int)s_arr[line][5],
           s_arr[line][6],
           (int)s_arr[line][7],
           s_arr[line][8],
           (int)s_arr[line][9]);
}

// Prints the confusion matrix table and Accuracy
void Print_CM_Table(char *title, int *cm_arr)
{
    int tp_count = cm_arr[0];
    int tn_count = cm_arr[1];
    int fp_count = cm_arr[2];
    int fn_count = cm_arr[3];
    int total = tp_count + tn_count + fp_count + fn_count;
    double score = Scoring(tn_count, tp_count, total);
    printf("\n%-20s%s\n", "", title);
    printf("%-20s%-20s%-20s\n", "", "Predicted: Normal", "Predicted: Altered");
    printf("%-25s%-25d%-10d\n", "Actual: Normal", tn_count, fp_count);
    printf("%-25s%-25d%-10d\n", "Actual: Altered", fn_count, tp_count);
    printf("Accuracy: %1.2lf%%\n", score);
}

// Plots a graph
void Plot_Graph(int terminal, char *title, char *dtitle, char *ylabel, char *xlabel, int size, double ydata_arr[], char *xdata_arr[])
{
    // Open persistent gnuplot window
    FILE *gnuplot_pipe = popen("gnuplot -persistent", "w");
    // Basic settings
    fprintf(gnuplot_pipe, "set terminal qt %d\n", terminal);
    fprintf(gnuplot_pipe, "set title '%s'\n", title);
    fprintf(gnuplot_pipe, "set ylabel '%s' textcolor rgb '#0060ad'\n", ylabel);
    fprintf(gnuplot_pipe, "set xlabel '%s' textcolor rgb '#FF7000'\n", xlabel);
    fprintf(gnuplot_pipe, "set grid\n");
    fprintf(gnuplot_pipe, "set style line 1 linecolor rgb '#0060ad' ");
    fprintf(gnuplot_pipe, "linetype 1 linewidth 1 pointtype 7 pointsize 1\n");
    // Fill it with data
    fprintf(gnuplot_pipe, "plot '-' using 2:xtic(1) title '%s' with linespoints linestyle 1\n", dtitle);
    for (size_t i = 0; i < size; ++i)
    {
        fprintf(gnuplot_pipe, "%s %f\n", xdata_arr[i], ydata_arr[i]);
    }
    fprintf(gnuplot_pipe, "e\n");
    // Refresh
    fprintf(gnuplot_pipe, "refresh\n");
}

void Free_Array_float(float **arr, int row)
{
    for (int i = 0; i < row; i++) //deallocate sub arrays first
    {
        free(arr[i]);  //free up *arr
        arr[i] = NULL; //dereference *array
    }
    free(arr);  //free up arr
    arr = NULL; //dereference array
}

void Free_Array_double(double **arr, int row)
{
    for (int i = 0; i < row; i++) //deallocate sub arrays first
    {
        free(arr[i]);  //free up *arr
        arr[i] = NULL; //dereference *array
    }
    free(arr);  //free up arr
    arr = NULL; //dereference array
}