#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <time.h>
//Define a linked list to be used as storage for discovered prime numbers
typedef struct _node {
    unsigned int num;
    struct _node *next;
} node;
node *head;
node *tail;
//Variable to store the current size of the linked list
unsigned int list_size = 1;
//Call at the start of the program
void initialize_with_2() {
    head = (node*)malloc(sizeof(node));
    if (head == NULL) {
        printf("ERROR: Failed to allocate memory");
        exit(1);
    }
    head->num = 2;
    tail = head;
}
//Call when a new prime number is discovered
void append(unsigned int new_num) {
    node *new_node = (node*)malloc(sizeof(node));
    if (new_node == NULL) {
        printf("ERROR: Failed to allocate memory");
        exit(1);
    }
    new_node->num = new_num;
    tail->next = new_node;
    tail = new_node;
    list_size++;
}
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
    unsigned int cur_num = 3;
    node *p; //A pointer used to read the prime linked list
    unsigned int cur_prime;
    double square;
    //Start of the generation
    initialize_with_2();
    printf("2\n");
    //A while loop that goes through each number one by one, starting with 3
    while (1) {
        if (list_size == num_prime) { //The program ends when enough primes have been generated
            break;
        }
        square = sqrt((double)cur_num);
        p = head;
        //A while loop that goes through each discovered prime number and performs remainder test
        while (1) {
            cur_prime = p->num;
            if (cur_prime > square) {
                printf("%u\n", cur_num);
                append(cur_num);
                break;
            }
            if (cur_num%cur_prime == 0) {
                break;
            }
            p = p->next;
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