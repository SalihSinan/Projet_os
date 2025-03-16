#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#define READ 4  // 100 (Lecture)
#define WRITE 2 // 010 (Écriture)
#define EXEC 1  // 001 (Exécution)

// Modifie les permissions d’un fichier
void set_permissions(const char *name, int permissions);

// Affiche les permissions d’un fichier
void get_permissions(const char *name);

// Vérifie si l'utilisateur a la permission demandée sur le fichier
int has_permission(const char *name, int requested_perm);

#endif
