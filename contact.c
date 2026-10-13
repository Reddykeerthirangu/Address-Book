#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"

void listContacts(AddressBook *addressBook)
{
    Contact temp;
    //sorting the contacts 
    for(int i=0;i<addressBook->contactCount-1;i++)
    {
        for(int j=0;j<addressBook->contactCount-i-1;j++)
        {
            if(strcmp(addressBook->contacts[j].name,addressBook->contacts[j+1].name)>0)
            {
                temp=addressBook->contacts[j];
                addressBook->contacts[j]=addressBook->contacts[j + 1];
                addressBook->contacts[j+1]=temp;
            }
        }
    }
    //printing the contacts
    printf("\n---------------------------------------------------------------\n");
    printf("\n%-5s %-20s %-15s %-30s\n","S.No", "Name", "Phone Number", "Email ID");
    printf("\n---------------------------------------------------------------\n");
    for(int i=0;i<addressBook->contactCount;i++)
    {
        printf("%-5d %-20s %-15s %-30s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf("\n---------------------------------------------------------------\n");
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);//function call
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

int validate_name(char *str)
{
    for(int i=0;str[i];i++)
    {
        if(!((str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122) || str[i]==' ' || str[i]=='.'))
        {
            return 0;//invalid 
        }
    }
    return 1;//correct
}
int validate_phone(char *str)
{
    int len=strlen(str);
    if(len==10)
    {
        for(int i=0;str[i];i++)
        {
            if(!(str[i]>=48 && str[i]<=57))
            {
                return 0;//invalid 
            }
        }
    }
    else
    {
        return 0;//invalid 
    }
    return 1;//correct
}
int validate_mail(char mail[])
{
    int ind=-1;
    //checking first character is digit not  
    if(mail[0]>=48 && mail[0]<=57)
    {
        return 0;//invalid 
    }
    //checking mail consits of '@' or not  
    for(int i=0;mail[i]!='\0';i++)
    {
        if(mail[i]=='@')
        {
            ind=i;
            break;
        }
    }
    if(ind<=0)
    {
        return 0;//invalid 
    }
    //checking mail consists of character like upper,lower,digits abd space or not
    for(int i=0;i<ind;i++)
    {
        if(!((mail[i]>=65 && mail[i]<=90) || (mail[i]>=97 && mail[i]<=122) || (mail[i]>=48 && mail[i]<=57) || mail[i]=='_'))
        {
            return 0;//invalid 
        }
    }
    //checking mail consists of '.com' or not
    if(strstr(mail,".com")==NULL)
    {
        return 0;//invalid 
    }
    //checking between '@' and '.com' , weather the atleast one character is there or not 
    char *ptr=strstr(mail, ".com");
    if(ptr==NULL)
    {
        return 0;//invalid 
    }
    char *str2=strchr(mail, '@');

    if(str2==NULL)
    {
        return 0;//invalid 
    }
    if(ptr<=str2+1)
    {
        return 0;//invalid 
    }
    return 1;//correct
}
int phone_unique(AddressBook *addressBook, char phone[])
{
    //checking uniqueness of the phone
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,phone)==0)
        {
            return 0;   // already exists
        }
    }
    return 1;           // unique
}
int mail_unique(AddressBook *addressBook, char mail[])
{
    //checking uniqueness of the mail
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,mail)==0)
        {
            return 0;   // already exists
        }
    }
    return 1;           // unique
}
void createContact(AddressBook *addressBook)
{
    int res;
    char str1[30], str2[11], str3[30];
    do
    {
        printf("Enter the name :");
        scanf(" %[^\n]", str1);
        res=validate_name(str1);//validating name
        if(res==0)
        {
            printf("\n***    Invalid name    ***\n");
        }
    }while(res==0); // 0 means invalid
    do
    {
        printf("Enter the phone :");
        scanf(" %[^\n]",str2);
        res=validate_phone(str2);//validating phone number
        if(res==0)
        {
            printf("\n***   Invalid phone number   ***\n");
        }
        else if(phone_unique(addressBook, str2) == 0)
        {
            printf("\n***   Phone number already exists   ***\n");
            res=0;
        }
    } while (res==0);//0 means invalid
    do
    {
        printf("Enter the email :");
        scanf(" %[^\n]",str3);
        res=validate_mail(str3);//validating email id
        if(res==0)
        {
            printf("\n***   Invalid email   ***\n");
        }   
        else if(mail_unique(addressBook, str3) == 0)
        {
            printf("\n***   Email already exists   ***\n");
            res=0;
        }
    } while (res==0);//0 means invalid

    //copying the data to database
    int ind = addressBook->contactCount;
    strcpy(addressBook->contacts[ind].name, str1);
    strcpy(addressBook->contacts[ind].phone, str2);
    strcpy(addressBook->contacts[ind].email, str3);
    addressBook->contactCount++;
    printf("\n***   contact created successfully   ***\n");

}
int search_by_name(AddressBook *addressBook)
{
    char name[50];
    int ind=-1;
    int flag=0,count=0;
    printf("Enter name: ");
    scanf(" %[^\n]",name);
    printf("\n");
    // search the name from database using string compare(strcmp) 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].name, name)==0)
        {
            flag=1;
            printf("%d.",count+1);
            printf("Name : %s Phone : %s Email : %s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            ind=i;
            count++;
        }
    }
    if(count>1)
    {
        //If multiple names found search using phone number 
        ind=search_by_phone(addressBook);
    }
    if(flag==0)
    {
        printf("***   Contact not found   ***\n");
    }
    return ind;
}
int search_by_phone(AddressBook *addressBook)
{
    char phone[20];
    int ind=-1;
    printf("Enter phone: ");
    scanf(" %[^\n]",phone);
    printf("\n");
    // search the phone number from database using string compare(strcmp) 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone)==0)
        {
            printf("Name : %s Phone : %s Email : %s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            ind=i;
            return ind;
        }
    }
    printf("\n***   Contact not found   ***\n");
    return ind;
}
int search_by_mail(AddressBook *addressBook)
{
    char mail[50];
    int ind=-1;
    printf("Enter email: ");
    scanf(" %[^\n]", mail);
    printf("\n");
    // search the email id from database using string compare(strcmp) 
    for(int i=0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,mail)==0)
        {
            printf("Name : %s Phone : %s Email : %s\n", addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
            ind=i;
            return ind;
        }
    }
    printf("\n***   Contact not found   ***\n");
    return ind;
}
void searchContact(AddressBook *addressBook) 
{
    //searching based on name,phone,mail
    printf("\nSearch by\n1)Name\n2)phone\n3)Email\n");
    int ch;
    printf("\nEnter the choice: ");
    scanf("%d", &ch);
    switch(ch)
    {
        case 1:
            search_by_name(addressBook);
            break;
        case 2:
            search_by_phone(addressBook);
            break;
        case 3:
            search_by_mail(addressBook);
            break;
        case 4:
            return;
        default:
            printf("\n***   Invalid choice   ***\n");
    }

}
void edit_name(AddressBook *addressBook,int ind)
{
    //Editing based on name
    int res;
    char name[50];
    do
    {
        printf("Enter New Name: ");
        scanf(" %[^\n]",name);
        res=validate_name(name);// validating name
        if(res==0)
        {
            printf("\n***   Invalid name   ***\n");
        }
        else
        {
            //if name is correct, copy to database
            strcpy(addressBook->contacts[ind].name,name);
            printf("\n***   Successfully Edited Name    ***\n");
        }
    } while(res==0);//0 means invalid
}
void edit_phone(AddressBook *addressBook,int ind)
{
    //Editing based on phone number
    int res;
    char phone[11];
    do
    {
        printf("Enter New Phone: ");
        scanf(" %[^\n]",phone);
        res=validate_phone(phone);//validating phone
        if(res==0)
        {
            printf("\n***   invalid phone number   ***\n");
        }
        else if(phone_unique(addressBook, phone) == 0)//cheking the uniqueness of the correct phone number 
        {
            printf("\n***   Phone number already exists   ***\n");
        }
        else
        {
            strcpy(addressBook->contacts[ind].phone, phone);//copying to database
            printf("\n***   Successfully Edited Phone   ***\n");
        }
    } while(res==0);
}
void edit_mail(AddressBook *addressBook,int ind)
{
    //Editing based on mail
    int res;
    char mail[50];
    do
    {
        printf("Enter New Mail: ");
        scanf(" %[^\n]",mail);
        res=validate_mail(mail);//validating mail
        if(res==0)
        {
            printf("\n***   Invalid email   ***\n");
        }
        else if(mail_unique(addressBook, mail) == 0)//cheking the uniqueness of the correct mail
        {
            printf("\n***   mail already exists   ***\n");
        }
        else
        {
            strcpy(addressBook->contacts[ind].email,mail);//copying to database
            printf("\n***   Successfully Edited mail   ***\n");
        }
    } while(res==0);
}
void editContact(AddressBook *addressBook)
{
	//Editing based on name,phone number,mail
    printf("\nSearch by\n1)Name\n2)phone\n3)Email\n");
    int ch,ind=-1;
    printf("\nEnter the choice: ");
    scanf("%d", &ch);
    switch(ch)
    {
        case 1:
            ind=search_by_name(addressBook);
            break;
        case 2:
            ind=search_by_phone(addressBook);
            break;
        case 3:
            ind=search_by_mail(addressBook);
            break;
        case 4:
            return;
        default:
            printf("\n***   Invalid choice   ***\n");
    }
    if(ind==-1)
    {
        return;
    }
    //Editing based on name,phone,mail
    printf("\nEnter the field to edit\n");
    printf("\n1)Name\n2)Phone\n3)Email\n");
    int choice;
    printf("\nEnter the choice\n");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            edit_name(addressBook,ind);
            break;
        case 2:
            edit_phone(addressBook,ind);
            break;
        case 3:
            edit_mail(addressBook,ind);
            break;
        default:
            printf("\n***   Invalid choice   ***\n");
    }
}

void deleteContact(AddressBook *addressBook)
{
	//Editing based on name,phone,mail
    printf("\nSearch by\n1)Name\n2)phone\n3)Email\n");
    int ch,ind=-1;
    printf("\nEnter the choice: ");
    scanf("%d", &ch);
    switch(ch)
    {
        case 1:
            ind=search_by_name(addressBook);
            break;
        case 2:
            ind=search_by_phone(addressBook);
            break;
        case 3:
            ind=search_by_mail(addressBook);
            break;
        case 4:
            return;
        default:
            printf("\n***   Invalid choice   ***\n");
    }
    if(ind==-1)
    {
        printf("\n*** No contact found to delete   ***\n");
        return;
    }
    //shifting the contacts
    for(int i=ind;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
    }
    addressBook->contactCount--;//decrementing count
    printf("\n***   Contact deleted successfully   ***\n");
}
