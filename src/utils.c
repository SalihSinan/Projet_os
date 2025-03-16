#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

// Fonction pour afficher un message de log avec horodatage (avec enregistrement dans un fichier)
void log_message(const char *message)
{
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    // Affiche le message de log à la console
    printf("[%02d-%02d-%04d %02d:%02d:%02d] LOG: %s\n",
           t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
           t->tm_hour, t->tm_min, t->tm_sec, message);

    // Enregistre le message dans un fichier log (optionnel)
    FILE *log_file = fopen("system_log.txt", "a");
    if (log_file)
    {
        fprintf(log_file, "[%02d-%02d-%04d %02d:%02d:%02d] LOG: %s\n",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                t->tm_hour, t->tm_min, t->tm_sec, message);
        fclose(log_file);
    }
}

// Fonction pour afficher une erreur et quitter le programme (avec enregistrement dans un fichier)
void print_error(const char *message)
{
    // Affiche l'erreur sur stderr
    fprintf(stderr, "ERREUR: %s\n", message);

    // Enregistre l'erreur dans un fichier log (optionnel)
    FILE *log_file = fopen("error_log.txt", "a");
    if (log_file)
    {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        fprintf(log_file, "[%02d-%02d-%04d %02d:%02d:%02d] ERREUR: %s\n",
                t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
                t->tm_hour, t->tm_min, t->tm_sec, message);
        fclose(log_file);
    }

    // Quitte le programme avec un code d'erreur
    exit(EXIT_FAILURE);
}
