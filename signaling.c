#include <stdlib.h>
#include <signal.h>
#include <curses.h>

#include "worms.h"

void handler(int);

void
initialize_signals(void)
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

void
handler(int signum)
{
    extern WINDOW *mainwin;
    extern int oldcur;

    switch (signum) {
    case SIGALRM:
        /*  Received from the timer  */
        move_worm();
        return;
    case SIGTERM:
    case SIGINT:
        /*  Clean up nicely  */
        delwin(mainwin);
        curs_set(oldcur);
        endwin();
        refresh();
        free_worm();
        exit(EXIT_SUCCESS);
    }
}
