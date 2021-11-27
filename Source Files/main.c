#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "..\Header Files\naive_bayes.h"

// Location of data file
#define FILE_NAME "fertility_Diagnosis_Data_Group5_8.txt"
// Training Set : Testing Set
#define TRAINING_SET 80
#define TESTING_SET 20

float **InitFile(int *s_row);                                                                                    // Reads the text file and stores into a dynamic arr, returns array and size of row
void PrintData(float **s_arr, int line);                                                                         // Prints data based on the row index
void Print_CM_Table(char *title, int *cm_arr);                                                                   // Prints confusion matrix table
void Plot_Graph(int terminal, char *title, char *ylabel, char *xlabel, int size, double **data_arr, int column); // Plots a graph based on data given
void Free_Array_float(float **arr, int row);                                                                     // Frees float 2D array
void Free_Array_double(double **arr, int row);                                                                   // Frees double 2D array   

int main()
{
    struct probability altered; // Altered probabilities struct
    struct probability normal;  // Normal probabilities struct
    float **semen_array;        // Dynamic 2D array of data
    int semen_row = 0;          // Amount of data (rows) in semen array

    clock_t endT;
    clock_t startT = clock(); // Starts timer
    int *training_cm_arr;
    int *testing_cm_arr;
    double **training_res;
    double **testing_res;
    char *title1 = "Training Set";
    char *title2 = "Testing Set";
    char *ylabel = "Error Probability";
    char *xlabel = "Data No.";
    int err_col = 4;

    semen_array = InitFile(&semen_row);                             // Read data from file and store in array
    Init_Probability(semen_array, TRAINING_SET, &altered, &normal); // Init Probabilities base on training size

    // Training Set
    printf("\nConfusion Matrix Table:\n");
    training_res = Make_Prediction(0, TRAINING_SET, TRAINING_SET, semen_array, &altered, &normal); // Init prediction result for training set
    training_cm_arr = Compute_Confusion_Matrix(training_res, TRAINING_SET);                        // Init confusion matrix results
    Plot_Graph(0, title1, ylabel, xlabel, TRAINING_SET, training_res, err_col);                    // Plots error probability graph
    Print_CM_Table(title1, training_cm_arr);                                                       // Prints confusion matrix table & accuracy

    // Free up malloc arrays
    Free_Array_double(training_res, TRAINING_SET);

    // Testing Set
    testing_res = Make_Prediction(TRAINING_SET, semen_row, TESTING_SET, semen_array, &altered, &normal); // Init prediction result for testing set
    testing_cm_arr = Compute_Confusion_Matrix(testing_res, TESTING_SET);                                 // Init confusion matrix results
    Plot_Graph(1, title2, ylabel, xlabel, TESTING_SET, testing_res, err_col);                            // Plots error probability graph
    Print_CM_Table(title2, testing_cm_arr);                                                              // Prints confusion matrix table & accuracy

    // Free up malloc arrays
    Free_Array_double(testing_res, TESTING_SET);
    Free_Array_float(semen_array, semen_row);

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
    printf("\n");
}

// Plots a graph
void Plot_Graph(int terminal, char *title, char *ylabel, char *xlabel, int size, double **data_arr, int column)
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
    fprintf(gnuplot_pipe, "plot '-' with linespoints linestyle 1\n");
    for (size_t i = 0; i < size; ++i)
    {
        fprintf(gnuplot_pipe, "%zu %f\n", i, data_arr[i][column]);
    }
    fprintf(gnuplot_pipe, "e\n");
    // Refresh
    fprintf(gnuplot_pipe, "refresh\n");
}

void Free_Array_float(float **arr, int row)
{
    for (int i=0; i< row; i++) //deallocate sub arrays first
    {
        free(arr[i]); //free up *arr
        arr[i] = NULL; //dereference *array
    }   
    free(arr); //free up arr
    arr = NULL; //dereference array
}

void Free_Array_double(double **arr, int row)
{
    for (int i=0; i< row; i++) //deallocate sub arrays first
    {
        free(arr[i]);   //free up *arr
        arr[i] = NULL;  //dereference *array
    }   
    free(arr);  //free up arr
    arr = NULL; //dereference array
}