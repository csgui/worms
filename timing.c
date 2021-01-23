#include <stdlib.h>
#include <sys/time.h> // time interval utilities

#define TIMESTEP 250000 // .25 seconds in microseconds

static void reset_timer(struct itimerval*);
static void set_timer(struct itimerval*);

/*
 * Initializes the game timing.
 *
 * Timer is used to signal a process in a time interval basis.
 * The signaling is done when the timer expires.
 */
void
initialize_timer(void)
{
    struct itimerval it;

    reset_timer(&it);
    set_timer(&it);
}

static void
reset_timer(struct itimerval *timer)
{
    timerclear(&(*timer).it_interval);
    timerclear(&(*timer).it_value);
}

static void
set_timer(struct itimerval *timer)
{
    (*timer).it_interval.tv_usec = TIMESTEP;
    (*timer).it_value.tv_usec = TIMESTEP;

    setitimer(ITIMER_REAL, &(*timer), NULL);
}
