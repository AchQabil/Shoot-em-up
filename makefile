CC = gcc
CFLAGS = -Wall -std=c17
LDFLAGS = -lMLV -lm
EXEC = shoot_em_up

SRC = main.c src/game.c src/graphics.c src/collision.c src/enemy.c src/player.c src/bullet.c  src/stars.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) -c $< $(CFLAGS) -I../include -o $@

$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@ 

clean:
	rm -f $(OBJ) $(EXEC)