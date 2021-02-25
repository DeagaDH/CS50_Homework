#include <stdio.h>
#include <cs50.h>
#include <math.h>

//function to print "INVALID"
void invalid(void)
{
    printf("INVALID\n");
}


//Function to count digits from input
int count_digits(long number)
{
    //Negative number: restart as positive
    if (number < 0)
    {
        return count_digits(-number);
    }

    //Less than 10: 1 digit
    if (number < 10)
    {
        return 1;
    }

    //Otherwise, add 1 digit and repeat with number/10
    return 1+count_digits(number/10);
}

//Calculates powers of 10 as longs
long longpow10(int power)
{

    if (power==0)
    {
        return 1;
    }

    return 10*longpow10(power-1);

}
/*Gets a digit from "number" at position "pos", counting from the RIGHT
Count starts at zero (rightmost digit is 0, then 1, 2, etc)*/
int get_digit(long number,int pos)
{
    //For position higher than possible, return 0 (ie 0 to the left)
    if (pos > count_digits(number)-1)
    {
        return 0;
    }

    //Start calculation
    long digit=(number%longpow10(pos+1)-number%longpow10(pos));

    return digit/longpow10(pos);

}

int main(void)
{
    //Get input
    long number = get_long("Number: ");

    //Number of digits
    int digits = count_digits(number);

    //Apply Luhn's Algorithm
    int first_sum=0; //Will be multiplied by 2 later
    int second_sum=0; //Won't

    for (int i=0 ; i < digits ; i=i+2) //Step=2
    {
        //Digit to add to first_sum
        int first_digit=get_digit(number,i+1);

        first_digit*=2;


        //Check for numbers larger than 9 (2 digits)
        if (first_digit > 9)
        {
            //Add the two digits
            first_sum += first_digit%10 + (first_digit-first_digit%10)/10;
        }
        else
        {
            //Add to first sum
            first_sum += first_digit;
        }

        //Digit to add to second_sum
        int second_digit=get_digit(number,i);

        //Add to second sum
        second_sum+=second_digit;
    }

    //Add both sums and check
    int total = first_sum+second_sum;

    //Get first and second digits of the number


    if (total % 10 == 0)
    {
        int first_digit=get_digit(number,digits-1);
        int second_digit=get_digit(number,digits-2);

        if (first_digit==4)
        {
            if (digits==16 || digits==13)
            {
                printf("VISA\n");
            }
            else
            {
                invalid();
            }

        }
        else if (first_digit==3)
        {
            if (second_digit==4 || second_digit ==7)
            {
                printf("AMEX\n");
            }
            else
            {
                invalid();
            }
        }
        else if (first_digit == 5)
        {
            if (second_digit < 6 && second_digit > 0)
            {
                printf("MASTERCARD\n");
            }
            else
            {
                invalid();
            }
        }
        else
        {
            invalid();
        }
    }
    else
    {
        invalid();
    }
}
