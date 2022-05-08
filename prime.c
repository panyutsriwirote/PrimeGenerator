#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
typedef struct _node {
    unsigned int num;
    struct _node *next;
} node;
node *prime;
unsigned int list_size = 1;
void initialize_with_2() {
    prime = (node*)malloc(sizeof(node));
    prime->num = 2;
    prime->next = NULL;
}
void append(int new_num) {
    node *new_node = (node*)malloc(sizeof(node));
    new_node->num = new_num;
    new_node->next = NULL;
    node **p = &prime;
    while (*p != NULL) {
        p = &((*p)->next);
    }
    *p = new_node;
    list_size += 1;
}
int main(int argc, char **argv) {
    if (argc != 2) {
        printf("ERROR: Incorrect arguments");
        exit(1);
    }
    clock_t begin = clock();
    unsigned int cur_num = 3;
    node *p;
    unsigned int num_prime = atoi(argv[1]);
    unsigned int cur_prime;
    double square;
    initialize_with_2();
    printf("2\n");
    while (1) {
        square = sqrt((double)cur_num);
        p = prime;
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
        if (list_size == num_prime) {
            break;
        }
        cur_num += 1;
    }
    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("Total time spent: %lf s", time_spent);
    return 0;
}