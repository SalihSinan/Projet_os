#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "filesystem.h"
#include "utils.h"

#define FS_SIZE 1024 * 1024 // 1MB pour la partition
#define BLOCK_SIZE 512      // Taille d'un bloc

FileSystem fs;              // Définition de fs (pas de static ici)
static FILE *fs_file;       // Fichier où la "partition" est stockée
static int has_changes = 0; // Indicateur pour savoir si une modification a été effectuée

// 🔹 Initialisation du système de fichiers
void init_filesystem(const char *fs_name)
{
    fs_file = fopen(fs_name, "wb+");
    if (!fs_file)
    {
        print_error("Impossible d'ouvrir le fichier système");
    }

    fs.free_space = FS_SIZE;
    memset(fs.files, 0, sizeof(fs.files));

    fwrite(&fs, sizeof(FileSystem), 1, fs_file);
    fclose(fs_file);
    log_message("Système de fichiers initialisé");
}

// 🔹 Chargement du système de fichiers
void load_filesystem(const char *fs_name)
{
    fs_file = fopen(fs_name, "rb+");
    if (!fs_file)
    {
        print_error("Erreur lors de l'ouverture du fichier système");
    }

    fread(&fs, sizeof(FileSystem), 1, fs_file);
}

// 🔹 Sauvegarde des modifications
void save_filesystem()
{
    if (!has_changes)
        return;

    fseek(fs_file, 0, SEEK_SET);
    fwrite(&fs, sizeof(FileSystem), 1, fs_file);
    fflush(fs_file);
    has_changes = 0; // Réinitialiser l'indicateur après la sauvegarde
}

// 🔹 Vérification si un fichier existe déjà
int file_exists(const char *name)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs.files[i].size > 0 && strcmp(fs.files[i].name, name) == 0)
        {
            return 1; // Existe déjà
        }
    }
    return 0;
}

// 🔹 Création d'un fichier
void create_file(const char *name, int size)
{
    if (fs.free_space < size)
    {
        printf("Espace insuffisant pour créer le fichier %s\n", name);
        return;
    }

    if (file_exists(name))
    {
        printf("Erreur : un fichier du même nom existe déjà\n");
        return;
    }

    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs.files[i].size == 0)
        { // Trouver un emplacement libre
            strcpy(fs.files[i].name, name);
            fs.files[i].size = size;
            fs.files[i].is_directory = 0;
            fs.files[i].permissions = 6; // Lecture + écriture (rw-)

            fs.free_space -= size;
            has_changes = 1; // Indiquer qu'une modification a été effectuée
            printf("Fichier '%s' créé avec succès (%d bytes)\n", name, size);
            log_message("Fichier créé");
            return;
        }
    }

    printf("Erreur : limite de fichiers atteinte\n");
}

// 🔹 Suppression d'un fichier
void delete_file(const char *name)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs.files[i].size > 0 && strcmp(fs.files[i].name, name) == 0)
        {
            fs.free_space += fs.files[i].size;
            memset(&fs.files[i], 0, sizeof(FileEntry));
            has_changes = 1; // Indiquer qu'une modification a été effectuée
            save_filesystem();
            printf("Fichier '%s' supprimé\n", name);
            log_message("Fichier supprimé");
            return;
        }
    }

    printf("Erreur : fichier '%s' non trouvé\n", name);
}

// 🔹 Copie d'un fichier
void copy_file(const char *source, const char *dest)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs.files[i].size > 0 && strcmp(fs.files[i].name, source) == 0)
        {
            create_file(dest, fs.files[i].size);
            printf("Fichier '%s' copié en '%s'\n", source, dest);
            log_message("Fichier copié");
            return;
        }
    }

    printf("Erreur : fichier source '%s' introuvable\n", source);
}

// 🔹 Déplacement (renommage) d'un fichier
void move_file(const char *source, const char *dest)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs.files[i].size > 0 && strcmp(fs.files[i].name, source) == 0)
        {
            strcpy(fs.files[i].name, dest);
            has_changes = 1; // Indiquer qu'une modification a été effectuée
            save_filesystem();
            printf("Fichier '%s' déplacé en '%s'\n", source, dest);
            log_message("Fichier déplacé");
            return;
        }
    }

    printf("Erreur : fichier '%s' introuvable\n", source);
}

// 🔹 Affichage des fichiers existants avec permissions
void list_files()
{
    printf("\n📂 Fichiers dans le système :\n");
    printf("| %-20s | %-10s | %-5s |\n", "Nom", "Taille", "Permissions");
    printf("------------------------------------------------\n");

    int found = 0;
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (fs.files[i].size > 0)
        {
            found = 1;
            printf("| %-20s | %-10d | ", fs.files[i].name, fs.files[i].size);
            printf((fs.files[i].permissions & 4) ? "r" : "-");
            printf((fs.files[i].permissions & 2) ? "w" : "-");
            printf((fs.files[i].permissions & 1) ? "x" : "-");
            printf(" |\n");
        }
    }

    if (!found)
    {
        printf("Aucun fichier enregistré.\n");
    }
}
