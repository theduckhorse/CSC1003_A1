#include <stdio.h>
#include <stdlib.h>

const char* FILENAME = "fertility_Diagnosis_Data_Group5_8.txt";

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
    // Character variable to read the content of file
    char c;

    // Opening a file in r mode
    fp= fopen (FILENAME, "r");

    // Check if file opened
    if(fp!=NULL)
    {
        printf("File opened successfully\n");
        //break out from fuction?
    }
    else
    {
        printf("Error in opening file\n");
    }

     // Infinite loop –I have used break to come out of the loop
     while(1)
     {
        c = fgetc(fp);
        if(c==EOF)
            break;
        else
            printf("%c", c);
     }
     printf("File closed\n");
     fclose(fp);
}