#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NAME_SIZE 64
#define SAVE_FILE "contacts.txt"

typedef struct {
    char name[NAME_SIZE];
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
    count = LoadContacts(addressBook, capacity);

    int choice = 0;

    while (choice != 5) {
        printf("Cap check %d of %d", count, capacity);
        if (count == capacity)
        {
            capacity = ResizeAddressbook(&addressBook, capacity);
        }
        
        printf("Select an option:\n 1.Add\n 2.List\n 3.Delete\n 4.Edit\n 5.Exit\n\n");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');   // discard the rest of the bad line
            printf("Please enter a number.\n");
            continue;
        }

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

    if (count == capacity)
    {
        printf("Address book is full.\n");
        return count;
    }

    printf("Input name:\n");
    scanf("%63s", name);

    Contact c = { 0 };
    strncpy(c.name, name, sizeof(c.name) -1);

    addressBook[count] = c;

    return count + 1;
}

void List(Contact *addressBook, int count)
{
    printf("Contacts:\n");

    for(int i = 0; i < count; i++)
    {
        if (addressBook[i].name[0] != '\0')
        {
            printf("%d: %s\n", i+1, addressBook[i].name);
        }
    }

    return;
}

void Edit(Contact *addressBook, int count)
{
    int index = 0;
    char name[NAME_SIZE];

    printf("Input the index for the contact you wish to edit.\n");
    scanf("%d", &index);

    index = index -1;

    if (index < 0 || index >= count || addressBook[index].name[0] == '\0')
    {
        printf("Invalid index.\n");
        return;
    }

    printf("You have selected %s.\n", addressBook[index].name);
    printf("Input new name.\n");

    scanf("%63s", name);

    strncpy(addressBook[index].name, name, sizeof(addressBook[index].name)-1);

    printf("Name updated to %s.\n", addressBook[index].name);
    return;
}

int Delete(Contact *addressBook, int count, int capacity)
{
    int index = 0;

    printf("Input the index for the contact you wish to delete.\n");
    scanf("%d", &index);

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

    char line[NAME_SIZE];
    int i = 0;
    
    while (fgets(line, sizeof line, fp) != NULL && i < capacity) {
        printf("reading a line\n");
        printf("%d,%d\n", i, capacity);
        line[strcspn(line, "\n")] = '\0';
        strncpy(addressBook[i].name, line, sizeof line - 1);

        i = i + 1;
    }

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
                perror("Error writing line to contacts.txt");
                return; 
            }
        }
    }

    fclose(fp);
    return;
}

int ResizeAddressbook(Contact **addressBook, int capacity)
{
    printf("Resizing from %d to %d", capacity, capacity*2);
    Contact *tmp = realloc(*addressBook, (capacity*2) * sizeof(Contact));
    if (tmp == NULL)
    {
        perror("Unable to allocate more memory");
        return capacity;
    }

    *addressBook = tmp;
    return (capacity*2);
}
