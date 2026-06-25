#ifndef CONTACT_H
    #define CONTACT_H
#endif

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