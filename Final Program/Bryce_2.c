#include <stdio.h>

int options, meal_number=0;
float calories[100];
char meal[100][100];

void Meal()
{
    do
    {
        printf("\n1. Add a meal\n2. Display meals\n3. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &options);
        getchar();
        switch (options)
        {
            case 1:
                printf("Meal name: ");
                fgets(meal[meal_number], 100, stdin);
                printf("Calories: ");
                scanf("%f", &calories[meal_number]);
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
                exit(0);
                break;
            default:
                break;
        }
    } while (options!=0);  
}

int Bryce2()
{
    Meal();
    return 0;
}
