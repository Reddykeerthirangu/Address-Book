#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount; 
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

int validate_name(char *str);
int validate_phone(char *str);
int validate_mail(char mail[]);
int phone_unique(AddressBook *addressBook, char phone[]);
int mail_unique(AddressBook *addressBook, char mail[]);
int search_by_name(AddressBook *addressBook);
int search_by_phone(AddressBook *addressBook);
int search_by_mail(AddressBook *addressBook);
void edit_name(AddressBook *addressBook,int ind);
void edit_phone(AddressBook *addressBook,int ind);
void edit_mail(AddressBook *addressBook,int ind);
void saveContactsToFile(AddressBook *addressBook);
void saveAndExit(AddressBook *addressBook);

#endif
