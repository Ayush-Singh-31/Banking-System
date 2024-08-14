#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "Account.h"

char getch()
{
    char ch;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

void account()
{
    user u1;
    FILE *fp;
    char filename[60];

    printf("\n\n!!!!!CREATE ACCOUNT!!!!!");

    printf("\n\nEnter username: ");
    fgets(u1.username, sizeof(u1.username), stdin);
    u1.username[strcspn(u1.username, "\n")] = '\0';

    snprintf(filename, sizeof(filename), "%s.txt", u1.username);
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char ch;
    int i = 0;
    int passLenght = 20;
    printf("\n\nPASSWORD can be of length 8 - 20. How long is your password? ");
    scanf("%d", &passLenght);
    while (passLenght < 8 || passLenght > 20)
    {
        printf("\n\nPassword length should be between 8 and 20. Please enter again: ");
        scanf("%d", &passLenght);
    }
    getchar();
    printf("\n\nPASSWORD: ");
    for (i = 0; i < passLenght; i++)
    {
        ch = getch();
        if (ch == 13)
            break;
        u1.password[i] = ch;
        printf("*");
    }
    u1.password[i] = '\0';

    printf("\n\nFIRST NAME: ");
    fgets(u1.fName, sizeof(u1.fName), stdin);
    u1.fName[strcspn(u1.fName, "\n")] = '\0';

    printf("\n\nLAST NAME: ");
    fgets(u1.lName, sizeof(u1.lName), stdin);
    u1.lName[strcspn(u1.lName, "\n")] = '\0';

    printf("\n\nFATHER's NAME: ");
    fgets(u1.fatherName, sizeof(u1.fatherName), stdin);
    u1.fatherName[strcspn(u1.fatherName, "\n")] = '\0';

    printf("\n\nMOTHER's NAME: ");
    fgets(u1.motherName, sizeof(u1.motherName), stdin);
    u1.motherName[strcspn(u1.motherName, "\n")] = '\0';

    printf("\n\nADDRESS: ");
    fgets(u1.address, sizeof(u1.address), stdin);
    u1.address[strcspn(u1.address, "\n")] = '\0';

    printf("\n\nPHONE NUMBER: ");
    fgets(u1.phoneNum, sizeof(u1.phoneNum), stdin);
    u1.phoneNum[strcspn(u1.phoneNum, "\n")] = '\0';

    printf("\n\nSOCIAL SECURITY NUMBER: ");
    fgets(u1.ssNum, sizeof(u1.ssNum), stdin);
    u1.ssNum[strcspn(u1.ssNum, "\n")] = '\0';

    printf("\n\nDAY OF BIRTH: ");
    scanf("%d", &u1.date);
    getchar();

    printf("\n\nMONTH OF BIRTH: ");
    scanf("%d", &u1.month);
    getchar();

    printf("\n\nYEAR OF BIRTH: ");
    scanf("%d", &u1.year);
    getchar();

    u1.balance = 0;

    fprintf(fp, "Username: %s\n", u1.username);
    fprintf(fp, "Password: %s\n", u1.password);
    fprintf(fp, "First Name: %s\n", u1.fName);
    fprintf(fp, "Last Name: %s\n", u1.lName);
    fprintf(fp, "Father's Name: %s\n", u1.fatherName);
    fprintf(fp, "Mother's Name: %s\n", u1.motherName);
    fprintf(fp, "Address: %s\n", u1.address);
    fprintf(fp, "Phone Number: %s\n", u1.phoneNum);
    fprintf(fp, "Social Security Number: %s\n", u1.ssNum);
    fprintf(fp, "Date of Birth: %d/%d/%d\n", u1.date, u1.month, u1.year);
    fprintf(fp, "Balance: $%.2f\n", u1.balance);
    fclose(fp);
}

void checkBalance(user u)
{
    printf("\n\nYour current balance is: $%.2f\n", u.balance);
}

void deposit(user *u)
{
    FILE *fp;
    char filename[60];
    float amount;

    printf("\n\nEnter the amount to deposit: $");
    scanf("%f", &amount);
    getchar();

    // Calculate new balance
    float new_balance = u->balance + amount;

    // Update the balance in the file
    snprintf(filename, sizeof(filename), "%s.txt", u->username);
    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    long int position;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strstr(line, "Balance: $") != NULL)
        {
            position = ftell(fp);
            fseek(fp, position - strlen(line), SEEK_SET);
            fprintf(fp, "Balance: $%.2f\n", new_balance);
            break;
        }
    }
    fclose(fp);

    // Update the balance in the struct
    u->balance = new_balance;

    // Log the transaction
    snprintf(filename, sizeof(filename), "%slog.txt", u->username);
    fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening log file!\n");
        return;
    }
    fprintf(fp, "Deposited $%.2f\n", amount);
    fclose(fp);

    printf("\n\nDeposit successful! New balance: $%.2f\n", u->balance);
}

void withdraw(user *u)
{
    FILE *fp;
    char filename[60];
    float amount;

    printf("\n\nEnter the amount to withdraw: $");
    scanf("%f", &amount);
    getchar();

    // Check if the user has enough balance to withdraw
    if (amount > u->balance)
    {
        printf("\n\nInsufficient balance! Your current balance is $%.2f\n", u->balance);
        return;
    }

    // Calculate the new balance
    float new_balance = u->balance - amount;

    // Update the balance in the file
    snprintf(filename, sizeof(filename), "%s.txt", u->username);
    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    long int position;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        if (strstr(line, "Balance: $") != NULL)
        {
            position = ftell(fp);
            fseek(fp, position - strlen(line), SEEK_SET);
            fprintf(fp, "Balance: $%.2f\n", new_balance);
            break;
        }
    }
    fclose(fp);

    // Update the balance in the struct
    u->balance = new_balance;

    // Log the transaction
    snprintf(filename, sizeof(filename), "%slog.txt", u->username);
    fp = fopen(filename, "a");
    if (fp == NULL)
    {
        printf("Error opening log file!\n");
        return;
    }
    fprintf(fp, "Withdrawn $%.2f\n", amount);
    fclose(fp);

    printf("\n\nWithdrawal successful! New balance: $%.2f\n", u->balance);
}

user login()
{
    user u;
    FILE *fp;
    char filename[60];
    char username[50];
    char password[20];

    printf("\n\nEnter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    snprintf(filename, sizeof(filename), "%s.txt", username);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error! Account not found\n");
        return u;
    }

    printf("\n\nEnter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    fscanf(fp, "Username: %s\n", u.username);
    fscanf(fp, "Password: %s\n", u.password);
    fscanf(fp, "First Name: %s\n", u.fName);
    fscanf(fp, "Last Name: %s\n", u.lName);
    fscanf(fp, "Father's Name: %s\n", u.fatherName);
    fscanf(fp, "Mother's Name: %s\n", u.motherName);
    fscanf(fp, "Address: %s\n", u.address);
    fscanf(fp, "Phone Number: %s\n", u.phoneNum);
    fscanf(fp, "Social Security Number: %s\n", u.ssNum);
    fscanf(fp, "Date of Birth: %d/%d/%d\n", &u.date, &u.month, &u.year);
    fscanf(fp, "Balance: $%f\n", &u.balance);

    while (strcmp(password, u.password) != 0)
    {
        printf("\n\nInvalid password!\n");
        printf("\n\nTry Again: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
    }

    fclose(fp);
    return u;
}

void transferLog(user u1, user u2, int amount)
{
    FILE *fp, *Slog, *rec, *Rlog;
    char filename[60], logFile[60], recFile[60];
    fprintf(Slog, "Transfered %d to %s\n", amount, u2.username);
    fprintf(Rlog, "Received %d from %s\n", amount, u1.username);
}

void transfer(user u1, user u2)
{
    FILE *fp, *Slog, *rec, *Rlog;
    char filename[60], logFile[60], recFile[60];
    int amount;

    printf("\n\nEnter the amount to transfer: $");
    scanf("%d", &amount);
    getchar();
    if (amount > u1.balance)
    {
        printf("Insufficient balance.\n");
        return;
    }

    u1.balance -= amount;
    u2.balance += amount;
    fprintf(fp, "Transfered %d to %s\n", amount, u2.username);
    transferLog(u1, u2, amount);
}

void preTransfer()
{
    user u1, u2;
    char username[50];
    FILE *fp, *Slog, *rec, *Rlog;
    char filename[60], logFile[60], recFile[60];

    printf("\n\nEnter username: ");
    fgets(u1.username, sizeof(u1.username), stdin);
    u1.username[strcspn(u1.username, "\n")] = '\0';
    snprintf(filename, sizeof(filename), "%s.txt", u1.username);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error! User not found\n");
        return;
    }
    fclose(fp);
    fp = fopen(filename, "a");

    snprintf(logFile, sizeof(filename), "%slog.txt", u1.username);
    Slog = fopen(logFile, "a");
    if (Slog == NULL)
    {
        printf("Error opening Log file!\n");
        return;
    }

    printf("\n\n!!!!!TRANSFER MONEY!!!!!");

    printf("\n\nEnter the user ID of the recepient: ");
    fgets(u2.username, sizeof(u2.username), stdin);
    u2.username[strcspn(u2.username, "\n")] = '\0';
    snprintf(recFile, sizeof(recFile), "%s.txt", u2.username);
    rec = fopen(recFile, "r");
    if (rec == NULL)
    {
        printf("Error! Recepient not found\n");
        return;
    }
    fclose(rec);
    rec = fopen(recFile, "a");

    snprintf(logFile, sizeof(recFile), "%slog.txt", u2.username);
    Rlog = fopen(logFile, "a");
    if (Rlog == NULL)
    {
        printf("Error opening Log file!\n");
        return;
    }

    transfer(u1, u2);

    fclose(fp);
    fclose(Slog);
    fclose(rec);
    fclose(Rlog);
}

int main()
{
    int choice1, choice;

    printf("\n\nWelcome to the Banking System!\n");
    printf("\n\n1. Create Account\n2. login\n3. Exit\n");
    printf("\n\nEnter your choice: ");
    scanf("%d", &choice1);
    getchar();
    while (choice1 < 1 || choice1 > 3)
    {
        printf("\n\nInvalid choice. Please enter again: ");
        printf("\n\n1. Create Account\n2. login\n3. Exit\n");
        printf("\n\nEnter your choice: ");
        scanf("%d", &choice1);
        getchar();
    }
    if (choice1 == 3)
    {
        printf("\n\nThank you for using the Banking System!\n\n");
        return 0;
    }
    if (choice1 == 1)
    {
        account();
    }
    else
    {
        user u = login();
        do
        {
            printf("\n\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Exit\n");
            printf("\n\nEnter your choice: ");
            scanf("%d", &choice);
            getchar();

            if (choice < 1 || choice > 5)
            {
                printf("\n\nInvalid choice. Please enter again: ");
                continue;
            }
            else
            {
                switch (choice)
                {
                case 1:
                    checkBalance(u);
                    break;
                case 2:
                    deposit(&u);
                    break;
                case 3:
                    withdraw(&u);
                    break;
                case 4:
                    preTransfer();
                    break;
                case 5:
                    printf("\n\nThank you for using the Banking System!\n\n");
                    break;
                default:
                    printf("\n\nError!\n\n");
                    break;
                }
            }
        } while (choice != 5);
        return 0;
    }
}