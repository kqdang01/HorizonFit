
// use link list and case staments

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 

//cardio
#define TREADMIL_CALORUES 11.7
#define ELLIPTICAL_CALORUES 3
#define ROWER_CALORUES 4
#define UPERIGHT_BIKE_CALORUES 8
#define STEPMILL_CALORUES 8
#define RECUMBENT_STEPPER_CALORUES 7.2
#define RECUBENT_BIKE_CALORUES 8.67
#define ARC_CALORUES 10.8
#define UBE_CALORUES 9

//Strength
#define CABLE_TOWER_BASE_CALORUES 15
#define FITBENCH_BASE_CALORUES 8.5
#define FREE_WEIGHTS_BASE_CALORUES 4
#define PULLEY_BASE_CALORUES 7
#define SMITH_MACHINE_BASE_CALORUES 4
#define FUNCTIONAL_STATION_BASE_CALORUES 4
#define TRX_BASE_CALORUES 6.67
#define SQUAT_LUNGE_MACHINE_BASE_CALORUES 8
#define SUPINE_BENCH_PRESS_BASE_CALORUES 4
#define GLUTE_MACHINE_BASE_CALORUES 5


void CC()
    {
        int TC=0;
        char UE;
        
        printf ("Did you use any equipment? (y/n): ");
        scanf("%c", &UE);

        while (UE=='y'|| UE=='Y')
        {
            int equipment=0;
            int ET,duration=0,sets=0,reps=0,CPM=0,EC=0,SC=0;
            char EN[100];

            printf("\n===== EQUIPMENT TYPE ======\n");
            printf("1. Cardio Equipment\n");
            printf("2. Strength Equipment\n");
            printf("Select equipment type (1-2): ");
            scanf("%d", &ET);

            switch (ET)
            {
                case 1:
                    while (equipment < 1 || equipment > 9)
                    {
                        printf("\n====== CARDIO EQUIPMENT ======\n");
                        printf("1. Treadmill\n");
                        printf("2. Elliptical\n");
                        printf("3. Rower\n");
                        printf("4. Upright Bike\n");
                        printf("5. Stepmill\n");
                        printf("6. Recumbent Bike\n");
                        printf("7. Recumbent Stepper\n");
                        printf("8. Arc\n");
                        printf("9. UBE\n");
                        printf("Select Cardio Equipment (1-9): ");
                        scanf("%d", &equipment);
                        if(equipment < 1 || equipment > 9)                        {
                            printf("Invalid Choice\n");
                        }
                    }
                do{
                    printf("Enter how many minutes used: ");
                    scanf(" %d", &duration);
                    if(duration < 0 || duration > 1400)
                    {
                        printf("Invalid Choice\n");
                    }
                }while(duration <= 0 || duration > 1440);
            
                switch (equipment)
                {
                    case 1:
                        strcpy(EN, "Treadmill");
                        CPM=TREADMIL_CALORUES;
                        break;
                    case 2:
                        strcpy(EN, "Elliptical");
                        CPM=ELLIPTICAL_CALORUES;
                        break;
                    case 3:
                        strcpy(EN, "Rower");
                        CPM=ROWER_CALORUES;
                        break;
                    case 4:
                        strcpy(EN, "Upright Bike");
                        CPM=UPERIGHT_BIKE_CALORUES;
                        break;
                    case 5:
                        strcpy(EN, "Stepmill");
                        CPM=STEPMILL_CALORUES;
                        break;
                    case 6:
                        strcpy(EN, "Recumbent Bike");
                        CPM=RECUBENT_BIKE_CALORUES;
                        break;
                    case 7:
                        strcpy(EN, "Recumbent Stepper");
                        CPM=RECUMBENT_STEPPER_CALORUES;
                        break;
                    case 8:
                        strcpy(EN, "Arc");
                        CPM=ARC_CALORUES;
                        break;
                    case 9:
                        strcpy(EN, "UBE");
                        CPM=UBE_CALORUES;
                        break;
                    default:
                        printf("Invalid choice.\n");
                        strcpy(EN, "Unknown Cardio");
                        CPM=5;
                }
                EC=duration * CPM;
                printf("%s: %d minutes - %d calories\n", EN,duration,EC);
                break;
            
                case 2:
                    while(SC < 1 || SC > 10)
                    {
                        printf("\n====== STRENGTH EQUIPMENT ======\n");
                        printf("1. Cable Tower\n");
                        printf("2. Fit Bench\n");
                        printf("3. Free Weights\n");
                        printf("4. Pulley\n");
                        printf("5. Smith Machine\n");
                        printf("6. Functional Station\n");
                        printf("7. TRX\n");
                        printf("8. Supine Bench Press\n");
                        printf("9. Squat Lunge Machine\n");
                        printf("10. Glute Machine\n");
                        printf("Select Strength Equipment (1-10): ");
                        scanf("%d", &SC);
                            if(SC < 1 || SC > 10)
                            {
                                printf("Invalid Choice\n");
                            }
                }
                do
                {
                printf("Enter the number of minutes used: ");
                scanf(" %d", &duration);
                    if(duration < 0 || duration > 1440)
                        {
                        printf("Invalid Number\n");
                        }
                }while(duration <= 0 || duration > 1440);
                do
                {
                printf("Enter the number of sets: ");
                scanf(" %d", &sets);
                    if(sets < 0 || sets > 100)
                        {
                        printf("Invalid Number\n");
                        }
                }while(sets <= 0 || sets > 100);

                do
                {
                printf("Enter the number of reps per set: ");
                scanf("%d", &reps);
                    if(reps < 0 || reps > 1000)
                        {
                        printf("Invalid Number\n");
                         }
                }while(reps <= 0 || reps > 1000);


                switch (SC)
                {
                    case 1:
                        strcpy(EN, "Cable Tower");
                        CPM=CABLE_TOWER_BASE_CALORUES;
                        break;
                    case 2:
                        strcpy(EN, "Fit Bench");
                        CPM=FITBENCH_BASE_CALORUES;
                        break;
                    case 3:
                        strcpy(EN, "Free Weights");
                        CPM=FREE_WEIGHTS_BASE_CALORUES;
                        break;
                    case 4:
                        strcpy(EN, "Pulley");
                        CPM=PULLEY_BASE_CALORUES;
                        break;
                    case 5:
                        strcpy(EN, "Smith Machine");
                        CPM=SMITH_MACHINE_BASE_CALORUES;
                        break;
                    case 6:
                        strcpy(EN, "Functional Station");
                        CPM=FUNCTIONAL_STATION_BASE_CALORUES;
                        break;
                    case 7:
                        strcpy(EN, "TRX");
                        CPM=TRX_BASE_CALORUES;
                        break;
                    case 8:
                        strcpy(EN, "Supine Bench Press");
                        CPM=SUPINE_BENCH_PRESS_BASE_CALORUES;
                        break;
                    case 9:
                        strcpy(EN, "Squat Lunge Machine");
                        CPM=SQUAT_LUNGE_MACHINE_BASE_CALORUES;
                        break;
                    case 10:
                        strcpy(EN, "Glute Machin");
                        CPM=GLUTE_MACHINE_BASE_CALORUES;
                    default:
                        printf("Invalid choice.\n");
                        strcpy(EN, "Unknown Cardio");
                        CPM=5;
            }
            CPM +=(sets * reps)/10;
            EC=duration * CPM;
            printf("%s: %d minutes (%d sets, %d reps) -%d calories\n", EN,duration,sets,reps,EC);
            break;

            default:
                printf("Invalid selection. Please try again.\n");
                EC=0;
                continue;

           
        }
        TC +=EC;
            printf("Did you use another equipment? (y/n): ");
            getchar();
            scanf("%c", &UE);
    }
    printf("\n======== WORKOUT SUMMARY =======\n");
    printf("TOTAL CALORIES BURNED: %d Kcal\n", TC);
    printf("===============================\n");

}

int options, meal_number=0;
float weight = 100;
float calories[100];
char meal[100][100];

void Meal()
{
    do
    {
        printf("\n1. Add a meal\n2. Display meals\n3.Display weight\n");
        scanf("%d", &options);
        switch (options)
        {
            case 1:
                printf("Meal name: ");
                //scanf("%99s", &meal[meal_number]);
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

int Connor()
{
    CC();
    //Meal();
    return 0;
}








