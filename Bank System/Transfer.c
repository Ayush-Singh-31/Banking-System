#include <stdio.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "Account.h"

void transfer()
{
    user u1;
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
    fgets(u1.username, sizeof(u1.username), stdin);
    u1.username[strcspn(u1.username, "\n")] = '\0';
    snprintf(recFile, sizeof(recFile), "%s.txt", u1.username);
    rec = fopen(recFile, "r");
    if (rec == NULL)
    {
        printf("Error! Recepient not found\n");
        return;
    }
    fclose(rec);
    rec = fopen(recFile, "a");

    snprintf(logFile, sizeof(recFile), "%slog.txt", u1.username);
    Rlog = fopen(logFile, "a");
    if (Rlog == NULL)
    {
        printf("Error opening Log file!\n");
        return;
    }
}

int main()
{
    transfer();
    return 0;
}