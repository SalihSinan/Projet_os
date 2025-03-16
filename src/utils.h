#ifndef UTILS_H
#define UTILS_H

// Déclaration des fonctions existantes
void log_message(const char *message);
void print_error(const char *message);

// Ajout d'une fonction de vérification de permissions
int check_permissions(int file_permissions, int required_permission);

#endif
