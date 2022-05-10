#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
int main(int argc, char **argv) {
    clock_t begin = clock();
    //The arguments should be "prime [integer]" where [integer] represents the number of primes to generate
    //or enter "prime 0" to continually generate new primes
    if (argc != 2) {
        printf("ERROR: Incorrect number of arguments");
        exit(1);
    }
    char *arg = argv[1];
    for (char c = *arg; c != '\0'; c = *(++arg)) {
        if (!isdigit(c)) {
            printf("ERROR: Argument must be a non-negative integer");
            exit(1);
        }
    }
    //Declare and initialize state variables
    unsigned int num_prime = atoi(argv[1]);
    unsigned int discovered = 1;
    unsigned int cur_num = 3;
    double square;
    unsigned int i;
    //Start of the generation
    printf("2\n");
    //A while loop that goes through each number one by one, starting with 3
    while (1) {
        if (discovered == num_prime) { //The program ends when enough primes have been generated
            break;
        }
        square = sqrt((double)cur_num);
        //A while loop that goes through each discovered prime number and performs remainder test
        for (i = 2; i < cur_num; i++) {
            if (i > square) {
                printf("%u\n", cur_num);
                discovered++;
                break;
            }
            if (cur_num%i == 0) {
                break;
            }
        }
        cur_num++;
        //In case of an overflow
        if (cur_num == 0) {
            printf("Maximum number of primes reached\n");
            break;
        }
    }
    //Log spent time
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time spent: %lf s", time_spent);
    return 0;
}