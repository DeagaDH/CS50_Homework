from cs50 import get_int

#Function to print "INVALID" for convenience
def invalid():
    print('INVALID')

#Function to count number of digits from input
def count_digits(number):

    #Negative number: restart as positive
    if number < 0:
        return count_digits(-number)

    #Less than 10: 1 digit
    if number < 10:
        return 1

    #Otherwise, add 1 digit and repeat with number/10
    return 1+count_digits(number/10)

#Gets a digit from number at position "pos" counting from the RIGHT
# Count starts at zero (rightmost digit is 0, then 1, 2, etc)

def get_digit(number,pos):

    #If position higher than possible, return 0
    if (pos > count_digits(number)-1):
        return 0

    #Start calculation
    digit = (number % 10**(pos+1) - number % 10**(pos))

    return digit/10**pos

def main():
    #Get input
    number = get_int('Number: ')

    #Number of digits
    digits = count_digits(number)

    #Apply Luhn's Algorithm
    first_sum = 0  #Will be multiplied by 2 later
    second_sum = 0 #Won't

    for i in range(0,digits,2):
        #Digit to add to first_sum
        first_digit = get_digit(number,i+1)

        first_digit *= 2

        #Check for numbers larger than 9 (2 digits)
        if (first_digit > 9):
            #Add the two digits
            first_sum += first_digit % 10 + (first_digit - first_digit % 10)/10

        else:
            #Add to frist sum
            first_sum += first_digit;

        #Digit to add to second_sum
        second_digit=get_digit(number,i)

        #Add to second sum
        second_sum += second_digit

    #Add both sums and check
    total = first_sum + second_sum

    if total % 10 ==0:
        first_digit  = get_digit(number,digits-1)
        second_digit = get_digit(number,digits-2)

        if (first_digit == 4):

            if (digits == 16 or digits == 13):
                print("VISA")

            else:
                invalid()

        elif (first_digit == 3):
            if (second_digit == 4 or second_digit == 7):
                print('AMEX')

            else:
                invalid()

        elif (first_digit == 5):

            if (second_digit < 6 and second_digit > 0):
                print('MASTERCARD')

            else:
                invalid()

        else:
            invalid()
    else:
        invalid()


main()