/*
    Parlez-vous francais?
    
    Vigenere cipher - similar to Caesar's cipher, it encrypts messages
    using a sequence of the prvided keys (aka keyword).
    If keyword (k) is shorter than the message (p), then letters in
    k must be reused cyclically as many times as it takes to encrypt p.
    
    ci = (pi + kl) % 26
    
    ie
    ./vigenere bacon
    Meet me at the park at eleven am
    Negh zf av huf pcfx bt gzrwep oz
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MSG_BLOCK_SIZE  50

int main(int argc, char* argv[])
{
    char c;
    char k;
    char* message = malloc(MSG_BLOCK_SIZE*sizeof(char));
    int size = MSG_BLOCK_SIZE;
    int n = 0;
    int j = 0;
    
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
    
    while (argv[1][j] != '\0')
    {
        if (!isalpha(argv[1][j++]))
        {
            printf("Keyword must be only A-Z and a-z\n");
            free(message);
            return 1;
        }
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

    /* Encryption */
    j = 0;
    for (int i = 0; i < n; ++i)
    {
        c = message[i];

        if (isalpha(c))
        {
            /* key shift value cycle */
            if (argv[1][j] == '\0')
                j = 0;
            
            k = islower(argv[1][j]) ? argv[1][j] - 'a' : argv[1][j] - 'A';
            ++j;
            message[i] = islower(c) ? ((c - 'a' + k) % 26) + 'a' : ((c - 'A' + k) % 26) + 'A';
        }
        printf("%c", message[i]);
    }
    
    printf("\n");
    free(message);
    
    return 0;
}
