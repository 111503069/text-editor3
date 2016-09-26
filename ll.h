#include<stdlib.h>
#include<ncurses.h>
typedef struct node {
    int data;
    struct node *next;
} node;
//node *newn, *start = NULL, *temp, *del;
void add(char);
void show(WINDOW*, FILE*);
//int countnode();
//void add_at_beg();
void insert(WINDOW*, char, int , int );
void delete_node(int , int );
int check(WINDOW*, int, int);
