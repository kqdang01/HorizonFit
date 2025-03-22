#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

#define MAX_LINE 30

cJSON* createUserObj(cJSON*,char*,char*);

int main(void)
{
    char name[MAX_LINE] = {};
    char pass[MAX_LINE] = {};

    //opening the database file for reading and writing
    FILE *db = fopen("db.json","r+");
    if (db == NULL)
    {
        printf("File did not open correctly, exiting...\n");
        exit(0);
    }
    //prompt for name and pass for creating an account
    printf("Enter a username: ");
    scanf("%s", name);
    printf("\n");
    getchar();
    printf("Enter a password: ");
    scanf("%s", pass);
    printf("\n");
    cJSON *user = cJSON_CreateObject();
    user = createUserObj(user,name,pass);
    printf("%s\n", cJSON_Print(user));
    fclose(db);
    return 0;
}

//creating json user object
cJSON* createUserObj(cJSON* acc,char* username, char* password)
{
    cJSON_AddStringToObject(acc, "username", username);
    cJSON_AddStringToObject(acc, "password", password);
    return acc;
}