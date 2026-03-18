/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Helper functions
*/

#include "dataframe.h"

char *to_lowercase(const char *str)
{
    char *tmp;

    if (!str)
        return NULL;
    tmp = strdup(str);
    if (!tmp)
        return NULL;
    for (int i = 0; tmp[i] != '\0'; i++) {
        if (tmp[i] >= 'A' && tmp[i] <= 'Z')
            tmp[i] += 32;
    }
    return tmp;
}

int bool_from_str(char *str, int *value)
{
    char *tmp = to_lowercase(str);

    if (!tmp)
        return 0;
    if (strcmp(tmp, "true") == 0 || strcmp(tmp, "false") == 0) {
        *value = (strcmp(tmp, "true") == 0);
        free(tmp);
        return 1;
    }
    free(tmp);
    return 0;
}
