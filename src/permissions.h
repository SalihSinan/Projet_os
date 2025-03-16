#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#define READ 4  // 100 (Lecture)
#define WRITE 2 // 010 (Écriture)
#define EXEC 1  // 001 (Exécution)

void set_permissions(const char *name, int permissions);
void get_permissions(const char *name);
int has_permission(const char *name, int requested_perm);

#endif
