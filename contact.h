#ifndef CONTACT_H
#define CONTACT_H

typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;




typedef struct {
    Contact contacts[100];  //100 people, where each person has name + phone + email together.
    int contactCount; 
    
} AddressBook;

void createContact(AddressBook *addressBook);
void searchContact(AddressBook *addressBook);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook); 
void space(void);
int search_name(AddressBook *addressBook);
int search_phone(AddressBook *addressBook);
int search_email(AddressBook *addressBook);
int edit_name(AddressBook *addressBook,int);
int edit_phone(AddressBook *addressBook,int);
int edit_email(AddressBook *addressBook,int);




#endif
