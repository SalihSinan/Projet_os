#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filesystem.h"
#include "permissions.h"
#include "utils.h"

#define FS_NAME "partition.fs"

void shell()
{
    char command[100], arg1[100], arg2[100];
    int perms, size;

    while (1)
    {
        printf("\nfs> ");
        fgets(command, 100, stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "ls", 2) == 0)
        {
            list_files();
        }
        else if (sscanf(command, "touch %s %d", arg1, &size) == 2)
        {
            // Si une taille est spécifiée, utiliser cette taille, sinon utiliser la taille par défaut (1024)
            if (size <= 0)
            {
                size = 1024; // Taille par défaut si aucune taille ou taille invalide n'est donnée
            }
            create_file(arg1, size);
        }
        else if (sscanf(command, "rm %s", arg1) == 1)
        {
            delete_file(arg1);
        }
        else if (sscanf(command, "cp %s %s", arg1, arg2) == 2)
        {
            copy_file(arg1, arg2);
        }
        else if (sscanf(command, "mv %s %s", arg1, arg2) == 2)
        {
            move_file(arg1, arg2);
        }
        else if (sscanf(command, "chmod %d %s", &perms, arg2) == 2)
        {
            set_permissions(arg2, perms);
        }
        else if (strcmp(command, "exit") == 0)
        {
            save_filesystem();
            printf("Fermeture...\n");
            break;
        }
        else
        {
            printf("Commande inconnue\n");
        }
    }
}

int main()
{
    load_filesystem(FS_NAME); // Charger le système de fichiers
    printf("Système de fichiers chargé avec succès.\n");
    shell(); // Lancer le shell
    return 0;
}
