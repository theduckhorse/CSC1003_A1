// implment your functions here
#include "..\Header Files\naive_bayes.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// init probabilities
void Init_Probability(float **semen, int s_row, struct probability *altered, struct probability *normal)
{
    Prior_Probability(semen, s_row, altered, normal);          // Init prior probability
    Prob_Season(semen, s_row, altered, normal);                // Init probability for Seasons
    Prob_Childish_Disease(semen, s_row, altered, normal);      // Init probability for Childish Disease
    Prob_Accident(semen, s_row, altered, normal);              // Init probability for Accident / Serious Trauma
    Prob_Surgical_Intervention(semen, s_row, altered, normal); // Init probability for Surgical Intervention
    Prob_Fever(semen, s_row, altered, normal);                 // Init probability for Fever
    Prob_Alcohol_Consumption(semen, s_row, altered, normal);   // Init probability for Alcohol Consumption
    Prob_Smoking(semen, s_row, altered, normal);               // Init probability for Smoking Habits
    Prob_Age(semen, s_row, altered, normal);                   // Init probability for Age
    Prob_Sitting(semen, s_row, altered, normal);               // Init probability for Sitting hours
}

// calculates prior probability
void Prior_Probability(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    // probability for being altered or normal
    float altered_probability = 0;
    float normal_probability = 0;

    for (int i = 0; i < s_row; i++)
    {
        if (s_arr[i][s_col - 1] == 1.0f) //assume last rows = results
            altered_probability++;
        else
            normal_probability++;
    }
    altered_probability /= s_row;
    normal_probability /= s_row;

    // Store prior probability into struct
    altered->prior_probability = altered_probability;
    normal->prior_probability = normal_probability;
}

// calculates season probability
void Prob_Season(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = SEASON_ALPHA;
    float aprobability[4] = {0};
    float nprobability[4] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][0] == -1.0f)
                nprobability[0]++;

            else if (s_arr[i][0] == -0.33f)
                nprobability[1]++;

            else if (s_arr[i][0] == 0.33f)
                nprobability[2]++;

            else if (s_arr[i][0] == 1.0f)
                nprobability[3]++;
            else
                printf("\nError in line %d for Seasons value = \"%.2f\" skipping entry, only input (-1, -0.33, 0.33, 1)", (i + 1), s_arr[i][0]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][0] == -1.0f)
                aprobability[0]++;

            else if (s_arr[i][0] == -0.33f)
                aprobability[1]++;

            else if (s_arr[i][0] == 0.33f)
                aprobability[2]++;

            else if (s_arr[i][0] == 1.0f)
                aprobability[3]++;
            else
                printf("\nError in line %d for Seasons value = \"%.2f\" skipping entry, only input (-1, -0.33, 0.33, 1)", (i + 1), s_arr[i][0]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->winter_probability = aprobability[0];
    altered->spring_probability = aprobability[1];
    altered->summer_probability = aprobability[2];
    altered->fall_probability = aprobability[3];
    normal->winter_probability = nprobability[0];
    normal->spring_probability = nprobability[1];
    normal->summer_probability = nprobability[2];
    normal->fall_probability = nprobability[3];
}

// calculates childish disease probability
void Prob_Childish_Disease(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][2] == 1)
                nprobability[0]++;

            else if (s_arr[i][2] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Childish Disease value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][2]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][2] == 1)
                aprobability[0]++;

            else if (s_arr[i][2] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Childish Disease value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][2]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->no_disease_probability = aprobability[0];
    altered->disease_probability = aprobability[1];
    normal->no_disease_probability = nprobability[0];
    normal->disease_probability = nprobability[1];
}

// calculates accident probability
void Prob_Accident(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][3] == 1)
                nprobability[0]++;

            else if (s_arr[i][3] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Accident/Trauma value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][3]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][3] == 1)
                aprobability[0]++;

            else if (s_arr[i][3] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Accident/Trauma value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][3]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->no_trauma_probability = aprobability[0];
    altered->trauma_probability = aprobability[1];
    normal->no_trauma_probability = nprobability[0];
    normal->trauma_probability = nprobability[1];
}

// calculates surgical intervention probability
void Prob_Surgical_Intervention(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][4] == 1)
                nprobability[0]++;

            else if (s_arr[i][4] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Surgical Intervention value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][4]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][4] == 1)
                aprobability[0]++;

            else if (s_arr[i][4] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Surgical Intervention value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][4]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->no_surgery_probability = aprobability[0];
    altered->surgery_probability = aprobability[1];
    normal->no_surgery_probability = nprobability[0];
    normal->surgery_probability = nprobability[1];
}

// calculates fever probability
void Prob_Fever(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = F_S_ALPHA;
    float aprobability[3] = {0};
    float nprobability[3] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][5] == -1)
                nprobability[0]++;

            else if (s_arr[i][5] == 0)
                nprobability[1]++;

            else if (s_arr[i][5] == 1)
                nprobability[2]++;

            else
                printf("\nError in line %d for High fevers in last year value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][5]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][5] == -1)
                aprobability[0]++;

            else if (s_arr[i][5] == 0)
                aprobability[1]++;

            else if (s_arr[i][5] == 1)
                aprobability[2]++;

            else
                printf("\nError in line %d for High fevers in last year value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), s_arr[i][5]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->fever_less3m_probability = aprobability[0];
    altered->fever_more3m_probability = aprobability[1];
    altered->no_fever_probability = aprobability[2];
    normal->fever_less3m_probability = nprobability[0];
    normal->fever_more3m_probability = nprobability[1];
    normal->no_fever_probability = nprobability[2];
}

// calculates alcohol probability
void Prob_Alcohol_Consumption(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = ALCOHOL_ALPHA;
    float aprobability[5] = {0};
    float nprobability[5] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][6] == 0.2f)
                nprobability[0]++;

            else if (s_arr[i][6] == 0.4f)
                nprobability[1]++;

            else if (s_arr[i][6] == 0.6f)
                nprobability[2]++;

            else if (s_arr[i][6] == 0.8f)
                nprobability[3]++;

            else if (s_arr[i][6] == 1.f)
                nprobability[4]++;

            else
                printf("\nError in line %d for Frequency of alcohol consumption value = \"%.2f\" skipping entry, only input (0.2, 0.4, 0.6, 0.8, 1)", (i + 1), s_arr[i][6]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][6] == 0.2f)
                aprobability[0]++;

            else if (s_arr[i][6] == 0.4f)
                aprobability[1]++;

            else if (s_arr[i][6] == 0.6f)
                aprobability[2]++;

            else if (s_arr[i][6] == 0.8f)
                aprobability[3]++;

            else if (s_arr[i][6] == 1.f)
                aprobability[4]++;

            else
                printf("\nError in line %d for Frequency of alcohol consumption value = \"%.2f\" skipping entry, only input (0.2, 0.4, 0.6, 0.8, 1)", (i + 1), s_arr[i][6]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->alcohol_several_day_probability = aprobability[0];
    altered->alcohol_everyday_probability = aprobability[1];
    altered->alcohol_several_week_probability = aprobability[2];
    altered->alcohol_once_week_probability = aprobability[3];
    altered->alcohol_hardly_probability = aprobability[4];
    normal->alcohol_several_day_probability = nprobability[0];
    normal->alcohol_everyday_probability = nprobability[1];
    normal->alcohol_several_week_probability = nprobability[2];
    normal->alcohol_once_week_probability = nprobability[3];
    normal->alcohol_hardly_probability = nprobability[4];
}

// calculates smoking probability
void Prob_Smoking(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    int alpha = F_S_ALPHA;
    float aprobability[3] = {0};
    float nprobability[3] = {0};
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            if (s_arr[i][7] == -1)
                nprobability[0]++;

            else if (s_arr[i][7] == 0)
                nprobability[1]++;

            else if (s_arr[i][7] == 1)
                nprobability[2]++;

            else
                printf("\nError in line %d for Smoking Habit value = \"%.2f\" skipping entry, only input (-1, 0, 1)", (i + 1), s_arr[i][7]);
            normalcount++;
            break;

        case 1: // Altered
            if (s_arr[i][7] == -1)
                aprobability[0]++;

            else if (s_arr[i][7] == 0)
                aprobability[1]++;

            else if (s_arr[i][7] == 1)
                aprobability[2]++;

            else
                printf("\nError in line %d for Smoking Habit value = \"%.2f\" skipping entry, only input (-1, 0, 1)", (i + 1), s_arr[i][7]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (s_row - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered->smoke_never_probability = aprobability[0];
    altered->smoke_occasional_probability = aprobability[1];
    altered->smoke_daily_probability = aprobability[2];
    normal->smoke_never_probability = nprobability[0];
    normal->smoke_occasional_probability = nprobability[1];
    normal->smoke_daily_probability = nprobability[2];
}

// calculates age probability
void Prob_Age(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    float mean[2] = {0, 0}, sd[2] = {0, 0};
    Mean(1, mean, s_arr, s_row);
    normal->age_mean = mean[0];
    altered->age_mean = mean[1];
    Standard_Deviation(1, mean, sd, s_arr, s_row);
    normal->age_standard_deviation = sd[0];
    altered->age_standard_deviation = sd[1];
}

// calculates sitting probability
void Prob_Sitting(float **s_arr, int s_row, struct probability *altered, struct probability *normal)
{
    float mean[2] = {0, 0}, sd[2] = {0, 0};
    Mean(8, mean, s_arr, s_row);
    normal->sitting_mean = mean[0];
    altered->sitting_mean = mean[1];
    Standard_Deviation(8, mean, sd, s_arr, s_row);
    normal->sitting_standard_deviation = sd[0];
    altered->sitting_standard_deviation = sd[1];
}

// calculates mean
void Mean(int column, float mean[], float **s_arr, int s_row)
{
    int normalcount = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            mean[0] += s_arr[i][column];
            normalcount++;
            break;

        case 1: // Altered
            mean[1] += s_arr[i][column];
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //returns average of the column
    mean[0] /= normalcount;
    mean[1] /= (s_row - normalcount);
}

// calculates std dev
void Standard_Deviation(int column, float mean[], float sd[], float **s_arr, int s_row)
{
    int normalcount = 0;
    //used for temporary storage of data-mean to not alter data in s_arr
    float temp = 0;
    for (int i = 0; i < s_row; i++)
    {
        switch ((int)s_arr[i][s_col - 1])
        {
        case 0: // Normal
            temp = s_arr[i][column] - mean[0];
            sd[0] += pow(temp, 2);
            normalcount++;
            break;

        case 1: // Altered
            temp = s_arr[i][column] - mean[1];
            sd[1] += pow(temp, 2);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry", (i + 1), (int)s_arr[i][s_col - 1]);
            break;
        }
    }
    //returns standard deviation value
    sd[0] = sqrt(sd[0] / (normalcount - 1));
    sd[1] = sqrt(sd[1] / (s_row - normalcount - 1));
}

//returns average of the column
float Gaussian_Probability(float data[], float age_mean, float age_standard_deviation, float sitting_mean, float sitting_standard_deviation)
{
    float age, sitting;
    age = (1 / sqrt(2 * M_PI)) * exp(-0.5 * pow((data[1] - age_mean) / age_standard_deviation, 2));
    sitting = (1 / sqrt(2 * M_PI)) * exp(-0.5 * pow((data[8] - sitting_mean) / sitting_standard_deviation, 2));
    return age * sitting;
}

//returns posterior probability for altered and normal
double Posterior_Probability(int i, struct probability *probability, float **s_arr)
{
    double pp = 0;
    float age_mean = probability->age_mean;
    float age_standard_deviation = probability->age_standard_deviation;
    float sitting_mean = probability->sitting_mean;
    float sitting_standard_deviation = probability->sitting_standard_deviation;

    // Age and Sitting hours probability
    double gp = Gaussian_Probability(s_arr[i], age_mean, age_standard_deviation, sitting_mean, sitting_standard_deviation);

    // Prior probability
    pp = gp * probability->prior_probability;

    // Seasons probability
    if (s_arr[i][0] == -1.f)
    {
        pp *= probability->winter_probability;
    }
    else if (s_arr[i][0] == -0.33f)
    {
        pp *= probability->spring_probability;
    }
    else if (s_arr[i][0] == 0.33f)
    {
        pp *= probability->summer_probability;
    }
    else if (s_arr[i][0] == 1.f)
    {
        pp *= probability->fall_probability;
    }
    else
    {
        pp *= 1;
    }

    // Childish Disease probability
    if (s_arr[i][2] == 0)
    {
        pp *= probability->disease_probability;
    }
    else if (s_arr[i][2] == 1)
    {
        pp *= probability->no_disease_probability;
    }
    else
    {
        pp *= 1;
    }

    // Accident / Serious Trauma probability
    if (s_arr[i][3] == 0)
    {
        pp *= probability->trauma_probability;
    }
    else if (s_arr[i][3] == 1)
    {
        pp *= probability->no_trauma_probability;
    }
    else
    {
        pp *= 1;
    }

    // Surgical Intervention probability
    if (s_arr[i][4] == 0)
    {
        pp *= probability->surgery_probability;
    }
    else if (s_arr[i][4] == 1)
    {
        pp *= probability->no_surgery_probability;
    }
    else
    {
        pp *= 1;
    }

    // Fever probability
    if (s_arr[i][5] == -1)
    {
        pp *= probability->fever_less3m_probability;
    }
    else if (s_arr[i][5] == 0)
    {
        pp *= probability->fever_more3m_probability;
    }
    else if (s_arr[i][5] == 1)
    {
        pp *= probability->no_fever_probability;
    }
    else
    {
        pp *= 1;
    }

    // Alcohol Consumption probability
    if (s_arr[i][6] == 0.2f)
    {
        pp *= probability->alcohol_several_day_probability;
    }
    else if (s_arr[i][6] == 0.4f)
    {
        pp *= probability->alcohol_everyday_probability;
    }
    else if (s_arr[i][6] == 0.6f)
    {
        pp *= probability->alcohol_several_week_probability;
    }
    else if (s_arr[i][6] == 0.8f)
    {
        pp *= probability->alcohol_once_week_probability;
    }
    else if (s_arr[i][6] == 1.f)
    {
        pp *= probability->alcohol_hardly_probability;
    }
    else
    {
        pp *= 1;
    }

    // Smoking Habits probability
    if (s_arr[i][7] == -1)
    {
        pp *= probability->smoke_never_probability;
    }
    else if (s_arr[i][7] == 0)
    {
        pp *= probability->smoke_occasional_probability;
    }
    else if (s_arr[i][7] == 1)
    {
        pp *= probability->smoke_daily_probability;
    }
    else
    {
        pp *= 1;
    }

    return pp;
}

//returns nb prediction based on Posterior Probability
int NB_Prediction(double pp_normal, double pp_altered)
{
    int res = 1; // 1 = altered
    if (pp_normal >= pp_altered)
    {
        res = 0; // 0 = normal
    }
    return res;
}

//returns array with final results after making final calculations
double **Make_Prediction(int start_count, int end_count, int size, float **s_arr, struct probability *altered, struct probability *normal)
{
    int count = 0;
    int columns = 5;
    int error_sum = 0;
    double error_probability;
    double pp_normal;
    double pp_altered;
    int predicted_res;
    int real_res;
    double **prediction_arr = malloc(size * sizeof(double *)); // dynamically allocate array

    for (size_t i = start_count; i < end_count; i++)
    {
        pp_normal = Posterior_Probability(i, normal, s_arr);
        pp_altered = Posterior_Probability(i, altered, s_arr);
        predicted_res = NB_Prediction(pp_normal, pp_altered);
        real_res = s_arr[i][s_col - 1];

        // check if predicted outcome = real outcome
        if (predicted_res != real_res)
        {
            error_sum++;
        }
        // calculates probability of error
        error_probability = 1.f / size * error_sum;

        // stores predicted values into the array
        // allocates 5 columns for the data (pp_normal, pp_altered, real_res, predicted_res, error_probability)
        prediction_arr[count] = malloc(columns * sizeof(double *));
        // adds pp_normal to array
        prediction_arr[count][0] = pp_normal;
        // adds pp_altered to array
        prediction_arr[count][1] = pp_altered;
        // adds real_res to array
        prediction_arr[count][2] = real_res;
        // adds predicted_res to array
        prediction_arr[count][3] = predicted_res;
        // adds error_probability to array
        prediction_arr[count][4] = error_probability;

        count++;
    }

    return prediction_arr;
}

//returns confusion matrix values in an array
int *Compute_Confusion_Matrix(double **data_arr, int size)
{
    int tp_count = 0, tn_count = 0, fp_count = 0, fn_count = 0;
    static int cm_arr[4];
    int real_res;
    int predicted_res;
    int real_res_col = 2;
    int pred_res_col = 3;

    for (size_t i = 0; i < size; i++)
    {
        real_res = data_arr[i][real_res_col];
        predicted_res = data_arr[i][pred_res_col];

        // True Positive : No of times predict correctly that patient is not normal
        if (real_res == 1 && predicted_res == 1)
        {
            tp_count++;
        }
        // True Negative: No of times predict correctly that patient is normal
        else if (real_res == 0 && predicted_res == 0)
        {
            tn_count++;
        }
        // False Positive: No of times predict wrongly that patient is not normal
        else if (real_res == 0 && predicted_res == 1)
        {
            fp_count++;
        }
        // False Negative: No of times predict wrongly that patient is normal
        else if (real_res == 1 && predicted_res == 0)
        {
            fn_count++;
        }
    }
    // store confusion matrix results into array
    cm_arr[0] = tp_count;
    cm_arr[1] = tn_count;
    cm_arr[2] = fp_count;
    cm_arr[3] = fn_count;

    return cm_arr;
}

//calculates accuracy percentage of the nb algo
double Scoring(int tn_count, int tp_count, int total)
{
    int total_res = tn_count + tp_count;
    double score = (total_res * 100.f) / total;
    return score;
}
