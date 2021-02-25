#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

string cipher_text(string text, int key);
void error_msg(void);

int main(int argc, string argv[])
{
    //Verify number ofcommand-line inputs
    if (argc != 2) {
        error_msg();
        return 1;
    }

    //Verify is string is valid
    int len = strlen(argv[1]);
    for (int i = 0; i < len ; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            error_msg();
            return 1;
        }
    }

    //If command-line input is valid, save as key
    int key = atoi(argv[1]);

    //Get text input from user
    string text = get_string("plaintext:  ");

    //Get cipher
    string cipher = cipher_text(text,key);
    len = strlen(cipher);

    //Print ciphertext
    printf("ciphertext: %s\n",cipher);

    return 0;
}

string cipher_text(string text, int key)
{
    //Get text length
    int len = strlen(text);

    //Declare cipher variable and cipher
    string cipher = text;

    for (int i = 0 ; i < len ; i++)
    {

        //Check for alphabetic characters; only cipher these
        if (isalpha(text[i]))
        {
            /*Obtain offset for lower or uppercase latter
            Valid chars are not index 0! 'A' is 65 and 'a' is 97*/
            char offset;

            if (isupper(text[i]))
            {
                offset='A';
            }
            else
            {
                offset='a';
            }
            char temp = offset+((text[i] + key - offset) % 26); //Mod 26 to wrap around the alphabet
            cipher[i] = temp;
        }
    }

    return cipher;
}

void error_msg(void)
{
    printf("Usage: ./caesar key\n");
}