#include <stdio.h>

int options, meal_number=0;
float weight = 100;
float calories[100];
char meal[100][100];

void Meal()
{
    do
    {
        printf("\n1. Add a meal\n2. Display meals\n3.Display weight\n");
        printf("\nEnter the number of the option selected: ");
        scanf("%d", &options);
        switch (options)
        {
            case 1:
                printf("Meal name: ");
                scanf("%99s", &meal[meal_number]);
                printf("Calories: ");
                scanf("%f", &calories[meal_number]);
                weight=weight+(calories[meal_number]/3500);
                meal_number++;
                break;
            case 2:
                if (meal_number!=0)
                {
                    for (int  i = 0; i < meal_number; i++)
                    {
                        printf("\nMeal %d: %s\nCalories: %.2f cal\n", i+1, meal[i], calories[i]);
                    }
                }
                else
                {
                    printf("\nNo meals\n");
                }
                break;
            case 3:
                printf("\nYou weigh %.2f lbs\n", weight);
                break;
            default:
                break;
        }
    } while (options!=0);  
}

int main()
{
    Meal();
    printf("Goodbye, have a good day!");
    return 0;
}
