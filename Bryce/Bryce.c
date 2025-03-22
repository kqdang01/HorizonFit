#include <stdio.h>
#include <string.h>

float BMI(float weight, float height)
{
    return weight/(height*height);
}
int main()
{
    
    int action;
    float weight, height, bmi;
    char name[100];
    printf("Please, enter your name:");
    fgets(name,100,stdin);
    printf("Welcome %s", name);
    do
    {
        printf("What would you like to do?\n\nOPTIONS:\n1- BMI\n2 - API\n3- Calorie Tracker\n\nEnter the number of the action you want to perform:", name);
        scanf("%d", &action);
        switch (action)
        {
            case 1:
                printf("BMI\n");
                printf("Enter your weight: ");
                scanf("%f", &weight);
                printf("Enter your height: ");
                scanf("%f", &height);
                bmi = BMI(weight, height);
                printf("Your BMI is %f\n", bmi);
                break;
            default:
                printf("restart");
        }
    }
    while (1);
    
    return 0;
}
