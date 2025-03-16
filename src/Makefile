CC = gcc
CFLAGS = -Wall -Wextra -g

OBJ = main.o filesystem.o permissions.o utils.o

# Nom de l'exécutable
TARGET = gestionnaire

# Règle par défaut pour compiler le programme
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Compilation des fichiers objets
main.o: main.c filesystem.h permissions.h utils.h
	$(CC) $(CFLAGS) -c main.c

filesystem.o: filesystem.c filesystem.h utils.h
	$(CC) $(CFLAGS) -c filesystem.c

permissions.o: permissions.c permissions.h
	$(CC) $(CFLAGS) -c permissions.c

utils.o: utils.c utils.h
	$(CC) $(CFLAGS) -c utils.c

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f *.o $(TARGET)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)
