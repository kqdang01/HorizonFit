#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "cJSON.c"
#include "Bryce.c"
#include "Bryce_2.c"
#include "Connor.c"

#define MAX_LINE 30
#define MAX_BUFFER 3000
#define MAX_CHAT 200

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define NORMAL "\x1b[m"

cJSON* createUserObj(cJSON*,char*,char*);
void readEntireFile(char*,char*,char*);
bool loginUser(cJSON*, char*);
bool registerUser(cJSON*, char*);
void prepFile();
int safeInput(char*, int);
void chat(char*);

int main(void)
{
    //variables
    int choiceVariable;
    int choiceVariable2;
    bool invalid;
    bool loggedOn;
    char buffer[MAX_BUFFER] = {};
    char line[MAX_LINE] = {};
    char usernameHolder[MAX_LINE] = {};
    cJSON *jsonFile = NULL;
start:
    //opening the database file for reading and writing
    FILE *db = fopen("db.json","r+");
    if (db == NULL)
    {
        printf("File did not open correctly, exiting...\n");
        exit(0);
    }

    //read database and parse json data
    readEntireFile("db.json",buffer,line);
    jsonFile = cJSON_Parse(buffer);

    //if database was empty, prep the database boilerplate
    if (jsonFile == NULL)
    {
        prepFile();
        readEntireFile("db.json",buffer,line);
        jsonFile = cJSON_Parse(buffer);
    }
    fclose(db);

    //prompt for user option
    do
    {
        printf("What would you like to do?\n");
        printf("1. Login with username and password\n");
        printf("2. Register\n");
        printf("Enter your choice: ");
        scanf("%d", &choiceVariable);
        getchar();
        printf("\n");
        invalid = false;
        switch(choiceVariable)
        {
            case 1:
                loggedOn = loginUser(jsonFile, usernameHolder);
                break;
            case 2:
                loggedOn = registerUser(jsonFile, usernameHolder);
                break;
            default:
                invalid = true;
                printf("Invalid choice, please try again.\n\n");
        }
    }
    while (invalid);
    cJSON_Delete(jsonFile);

    printf("\n");

    if (loggedOn)
    {
        printf("==============\n\n");
        printf("hi %s\n\n", usernameHolder);
        printf("==============\n\n");
    }
    else
    {
        exit(0);
    }

    //prompt main features
    do
    {
        printf("What would you like to do?\n");
        printf("1. Chat\n");
        printf("2. BMI Calculator\n");
        printf("3. Calorie Calculator\n");
        printf("4. Meal Manager\n");
        printf("5. Log Out\n");

        printf("Enter your choice here: ");
        scanf("%d", &choiceVariable2);
        getchar();
        printf("\n");

        invalid = false;
        switch(choiceVariable2)
        {
            case 1:
                chat(usernameHolder);
                break;
            case 2:
                Bryce();
                break;
            case 3:
                Connor();
                break;
            case 4:
                Bryce2();
                break;
            case 5:
                goto start;
                break;
            default:
                invalid = true;
                printf("Invalid choice, please try again\n\n");
        }
    }
    while (invalid);
    return 0;
}

//creating json user object with all user items
cJSON* createUserObj(cJSON* acc,char* username, char* password)
{
    cJSON_AddStringToObject(acc, "username", username);
    cJSON_AddStringToObject(acc, "password", password);
    return acc;
}

void readEntireFile(char *filename,char *buffer, char *line)
{
    //resetting the buffer
    buffer[0] = '\0';
    //open file for reading
    FILE *randFile = fopen(filename, "r");
    if (randFile == NULL)
    {
        printf("File did not open correctly.\n");
        {
            exit(0);
        }
    }
    //while the line isn't null or eof
    while (fgets(line, MAX_LINE, randFile) != NULL)
    {
        //concate the current line to the previous line
        strcat(buffer,line);
    }
    fclose(randFile);
}

bool loginUser(cJSON *jsonFile, char *usernameHolder)
{
    //variables
    int foundUsername = 0;
    char username[MAX_LINE] = {};
    char pass[MAX_LINE] = {};
    cJSON *users = NULL;
    cJSON *user = NULL;
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
        printf("Something has went wrong.\n");
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
                strcpy(usernameHolder, name->valuestring);
                return true;
            }
            else
            {
                printf("incorrect password.\n");
            }
        }
    }
    //pray for no memory leaks 🙏🙏🙏
    //if username matches nothing in database
    if (!foundUsername)
    {
        printf("Could not find an account with that username.\n");
    }
    return false;
}

bool registerUser(cJSON *jsonFile, char *usernameHolder)
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
        printf("Something has went wrong.\n");
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
            printf("Username is too short, please try again\n\n");
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
            printf("Password is too short, please try again\n\n");
        }
    } 
    while (invalid);
    printf("\n");

    //get and create objects
    users = cJSON_GetObjectItemCaseSensitive(jsonFile, "users");
    if (users == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }
    user = cJSON_CreateObject();
    if (user == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }

    //check if there are existing usernames in the database
    cJSON_ArrayForEach(userElement, users)
    {
        usernames = cJSON_GetObjectItemCaseSensitive(userElement, "username");
        if (!strcmp(usernames->valuestring, username))
        {
            printf("Another account with this same username has already been created.\n");
            return false;
        }
    }

    //add items to user object & add it to the database
    user = createUserObj(user, username, pass);
    cJSON_AddItemToArray(users, user);
    fprintf(db, "%s", cJSON_Print(jsonFile));

    printf("Account has been successfully created!\n");
    fclose(db);
    strcpy(usernameHolder, username);
    return true;
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
        printf("Something has went wrong.\n");
        exit(0);
    }

    name = cJSON_CreateString("User Database");
    if (name == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }
    cJSON_AddItemReferenceToObject(database, "name", name);

    userArray = cJSON_CreateArray();
    if (userArray == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }
    cJSON_AddItemToObject(database, "users", userArray);

    //write structure to file
    fprintf(db, "%s", cJSON_Print(database));
    fclose(db);
}

void prepChatFile()
{
    //variables
    cJSON *chat = NULL;
    cJSON *chatArray = NULL;
    FILE *chatFile = NULL;

    //open chat file
    chatFile = fopen("chat.json", "r+");
    if (chatFile == NULL)
    {
        printf("File did not open correctly, exiting...\n");
        exit(0);
    }

    //create objects
    chat = cJSON_CreateObject();
    if (chat == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }
    chatArray = cJSON_CreateArray();
    if (chatArray == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }

    //add objects to chat
    cJSON_AddStringToObject(chat, "name", "chat");
    cJSON_AddItemToObject(chat, "chatArray", chatArray);

    fprintf(chatFile, "%s", cJSON_Print(chat));
    fclose(chatFile);
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
        printf("Input was too long, please try again.\n\n");
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
    return 1;
}

void chat(char *usernameHolder)
{
    //variables
    char buffer[MAX_BUFFER] = {};
    char line[MAX_LINE] = {};
    char chatBuffer[MAX_CHAT] = {};
    cJSON *chat = NULL;
    cJSON *chatArray = NULL;
    cJSON *chatObject = NULL;
    cJSON *message = NULL;
    cJSON *user = NULL;
    FILE *chatFile = NULL;

    //open chat file
    chatFile = fopen("chat.json", "r+");
    if (chatFile == NULL)
    {
        printf("File did not open correctly, exiting...\n");
        exit(0);
    }

    readEntireFile("chat.json", buffer, line);
    chat = cJSON_Parse(buffer);
    //if chat file is empty, set up chat boilerplate
    if (chat == NULL)
    {
        prepChatFile();
        readEntireFile("chat.json", buffer, line);
        chat = cJSON_Parse(buffer);
    }

    chatArray = cJSON_GetObjectItemCaseSensitive(chat, "chatArray");
    if (chatArray == NULL)
    {
        printf("Something has went wrong.\n");
        exit(0);
    }

    //loop through all chat objects and display them to the user
    cJSON_ArrayForEach(chatObject,chatArray)
    {
        message = cJSON_GetObjectItemCaseSensitive(chatObject, "message");
        user = cJSON_GetObjectItemCaseSensitive(chatObject, "user");
        if (!strcmp(user->valuestring, usernameHolder))
        {
            printf("%s%s%s\n", GREEN, user->valuestring, NORMAL);
            printf("%s\n\n", message->valuestring);
        }
        else
        {
            printf("%s%50s%s\n", RED, user->valuestring, NORMAL);
            printf("%50s\n\n", message->valuestring);
        }
    }

    printf("\nenter \"quit\" to quit\n\n");
    
    //actual chat stuff
    while (true)
    {
        printf("%s%s%s\n", GREEN, usernameHolder, NORMAL);
        fgets(chatBuffer, MAX_CHAT, stdin);
        printf("\n");
        chatBuffer[strlen(chatBuffer)-1] = '\0';
        if (!strcmp(chatBuffer, "quit"))
        {
            break;
        }
        chatObject = cJSON_CreateObject();
        if (chatObject == NULL)
        {
            printf("Something has went wrong.\n");
            exit(0);
        }
        cJSON_AddStringToObject(chatObject, "message", chatBuffer);
        cJSON_AddStringToObject(chatObject, "user", usernameHolder);
        cJSON_AddItemReferenceToArray(chatArray, chatObject);
    }
    fprintf(chatFile, "%s", cJSON_Print(chat));
    fclose(chatFile);
}