#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cJSON.c"

#define MAX_LINE 30
#define MAX_BUFFER 3000

cJSON* createUserObj(cJSON*,char*,char*);
void readEntireFile(char*,char*);
void loginUser(cJSON*);
void registerUser(cJSON*);
void prepFile();
int safeInput(char*, int);

int main(void)
{
    //variables
    int choiceVariable;
    char buffer[MAX_BUFFER] = {};
    char line[MAX_LINE] = {};
    cJSON *jsonFile = NULL;

    //opening the database file for reading and writing
    FILE *db = fopen("db.json","r+");
    if (db == NULL)
    {
        printf("File did not open correctly, exiting...\n");
        exit(0);
    }
    //read database and parse json data
    readEntireFile(buffer,line);
    jsonFile = cJSON_Parse(buffer);
    //if database was empty, prep the database boilerplate
    if (jsonFile == NULL)
    {
        prepFile();
        readEntireFile(buffer,line);
        jsonFile = cJSON_Parse(buffer);
    }
    fclose(db);

    //prompt for user option
    printf("What would you like to do?\n");
    printf("1. Login with username and password\n");
    printf("2. Register\n");
    printf("Enter your choice: ");
    scanf("%d", &choiceVariable);
    getchar();
    printf("\n");

    //switch on user choice
    switch(choiceVariable)
    {
        case 1:
            loginUser(jsonFile);
            break;
        case 2:
            registerUser(jsonFile);
            break;
        default:
            printf("Invalid Choice.\n");
    }

    cJSON_Delete(jsonFile);
    return 0;
}

//creating json user object with all user items
cJSON* createUserObj(cJSON* acc,char* username, char* password)
{
    cJSON_AddStringToObject(acc, "username", username);
    cJSON_AddStringToObject(acc, "password", password);
    return acc;
}

void readEntireFile(char *buffer, char *line)
{
    //open file for reading and writing
    FILE *db = fopen("db.json", "r+");
    if (db == NULL)
    {
        printf("File did not open correctly.\n");
        {
            exit(0);
        }
    }
    //while the line isn't null or eof
    while (fgets(line, MAX_LINE, db) != NULL)
    {
        //concate the current line to the previous line
        strcat(buffer,line);
    }
    fclose(db);
}

void loginUser(cJSON *jsonFile)
{
    //variables
    int foundUsername = 0;
    char username[MAX_LINE] = {};
    char pass[MAX_LINE] = {};
    const cJSON *users = NULL;
    const cJSON *user = NULL;
    cJSON *name = NULL;
    cJSON *userPass = NULL;

    //prompt for username & password
    printf("Enter your username: ");
    scanf("%s", username);
    printf("\n");
    printf("Enter a password: ");
    scanf("%s", pass);
    printf("\n");

    //get objects
    users = cJSON_GetObjectItemCaseSensitive(jsonFile, "users");
    if (users == NULL)
    {
        printf("Something went wrong.\n");
        exit(0);
    }

    //iterate through each user object within the userArray
    cJSON_ArrayForEach(user,users)
    {
        name = cJSON_GetObjectItemCaseSensitive(user, "username");
        userPass = cJSON_GetObjectItemCaseSensitive(user, "password");
        //if username matches one in database
        if (!strcmp(name->valuestring,username))
        {
            foundUsername = 1;
            //if password matches that account
            if (!strcmp(userPass->valuestring, pass))
            {
                printf("login successful!\n");
            }
            else
            {
                printf("incorrect password.\n");
            }
        }
    }
    //if username matches nothing in database
    if (!foundUsername)
    {
        printf("Cannot find an account with that username.\n");
    }
}

void registerUser(cJSON* jsonFile)
{
    //variables
    int invalid = 0;
    cJSON *users = NULL;
    cJSON *userElement = NULL;
    cJSON *user = NULL;
    cJSON *usernames = NULL;
    char username[MAX_LINE] = {};
    char pass[MAX_LINE] = {};
    FILE *db;

    //open file for reading and writing
    db = fopen("db.json", "r+");
    if (db == NULL)
    {
        printf("Something went wrong.\n");
    }

    //prompt for username & password and check if both username and password typed is valid
    do
    {
        printf("Please create your username: ");
        invalid = safeInput(username,MAX_LINE);
        //check for if input contained any invalid characters
        for (int i = 0; i < strlen(username); i++)
        {
            if (!isalnum(username[i]))
            {
                invalid = 1;
                printf("Username contained invalid character, please re-type your username.\n\n");
                break;
            }
        }
        //if input was too short
        if (strlen(username) <= 3)
        {
            invalid = 1;
            printf("Username is too short, please try again\n");
        }
    } 
    while (invalid);
    printf("\n");
    do
    {
        printf("Please create your password: ");
        invalid = safeInput(pass, MAX_LINE);
        for (int i = 0; i < strlen(pass); i++)
        {
            if (!isalnum(pass[i]))
            {
                invalid = 1;
                printf("Password contained an invalid character, please re-type your password.\n\n");
                break;
            }
        }
        if (strlen(pass) <= 3)
        {
            invalid = 1;
            printf("Password is too short, please try again\n");
        }
    } 
    while (invalid);
    printf("\n");

    //get and create objects
    users = cJSON_GetObjectItemCaseSensitive(jsonFile, "users");
    if (users == NULL)
    {
        printf("Something went wrong.\n");
        exit(0);
    }
    user = cJSON_CreateObject();
    if (user == NULL)
    {
        printf("Something went wrong.\n");
        exit(0);
    }

    //check if there are existing usernames in the database
    cJSON_ArrayForEach(userElement, users)
    {
        usernames = cJSON_GetObjectItemCaseSensitive(userElement, "username");
        if (!strcmp(usernames->valuestring, username))
        {
            printf("Another account with this same username has already been created.\n");
            return;
        }
    }

    //add items to user object & add it to the database
    user = createUserObj(user, username, pass);
    cJSON_AddItemToArray(users, user);
    fprintf(db, "%s", cJSON_Print(jsonFile));

    printf("Account has been successfully created!\n\n");
    return;
}

void prepFile()
{
    //variables
    cJSON *database = NULL;
    cJSON *name = NULL;
    cJSON *userArray = NULL;
    
    //open database file
    FILE *db = fopen("db.json", "r+");
    if (db == NULL)
    {
        printf("File did not open correctly, exiting...\n");
        exit(0);
    }
    //create json objects
    database = cJSON_CreateObject();
    if (database == NULL)
    {
        printf("Something went wrong.\n");
        exit(0);
    }

    name = cJSON_CreateString("User Database");
    if (name == NULL)
    {
        printf("Something went wrong.\n");
        exit(0);
    }
    cJSON_AddItemReferenceToObject(database, "name", name);

    userArray = cJSON_CreateArray();
    if (userArray == NULL)
    {
        printf("Something went wrong.\n");
        exit(0);
    }
    cJSON_AddItemToObject(database, "users", userArray);

    //write structure to file
    fprintf(db, "%s", cJSON_Print(database));
    fclose(db);
}

int safeInput(char *buffer, int size)
{
    fgets(buffer, size, stdin);
    //check if buffer contains something and replace the newline at the end
    if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n')
    {
        buffer[strlen(buffer) - 1] = '\0';
        return 0;
    }
    else
    {
        //flush out stdin if user input overflows the buffer
        printf("Input was too long, please try again.\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return 1;
}