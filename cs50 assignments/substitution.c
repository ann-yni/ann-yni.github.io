// substitution.c translates text based on a inputted cipher alphabet. For specifications, view: https://cs50.harvard.edu/x/2022/psets/2/substitution/


#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    string cipher = argv[1];
    string alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // too many arguments
    if (argc > 2)
    {
        printf("Error: Too many arguments.\n");
        return 1;
    }
    // no key input
    if (argv[1] == NULL)
    {
        printf("Error: Usage ./substitution key\n");
        return 1;
    }

    // incorrect key length
    if (strlen(cipher) != 26)
    {
        printf("Error: Key must contain 26 characters.\n");
        return 1;
    }

    for (int i = 0; i < 26; i++)
    {
        // non-alphabetical characters
        if (isalpha(cipher[i]) == 0)
        {
            printf("Error: Key cannot contain non-alphabetical characters.\n");
            return 1;
        }

        // duplicate characters
        for (int k = i + 1; k < 26; k++)
        {
            if (cipher[k] == cipher[i])
            {
                printf("Error: Key must contain each letter once.\n");
                return 1;
            }
        }
    }

    // input for translation
    string plaintext = get_string("plaintext: ");
    for (int a = 0; a < strlen(plaintext); a++)
    {
        // check cases
        int match = 0;
        if (islower(plaintext[a]))
        {
            match = 1;
        }
        else if (isupper(plaintext[a]))
        {
            match = 2;
        }
        plaintext[a] = toupper(plaintext[a]);
        for (int b = 0; b < 26; b++)
        {
            if (plaintext[a] == alpha[b])
            {
                plaintext[a] = cipher[b];
                // match cases
                if (match == 1)
                {
                    plaintext[a] = tolower(plaintext[a]);
                }
                else if (match == 2)
                {
                    plaintext[a] = toupper(plaintext[a]);
                }
                // stop checking against key
                break;
            }
        }
    }
    printf("ciphertext: %s\n", plaintext);
    return 0;
}
