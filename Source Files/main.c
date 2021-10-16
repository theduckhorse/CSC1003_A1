#include <stdio.h>
#include <stdlib.h>

#include "..\Header Files\semen.h"
#include "..\Header Files\naive_bayes.h"

//location of data file
const char* kFileName = "fertility_Diagnosis_Data_Group5_8.txt";

//define functions
void ReadFile();

int main()
{
    printf("Group 8 Assignment 1\n");
    ReadFile();
    return 0;
}

void ReadFile()
{
    // Pointer to the file
    FILE *fp;
    // variable to read the content of file
    char c;

    // Opening a file in r mode
    fp= fopen (kFileName, "r");

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

     // loop to print all the lines in text file
     while(1)
     {
        c = fgetc(fp);
        // breaks the loop at the end
        if(c==EOF)
            break;
        else
            printf("%c", c);
     }

     printf("File closed\n");
     fclose(fp);
}