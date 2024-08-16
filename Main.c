#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "Account.h"

/**
 * @brief Reads a single character from standard input without echo.
 *
 * @return char The input character.
 */
char getch()
{
    char ch;
    struct termios oldt, newt;

    // Save current terminal settings and disable canonical mode and echo
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    // Read character and restore terminal settings
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    return ch;
}

/**
 * @brief Creates a new user account by collecting user information and saving it to a file.
 */
void account()
{
    user u1;
    FILE *fp;
    char filename[60];
    char ch;
    int passLength;

    printf("\n\n!!!!!CREATE ACCOUNT!!!!!\n");

    // Get username
    printf("Enter username: ");
    fgets(u1.username, sizeof(u1.username), stdin);
    u1.username[strcspn(u1.username, "\n")] = '\0';

    // Create filename and open file for writing
    snprintf(filename, sizeof(filename), "%s.txt", u1.username);
    fp = fopen(filename, "w");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    // Get password length and validate
    printf("\nPASSWORD length (8-20): ");
    scanf("%d", &passLength);
    while (passLength < 8 || passLength > 20)
    {
        printf("Invalid length. Enter again (8-20): ");
        scanf("%d", &passLength);
    }
    getchar(); // Clear newline left by scanf

    // Get password with hidden input
    printf("PASSWORD: ");
    for (int i = 0; i < passLength; i++)
    {
        ch = getch();
        if (ch == '\n')
            break;
        u1.password[i] = ch;
        printf("*");
    }
    u1.password[passLength] = '\0';

    // Get additional user information
    printf("\nFIRST NAME: ");
    fgets(u1.fName, sizeof(u1.fName), stdin);
    u1.fName[strcspn(u1.fName, "\n")] = '\0';

    printf("LAST NAME: ");
    fgets(u1.lName, sizeof(u1.lName), stdin);
    u1.lName[strcspn(u1.lName, "\n")] = '\0';

    printf("FATHER'S NAME: ");
    fgets(u1.fatherName, sizeof(u1.fatherName), stdin);
    u1.fatherName[strcspn(u1.fatherName, "\n")] = '\0';

    printf("MOTHER'S NAME: ");
    fgets(u1.motherName, sizeof(u1.motherName), stdin);
    u1.motherName[strcspn(u1.motherName, "\n")] = '\0';

    printf("ADDRESS: ");
    fgets(u1.address, sizeof(u1.address), stdin);
    u1.address[strcspn(u1.address, "\n")] = '\0';

    printf("PHONE NUMBER: ");
    fgets(u1.phoneNum, sizeof(u1.phoneNum), stdin);
    u1.phoneNum[strcspn(u1.phoneNum, "\n")] = '\0';

    printf("SOCIAL SECURITY NUMBER: ");
    fgets(u1.ssNum, sizeof(u1.ssNum), stdin);
    u1.ssNum[strcspn(u1.ssNum, "\n")] = '\0';

    // Get birth date
    printf("DAY OF BIRTH: ");
    scanf("%d", &u1.date);
    printf("MONTH OF BIRTH: ");
    scanf("%d", &u1.month);
    printf("YEAR OF BIRTH: ");
    scanf("%d", &u1.year);
    getchar(); // Clear newline left by scanf

    u1.balance = 0.0;

    // Write user data to file
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

/**
 * @brief Retrieves and displays the user's balance from their file.
 *
 * @param u Pointer to a user struct containing the username.
 */
void checkBalance(user *u)
{
    char filename[60];
    char line[256];
    FILE *fp;

    // Construct filename and open file for reading
    snprintf(filename, sizeof(filename), "%s.txt", u->username);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error! Unable to open user file.\n");
        return;
    }

    // Search for the balance line and extract balance
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "Balance: $"))
        {
            sscanf(line, "Balance: $%f", &u->balance);
            break;
        }
    }

    printf("\nYour current balance is: $%.2f\n", u->balance);
    fclose(fp);
}

/**
 * @brief Deposits an amount into the user's account and updates the balance in the file.
 *
 * @param u Pointer to a user struct containing the username and current balance.
 */
void deposit(user *u)
{
    FILE *fp;
    char filename[60];
    float amount;

    // Get deposit amount from user
    printf("\nEnter the amount to deposit: $");
    scanf("%f", &amount);
    getchar();

    // Update balance
    float new_balance = u->balance + amount;

    // Open user's file to update balance
    snprintf(filename, sizeof(filename), "%s.txt", u->username);
    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    long position;

    // Find and update the balance line
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "Balance: $"))
        {
            position = ftell(fp);
            fseek(fp, position - strlen(line), SEEK_SET);
            fprintf(fp, "Balance: $%.2f\n", new_balance);
            break;
        }
    }

    fclose(fp);

    // Update user's balance in memory
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

    // Notify user of successful deposit
    printf("\nDeposit successful! New balance: $%.2f\n", u->balance);
}

/**
 * @brief Withdraws an amount from the user's account and updates the balance in the file.
 *
 * @param u Pointer to a user struct containing the username and current balance.
 */
void withdraw(user *u)
{
    FILE *fp;
    char filename[60];
    float amount;

    // Get withdrawal amount from user
    printf("\nEnter the amount to withdraw: $");
    scanf("%f", &amount);
    getchar();

    // Check if sufficient balance is available
    if (amount > u->balance)
    {
        printf("\nInsufficient balance! Your current balance is $%.2f\n", u->balance);
        return;
    }

    // Update balance
    float new_balance = u->balance - amount;

    // Open user's file to update balance
    snprintf(filename, sizeof(filename), "%s.txt", u->username);
    fp = fopen(filename, "r+");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    char line[256];
    long position;

    // Find and update the balance line
    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, "Balance: $"))
        {
            position = ftell(fp);
            fseek(fp, position - strlen(line), SEEK_SET);
            fprintf(fp, "Balance: $%.2f\n", new_balance);
            break;
        }
    }

    fclose(fp);

    // Update user's balance in memory
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

    // Notify user of successful withdrawal
    printf("\nWithdrawal successful! New balance: $%.2f\n", u->balance);
}

/**
 * @brief Logs in a user by verifying their credentials.
 *
 * @return user Struct containing user information if login is successful; otherwise, an empty user struct.
 */
user login()
{
    user u = {0}; // Initialize user struct with zeros
    FILE *fp;
    char filename[60];
    char username[50];
    char password[20];

    // Get username
    printf("\nEnter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0';

    snprintf(filename, sizeof(filename), "%s.txt", username);
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error! Account not found\n");
        return u;
    }

    // Get password
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    // Read user data from file
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

    // Validate password
    while (strcmp(password, u.password) != 0)
    {
        printf("Invalid password! Try Again: ");
        fgets(password, sizeof(password), stdin);
        password[strcspn(password, "\n")] = '\0';
    }

    fclose(fp);
    return u;
}

/**
 * @brief Logs a transfer transaction for both the sender and recipient.
 *
 * @param u1 Pointer to the sender's user struct.
 * @param u2 Pointer to the recipient's user struct.
 * @param amount The amount transferred.
 */
void transferLog(user *u1, user *u2, float amount)
{
    FILE *log;
    char logFile[60];

    // Log sender's transaction
    snprintf(logFile, sizeof(logFile), "%slog.txt", u1->username);
    log = fopen(logFile, "a");
    if (log)
    {
        fprintf(log, "Transferred $%.2f to %s\n", amount, u2->username);
        fclose(log);
    }
    else
    {
        printf("Error opening log file for sender!\n");
    }

    // Log recipient's transaction
    snprintf(logFile, sizeof(logFile), "%slog.txt", u2->username);
    log = fopen(logFile, "a");
    if (log)
    {
        fprintf(log, "Received $%.2f from %s\n", amount, u1->username);
        fclose(log);
    }
    else
    {
        printf("Error opening log file for recipient!\n");
    }
}

/**
 * @brief Transfers money from one user to another and updates their balances.
 *
 * @param u1 Pointer to the sender's user struct.
 * @param u2 Pointer to the recipient's user struct.
 */
void transfer(user *u1, user *u2)
{
    float amount;

    // Get transfer amount
    printf("\nEnter the amount to transfer: $");
    scanf("%f", &amount);
    getchar();

    if (amount > u1->balance)
    {
        printf("Insufficient balance.\n");
        return;
    }

    // Update sender's balance
    FILE *fp;
    char filename[60];
    u1->balance -= amount;
    snprintf(filename, sizeof(filename), "%s.txt", u1->username);
    fp = fopen(filename, "r+");
    if (fp)
    {
        char line[256];
        long position;
        while (fgets(line, sizeof(line), fp))
        {
            if (strstr(line, "Balance: $"))
            {
                position = ftell(fp);
                fseek(fp, position - strlen(line), SEEK_SET);
                fprintf(fp, "Balance: $%.2f\n", u1->balance);
                break;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("Error opening file for sender!\n");
        return;
    }

    // Update recipient's balance
    u2->balance += amount;
    snprintf(filename, sizeof(filename), "%s.txt", u2->username);
    fp = fopen(filename, "r+");
    if (fp)
    {
        char line[256];
        long position;
        while (fgets(line, sizeof(line), fp))
        {
            if (strstr(line, "Balance: $"))
            {
                position = ftell(fp);
                fseek(fp, position - strlen(line), SEEK_SET);
                fprintf(fp, "Balance: $%.2f\n", u2->balance);
                break;
            }
        }
        fclose(fp);
    }
    else
    {
        printf("Error opening file for recipient!\n");
        return;
    }

    // Log the transaction
    transferLog(u1, u2, amount);
    printf("\nTransfer successful! New balance: $%.2f\n", u1->balance);
}

/**
 * @brief Handles the pre-transfer process, including recipient validation.
 *
 * @param u1 Pointer to the sender's user struct.
 */
void preTransfer(user *u1)
{
    user u2;
    char filename[60];
    FILE *rec;

    printf("\n\n!!!!!TRANSFER MONEY!!!!!\n");

    // Get recipient username
    printf("\nEnter the username of the recipient: ");
    fgets(u2.username, sizeof(u2.username), stdin);
    u2.username[strcspn(u2.username, "\n")] = '\0';

    snprintf(filename, sizeof(filename), "%s.txt", u2.username);
    rec = fopen(filename, "r");
    if (rec)
    {
        fclose(rec);
        transfer(u1, &u2);
        printf("\nTransfer completed successfully!\n");
    }
    else
    {
        printf("Error! Recipient not found\n");
    }
}

int main()
{
    int choice1, choice;

    printf("\n\nWelcome to the Banking System!\n");
    printf("\n1. Create Account\n2. Login\n3. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice1);
    getchar();

    // Validate initial choice
    while (choice1 < 1 || choice1 > 3)
    {
        printf("\nInvalid choice. Please enter again: ");
        printf("\n1. Create Account\n2. Login\n3. Exit\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice1);
        getchar();
    }

    if (choice1 == 3)
    {
        printf("\nThank you for using the Banking System!\n");
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
            printf("\n1. Check Balance\n2. Deposit\n3. Withdraw\n4. Transfer\n5. Exit\n");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
            getchar();

            // Validate user choice
            if (choice < 1 || choice > 5)
            {
                printf("\nInvalid choice. Please enter again.\n");
                continue;
            }

            switch (choice)
            {
            case 1:
                checkBalance(&u);
                break;
            case 2:
                deposit(&u);
                break;
            case 3:
                withdraw(&u);
                break;
            case 4:
                preTransfer(&u);
                break;
            case 5:
                printf("\nThank you for using the Banking System!\n");
                break;
            default:
                printf("\nError!\n");
                break;
            }
        } while (choice != 5);
    }

    return 0;
}
