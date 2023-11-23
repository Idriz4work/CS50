#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int convert(string key);
string plain_text();
char encipher(string text, int k);

int main(int argc, string argv[])
{
    // Make sure program was run with just one command-line argument
    string key = argv[1];
    {
        if (argc != 2)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    for (int i = 0; i < strlen(key); i++)
    {
        if (!isdigit(argv[1][i]))
        {
            return 1;
        }
        else if (isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
        }
    }

    // Convert argv[1] from a `string` to an `int`
    int k = convert(key);

    // Prompt for plaintext
    string text = get_string("Plaintext: ");

    // For each character in the plaintext:
    char c = encipher(text, k);

    return 0;
}

int convert(string key)
{
    int k = atoi(key);
    return k;
}

char encipher(string text, int k)
{
    char c;
    printf("ciphertext: ");
    for (int n = 0; n < strlen(text); n++)
    {
        if (isupper(text[n]))
        {
            c = (text[n] - 65 + k) % 26 + 65;
            printf("%c", (text[n] - 65 + k) % 26 + 65);
        }
        else if (islower(text[n]))
        {
            c = (text[n] - 97 + k) % 26 + 97;
            printf("%c", (text[n] - 97 + k) % 26 + 97);
        }
        else
        {
            printf("%c", (text[n]));
        }
    }
    printf("\n");
    return 0;
}