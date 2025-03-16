# Définir le compilateur et les options de compilation
CC = gcc
CFLAGS = -Wall -Wextra -g

# Liste automatique des fichiers objets
SRC = $(wildcard *.c)               # Recherche tous les fichiers .c dans le répertoire
OBJ = $(SRC:.c=.o)                   # Convertir les fichiers .c en .o
TARGET = gestionnaire                 # Nom de l'exécutable

# Règle par défaut : Compiler et lier les objets
all: $(TARGET)

# Règle pour créer l'exécutable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Règles pour compiler les fichiers objets (pas besoin de les spécifier une par une)
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Nettoyage des fichiers objets et de l'exécutable
clean:
	rm -f $(OBJ) $(TARGET)

# Règle pour exécuter le programme
run: $(TARGET)
	./$(TARGET)

# Optionnel : Règle pour installer le programme
install: $(TARGET)
	cp $(TARGET) /usr/local/bin/$(TARGET)

# Règle pour vérifier les dépendances
.PHONY: all clean run install
