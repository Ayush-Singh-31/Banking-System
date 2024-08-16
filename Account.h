#ifndef ACCOUNT_H
#define ACCOUNT_H

// Structure to hold user account information
typedef struct
{
    char username[50];   // Username of the account holder
    char password[20];   // Password for the account
    int date;            // Day of birth
    int month;           // Month of birth
    int year;            // Year of birth
    char phoneNum[15];   // Phone number of the account holder
    char ssNum[20];      // Social Security Number
    char fName[20];      // First name of the account holder
    char lName[20];      // Last name of the account holder
    char fatherName[50]; // Father's name
    char motherName[50]; // Mother's name
    char address[100];   // Address of the account holder
    char accType[20];    // Type of account (e.g., savings, checking)
    float balance;       // Current balance in the account
} user;

#endif