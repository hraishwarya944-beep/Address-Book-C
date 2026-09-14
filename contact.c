#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#define RED   "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
//#include "populate.h"
void space()
{
    int i = 0;
    printf(BLUE);
    while(i<=70)
    {
        putchar('-');
        i++;
    }
    printf(RESET"\n");
    
}

void listContacts(AddressBook *addressBook) 
{
    int i = 0,j = 0,n;
    Contact temp;
    
    for(i = 0 ;i < addressBook->contactCount-1;i++)
    {
        for(j = 0;j < addressBook->contactCount-1-i;j++)
        {
            n = strcasecmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name);
            
                if(n > 0)
                {
                    temp=addressBook->contacts[j];
                    addressBook->contacts[j] =addressBook->contacts[j+1];
                    addressBook->contacts[j+1] =temp;
                }
                
            
        }
    }
    
    // Sort contacts based on the chosen criteria
    space();
    printf("%-6s %-20s %-15s %-30s\n","Sl.No","Name","Mobile nmb","Email-ID");
    space();
    
    for(i = 0; i < (addressBook->contactCount);i++)
    {
        printf("%-6d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    space();
    if(addressBook->contactCount > 0)
    {
        printf(GREEN"Contacts are listed.\n"RESET);
    }

    
}

void initialize(AddressBook *addressBook) {
    //addressBook->contactCount = 0;
    //populateAddressBook(addressBook);// me
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}


void saveAndExit(AddressBook *addressBook) {

    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS);
}



int validate_name(char *name)
{
    int i = 0;
    while(name[i] != '\0')
    {
        if(!((name[i] >= 'A' && name[i] <= 'Z') || (name[i] >= 'a' && name[i] <= 'z')||(name[i] == '.') || (name[i] == ' ')))
        {
            printf(RED "Entered Invalid name\n" RESET);
            return 0; // invalid
        }
        
        i++;
    }
    return 1;


    
}

int validate_phone(char *mobile, AddressBook *addressBook)
{
    if (mobile == NULL || mobile[0] == '\0')  // Empty mobile checking
        return 0;
    
    int mob_len = strlen(mobile);
    if(mob_len != 10)
    {
        printf(RED "Enter valid number with exact 10 digit\n " RESET);
        return 0; // invalid
    }
    int i;
    for(i = 0; i < (addressBook->contactCount);i++)   // checking duplicate
    {
       if(strcmp(addressBook->contacts[i].phone,mobile) == 0)
       {
            printf(RED "Duplicate number entered\n" RESET);
            return 0; //invalid
       }
       
    }
    
    i = 0;    // checking the mobile b/w 0 to 9 digit
    while(mobile[i] != '\0')
    {
        if(mobile[i] < '0' || mobile[i] > '9')
        {
            printf(RED "Phone number should contain only digits\n"RESET);
            return 0;//invalid
        }
        i++;
    }

    
    return 1; // valid
}

int validate_mail(char *mail,AddressBook *addressBook)
{
     int i = 0;
     if(mail[0] < 'a' || mail[0] > 'z')
     {
        
        return 0; // invalid
     }
     int n = strlen(mail);
     if(n < 7)   // 7 = a@b.com must be there so(validation checking)
     {
        printf(RED "Entered Ivalid Email\n"RESET);
        return 0;
     }
     for(i = 0; i < (addressBook->contactCount);i++)   // checking duplicate
    {
       if(strcasecmp(addressBook->contacts[i].email,mail) == 0)
       {
            printf(RED "Duplicate email id is entered\n"RESET);
            return 0;
       }
       
    }
     char *ptr = &mail[n-4];  // ex if n = 2, 2-4 = -2 -> &mail[-4] --> invalid
     char *sptr = strstr(mail,".com");  // if .com present in mail then it will return substrimg add else it will return NULL
     char *at_add = NULL;
     int at = 0;
     if(sptr == NULL)
     {
        return 0;
     }
     if(strcmp(ptr,sptr) != 0)
     {
        return 0;
     }
     for(i = 0;i < n;i++)
     {
        
            if(mail[i] == '@')
            {
                at_add = &mail[i];

                at++;
                
            }
            
     } 
    if(at_add == NULL)  // if @ not present in mail at_add become NULL(intitlized value), it leads to segmentation fault
    {
        printf(RED "Entered Ivalid Email\n"RESET);
        return 0;
    }
    if(at != 1)
    {
        printf(RED"Entered Ivalid Email\n"RESET);
        return 0;
    }
    if(*(at_add+1) == '.')   // if(mail[at_add+1] != '.')
    {
        printf(RED "Entered Ivalid Email\n"RESET);
        return 0;
    }
        
       
    
     return 1;
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

    char name[20];
    int valid;

    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        valid = validate_name(name);
        if(valid == 1)// valid
            break;
    }

    char mobile[11];

    while(1)
    {
        printf("Enter the phone : ");
        scanf(" %[^\n]", mobile);

        valid = validate_phone(mobile,addressBook);
        if(valid == 1)// valid
            break;
    }


    char mail[30];

    while(1)
    {
        printf("Enter the mail : ");
        scanf(" %[^\n]", mail);
        
        valid = validate_mail(mail,addressBook);
        
        if(valid == 1) //valide
            break;
        
        
       
    }
    strcpy(addressBook->contacts[addressBook->contactCount].name, name);

    strcpy(addressBook->contacts[addressBook->contactCount].phone, mobile);

    strcpy(addressBook->contacts[addressBook->contactCount].email, mail);



    addressBook->contactCount++;

    
}
int search_name(AddressBook *addressBook)
{
    char name[100];
    int count = 0,i,ind;
    while(1)
    {
        printf("Enter the name: ");
        scanf(" %[^\n]",name);
        space();
        printf("%-6s %-20s %-15s %-30s\n","Sl.No","Name","Mobile nmb","Email-ID");
        space();
        for(i = 0; i < (addressBook->contactCount);i++)
        {
            if(strcasecmp(addressBook->contacts[i].name,name) == 0)
            {
                printf("%-6d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                count++;
                ind = i;

            }
        }
        space();
        if(count == 0)
        {
            printf(RED"Contact not found\n"RESET);
            return -1;
        }
        else if(count == 1)
        {
            return ind;
        }
        else if(count > 1)
        {
            return search_phone(addressBook);
        }
        
        
            

    }
    
    

}

int search_phone(AddressBook *addressBook)
{
    char phone[11];
    int count = 0,i;
    printf("Enter the phone number to search :");
    scanf(" %[^\n]",phone);
    for(i = 0;i < (addressBook->contactCount);i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone) == 0)
        {
            space();
            printf("%-6s %-20s %-15s %-30s\n","Sl.No","Name","Mobile nmb","Email-ID");
            space();
            printf("Selected contact is :\n%-6d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            space();
            count++;
            return i;
            
        }
    }
    if(count == 0)
    {
        printf(RED "Contact not found\n" RESET);
        return -1;
    }
    

}
int search_email(AddressBook *addressBook)
{
    char email[100];
    int count = 0,i;
    printf("Enter the email to search :");
    scanf(" %[^\n]",email);
    for(i = 0;i < (addressBook->contactCount);i++)
    {
        if(strcmp(addressBook->contacts[i].email,email) == 0)
        {
            space();
            printf("%-6s %-20s %-15s %-30s\n","Sl.No","Name","Mobile nmb","Email-ID");
            space();
            printf("Selected contact is :\n%-6d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            space();
            count++;
            return i;
            
        }
    }
    if(count == 0)
    {
        printf(RED "Contact not found\n"RESET);
        return -1;
    }
    

}
void searchContact(AddressBook *addressBook) 

{
    int sel,res;
    printf("Select the option to search : ");
    printf("\n");
    printf(YELLOW"1.Name\n2.Phone\n3.Email\n"RESET);
    scanf("%d",&sel);
    switch(sel)
    {
        case 1: res = search_name(addressBook);
                break;
        case 2: res = search_phone(addressBook);
                break;
        case 3: res = search_email(addressBook);
                break;
        default : printf("Invalid input\n");
    }
}

void editContact(AddressBook *addressBook)
{
    /* Define the logic for Editcontact */
    int search_choice;
    int edit_choice;
    printf("Select the option to search the contact to edit :");
    printf(YELLOW"\n1.Name\n2.Phone\n3.Email\n"RESET);
    scanf("%d",&search_choice);
    

    int res;

    switch(search_choice)
    {
        case 1:
            res = search_name(addressBook);
            break;
        case 2: 
            res = search_phone(addressBook);
            break;
        case 3: 
            res = search_email(addressBook);
            break;
        default :
            printf("Invalid input\n");
    }


    printf("Select the option to edit :");
    printf(YELLOW"\n1.Name\n2.Phone\n3.Email\n"RESET);
    scanf("%d",&edit_choice);

    switch(edit_choice)
    {
        case 1:
            edit_name(addressBook, res);
            break;
        case 2: 
            edit_phone(addressBook, res);
            break;
        case 3: 
            edit_email(addressBook, res);
            break;
        default :
            printf("Invalid input\n");
    }

    
}
int edit_name(AddressBook *addressBook,int res)
{
    int valid;
    char name[20];
    while(1)
    {
        printf("Enter the name : ");
        scanf(" %[^\n]", name);

        valid = validate_name(name);
        if(valid == 1)// valid
            break;
    }

    strcpy(addressBook->contacts[res].name, name);
    
     

}
int edit_phone(AddressBook *addressBook,int res)
{
    int valid;
    char phone[20];
    while(1)
    {
        printf("Enter the phone : ");
        scanf(" %[^\n]", phone);

        valid = validate_phone(phone,addressBook);
        if(valid == 1)// valid
            break;
    }

    strcpy(addressBook->contacts[res].phone, phone);
    
     

}
int edit_email(AddressBook *addressBook,int res)
{
    int valid;
    char email[20];
    while(1)
    {
        printf("Enter the email : ");
        scanf(" %[^\n]", email);

        valid = validate_mail(email,addressBook);
        if(valid == 1)// valid
            break;
    }

    strcpy(addressBook->contacts[res].email, email);
    
     

}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int search_choice;
    
    printf("Select the option to search the contact to delet :");
    printf(YELLOW"\n1.Name\n2.Phone\n3.Email\n"RESET);
    scanf("%d",&search_choice);
    

    int res,i;

    switch(search_choice)
    {
        case 1:
            res = search_name(addressBook);
            break;
        case 2: 
            res = search_phone(addressBook);
            break;
        case 3: 
            res = search_email(addressBook);
            break;
        default :
            printf("Invalid input\n");
    }
    for(i = res; i < (addressBook->contactCount);i++)
    {
        addressBook->contacts[i] = addressBook->contacts[i+1];
    }
    addressBook->contactCount--;
    printf(GREEN"Successfully deletd\n"RESET);


   
}
