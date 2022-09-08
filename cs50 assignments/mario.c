// 1st Assignment. mario.c prints pyramids to mimic the Mario game environment. For specifications, view: https://cs50.harvard.edu/x/2022/psets/1/mario/more/


#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // asks for integer 1-8
    int x;
    do
    {
        x = get_int("Height: ");
    }
    while (x < 1 || x > 8);

    // counter for #
    int y = 1;
    // counter for spaces
    int z = x - 1;
    do
    {
        // prints left-side spaces
        for (int j = 0; j < z ; j++)
        {
            printf(" ");
        }
        // prints left-side #
        for (int i = 0; i < y; i++)
        {
            printf("#");
        }
        // prints center spaces
        printf("  ");
        // prints right side #
        for (int i = 0; i < y; i++)
        {
            printf("#");
        }
        printf("\n");
        y++;
        z--;
    }
    while (y <= x);
}



