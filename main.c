// TODO
// Move scanf to fgets?


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NAME_SIZE 64
#define NUMBER_SIZE 15
#define ADDRESS_SIZE 256
#define SAVE_FILE "contacts.txt"

typedef struct {
    char name[NAME_SIZE];
    char number[NUMBER_SIZE];
    char address[ADDRESS_SIZE];
} Contact;

int Add(Contact *addressBook, int count, int capacity);
void List(Contact *addressBook, int count);
void Edit(Contact *addressBook, int count);
int Delete(Contact *addressBook, int count, int capacity);
int LoadContacts(Contact *addressBook, int capacity);
void SaveContacts(Contact *addressBook, int count);
int ResizeAddressbook(Contact **addressBook, int capacity);

int main(void) {
    printf("Address book starting up.\n");

    int count = 0;
    int capacity = 4;
    Contact *addressBook = NULL;
    addressBook = malloc(capacity * sizeof(Contact));
    if (addressBook == NULL)
    {
        perror("Unable to allocate memory");
        return 1;
    }
    
    count = LoadContacts(addressBook, capacity);

    int choice = 0;

    while (choice != 5) {
        if (count == capacity)
        {
            capacity = ResizeAddressbook(&addressBook, capacity);
        }
        
        printf("Select an option:\n 1.Add\n 2.List\n 3.Delete\n 4.Edit\n 5.Exit\n\n");
        
        if (scanf("%d", &choice) != 1) {
            printf("Please enter a number.\n");
            continue;
        }
        while (getchar() != '\n');

        switch (choice) {
            case 1:
                count = Add(addressBook, count, capacity);
                break;

            case 2:
                List(addressBook, count);
                break;

            case 3:
                count = Delete(addressBook, count, capacity);
                break;

            case 4:
                Edit(addressBook, count);
                break;
        }
        
    }

    SaveContacts(addressBook, count);

    free(addressBook);
    return 0;
}

int Add(Contact *addressBook, int count, int capacity) 
{
    char name[NAME_SIZE];
    char number[NUMBER_SIZE];
    char address[ADDRESS_SIZE];

    if (count == capacity)
    {
        printf("Address book is full.\n");
        return count;
    }

    printf("Input name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    printf("Input number:\n");
    fgets(number, sizeof(number), stdin);
    number[strcspn(number, "\n")] = '\0';

    printf("Input address:\n");
    fgets(address, sizeof(address), stdin);
    address[strcspn(address, "\n")] = '\0';

    Contact c = { 0 };
    strncpy(c.name, name, sizeof(c.name) -1);
    strncpy(c.number, number, sizeof(c.number) -1);
    strncpy(c.address, address, sizeof(c.address) -1);
    printf("DEBUG stored: name=[%s] number=[%s] address=[%s]\n", c.name, c.number, c.address);

    addressBook[count] = c;

    return count + 1;
}

void List(Contact *addressBook, int count)
{
    for(int i = 0; i < count; i++)
    {
        if (addressBook[i].name[0] != '\0')
        {
            printf("====================\n");
            printf("Contact: %d\n", i+1);
            printf("Name: %s\n", addressBook[i].name);
            printf("Number: %s\n", addressBook[i].number);
            printf("Address: %s\n", addressBook[i].address);
        }
    }

    return;
}

void Edit(Contact *addressBook, int count)
{
    int index = 0;
    int field = 0;

    printf("Input the index for the contact you wish to edit.\n");
    scanf("%d", &index);
    while (getchar() != '\n');

    index = index -1;

    if (index < 0 || index >= count || addressBook[index].name[0] == '\0')
    {
        printf("Invalid index.\n");
        return;
    }

    printf("You have selected %s.\n", addressBook[index].name);

    printf("Which field do you want to edit?.\n");
    printf("1. Name\n");
    printf("2. Number\n");
    printf("3. Address\n");

    scanf("%d", &field);
    while (getchar() != '\n');

    if (field > 3 || field < 1)
    {
        printf("Invalid field");
        return;
    }

    // NAME
    if (field == 1)
    {
        char name[NAME_SIZE];

        printf("Please input a new name\n");
        fgets(name, sizeof(name), stdin);

        strncpy(addressBook[index].name, name, sizeof(addressBook[index].name)-1);

        printf("Name updated to %s.\n", addressBook[index].name);
    }

    // NUMBER
    if (field == 2)
    {
        char number[NUMBER_SIZE];
    
        printf("Please input a new number\n");
        fgets(number, sizeof(number), stdin);

        strncpy(addressBook[index].number, number, sizeof(addressBook[index].number)-1);

        printf("Number updated to %s.\n", addressBook[index].number);
    }

    // ADDRESS
    if (field == 3)
    {
        char address[ADDRESS_SIZE];

        printf("Please input a new address\n");
        
        fgets(address, sizeof(address), stdin);

        strncpy(addressBook[index].address, address, sizeof(addressBook[index].address)-1);

        printf("Address updated to %s.\n", addressBook[index].address);
    }
    
    
    return;
}

int Delete(Contact *addressBook, int count, int capacity)
{
    int index = 0;

    printf("Input the index for the contact you wish to delete.\n");
    scanf("%d", &index);
    while (getchar() != '\n');

    index = index -1;

    if (index < 0 || index > count || addressBook[index].name[0] == '\0')
    {
        printf("Invalid index.\n");
        return count;
    }
    
    printf("%s has been removed.\n", addressBook[index].name);
    
    while (index < count)
    {
        if (index == capacity)
        {
            addressBook[index].name[0] = '\0';
        } else {
            addressBook[index] = addressBook[index + 1];
        }
        
        index = index + 1;
    }

    count = count - 1;

    return count;
}

int LoadContacts(Contact *addressBook, int capacity)
{
    FILE *fp = fopen(SAVE_FILE, "r");
    if (fp == NULL)
    {
        printf("No save file to read\n");
        // No saved data to load
        return 0;
    }

    int i = 0;
    int field = 1;
    bool endOfFile = false;

    while (!endOfFile || i < capacity)
    {
        if (field == 1)
        {
            char name[NAME_SIZE];
            if (fgets(name, sizeof(name), fp) == NULL)
            {
                endOfFile = true;
                break;
            }

            name[strcspn(name, "\n")] = '\0';
            strncpy(addressBook[i].name, name, sizeof name - 1);
            
            field = 2;
        }

        if (field == 2)
        {
            char number[NUMBER_SIZE];
            if (fgets(number, sizeof(number), fp) == NULL)
            {
                endOfFile = true;
                break;
            }

            number[strcspn(number, "\n")] = '\0';
            strncpy(addressBook[i].number, number, sizeof number - 1);
            
            field = 3;
        }

        if (field == 3)
        {
            char address[ADDRESS_SIZE];
            if (fgets(address, sizeof(address), fp) == NULL)
            {
                endOfFile = true;
                break;
            }

            address[strcspn(address, "\n")] = '\0';
            strncpy(addressBook[i].address, address, sizeof address - 1);
            
            field = 1;
            i = i +1;
        }
    }
    
    
    // while (fgets(line, sizeof line, fp) != NULL && i < capacity) {
    //     line[strcspn(line, "\n")] = '\0';
    //     strncpy(addressBook[i].name, line, sizeof line - 1);

    //     i = i + 1;
    // }

    fclose(fp);
    return i;
}

void SaveContacts(Contact *addressBook, int count)
{
    FILE *fp = fopen(SAVE_FILE, "w");
    if (fp == NULL)
    {
        // error
        perror("Error opening contacts.txt for save");
        return;
    }

    for(int i = 0; i < count; i++)
    {
        if (addressBook[i].name[0] != '\0')
        {
            if (fprintf(fp, "%s\n", addressBook[i].name) <  0)
            {
                perror("Error writing name to contacts.txt");
                return; 
            }
            if (fprintf(fp, "%s\n", addressBook[i].number) <  0)
            {
                perror("Error writing number to contacts.txt");
                return; 
            }
            if (fprintf(fp, "%s\n", addressBook[i].address) <  0)
            {
                perror("Error writing address to contacts.txt");
                return; 
            }
        }
    }

    fclose(fp);
    return;
}

int ResizeAddressbook(Contact **addressBook, int capacity)
{
    Contact *tmp = realloc(*addressBook, (capacity*2) * sizeof(Contact));
    if (tmp == NULL)
    {
        perror("Unable to allocate more memory");
        return capacity;
    }

    *addressBook = tmp;
    return (capacity*2);
}
