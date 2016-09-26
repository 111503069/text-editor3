#include<stdio.h>
#include<ncurses.h>
#include <string.h>
#include "ll.h"
void print(WINDOW*, char* , FILE* );
void curses_init()
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, TRUE);
}
int main(int argc, char* argv[]) {
    int parent_x, parent_y,new_y,new_x;
    FILE* fn;
    curses_init();
    getmaxyx(stdscr, parent_y, parent_x);
    WINDOW *win = newwin(parent_y - 4, parent_x,4 , 0);
    WINDOW *menu = newwin(3, parent_x, 1, 0);
    WINDOW *name = newwin(1, parent_x, 0, 0);
    keypad(win, TRUE);
    curs_set(FALSE);
    //wmove(win, 0, 0);
    int ch;
    int i, y = 0, x = 0, flag;
    fn = fopen(argv[1], "a");
    while(1) {
        flag = 1;
        curs_set(FALSE);
        getmaxyx(stdscr, new_y, new_x);
        if (new_y != parent_y || new_x != parent_x) {
            flag = 0;
            parent_x = new_x;
            parent_y = new_y;
            wresize(win, new_y - 4, new_x);
            wresize(menu, 3, new_x);
            wresize(name, 1, new_x);
            //flag = 0;
        }
        
        if(flag == 1) {
            //curs_set(TRUE);
            wmove(win, x, y);
            ch = wgetch(win);
            if(ch == KEY_LEFT || ch == KEY_RIGHT || ch == KEY_UP || ch == KEY_DOWN || ch == KEY_BACKSPACE || ch == '\n') {
                switch(ch) {
                    case KEY_LEFT :
                        y--;
                        break;
                    case KEY_RIGHT :
                        if(check(win, x, y)) {
                            insert(win, '\n', x, y);
                            y = -1;
                            x++;
                        }
                        y++;
                        break;
                    case KEY_UP:
                        x--;
                        break;
                    case KEY_DOWN :
                        x++;
                        break;
                    case KEY_BACKSPACE :
                        y--;
                        if(y < 0) {
                            delete_node(x-1, getmaxy(win)-1);
                        }
                        else
                            delete_node(x, y);
                            wrefresh(win);
                            wclear(win);
                            show(win, fn);
                        break;
                    
                    case '\n' :
                        insert(win, '\n', x, y);
                        y = 0;
                        x++;
                        break;
                }
                if(y < 0) {
                    y = getmaxx(win)-1;
                    x--;
                }
                else if(y == getmaxx(win)) {
                    insert(win, '\n', x, y);
                    y = 0;
                    x++;
                }
                wmove(win, x, y);
                wrefresh(win);
            
            }
        
        
            else {
                insert(win, ch, x, y);
                y++;
                if(y == getmaxx(win)) {
                    y = 0;
                    x++;
                }
                if(y < 0) {
                    y = getmaxx(win);
                    x--;
                }
                wrefresh(win);
                wclear(win);
            // draw_borders(w);
                wrefresh(win);
                show(win, fn);
                wmove(win, x, y);
                wrefresh(win);
            }
            wrefresh(win);
            wrefresh(menu);
            wrefresh(name);
            fclose(fn);
        }
    }
    refresh();
    endwin();
    return 0;
}
