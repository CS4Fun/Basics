/*
    It's a Mario
    
    A program that recreates the half-pyramids using hashes based on
    the given height no greater than 23.
    
    ie
    
    ./mario
    Height: 4
       #  #
      ##  ##
     ###  ###
    ####  ####
*/

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int h;
    do
    {
        printf("Enter pyramid height under 24: ");
        h = GetInt();
    }
    while ((h <= 0) || (h > 23));
    
    for (int i = 1; i <= h; i++)
    {
        /* Print space before left pyramid */
        for (int j = h; j > i; j--)
        {
            printf(" ");
        }
        
        /* Print left pyramid */
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        printf("  ");
        
        /* Print left pyramid */
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }
        
        /* Print space after right pyramid */
        for (int j = h; j > i; j--)
        {
            printf(" ");
        }
        
        printf("\n");
    }
    
    return 0;
}
