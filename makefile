CC = gcc
CFLAGS = -Wall -std=c17
LDFLAGS = -lMLV -lm
EXEC = bin/shoot_em_up main.o

# Liste des fichiers sources
SRC = main.c src/game.c src/collision.c src/player.c src/bullet.c src/stars.c  src/explosion.c src/menu.c
OBJ = $(SRC:src/%.c=bin/%.o)

# Règle pour la création du dossier bin
$(shell mkdir -p bin)

# Règle pour la compilation des fichiers objets
bin/%.o: src/%.c
	$(CC) -c $< $(CFLAGS) -Iinclude -o $@

# Règle pour la création de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $@

# Règle pour nettoyer les fichiers objets, en excluant main.c
clean:
	rm -f $(filter-out main.c, $(OBJ))  $(EXEC)

