#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

struct user
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
};

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
    struct user u1;
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
    for (i = 0; i < passLenght - 1; i++)
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
    fclose(fp);
}

int main()
{
    account();
    return 0;
}