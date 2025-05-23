#include <stdio.h>
#include <string.h>

struct User
{
    float weight;
    float height;
    float bmi;
    char bmi_cat[30];
}info;


void BMI()
{
    printf("BMI\n");
    printf("Enter your weight in lbs: ");
    scanf("%f", &info.weight);
    printf("Enter your height in feet: ");
    scanf("%f", &info.height);
    info.height=info.height;
    info.bmi = info.weight*703/(info.height*info.height);
    printf("Your BMI is %.2f", info.bmi);
    if (info.bmi < 18.5)
    {
        strcpy(info.bmi_cat, "You are UNDERWEIGHT\n");
        printf("\nYou are UNDERWEIGHT\n");
    }
    else
    {   
        if (info.bmi < 25)
        {
            strcpy(info.bmi_cat, "You have a NORMAL WEIGHT\n");
            printf("\nYou have a NORMAL WEIGHT\n");
        }
        else
        {
            if (info.bmi < 30)
            {
                strcpy(info.bmi_cat,"You are OVERWEIGHT\n");
                printf("\nYou are OVERWEIGHT\n");
            }
            else if (info.bmi >= 30)
            {
                strcpy(info.bmi_cat,"You are OBESE\n");
                printf("\nYou are OBESE\n");
            }
        }
    }
    
    return;
}

int main(void)
{
    int action;
    char string[100];
    do
    {
        printf("\nWhat would you like to do?\n\nOPTIONS:\n1- BMI\n2 - API\n3- Calorie Tracker\n\nEnter the number of the action you want to perform: ");
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
                    printf("Would you like to recalculate your BMI?\n1- YES\n2- NO\nEnter the number of the action you want to perform: ");
                    scanf("%d", &action);
                    if (action == 1)
                    {
                        BMI();
                    }
                    else
                    {
                        printf("Your BMI is %.2f\n", info.bmi);
                        printf("%s",info.bmi_cat);
                    }
                }
                break;   
            default:
                printf("\nWrong input");
                break;
        }
        printf("\nAre you done?\n1- YES\n2- NO\nEnter the number of the action you want to perform: ");
        scanf("%d", &action);
    } while (action != 1);
    printf("Goodbye, have a good day!");
    return 0;
}
