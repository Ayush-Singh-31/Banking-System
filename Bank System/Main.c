#include <stdio.h>

struct user
{
    char username[50];
    int date, month, year;
    char phoneNum[15];
    char ssNum[20];
    char fName[20];
    char lName[20];
    char fatherName[20];
    char motherName[20];
    char address[50];
    char accType[20];
};

void userInfo(struct user u1)
{
    printf("\n\nFIRST NAME is %s", u1.fName);
    printf("\n\nLAST NAME is %s", u1.lName);
    printf("\n\nFATHER's NAME is %s", u1.fatherName);
    printf("\n\nMOTHER's NAME is %s", u1.motherName);
    printf("\n\nADDRESS is %s", u1.address);
    printf("\n\nPHONE NUMBER is %s", u1.phoneNum);
    printf("\n\nSOCIAL SECURITY NUMBER is %s", u1.ssNum);
    printf("\n\nDATE OF BIRTH is %d/%d/%d", u1.date, u1.month, u1.year);
}

void account()
{
    struct user u1;
    FILE *fp;

    fp = fopen("username.txt", "ab");
    if (fp == NULL)
    {
        printf("Error opening file!\n");
        return;
    }

    printf("\n\n!!!!!CREATE ACCOUNT!!!!!");
    // Can't take multiword input yet
    printf("\n\nFIRST NAME: ");
    scanf("%s", u1.fName);

    printf("\n\nLAST NAME: ");
    scanf("%s", u1.lName);

    printf("\n\nFATHER's NAME: ");
    scanf("%s", u1.fatherName);

    printf("\n\nMOTHER's NAME: ");
    scanf("%s", u1.motherName);

    printf("\n\nADDRESS: ");
    scanf("%s", u1.address);

    printf("\n\nPHONE NUMBER: ");
    scanf("%s", u1.phoneNum);

    printf("\n\nSOCIAL SECURITY NUMBER: ");
    scanf("%s", u1.ssNum);

    printf("\n\nDAY OF BIRTH: ");
    scanf("%d", &u1.date);

    printf("\n\nMONTH OF BIRTH: ");
    scanf("%d", &u1.month);

    printf("\n\nYEAR OF BIRTH: ");
    scanf("%d", &u1.year);

    userInfo(u1);

    // You could write `u1` data to the file here if needed

    fclose(fp); // Always close the file when done
}

int main()
{
    account();
    return 0;
}
