#ifndef WORMS_H
#define WORMS_H

/* prototyping */
void init_worm(void);
void move_worm(void);
void Draw(void);
void free_worm(void);


/*  Structures and typedefs  */

struct worm_part {
    struct worm_part * next;
    int x;
    int y;
};

typedef struct worm_part WORM;


/*  Macros  */

#define DOWN  1
#define UP    2
#define LEFT  3
#define RIGHT 4

#define WORMBIT  'O'
#define EMPTY    ' '
#define WORMFOOD 'X'

#endif  // WORMS_H
