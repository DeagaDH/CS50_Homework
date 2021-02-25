from cs50 import get_string

def main():
    #Get text input from user
    text = get_string("Text: ")

    #Compute grade level
    grade = get_grade(text)

    #Print grade
    if (grade < 1):
        print("Before Grade 1")

    elif (grade >= 16):
        print("Grade 16+")

    else:
        print(f'Grade {grade}')


def get_grade(text):
    # Get length of text
    length = len(text)

    # Variables to count letters, words and sencentes
    letters = 0
    words = 0
    sentences = 0

    #Check all characters in text
    for c in text:

        #Check for alphanumeric characters
        if c.isalpha():
            letters +=1

        #Punctuation indicates end of sentence
        elif (c == '.' or c=='!' or c =='?'):
            sentences += 1

        #Spaces denote new words
        elif (c == ' '):
            words += 1

    #Add one final word; no space at the end!
    words += 1

    #Calculate average number of letters and sentences
    words_100 = words/100.0 #Multiplier to get 100 words

    #Averages per 100 words
    avg_letters = letters/words_100
    avg_sentences = sentences/words_100

    # Calculate grade
    grade = 0.0588 * avg_letters - 0.296 * avg_sentences - 15.8

    # Return rounded grade
    return int(round(grade,0))

main()