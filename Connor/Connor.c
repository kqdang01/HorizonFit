#include <stdio.h>
#include <string.h>
 
#define RUNNING_CALORIES_PER_MINUTE 11.7
//cardio
#define TREADMIL_CALORUES 11.7
#define ELLIPTICAL_CALORUES 3
#define ROWER_CALORUES 4
#define UPERIGHT_BIKE_CALORUES 8
#define STEPMILL_CALORUES
#define RECUMBENT_STEPPER_CALORUES
#define RECUBENT_BIKE_CALORUES
#define ARC_CALORUES
#define UBE_CALORUES

//Strength
#define CABLE_TOWER_BASE_CALORUES
#define FITBENCH_BASE_CALORUES
#define FREE_WIGHTS_BASE_CALORUES
#define PULLEY_BASE_CALORUES
#define SMITH_MACHINE_BASE_CALORUES
#define FUNCTIONAL_STATION_BASE_CALORUES
#define TRX_BASE_CALORUES
#define SQUAT_LUNGE_MACHINE_BASE_CALORUES
#define SUPINE_BENCH_PRESS_BASE_CALORUES
#define GLUTE_MACHINE_BASE_CALORUES


void cc()
{
    int runTime, eTime, totalcal =0;
    char useE;
//run time
    printf("Enter the number of minutes you ran for: ");
    scanf("%d",&runTime);
    totalcal += runTime * RUNNING_CALORIES_PER_MINUTE;

    //asking if they used any equipment
    printf("Did you use any equipment? (y/n): ");
    scanf("%c", &useE);

    while (useE =='y' || useE == 'y')
    {
        char eType[30];
        int sets=0, rps=0;

        printf("Enter the type of equipment used: ");
        scanf("%s",&eType);
        printf("Enter the number of minutes used the equipment: ");
        scanf("%s",&eTime);

        int cpm = ;

        //cardio
    if (strcmp(eType,"Treadmill")==0)
    {
        cpm=TREADMIL_CALORUES;
    }else if (srtcmp(eType,"Elliptical")==0)
    {
        cpm=ELLIPTICAL_CALORUES;
    }else if (srtcmp(eType,"Rower")==0)
    {
        cpm=ROWER_CALORUES;
    }else if (srtcmp(eType,"UprightBike")==0)
    {
        cpm=UPERIGHT_BIKE_CALORUES;
    }else if (srtcmp(eType,"Stepmill")==0)
    {
        cpm=STEPMILL_CALORUES;
    }else if (srtcmp(eType,"RecumbentBike")==0)
    {
        cpm=RECUBENT_BIKE_CALORUES;
    }else if (srtcmp(eType,"RecumbentStepper")==0)
    {
        cpm=RECUMBENT_STEPPER_CALORUES;
    }else if (srtcmp(eType,"Arc")==0)
    {
        cpm=ARC_CALORUES;
    }else if (srtcmp(eType,"UBE")==0)
    {
        cpm=UBE_CALORUES;
    }

    //strength equipment
    
    }
    return 0;
}