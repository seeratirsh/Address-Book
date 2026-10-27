#ifndef CONTACT_H
#define CONTACT_H
#include<stdio.h>
#include <string.h>
#include <ctype.h>


struct Contact{
    char name[50];
    char phone[15];
    char email[50];
};

struct AddressBook {
    struct Contact contacts[100];
    int contactCount;
    int index_record[100];
    int ir_size;
};

int validate_phone(char * phone);
int duplicate_Phone_validation(char * temp_phone, struct AddressBook *addressBook);
int validate_email(char *email);
int unique_email_validation(char *temp_emal, struct AddressBook *addressBook);
void add_contact(struct AddressBook *addressBook);
void search_contact(struct AddressBook *addressBook);
void edit_contact(struct AddressBook *addressBook);
void delete_contact(struct AddressBook *addressBook);
void list_contacts(struct AddressBook *addressBook);

#endif
