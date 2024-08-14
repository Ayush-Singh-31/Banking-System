#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "Account.h"

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

    Transfer(u1, u2);

    fclose(fp);
    fclose(Slog);
    fclose(rec);
    fclose(Rlog);
}

void Transfer(user u1, user u2)
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
}

void TransferLog(user u1, user u2, int amount)
{
    FILE *fp, *Slog, *rec, *Rlog;
    char filename[60], logFile[60], recFile[60];
    fprintf(Slog, "Transfered %d to %s\n", amount, u2.username);
    fprintf(Rlog, "Received %d from %s\n", amount, u1.username);
}

int main()
{
    preTransfer();
    return 0;
}