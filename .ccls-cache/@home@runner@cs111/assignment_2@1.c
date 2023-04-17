#include <stdio.h>
#include <stdlib.h>

#define N_STUDENTS 50
#define N_SUBJECTS 4

/* 
    0 - Maths
    1 - Science
    2 - English
    3 - Hindi
*/

void subject_marks(int marks[N_SUBJECTS][N_SUBJECTS])
{
    int lowest = 0, highest = 100;
    for(int i = 0; i < N_STUDENTS; i++)
    {
        marks[i][0] = (rand()%(highest - lowest + 1)) + lowest;
        marks[i][1] = (rand()%(highest - lowest + 1)) + lowest;
        marks[i][2] = (rand()%(highest - lowest + 1)) + lowest;
        marks[i][3] = (rand()%(highest - lowest + 1)) + lowest;
    }
}

void computeMathAGrade(int marks[N_STUDENTS][N_SUBJECTS])
{
    int count = 0;
    for(int i = 0; i < N_STUDENTS; i++)
        if(marks[i][0] >= 90 && marks[i][0] <= 100)
            count++;
    printf("(a)\n");
    printf("%d students have got an A grade in Math.\n", count);
}

void findHighestInEnglish(int marks[N_STUDENTS][N_SUBJECTS])
{
    int highest_marks = 0;
    for(int i = 0; i < N_STUDENTS; i++)
        if(highest_marks < marks[i][2]) highest_marks = marks[i][2];
    printf("(b)\n");
    printf("%d is/are the highest marks obtained by a student in English.\n", highest_marks);
}

void findLowestInHindi(int marks[N_STUDENTS][N_SUBJECTS])
{
    int lowest_marks = 0;
    for(int i = 0; i < N_STUDENTS; i++)
        if(lowest_marks > marks[i][3]) lowest_marks = marks[i][3];
    printf("%d is/are the lowest marks obtained by a student in Hindi.\n", lowest_marks);
}

int failed(int m)
{
    if(m <= 32) return 1;
    return 0;
}

void numberOfStudentsWhoFailed(int marks[N_STUDENTS][N_SUBJECTS])
{
    int count = 0;
    for(int i = 0; i < N_STUDENTS; i++)
    {
        int n_failed = 0;
        for(int j = 0; i < N_SUBJECTS; i++)
            if(failed(marks[i][j])) n_failed++;
        if(n_failed > 3) count++;
    }
    printf("(c)\n");
    printf("%d students have failed in the semester.\n", count);
}

void classAverage(int marks[N_STUDENTS][N_SUBJECTS])
{
    double class_avg = 0;
    for(int i = 0; i < N_STUDENTS; i++)
        for(int j = 0; j < N_SUBJECTS; j++)
            class_avg += (double)(marks[i][j])/(double)(N_SUBJECTS*N_STUDENTS);
    printf("(d)\n");
    printf("%lf is the class average for all the subjects.\n", class_avg);
}

void subjectWiseAverage(int marks[N_STUDENTS][N_SUBJECTS])
{
    double averages[4];
    for(int i = 0; i < N_STUDENTS; i++)
        for(int j = 0; j < N_SUBJECTS; j++)
            averages[j] += (double)marks[i][j]/(double)N_STUDENTS;
    printf("%lf is the average for Math.\n", averages[0]);
    printf("%lf is the average for Science.\n", averages[1]);
    printf("%lf is the average for English.\n", averages[2]);
    printf("%lf is the average for Hindi.\n", averages[3]);
}

void percentages(int marks[N_STUDENTS][N_SUBJECTS])
{
    double p[N_STUDENTS];
    for(int i = 0; i < N_STUDENTS; i++)
        p[i] = 100.0*(double)(marks[i][0]+marks[i][0]+marks[i][0]+marks[i][0])/(double)(N_SUBJECTS*100);
    printf("(e)\n");
    printf("The percentages of the students are\n");
    for(int i = 0; i < N_STUDENTS; i++)
        printf("%d. %lf %%\n", i + 1, p[i]);
}

int main()
{
    int marks[N_STUDENTS][N_SUBJECTS];
    subject_marks(marks);
    computeMathAGrade(marks);
    findHighestInEnglish(marks);
    findLowestInHindi(marks);
    numberOfStudentsWhoFailed(marks);
    classAverage(marks);
    subjectWiseAverage(marks);
    percentages(marks);
    return 0;
}
