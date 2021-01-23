#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <curses.h>
#include <time.h>

#include "worms.h"
#include "timing.h"
#include "signaling.h"
#include "helper.h"

/* prototyping */
void set_signals(void);

WINDOW *mainwin;
int oldcur;

int
main(void)
{
    /* sets the seed which is used by rand to generate a random position for the worm food */
    srand(time(NULL));

    /* game timing */
    initialize_timer();

    /* game signaling */
    initialize_signals();

    /* initialize ncurses */
    if ((mainwin = initscr()) == NULL) {
        perror("error initializing ncurses");
        exit(EXIT_FAILURE);
    }
    noecho();
    keypad(mainwin, TRUE);
    oldcur = curs_set(0);

    /* initialize worm and draw it */
    init_worm();
    Draw();

    /* game loop */
    while (1) {
        int key = getch();

        switch (key) {

        case KEY_UP:
        case 'Y':
        case 'y':
            ChangeDir(UP);
            break;

        case KEY_DOWN:
        case 'N':
        case 'n':
            ChangeDir(DOWN);
            break;

        case KEY_LEFT:
        case 'G':
        case 'g':
            ChangeDir(LEFT);
            break;

        case KEY_RIGHT:
        case 'J':
        case 'j':
            ChangeDir(RIGHT);
            break;

        case 'Q':
        case 'q':
            Quit(USER_QUIT);
            break;
        }
    }

    /*  We never get here  */
    return EXIT_SUCCESS;
}
