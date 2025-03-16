#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#define MAX_FILES 100 // Nombre maximum de fichiers

typedef struct
{
    char name[100];
    int start_block;
    int size;
    int is_directory;
    int permissions; // 0: --- | 1: --x | 2: -w- | 4: r--
} FileEntry;

typedef struct
{
    FileEntry files[MAX_FILES];
    int free_space;
} FileSystem;

extern FileSystem fs; // Déclaration externe de fs

void init_filesystem(const char *fs_name);
void load_filesystem(const char *fs_name);
void save_filesystem();
int file_exists(const char *name);
void create_file(const char *name, int size);
void delete_file(const char *name);
void copy_file(const char *source, const char *dest);
void move_file(const char *source, const char *dest);
void list_files();

#endif
