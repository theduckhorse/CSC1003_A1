#include "..\Header Files\semen.h"

// Reads the .txt file and store in a 2D array
void ReadFile()
{
    // Pointer to the file
    FILE *fp;
    // variable to read the content of file
    char c;

    // Opening a file in r mode
    fp= fopen (FILE_NAME, "r");

    // Check if file opened
    if(fp!=NULL)
    {
        printf("File opened successfully\n");
    }
    else
    {
        printf("Error in opening file\n");
        return;
    }

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
        semen_data[line][0] = season_of_analysis;
        semen_data[line][1] = age_of_analysis;
        semen_data[line][2] = childish_disease;
        semen_data[line][3] = accident_or_serious_trauma;
        semen_data[line][4] = surgical_intervention;
        semen_data[line][5] = high_fevers_in_last_year;
        semen_data[line][6] = frequency_of_alcohol_consumption;
        semen_data[line][7] = smokin_habit;
        semen_data[line][8] = number_of_hours_spent_sitting_per_day;
        semen_data[line][9] = semen_diagnosis;
        line++;
     }

     printf("File closed\n");
     fclose(fp);
}

void PrintData(int line)
{
    printf("Semen Data %d \n", line);
    printf("Season of analysis: %f \n", semen_data[line][0]);
    printf("Age of analysis: %f \n", semen_data[line][1]);
    printf("Childish disease: %d \n", (int)semen_data[line][2]);
    printf("Accident or serious trauma: %d \n", (int)semen_data[line][3]);
    printf("surgical intervention: %d \n", (int)semen_data[line][4]);
    printf("high fevers in last year: %d \n", (int)semen_data[line][5]);
    printf("frequency of alcohol consumption: %f \n", semen_data[line][6]);
    printf("smokin habit: %d \n", (int)semen_data[line][7]);
    printf("number of hours spent sitting per day: %f \n", semen_data[line][8]);
    printf("semen diagnosis: %d \n", (int)semen_data[line][9]);
}