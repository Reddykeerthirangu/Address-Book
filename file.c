#include <stdio.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("file.csv","w");//opening file in write mode
    if(fptr==NULL)
    {
        printf("File open failed\n");
        return;
    }
    printf("File opened successfully\n");
    //printing the contacts in file
    fprintf(fptr,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}

void loadContactsFromFile(AddressBook *addressBook) 
{
    FILE *fptr=fopen("file.csv","r");//opening file in read mode
    if(fptr==NULL)
    {
        printf("File open failed\n");
        return;
    }
    printf("File opened successfully\n");
    //reading the contacts from file
    fscanf(fptr,"#%d\n",&addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fscanf(fptr,"%[^,],%[^,],%[^\n]\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    fclose(fptr);
}