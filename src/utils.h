#ifndef UTILS_H
#define UTILS_H

void log_message(const char *message);
void print_error(const char *message);
int check_permissions(int file_permissions, int required_permission);

#endif
