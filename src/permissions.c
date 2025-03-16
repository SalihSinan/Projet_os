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
            log_message("Permissions modifiées");
            printf("Permissions de %s mises à %d\n", name, permissions);
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
            printf("Permissions de %s : ", name);
            printf((fs.files[i].permissions & READ) ? "r" : "-");
            printf((fs.files[i].permissions & WRITE) ? "w" : "-");
            printf((fs.files[i].permissions & EXEC) ? "x\n" : "-\n");
            return;
        }
    }
    print_error("Fichier introuvable");
}
