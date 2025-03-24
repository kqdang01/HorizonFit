#include <stdio.h>
#include <string.h>

struct User
{
    char name[100];
    float weight;
    float height;
    float bmi;
    char bmi_cat[50];
}info;


void BMI()
{
    printf("BMI\n");
    printf("Enter your weight in lbs: ");
    scanf("%f", &info.weight);
    printf("Enter your height in inches: ");
    scanf("%f", &info.height);
    info.bmi = info.weight*703/(info.height*info.height);
    printf("Your BMI is %.2f", info.bmi);
    if (info.bmi < 18.5)
    {
        strcpy(info.bmi_cat, "You are UNDERWEIGHT");
        printf("\nYou are UNDERWEIGHT");
    }
    else
    {   
        if (info.bmi < 25)
        {
            strcpy(info.bmi_cat, "You have a NORMAL WEIGHT");
            printf("\nYou have a NORMAL WEIGHT");
        }
        else
        {
            if (info.bmi < 30)
            {
                strcpy(info.bmi_cat,"You are OVERWEIGHT");
                printf("\nYou are OVERWEIGHT");
            }
            else if (info.bmi >= 30)
            {
                strcpy(info.bmi_cat,"You are OBESE");
                printf("\nYou are OBESE");
            }
        }
    }
    
    return;
}

int main()
{
    int action;
    char string[100];
    printf("Please, enter your name:");
    fgets(info.name,100,stdin);
    printf("Welcome %s", info.name);
    do
    {
        printf("What would you like to do?\n\nOPTIONS:\n1- BMI\n2 - API\n3- Calorie Tracker\n\nEnter the number of the action you want to perform:", info.name);
        scanf("%d", &action);
        switch (action)
        {
            case 1:
                if (info.bmi==0)
                {
                    BMI();
                }
                else
                {
                    printf("Would you like to recalculate your BMI?\n1- YES\n2- NO");
                    scanf("%d", &action);
                    if (action == 1)
                    {
                        BMI();
                    }
                    else
                    {
                        printf("Your BMI is %f", info.bmi);
                    }
                }
                break;    
            default:
                printf("\nWrong input");
        }
        printf("\nAre you done?\nEnter a number to select an answer:\n1- YES\n2- NO\n ");

    }
    while (1);
    
    return 0;
}
