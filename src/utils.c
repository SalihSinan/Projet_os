#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Fonction pour afficher un message de log avec horodatage
void log_message(const char *message)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    printf("[%02d-%02d-%04d %02d:%02d:%02d] LOG: %s\n",
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
           t->tm_hour, t->tm_min, t->tm_sec, message);
}

// Fonction pour afficher une erreur et quitter le programme
void print_error(const char *message)
{
    fprintf(stderr, "ERREUR: %s\n", message);
    exit(EXIT_FAILURE);
}
