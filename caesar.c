/*
    Hail, Caesar!
    
    Caesar cipher - encrypts messages by rotating each letter by specified (k)
    positions, wrapping around from Z to A as needed.
    
    ci = (pi + k) % 26
    
    ie
    ./caesar 13
    Be sure to drink your Ovaltine!
    Or fher gb qevax lbhe Binygvar!
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MSG_BLOCK_SIZE  50

int main(int argc, char* argv[])
{
    char c;
    int k;
    char* message = malloc(MSG_BLOCK_SIZE*sizeof(char));
    int size = MSG_BLOCK_SIZE;
    int n = 0;
    
    if (message == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }
       
    if (argc != 2)
    {
        printf("Invalid argument: run program with encryption key.\n");
        return 1;
    }
    
    while (((c = fgetc(stdin)) != '\n') && (c != EOF))
    {
        ++n;
        if (n >= size)
        {
            
            char* temp = realloc(message, (size + MSG_BLOCK_SIZE)*sizeof(char));
            if (temp != NULL)
            {
                message = temp;
                size += MSG_BLOCK_SIZE;
            }
            else
            {
                free(message);
                printf("Memory allocation failed.\n");
                return 1;
            }
        }
        
        message[n-1] = c;
    }
    
    k = atoi(argv[1]);  /* shift value */

    /* Encryption */
    for (int i = 0; i < n; ++i)
    {
        c = message[i];

        if (isalpha(c))
        {
            message[i] = islower(c) ? ((c - 'a' + k) % 26) + 'a' : ((c - 'A' + k) % 26) + 'A';
        }
        printf("%c", message[i]);
    }
    
    printf("\n");
    free(message);
    
    return 0;
}
