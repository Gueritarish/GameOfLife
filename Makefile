CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -g

OBJS = 	src/main.o \
		src/game.o \
		src/io_utils.o

EXE = gol

gol: ${OBJS}
	${CC} -o ${EXE} ${OBJS} ${CFLAGS}

.PHONY: clean

clean:
	rm -f ${OBJS} ${EXE}