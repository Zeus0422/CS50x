#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

bool only_digits(string argv[]);
string rotate(string plaintext, int argkey);

int main(int argc, string argv[])
{
    bool isdigit = only_digits(argv);

    if (!isdigit)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    if (argc != 2)
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    string ciphertext;
    string plaintext;

    plaintext = get_string("Plaintext:  ");
    if (plaintext[0] == '\0')
    {
        printf("Usage: %s <key>\n", argv[0]);
        return 1;
    }

    int key = atoi(argv[1]);

    ciphertext = rotate(plaintext, key);
    printf("ciphertext: %s\n", ciphertext);
}

bool only_digits(string argv[])
{
    for (int i = 1; argv[i] != NULL; i++) {
        for (int j = 0; argv[i][j] != '\0'; j++)
        {
            if (!isdigit(argv[i][j]))
            {
                return false;
            }
        }
    }
    return true;
}

string rotate(string plaintext, int key)
{
    for (int i = 0; plaintext[i] != '\0'; i++)
    {
        if (isalpha(plaintext[i]))
        {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = ((plaintext[i] - base + key) % 26) + base;
        }
    }
    return plaintext;
}
