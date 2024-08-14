#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct
{
    char username[50];
    char password[20];
    int date, month, year;
    char phoneNum[15];
    char ssNum[20];
    char fName[20];
    char lName[20];
    char fatherName[50];
    char motherName[50];
    char address[100];
    char accType[20];
    float balance = 0;
} user;

#endif
