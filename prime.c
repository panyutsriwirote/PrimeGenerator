#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//Used to time the program for later analysis
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
    head->num = 2;
    head->next = NULL;
    tail = head;
}
//Call when a new prime number is discovered
void append(int new_num) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->num = new_num;
    new_node->next = NULL;
    //Insert the new node and update the tail pointer and list_size variable
    tail->next = new_node;
    tail = new_node;
    list_size += 1;
}
int main(int argc, char **argv) {
    //The arguments should be "prime [integer]" where [integer] represents the number of primes to generate
    if (argc != 2) {
        printf("ERROR: Incorrect arguments");
        exit(1);
    }
    clock_t begin = clock();
    //Declare and initialize state variables
    unsigned int cur_num = 3;
    node *p; //A pointer used to read the prime linked list
    unsigned int num_prime = atoi(argv[1]);
    unsigned int cur_prime;
    double square;
    //Start of the generation
    initialize_with_2();
    printf("2\n");
    //A while loop that goes through each number one by one, starting with 3
    while (1) {
        square = sqrt((double)cur_num); //Used to reduce the number of required division
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
            p = p->next; //Go to the next discovered prime numbers
        }
        if (list_size == num_prime) { //The program ends when enough primes have been generated
            break;
        }
        cur_num += 1; //Go to the next number
    }
    //Log spent time
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time spent: %lf s", time_spent);
    return 0;
}