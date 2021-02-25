#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int get_grade(string text);

int main(void)
{
    // Get text input from user
    string text = get_string("Text: ");

    // Compute grade level
    int grade = get_grade(text);

    //Print grade
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
        printf("Grade %i\n",grade);


    return 0;
}

int get_grade(string text)
{
    //Get length of text
    int length=strlen(text);

    //Variables to count letters, words and texts
    int letters = 0, words = 0, sentences = 0;

    //Iterate through text to count letters, words and sentences
    for (int i = 0 ; i < length ; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
        else if (text[i] == ' ')
        {
            words++;
        }
    }

    //Add final word; no white space at the end!
    words++;

    //Calculate average number of letters and sentences
    float words_100, avg_letters, avg_sentences;

    //Multiplier to get to 100 words
    words_100=words/100.0;

    //Averages per 100 words
    avg_letters=letters/words_100;
    avg_sentences=sentences/words_100;

    //Calculate grade
    float grade = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8;

    //Return rounded grade
    int rounded_grade = round(grade);

    return rounded_grade;
}
