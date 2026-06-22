#include <stdio.h>
#include <string.h>

#define MAX_CONTACTS 3
#define NAME_SIZE 64

typedef struct {
    char name[NAME_SIZE];
} Contact;

void Add(Contact addressBook[]);
void List(Contact addressBook[]);
void Edit(Contact addressBook[]);
void Delete(Contact addressBook[]);
int GetNextSpace(Contact addressBook[]);

int main(void) {
    printf("Address book starting up.\n");
    int choice = 0;
    Contact addressBook[MAX_CONTACTS] = {0};

    while (choice != 5) {
        printf("Select an option:\n 1.Add\n 2.List\n 3.Delete\n 4.Edit\n 5.Exit\n\n");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');   // discard the rest of the bad line
            printf("Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                Add(addressBook);
                break;

            case 2:
                List(addressBook);
                break;

            case 3:
                Delete(addressBook);
                break;

            case 4:
                Edit(addressBook);
                break;
        }
        
    }

    return 0;
}

void Add(Contact addressBook[]) 
{
    char name[NAME_SIZE];
    int nextSpace = GetNextSpace(addressBook);

    if (nextSpace == -1)
    {
        printf("Address book is full.\n");
        return;
    }

    printf("Input name:\n");
    scanf("%63s", name);

    Contact c = { 0 };
    strncpy(c.name, name, sizeof(c.name) -1);

    addressBook[nextSpace] = c;

    return;
}

void List(Contact addressBook[])
{
    printf("Contacts:\n");

    for(int i = 0; i < MAX_CONTACTS; i++)
    {
        if (addressBook[i].name[0] != '\0')
        {
            printf("%d: %s\n", i+1, addressBook[i].name);
        }
    }

    return;
}

void Edit(Contact addressBook[])
{
    int index = 0;
    char name[NAME_SIZE];

    printf("Input the index for the contact you wish to edit.\n");
    scanf("%d", &index);

    index = index -1;

    if (index < 0 || index >= MAX_CONTACTS || addressBook[index].name[0] == '\0')
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

void Delete(Contact addressBook[])
{
    int index = 0;

    printf("Input the index for the contact you wish to delete.\n");
    scanf("%d", &index);

    index = index -1;

    if (index < 0 || index >= MAX_CONTACTS || addressBook[index].name[0] == '\0')
    {
        printf("Invalid index.\n");
        return;
    }
    
    printf("%s has been removed.\n", addressBook[index].name);

    addressBook[index].name[0] = '\0';

    return;
}

int GetNextSpace(Contact addressBook[])
{
    for(int i = 0; i < MAX_CONTACTS; i++)
    {
        if (addressBook[i].name[0] == '\0')
        {
            return i;
        }
    }

    return -1;
}