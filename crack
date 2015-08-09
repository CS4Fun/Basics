/*
    Passwords Et Cetera
    Brute force decryption of one way hash of DES crypt with salt.
    Assuming passwords are 8-character long and consist of only ASCII
    printable characters.

    ie
    ./crack 50yoN9fp966dU
    crimson
    
    NOTE: brute force method takes a while to decrypt.
*/

#define _XOPEN_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <cs50.h>

/* ASCII printable code range */
#define MAX_C           126 /* char ~ */
#define MIN_C           32  /* char space */
#define PASSWORD_SIZE   8

/*
    char_idx: 0 - (PASSWORD_SIZE - 1)
    return:
        - false = update success
        - true = at max
*/
bool update_char(int char_idx, char* c)
{
    if (c[char_idx] < MAX_C)
    {
        for (int i = 0; i < char_idx; i++)
        { 
            c[i] = MIN_C;
        }
        
        if (c[char_idx] == 0)
            c[char_idx] = MIN_C;
        else    
            ++c[char_idx];
        
        return false;
    }

    return true;
}

int main (int argc, char* argv[])
{
    bool found = false;
    if (argc != 2)
    {
        printf("Invalid argument, run program with encrytped password.\n");
        return 1;
    }
    
    char password[PASSWORD_SIZE] = {0};
    char c[PASSWORD_SIZE] = {0};
    
    /*
        crypt() only uses the 1st 64 bits for encryption.
        Password returned from crypt() are 13 ASCII characters, first 2 are salt
        characters.
    */
    while (!found)
    {
        char* encryption_expected = crypt(&password[0], &argv[1][0]);
        
        int i = 2;
        found = true;
        while (i < 13)
        {
            if (encryption_expected[i] != argv[1][i])
            {
                found = false;
                break;
            }
            ++i;
        }
        
        if (encryption_expected[i] == argv[1][i])
        {
            found = true;
        }
        else if (update_char(0, c) &&
                    update_char(1, c) &&
                    update_char(2, c) &&
                    update_char(3, c) &&
                    update_char(4, c) &&
                    update_char(5, c) &&
                    update_char(6, c) &&
                    update_char(7, c))
        {
            /* password not found after trying all combinations. */
            break;
        }
        else
        {
            for (int j = 0; j < PASSWORD_SIZE; j++)
            {
                password[j] = c[j];
            }
        }
    }

    if (found)
         printf("%s\n", password);

    return 0;
}
