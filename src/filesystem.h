#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "utils.h" // Si tu utilises des fonctions de utils.h comme log_message, print_error

#define MAX_FILES 100 // Nombre maximum de fichiers

// Définition d'une entrée de fichier
typedef struct
{
    char name[100];   // Nom du fichier
    int start_block;  // Bloc de début du fichier
    int size;         // Taille du fichier en octets
    int is_directory; // Si c'est un répertoire (1) ou un fichier (0)
    int permissions;  // Permissions : 0 = "---", 1 = "--x", 2 = "-w-", 4 = "r--"
} FileEntry;

// Structure représentant le système de fichiers
typedef struct
{
    FileEntry files[MAX_FILES]; // Tableau des fichiers
    int free_space;             // Espace libre disponible
} FileSystem;

// Déclaration de la variable externe fs (le système de fichiers)
extern FileSystem fs;

// Déclaration des fonctions
void init_filesystem(const char *fs_name);            // Initialiser le système de fichiers
void load_filesystem(const char *fs_name);            // Charger le système de fichiers depuis un fichier
void save_filesystem();                               // Sauvegarder le système de fichiers
int file_exists(const char *name);                    // Vérifier si un fichier existe
void create_file(const char *name, int size);         // Créer un fichier
void delete_file(const char *name);                   // Supprimer un fichier
void copy_file(const char *source, const char *dest); // Copier un fichier
void move_file(const char *source, const char *dest); // Déplacer (renommer) un fichier
void list_files();                                    // Afficher la liste des fichiers

#endif
