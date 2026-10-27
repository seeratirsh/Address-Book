#include "addressbook.h"

/* creating a function to valide phone number*/
int validate_phone(char *phone)
{
    /*
    Returning 0 if validation is passed, -1 if it is invalid.
     * Required format: +91 followed by exactly 10 digits
     * Example: +918765989037
    */
    int length = strlen(phone);

     /*
    Checking for the length of a number including country code.
    Total length must be 13: +, 9, 1 and 10 digits phone number.
    */

    if(length != 13)
    {
        printf("**ERROR**\nNumber must start with +91 and should have exactly 10 digits number.\nExample: +918765989037\n");
        return -1;
    }
    /*
    Country code is mandatory.
    strncmp compares n characters of two string
    using strncmp to check if +91 is not present 
    return -1.
    */
   if(strncmp(phone, "+91", 3) != 0)
   {
      printf("**ERROR**\nNumber must start with +91\n");
      return -1;
   }
    /*
    Function is present in <ctype.h> library
    Using a library function isdigit to check weather a
    character is a digit from 0 to 9 or not
    */ 
    for(int i = 3; i < length; i++)
    {
        if(!isdigit(phone[i]))
        {
            printf("**ERROR**\nAfter +91, only digits are allowed.\n");
            return -1;
        }
    }

    /*
    Indian phone numbers start from 6, 7, 8 or 9
    if 0th index number is smaller than 6 return -1
    means invalid
    */

    if(phone[3] < '6' || phone[3] > '9')
    {
        printf("**ERROR**\nNumber must start with 6, 7, 8 or 9 after +91.\n");
        return -1;
    }

    /*
    returning zero if validation is passed
    */
    return 0;
}

// create duplicate number validation

int duplicate_Phone_validation(char * temp_phone, struct AddressBook *addressBook)
{
    /*
    if duplicate contact is found return 1;
    use strcmp to compare contact already present in the structure with the contact which user is entering
    */
      
        for(int j = 0; j < addressBook->contactCount; j++)
        {
           if(strcmp(addressBook->contacts[j].phone, temp_phone) == 0)
           {
            printf("Duplicate contact found\n");
            printf("Enter a new contact number\n");
            return 1;
           }
        }

    return 0; // no duplicate found
}

int validate_email(char * email)
{
    int length = strlen(email);
    /*
    Returns 0 if valid, -1 if invalid.
    Email cannot start with spaces or any special character.
    */
   /*If length is zero
   return -1*/
   if(length == 0)
   {
      printf("**ERROR**\nEmail should not be empty.\n");
      return -1;
   }
   /*
   Email cannot start with a space or special character
   Checking zeroth index of the email
   if is not between a to z and A to Z then 
   return -1 means invalid.
   */
   if(!((email[0] >= 'a' && email[0] <= 'z') || (email[0] >= 'A' && email[0] <= 'Z')))
   {
      printf("**ERROR**\nEmail should start with an alphabet.\n");
      return -1;
   }
   /*
   Emeil should contain only one @ 
   using count to keep track of @ and ath_index to keep track of it's index
   later to compare ath_index with dot_index
   Email should contain a dot after @ and alphabets
   using dot_found to find the . and dot_index to keep the track of . as it should 
   be present after the @ only
   */
   int i = 0;
   int count = 0;
   int dot_found = 0;
   int ath_index = 0;
   int dot_index = 0;

   /* Count '@' and remember the 
   position of '@' and the last '.' */
   while(email[i] != '\0')
   {
     if(email[i] == '@')
     {
        count++;
        ath_index = i;
     }

    if(email[i] == '.')
    {
       dot_found = 1;
       dot_index = i;
    }
     
     i++;
   }

    /* Exactly one '@' */
   if(count != 1)
   {
        printf("**ERROR**\nEmail must exactly contain one @\n");
        return -1;
   }

    /* A dot must exist after '@' */
   if(dot_found == 0 || ath_index >= dot_index)
   {
        printf("**ERROR**\nDot must be present after @\n");
        return -1;
   }

   /* Domain name must exist between '@' and the dot */
    if (dot_index == ath_index + 1)
    {
        printf("**ERROR**\nThe domain name is missing after @\n");
        return -1;
    }

    /* Something must exist after the last dot */
    if (dot_index == length - 1)
    {
        printf("**ERROR**\nEmail must have an extension after the dot\n");
        return -1;
    }

    return 0;
}

int unique_email_validation(char *temp_email, struct AddressBook *addressBook)
{
    
    for(int j = 0; j < addressBook->contactCount; j++)
    {
        if(strcmp(addressBook->contacts[j].email, temp_email) == 0)
        {
           printf("Duplicate Email found\n");
           printf("Enter a new Email\n");
           return 1;
        }
    }

    return 0; // no duplicate found
}


void add_contact(struct AddressBook *addressBook)
{
    char temp_phone[15];
    char temp_email[50];
    // contactcount willkeep the count of the 100 contacts
    int i = addressBook->contactCount;
    // read name from the user
    printf("Name\n");
    // getchar();
    scanf(" %[^\n]", addressBook->contacts[i].name);

    /*
    Reading phone number into the temporary string, 
    validating it using the phone_validation function
    if it returns 0 means number is valid and can be coppied into the original 
    structure member of addressBook
    if it returns -1, it will ask user to again enter number.
    Repeat the same until it is validated.
    */ 
    // getchar();

    /* Keep asking until the phone is valid
     and not a duplicate */
    do
    {
        printf("📞Phone \n");
        scanf(" %[^\n]",temp_phone);
    } 
    while (validate_phone(temp_phone) != 0 || duplicate_Phone_validation(temp_phone, addressBook) != 0);/*If validate phone number return 0 means I can copy the temp phone into the real structure*/
    strcpy(addressBook->contacts[i].phone, temp_phone);
    /*
    Reading email into the temp_email string,
    validating email by using email_validation function
    if it returns 0 means email is validated and can be coppied into the
    structure of email
    if it is invalid it will return -1, and will ask user to enter the email again.
    Repeat the same until it is validated.
    */
    
    /* Keep asking until the email is valid
     and unique */
    do
    {
        printf("📧Email\n");
        scanf(" %[^\n]", temp_email);   
    } 
    while (validate_email(temp_email) != 0 || unique_email_validation(temp_email, addressBook) != 0);
    strcpy(addressBook->contacts[i].email, temp_email);
    
    addressBook->contactCount++;
}

void search_contact(struct AddressBook *addressBook)
{
    char name_search[50];
    char phone_search[15];
    char email_search[50];

    int choice;
    printf("---------------------------------------\n");
    printf("\n------Enter the choice for which you want to search by: -----\n");
    printf("1. Name:\n2. Phone NUmber:\n3. Email ID:\n");
    scanf(" %d", &choice);

    if(choice == 1)
    {
        printf("Enter the name:\n");
        scanf(" %[^\n]", name_search);
    }

    else if(choice == 2)
    {
        printf("Enter the phone number:\n");
        scanf(" %[^\n]", phone_search);
    }

    else if(choice == 3)
    {
        printf("Enter the email:\n");
        scanf(" %[^\n]", email_search);
    }

    addressBook->ir_size = 0;

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        int found = 0;

        if(choice == 1 && strcmp(addressBook->contacts[i].name, name_search) == 0)
        {
            found = 1;
        }

        else if(choice == 2 && strcmp(addressBook->contacts[i].phone, phone_search) == 0)
        {
            found = 1;
        }

        else if(choice == 3 && strcmp(addressBook->contacts[i].email, email_search) == 0)
        {
            found = 1;
        }

        if(found == 1)
        {
            addressBook->index_record[addressBook->ir_size] = i;
            addressBook->ir_size++;

             printf("\nName: %s\n", addressBook->contacts[i].name);
             printf("Phone Number: %s\n", addressBook->contacts[i].phone);
             printf("Email ID: %s\n", addressBook->contacts[i].email);
        }

    }


    if( addressBook->ir_size == 0 )
    {
       printf("Contact not found\n");
    }

       printf("---------------------------------------\n");

    /*
    a)Initilize ir_size as 0 outside of the loopso, that it reset's before searching
    b)Also check with the choice entered by the user that name entered and alredy saved are
    same or not if they are same make the flag as 1 if not flag as 0;
    c) Repeat the same for phone and email also
    d) If flag is 1 store the index_record with the actual index of structure addressBookand then print everything
    */
    
    /*if( addressBook->ir_size == 0 )
	printf("Contact not found\n");
    else
    {
	 Print the searched contacts
    }*/

}
void edit_contact(struct AddressBook *addressBook)
{
    int choice;
    int index;
    int serial_num;
    char temp_name[50];
    char temp_phone[15];
    char temp_email[50];

   /*calling the search function*/
   search_contact(addressBook);

   /*Check whether any contact was found
   if not return;
   Nothing found, nothing to edit
   */
   if(addressBook->ir_size == 0)
   {
    return;
   }

   /* One match: use it. 
   Several matches: let the user pick. */

   if(addressBook->ir_size == 1)
   {
     index = addressBook->index_record[0];
   }
   else
   {
     printf("Multiple contacts found:\n");
     for(int i = 0; i < addressBook->ir_size; i++)
     {
        int ind = addressBook->index_record[i];
        printf("%d. %s | %s | %s\n", i + 1, 
            addressBook->contacts[ind].name, 
            addressBook->contacts[ind].phone, 
            addressBook->contacts[ind].email);
     }

     printf("Enter the serial number of the contact to edit: ");
     if(scanf(" %d", &serial_num) != 1)
     {
        printf("Invalid input\n");
        return;
     }
     if(serial_num < 1 || serial_num > addressBook->ir_size)
     {
         printf("Invalid serial number\n");
        return;
     }
     
    index = addressBook->index_record[serial_num - 1];

   }

    printf("Which field do you want to edit?\n");
    printf("1. Name\n");
    printf("2. Phone number\n");
    printf("3. Email ID\n");
    printf("Enter your choice: ");

    if (scanf(" %d", &choice) != 1)
    {
        printf("Invalid input\n");
        return;
    }


   if(choice == 1)
   {
    printf("Enter new name:\n");
    scanf(" %[^\n]", temp_name);

    strcpy(addressBook->contacts[index].name, temp_name);
    printf("Name updated successfully\n");
   }

   else if(choice == 2)
   {
     do
     {
        printf("Enter new phone number: ");
        scanf(" %[^\n]", temp_phone);
     }
    while(validate_phone(temp_phone) != 0 || duplicate_Phone_validation(temp_phone, addressBook) != 0);
    strcpy(addressBook->contacts[index].phone, temp_phone);
    printf("Phone number updated successfully\n");
     
   }

   else if(choice == 3)
   {
     do
     {
        printf("Enter new email ID: ");
        scanf(" %[^\n]", temp_email);
     }
     while(validate_email(temp_email) != 0 || unique_email_validation(temp_email, addressBook) != 0);
     strcpy(addressBook->contacts[index].email, temp_email);
     printf("Email updated successfully\n");
   }
   else
   {
      printf("Invalid choice\n");
   }
/*
Algorithm: edit_contact

Start
a)Declare choice, index, serial_num, temp_name[50], temp_phone[15], temp_email[50].
b)Call search_contact(addressBook). It fills index_record[] and sets ir_size.
c)If ir_size == 0, return, because there is nothing to edit.
d)Decide which contact to edit:
e)If ir_size == 1, set index = index_record[0].
Otherwise:
f)Print “Multiple contacts found”.
g)For i = 0 to ir_size - 1, print serial number i + 1 with the name, phone and email at index_record[i].
h)Read serial_num. If the read fails, print “Invalid input” and return.
i)If serial_num < 1 or serial_num > ir_size, print “Invalid serial number” and return.
j)Set index = index_record[serial_num - 1].
k)Print the field menu (1. Name, 2. Phone number, 3. Email ID) and read choice. If the read fails, print “Invalid input” and return.
l)Based on choice:
1 (Name): read temp_name, copy it to contacts[index].name, print a success message.
2 (Phone):
Repeat: read temp_phone.
Until validate_phone returns 0 and duplicate_Phone_validation returns 0.
Copy temp_phone to contacts[index].phone and print a success message.
3 (Email):
Repeat: read temp_email.
Until validate_email returns 0 and unique_email_validation returns 0.
Copy temp_email to contacts[index].email and print a success message.
Otherwise: print “Invalid choice”.
END
*/
}
void delete_contact(struct AddressBook *addressBook)
{

}
void list_contacts(struct AddressBook *addressBook)
{
    if(addressBook->contactCount == 0)
    {
        printf("No contact found\n");
        printf("X----------------------X\n");
        return;
    }
    /*
    Displaying the contacts
    */
   for(int i = 0; i < addressBook->contactCount; i++)
   {
      printf("------------------------------------------------\n");
      printf("Name: %s\n", addressBook->contacts[i].name);
      printf("Phone Number: %s\n", addressBook->contacts[i].phone);
      printf("Email ID: %s\n", addressBook->contacts[i].email);
      printf("------------------------------------------------\n");
   }
}


