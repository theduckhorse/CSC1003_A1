#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "..\Header Files\naive_bayes.h"

// Location of data file
#define FILE_NAME "fertility_Diagnosis_Data_Group5_8.txt"
// Training Set : Testing Set
#define training_set 80
#define testing_set 20

float** InitFile(int *s_row); // Reads the text file and stores into a dynamic arr, returns array and size of row
void PrintData(float **s_arr, int line); // Prints data based on the row index

int main()
{
    float** semen_array; // Dynamic 2D array
    int semen_row = 0; // Amount of data (rows) in semen array

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

    semen_array = InitFile(&semen_row);
    Init_Probability(semen_array, training_set);

    // Training Set
    printf("\nConfusion Matrix Table:\n");
    training_res = Make_Prediction(0, training_set, training_set, semen_array); // Init prediction result for training set (80)
    training_cm_arr = Compute_Confusion_Matrix(training_res, training_set);     // Init confusion matrix results
    Plot_Graph(0, title1, ylabel, xlabel, training_set, training_res, err_col); // Plots error probability graph
    Print_CM_Table(title1, training_cm_arr);                                    // Prints confusion matrix table

    // Free up malloc arrays
    free(*training_res);
    free(training_res);

    // Testing Set
    testing_res = Make_Prediction(training_set, semen_row, testing_set, semen_array); // Init prediction result for testing set (20)
    testing_cm_arr = Compute_Confusion_Matrix(testing_res, testing_set);
    Plot_Graph(1, title2, ylabel, xlabel, testing_set, testing_res, err_col);
    Print_CM_Table(title2, testing_cm_arr);

    // Free up malloc arrays
    free(*testing_res);
    free(testing_res);

    endT = clock();
    printf("\nElapsed Time: %f seconds\n", (double)(endT - startT) / CLOCKS_PER_SEC);

    return 0;
}

// Reads the .txt file and store in a 2D array
float** InitFile(int *s_row)
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
    fp = fopen (FILE_NAME, "r");

    // Check if file exist
    if(fp == NULL)
    {
        printf("Error in opening file \n");
        return NULL;
    }

    printf("Number of lines: %d \n", *s_row);
	// read character by character and check for new line	
	while((c=fgetc(fp))!=EOF)
	{
		if(c=='\n') 
			(*s_row)++; // The value pointed at by rows is incremented
	}
    printf("Number of lines: %d \n", *s_row);

    // set dynamic array here
    s_arr = malloc(sizeof(float*) * (*s_row));
    for(int i=0;i<(*s_row);i++)
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
