// implment your functions here
#include "..\Header Files\naive_bayes.h"
#include "..\Header Files\semen.h"
#include <stdio.h>
#include <math.h>

//probablity for being altered or normal
float altered_probablity = 0;
float normal_probablity = 0;

//80:20 (Training Set : Testing Set)
int training_set, testing_set = 0;

//store the caculated probablities into these structs
struct Probablity altered;
struct Probablity normal;

float Init_Probablity(float **semen)
{
    //Get Amount for 80:20 (Training Set : Testing Set)
    testing_set = s_row * 0.2;
    training_set = s_row - testing_set;

    for (int i = 0; i < training_set; i++)
    {
        if (semen[i][s_col - 1] == 1.0f) //assume last rows = results
            altered_probablity++;
        else
            normal_probablity++;
    }
    altered_probablity /= s_row;
    normal_probablity /= s_row;
    printf("\nTraining Dataset\n");
    printf("Normal Probability: %f, Altered Probability: %f\n", normal_probablity, altered_probablity);

    Prob_Season();                // Init probablity for Seasons
    Prob_Childish_Disease();      // Init probablity for Childish Disease
    Prob_Accident();              // Init probablity for Accident / Serious Trauma
    Prob_Surgical_Intervention(); // Init probablity for Surgical Intervention
    Prob_Fever();                 // Init probablity for Fever
    Prob_Alcohol_Consumption();   // Init probablity for Alcohol Consumption
    Prob_Smoking();               // Init probablity for Smoking Habits
    Prob_Age();                   // Init probablity for Age
    Prob_Sitting();               // Init probability for Sitting hours

    //print to check probablity values
    //Seasons
    /*
    printf("\nProb of Normal Winter, Spring, Summer, Fall: %f, %f, %f, %f", normal.winter_probablity,normal.spring_probablity,normal.summer_probablity,normal.fall_probablity);
    printf("\nProb of Alt Winter, Spring, Summer, Fall: %f, %f, %f, %f", altered.winter_probablity,altered.spring_probablity,altered.summer_probablity,altered.fall_probablity);
    */

    //Age

    //Childish Disease
    /*
    printf("\nProb of Normal Childish Disease| Yes, No: %f, %f", normal.disease_probablity,normal.no_disease_probablity);
    printf("\nProb of Alt Childish Disease| Yes, No: %f, %f", altered.disease_probablity,altered.no_disease_probablity);
    */

    //Accident / Serious Trauma
    /*
    printf("\nProb of Normal Accident/Serious Trauma| Yes, No: %f, %f", normal.trauma_probablity,normal.no_trauma_probablity);
    printf("\nProb of Alt Accident/Serious Trauma| Yes, No: %f, %f", altered.trauma_probablity,altered.no_trauma_probablity);
    */

    //Surgical Intervention
    /*
    printf("\nProb of Normal Surgical Intervention| Yes, No: %f, %f", normal.surgery_probablity,normal.no_surgery_probablity);
    printf("\nProb of Alt Surgical Intervention| Yes, No: %f, %f", altered.surgery_probablity,altered.no_surgery_probablity);
    */

    //Fever
    /*
    printf("\nProb of Normal Fever| L3, M3, No: %f, %f, %f", normal.fever_less3m_probablity,normal.fever_more3m_probablity,normal.no_fever_probablity);
    printf("\nProb of Alt Fever| L3, M3, No: %f, %f, %f", altered.fever_less3m_probablity,altered.fever_more3m_probablity,altered.no_fever_probablity);
    */

    //Frequency of alcohol consumption
    /*
    printf("\nProb of Normal Frequency of alcohol consumption| Several times a day, Every day, Several times a week, Once a week, Hardly ever or never: %f, %f, %f, %f, %f", normal.alcohol_several_day_probablity,normal.alcohol_everyday_probablity,normal.alcohol_several_week_probablity,normal.alcohol_once_week_probablity,normal.alcohol_hardly_probablity);
    printf("\nProb of Alt Frequency of alcohol consumption| Several times a day, Every day, Several times a week, Once a week, Hardly ever or never: %f, %f, %f, %f, %f", altered.alcohol_several_day_probablity,altered.alcohol_everyday_probablity,altered.alcohol_several_week_probablity,altered.alcohol_once_week_probablity,altered.alcohol_hardly_probablity);
    */

    //Smoking Habit
    /*
    printf("\nProb of Normal Smoking Habit| Never, Occasional, Daily: %f, %f, %f", normal.smoke_never_probablity,normal.smoke_occasional_probablity,normal.smoke_daily_probablity);
    printf("\nProb of Alt Smoking Habit| Never, Occasional, Daily: %f, %f, %f", altered.smoke_never_probablity,altered.smoke_occasional_probablity,altered.smoke_daily_probablity);
    */

    // mean + SD of age
    // printf("\nMean of age: %f", normal.age_mean);
    // printf("\nSD of age: %f", normal.age_standard_deviation);

    // mean + SD of sitting
    // printf("\nMean of sitting: %f", normal.sitting_mean);
    // printf("\nSD of sitting: %f", normal.sitting_standard_deviation);

    // Gaussian Probability of age and sitting
    // for (size_t i = 81; i < 100; i++)
    // {
    //     printf("\ntest guassian normal prob %d: %1.30lf",i, Gaussian_Probablity(semen_array[i], normal));
    //     printf("\ntest guassian altered prob %d: %1.30lf",i, Gaussian_Probablity(semen_array[i], altered));
    // }

    // Training Set Posterior Probability
    // for (size_t i = 0; i < training_set; i++)
    // {
    //     printf("\n%d -> Normal Posterior Probability: %1.30lf", i, Posterior_Probability(i, normal));
    //     printf("\n%d -> Altered Posterior Probability: %1.30lf", i, Posterior_Probability(i, altered));
    // }

    // Training Set NB Decision
    // for (size_t i = 0; i < training_set; i++)
    // {
    //     printf("\n%d -> Decision: %d", i, NB_Decision(Posterior_Probability(i, normal), Posterior_Probability(i, altered)));
    // }
}

void Prob_Season()
{
    int alpha = SEASON_ALPHA;
    float aprobability[4] = {0};
    float nprobability[4] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][0] == -1.0f)
                nprobability[0]++;

            else if (semen_array[i][0] == -0.33f)
                nprobability[1]++;

            else if (semen_array[i][0] == 0.33f)
                nprobability[2]++;

            else if (semen_array[i][0] == 1.0f)
                nprobability[3]++;
            else
                printf("\nError in line %d for Seasons value = \"%.2f\" skipping entry, only input (-1, -0.33, 0.33, 1)", (i + 1), semen_array[i][0]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][0] == -1.0f)
                aprobability[0]++;

            else if (semen_array[i][0] == -0.33f)
                aprobability[1]++;

            else if (semen_array[i][0] == 0.33f)
                aprobability[2]++;

            else if (semen_array[i][0] == 1.0f)
                aprobability[3]++;
            else
                printf("\nError in line %d for Seasons value = \"%.2f\" skipping entry, only input (-1, -0.33, 0.33, 1)", (i + 1), semen_array[i][0]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.winter_probablity = aprobability[0];
    altered.spring_probablity = aprobability[1];
    altered.summer_probablity = aprobability[2];
    altered.fall_probablity = aprobability[3];
    normal.winter_probablity = nprobability[0];
    normal.spring_probablity = nprobability[1];
    normal.summer_probablity = nprobability[2];
    normal.fall_probablity = nprobability[3];
}

void Prob_Childish_Disease()
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][2] == 1)
                nprobability[0]++;

            else if (semen_array[i][2] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Childish Disease value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][2]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][2] == 1)
                aprobability[0]++;

            else if (semen_array[i][2] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Childish Disease value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][2]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.no_disease_probablity = aprobability[0];
    altered.disease_probablity = aprobability[1];
    normal.no_disease_probablity = nprobability[0];
    normal.disease_probablity = nprobability[1];
}

void Prob_Accident()
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][3] == 1)
                nprobability[0]++;

            else if (semen_array[i][3] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Accident/Trauma value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][3]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][3] == 1)
                aprobability[0]++;

            else if (semen_array[i][3] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Accident/Trauma value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][3]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.no_trauma_probablity = aprobability[0];
    altered.trauma_probablity = aprobability[1];
    normal.no_trauma_probablity = nprobability[0];
    normal.trauma_probablity = nprobability[1];
}

void Prob_Surgical_Intervention()
{
    int alpha = D_T_S_ALPHA;
    float aprobability[2] = {0};
    float nprobability[2] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][4] == 1)
                nprobability[0]++;

            else if (semen_array[i][4] == 0)
                nprobability[1]++;

            else
                printf("\nError in line %d for Surgical Intervention value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][4]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][4] == 1)
                aprobability[0]++;

            else if (semen_array[i][4] == 0)
                aprobability[1]++;

            else
                printf("\nError in line %d for Surgical Intervention value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][4]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.no_surgery_probablity = aprobability[0];
    altered.surgery_probablity = aprobability[1];
    normal.no_surgery_probablity = nprobability[0];
    normal.surgery_probablity = nprobability[1];
}

void Prob_Fever()
{
    int alpha = F_S_ALPHA;
    float aprobability[3] = {0};
    float nprobability[3] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][5] == -1)
                nprobability[0]++;

            else if (semen_array[i][5] == 0)
                nprobability[1]++;

            else if (semen_array[i][5] == 1)
                nprobability[2]++;

            else
                printf("\nError in line %d for High fevers in last year value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][5]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][5] == -1)
                aprobability[0]++;

            else if (semen_array[i][5] == 0)
                aprobability[1]++;

            else if (semen_array[i][5] == 1)
                aprobability[2]++;

            else
                printf("\nError in line %d for High fevers in last year value = \"%.2f\" skipping entry, only input (0, 1)", (i + 1), semen_array[i][5]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.fever_less3m_probablity = aprobability[0];
    altered.fever_more3m_probablity = aprobability[1];
    altered.no_fever_probablity = aprobability[2];
    normal.fever_less3m_probablity = nprobability[0];
    normal.fever_more3m_probablity = nprobability[1];
    normal.no_fever_probablity = nprobability[2];
}
void Prob_Alcohol_Consumption()
{
    int alpha = ALCOHOL_ALPHA;
    float aprobability[5] = {0};
    float nprobability[5] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][6] == 0.2f)
                nprobability[0]++;

            else if (semen_array[i][6] == 0.4f)
                nprobability[1]++;

            else if (semen_array[i][6] == 0.6f)
                nprobability[2]++;

            else if (semen_array[i][6] == 0.8f)
                nprobability[3]++;

            else if (semen_array[i][6] == 1.f)
                nprobability[4]++;

            else
                printf("\nError in line %d for Frequency of alcohol consumption value = \"%.2f\" skipping entry, only input (0.2, 0.4, 0.6, 0.8, 1)", (i + 1), semen_array[i][6]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][6] == 0.2f)
                aprobability[0]++;

            else if (semen_array[i][6] == 0.4f)
                aprobability[1]++;

            else if (semen_array[i][6] == 0.6f)
                aprobability[2]++;

            else if (semen_array[i][6] == 0.8f)
                aprobability[3]++;

            else if (semen_array[i][6] == 1.f)
                aprobability[4]++;

            else
                printf("\nError in line %d for Frequency of alcohol consumption value = \"%.2f\" skipping entry, only input (0.2, 0.4, 0.6, 0.8, 1)", (i + 1), semen_array[i][6]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.alcohol_several_day_probablity = aprobability[0];
    altered.alcohol_everyday_probablity = aprobability[1];
    altered.alcohol_several_week_probablity = aprobability[2];
    altered.alcohol_once_week_probablity = aprobability[3];
    altered.alcohol_hardly_probablity = aprobability[4];
    normal.alcohol_several_day_probablity = nprobability[0];
    normal.alcohol_everyday_probablity = nprobability[1];
    normal.alcohol_several_week_probablity = nprobability[2];
    normal.alcohol_once_week_probablity = nprobability[3];
    normal.alcohol_hardly_probablity = nprobability[4];
}

void Prob_Smoking()
{
    int alpha = F_S_ALPHA;
    float aprobability[3] = {0};
    float nprobability[3] = {0};
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            if (semen_array[i][7] == -1)
                nprobability[0]++;

            else if (semen_array[i][7] == 0)
                nprobability[1]++;

            else if (semen_array[i][7] == 1)
                nprobability[2]++;

            else
                printf("\nError in line %d for Smoking Habit value = \"%.2f\" skipping entry, only input (-1, 0, 1)", (i + 1), semen_array[i][7]);
            normalcount++;
            break;

        case 1: // Altered
            if (semen_array[i][7] == -1)
                aprobability[0]++;

            else if (semen_array[i][7] == 0)
                aprobability[1]++;

            else if (semen_array[i][7] == 1)
                aprobability[2]++;

            else
                printf("\nError in line %d for Smoking Habit value = \"%.2f\" skipping entry, only input (-1, 0, 1)", (i + 1), semen_array[i][7]);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry, only input (0, 1)", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //Add 1 to all data so there is no 0
    for (int i = 0; i < alpha; i++)
    {
        nprobability[i]++;
        aprobability[i]++;
        nprobability[i] /= (normalcount + alpha);
        aprobability[i] /= (training_set - normalcount + alpha);
    }
    //Store value to struct Probability variable
    altered.smoke_never_probablity = aprobability[0];
    altered.smoke_occasional_probablity = aprobability[1];
    altered.smoke_daily_probablity = aprobability[2];
    normal.smoke_never_probablity = nprobability[0];
    normal.smoke_occasional_probablity = nprobability[1];
    normal.smoke_daily_probablity = nprobability[2];
}

void Prob_Age()
{
    float mean[2] = {0, 0}, sd[2] = {0, 0};
    Mean(1, mean);
    normal.age_mean = mean[0];
    altered.age_mean = mean[1];
    Standard_Deviation(1, mean, sd);
    normal.age_standard_deviation = sd[0];
    altered.age_standard_deviation = sd[1];
}

void Prob_Sitting()
{
    float mean[2] = {0, 0}, sd[2] = {0, 0};
    Mean(8, mean);
    normal.sitting_mean = mean[0];
    altered.sitting_mean = mean[1];
    Standard_Deviation(8, mean, sd);
    normal.sitting_standard_deviation = sd[0];
    altered.sitting_standard_deviation = sd[1];
}

void Mean(int column, float mean[])
{
    int normalcount = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            mean[0] += semen_array[i][column];
            normalcount++;
            break;

        case 1: // Altered
            mean[1] += semen_array[i][column];
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //returns average of the column
    mean[0] /= normalcount;
    mean[1] /= (training_set - normalcount);
}
//assume mean is already calculated
void Standard_Deviation(int column, float mean[], float sd[])
{
    int normalcount = 0;
    //used for temporary storage of data-mean to not alter data in semen_array
    float temp = 0;
    for (int i = 0; i < training_set; i++)
    {
        switch ((int)semen_array[i][s_col - 1])
        {
        case 0: // Normal
            temp = semen_array[i][column] - mean[0];
            sd[0] += pow(temp, 2);
            normalcount++;
            break;

        case 1: // Altered
            temp = semen_array[i][column] - mean[1];
            sd[1] += pow(temp, 2);
            break;

        default:
            printf("\nError in line %d for Semen Diagnosis value = \"%d\" skipping entry", (i + 1), (int)semen_array[i][s_col - 1]);
            break;
        }
    }
    //returns average of the column
    sd[0] /= (normalcount - 1);
    sd[1] /= (training_set - normalcount - 1);
}

//returns average of the column
float Gaussian_Probablity(float data[], struct Probablity probablity)
{
    float age, sitting;
    age = (1 / sqrt(2 * M_PI)) * exp(-0.5 * pow((data[1] - probablity.age_mean) / probablity.age_standard_deviation, 2));
    sitting = (1 / sqrt(2 * M_PI)) * exp(-0.5 * pow((data[8] - probablity.sitting_mean) / probablity.sitting_standard_deviation, 2));
    return age * sitting;
}

//returns posterior probability
float Posterior_Probability(int i, struct Probablity probablity)
{
    float pp;
    // Age and Sitting hours probability
    float gp = Gaussian_Probablity(semen_array[i], probablity);
    pp = gp;
    // Seasons probability
    pp *= probablity.winter_probablity * probablity.spring_probablity * probablity.summer_probablity * probablity.fall_probablity;
    // Childish Disease probability
    pp *= probablity.disease_probablity * probablity.no_disease_probablity;
    // Accident / Serious Trauma probability
    pp *= probablity.trauma_probablity * probablity.no_trauma_probablity;
    // Surgical Intervention probability
    pp *= probablity.surgery_probablity * probablity.no_surgery_probablity;
    // Fever probability
    pp *= probablity.fever_less3m_probablity * probablity.fever_more3m_probablity * probablity.no_fever_probablity;
    // Alcohol Consumption probability
    pp *= probablity.alcohol_several_day_probablity * probablity.alcohol_everyday_probablity * probablity.alcohol_several_week_probablity * probablity.alcohol_once_week_probablity * probablity.alcohol_hardly_probablity;
    // Smoking Habits probability
    pp *= probablity.smoke_never_probablity * probablity.smoke_occasional_probablity * probablity.smoke_daily_probablity;
    return pp;
}

//returns nb algo decision based on Posterior Probability
int NB_Decision(float normal_p, float altered_p)
{
    int res = 0; // 0 = normal
    if (normal_p >= altered_p)
    {
        return res;
    }
    else
    {
        res = 1; // 1 = altered
        return res;
    }
}

//returns probability of error