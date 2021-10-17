#include "..\Header Files\semen.h"

// Reads the .txt file and store in a 2D array
void InitFile()
{
    // Pointer to the file
    FILE *fp;
    // variable to read the content of file
    char c;
    // variables for semen
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
        return;
    }

	// read character by character and check for new line	
	while((c=fgetc(fp))!=EOF)
	{
		if(c=='\n')
			s_row++;
	}
    printf("Number of lines: %d \n", s_row);

    // set dynamic array here
    s_col = 10;
    semen_array = malloc(sizeof(float*) * s_row);
    for(int i=0;i<s_row;i++)
    {
        semen_array[i] = malloc(sizeof(float) * s_col);
    }
    printf("Size of semen_array: %llu\n", sizeof(semen_array) + sizeof(semen_array[0]) * s_row );

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
       semen_array[line][0] = season_of_analysis;
       semen_array[line][1] = age_of_analysis;
       semen_array[line][2] = childish_disease;
       semen_array[line][3] = accident_or_serious_trauma;
       semen_array[line][4] = surgical_intervention;
       semen_array[line][5] = high_fevers_in_last_year;
       semen_array[line][6] = frequency_of_alcohol_consumption;
       semen_array[line][7] = smokin_habit;
       semen_array[line][8] = number_of_hours_spent_sitting_per_day;
       semen_array[line][9] = semen_diagnosis;
       line++;
    }
    fclose(fp);
    printf("File closed\n");
}

// prints data based on the row index
void PrintData(int line)
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
        semen_array[line][0],
        semen_array[line][1],
        (int)semen_array[line][2],
        (int)semen_array[line][3],
        (int)semen_array[line][4],
        (int)semen_array[line][5],
        semen_array[line][6],
        (int)semen_array[line][7],
        semen_array[line][8],
        (int)semen_array[line][9]);
}