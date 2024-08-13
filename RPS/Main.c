#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int game(char you, char computer)
{
    if (you == computer)
        return -1;
    if (you == 's' && computer == 'p')
        return 0;
    else if (you == 'p' && computer == 's')
        return 1;
    if (you == 's' && computer == 'z')
        return 1;
    else if (you == 'z' && computer == 's')
        return 0;
    if (you == 'p' && computer == 'z')
        return 0;
    else if (you == 'z' && computer == 'p')
        return 1;

    return -1;
}

int main()
{
    int n;
    char EndGame = 'y';
    char you, computer;
    int result;

    srand(time(NULL));

    while (EndGame != 'n')
    {
        n = rand() % 100;
        if (n < 33)
            computer = 's';
        else if (n >= 33 && n < 66)
            computer = 'p';
        else
            computer = 'z';

        printf("\n\n\n\n\t\t\t\tEnter s for STONE, p for PAPER and z for SCISSOR\n\t\t\t\t\t\t\t");
        scanf(" %c", &you);

        result = game(you, computer);

        if (result == -1)
        {
            printf("\n\n\t\t\t\tGame Draw!\n");
        }
        else if (result == 1)
        {
            printf("\n\n\t\t\t\tWow! You have won the game!\n");
        }
        else
        {
            printf("\n\n\t\t\t\tOh! You have lost the game!\n");
        }
        printf("\t\t\t\tYou chose: %c and Computer chose: %c\n", you, computer);

        printf("\n\n\t\t\t\tDo you want to play again? (y/n) : ");
        scanf(" %c", &EndGame); // Add a space to skip newline
    }
    printf("\n\n\t\t\t\tThanks for playing the game!\n\n\n\n");
    return 0;
}