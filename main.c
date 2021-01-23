#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <curses.h>
#include <time.h>

#include "worms.h"
#include "helper.h"
#include "timing.h"

/* prototyping */
void set_signals(void);

WINDOW *mainwin;
int oldcur;

int
main(void)
{
    /* sets the seed which is used by rand to generate a random position for the worm food */
    srand(time(NULL));

    /* game timing setup */
    initialize_timer();

    /* set process signals */
    set_signals();

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

/* game signaling set up  */
void
set_signals(void)
{
    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    /* set signal handlers */
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGALRM, &sa, NULL);

    /* ignore SIGTSTP */
    sa.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &sa, NULL);
}
