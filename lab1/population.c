#include <cs50.h>
#include <stdio.h>

//Function to calculate population growth base on an initial population value
int pop_growth(int pop_init) {
        return pop_init-pop_init/4+pop_init/3;
}

int main(void) {

    //Declare variables
    int pop_init=0,pop_final=0,years=0;

    //Initial population value
    do {
        pop_init=get_int("Start size: ");
    } while (pop_init < 9);

    //Final population value
    do {
        pop_final=get_int("End size: ");
    } while (pop_final < pop_init);

    //Iterate until initial pop reaches final pop
    while (pop_init < pop_final){
        pop_init=pop_growth(pop_init);
        years++;
    }

    //Print the number of years
    printf("Years: %i\n",years);
}