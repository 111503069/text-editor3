#include "ll.h"
#include<stdlib.h>
#include<ncurses.h>
node *newn, *start = NULL, *temp, *del;
void add(char ch) {
    newn = (node*)malloc(sizeof(node));
    newn -> data = ch;
    newn -> next = NULL;
    if(start == NULL) {
        start = newn;
    }
    else {
        temp = start;
        while(temp -> next != NULL)
            temp = temp -> next;
        temp -> next = newn;
    }
}
void show(WINDOW* wn, FILE* fl) {
    int x = 0, y = 0;
    if(start == NULL) {
        
    }
    else {
        temp = start;
        while(temp != NULL) {
            wprintw(wn, "%c", temp -> data);
            fprintf(fl, "%c", temp -> data);
            temp = temp -> next;
            //wmove(wn, 0,0);
            
            
        }
    }
}
//void add_at_beg();
    void insert(WINDOW* wn, char ch, int x, int y) {
        int p = x*getmaxy(wn) + y, c = 0;
        
	if(p == 0) {
        add(ch);
	}
	else {
		temp = start;
		while(temp != NULL) {
		    c++;
		    if(c == p) {
		        newn = (node*)malloc(sizeof(node));
		        newn -> data = ch;
		        newn -> next = temp -> next;
		        temp -> next = newn;
		        break;
		    }
		    temp = temp -> next;
            
        }
	}
    }
    void delete_node(int x, int y) {
        int p = x + y, c = 0;
        temp = start;
        while(temp != NULL) {
            c++;
            if(c == p) {
                del = temp -> next;
                temp -> next = temp -> next -> next;
                free(del);
                break;
            }
            temp = temp -> next;
        }
    }
int check(WINDOW* wn, int x, int y) {
    int p = x*getmaxy(wn) + y, c = 0;
    temp = start;
    while(temp != NULL) {
        temp = temp -> next;
        c++;
    }
    if(c == p)
        return 1;
    else
        return 0;
        
}
