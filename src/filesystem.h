#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void init_filesystem(const char *fs_name);
void load_filesystem(const char *fs_name);
void save_filesystem();

void create_file(const char *name, int size);
void delete_file(const char *name);
void copy_file(const char *source, const char *dest);
void move_file(const char *source, const char *dest);
void list_files();

#endif
