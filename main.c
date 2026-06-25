#include "contact.h"
#include <stdio.h>
#include <stdlib.h>

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
