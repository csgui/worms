CFLAGS = -O2 -Wall -Wextra -Wno-unused -Wno-unused-parameter -std=c99 -D_GNU_SOURCE -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS
LDFLAGS = -lncurses
SOURCES = main.c worms.c helper.c timing.c signaling.c
HEADERS = worms.h helper.h timing.h signaling.h

worms: $(SOURCES) $(HEADERS)
	gcc $(CFLAGS) $(SOURCES) -o worms $(LDFLAGS)

clean:
	rm -f *.o worms
