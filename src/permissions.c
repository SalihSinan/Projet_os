#include <stdio.h>
#include <string.h>
#include "filesystem.h"
#include "permissions.h"
#include "utils.h"

// Modifier les permissions d’un fichier
void set_permissions(const char *name, int permissions)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (strcmp(fs.files[i].name, name) == 0)
        {
            fs.files[i].permissions = permissions;
            save_filesystem();
            // Afficher les permissions sous forme rwx
            char perms[4] = "---";
            if (permissions & READ)
                perms[0] = 'r';
            if (permissions & WRITE)
                perms[1] = 'w';
            if (permissions & EXEC)
                perms[2] = 'x';

            log_message("Permissions modifiées");
            printf("Permissions de %s mises à %s\n", name, perms);
            return;
        }
    }
    print_error("Fichier introuvable");
}

// Afficher les permissions d’un fichier
void get_permissions(const char *name)
{
    for (int i = 0; i < MAX_FILES; i++)
    {
        if (strcmp(fs.files[i].name, name) == 0)
        {
            // Afficher les permissions sous forme rwx
            printf("Permissions de %s : ", name);
            printf((fs.files[i].permissions & READ) ? "r" : "-");
            printf((fs.files[i].permissions & WRITE) ? "w" : "-");
            printf((fs.files[i].permissions & EXEC) ? "x\n" : "-\n");
            return;
        }
    }
    print_error("Fichier introuvable");
}
