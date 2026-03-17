/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Includes functions to determine
** the type of a column.
*/

#include "dataframe.h"

static int is_bool(char *str)
{
    char *tmp = to_lowercase(str);

    if (!tmp)
        return 0;
    if (strcmp(tmp, "true") == 0 || strcmp(tmp, "false") == 0) {
        free(tmp);
        return 1;
    }
    free(tmp);
    return 0;
}

static int is_uint(char *str)
{
    int i = 0;

    if (str[i] == '\0')
        return 0;
    while (str[i] != '\0') {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

static int is_int(char *str)
{
    int i = 0;

    if (str[0] == '-')
        i = 1;
    if (str[i] == '\0')
        return 0;
    while (str[i]) {
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    return 1;
}

static int is_float(char *str)
{
    int count = 0;
    int i = 0;

    if (str[0] == '-')
        i = 1;
    while (str[i]) {
        if (str[i] == '.') {
            count++;
            i++;
            continue;
        }
        if (str[i] < '0' || str[i] > '9')
            return 0;
        i++;
    }
    if (count == 1)
        return 1;
    return 0;
}

column_type_t determine_str_type(char *str)
{
    if (!str || str[0] == '\0')
        return UNDEFINED;
    if (is_bool(str))
        return BOOL;
    if (is_float(str))
        return FLOAT;
    if (is_uint(str))
        return UINT;
    if (is_int(str))
        return INT;
    return STRING;
}

static void *convert_to_int(char *str)
{
    int *value;

    if (!str || str[0] == '\0')
        return NULL;
    value = malloc(sizeof(int));
    if (!value)
        return NULL;
    if (is_int(str) || is_float(str) || is_uint(str)) {
        *value = atoi(str);
        return (void *)value;
    }
    if (strcmp(str, "true") == 0) {
        *value = 1;
    } else if (strcmp(str, "false") == 0) {
        *value = 0;
    } else {
        free(value);
        return NULL;
    }
    return (void *)value;
}

static void *convert_to_float(char *str)
{
    float *value;

    if (!str || str[0] == '\0' || (!is_float(str) && !is_int(str)))
        return NULL;
    value = malloc(sizeof(float));
    if (!value)
        return NULL;
    *value = atof(str);
    return (void *)value;
}

static void *convert_to_bool(char *str)
{
    int *value;

    if (!str || str[0] == '\0')
        return NULL;
    value = malloc(sizeof(int));
    if (!value)
        return NULL;
    if (bool_from_str(str, value))
        return (void *)value;
    if (is_int(str) || is_float(str)) {
        *value = (atof(str) != 0);
        return (void *)value;
    }
    free(value);
    return NULL;
}

static void *convert_to_uint(char *str)
{
    unsigned int *value;

    if (!str || !is_uint(str))
        return NULL;
    value = malloc(sizeof(unsigned int));
    if (!value)
        return NULL;
    *value = (unsigned int)atoi(str);
    return (void *)value;
}

void *convert_to_type(char *str, column_type_t type)
{
    if (!str)
        return NULL;
    if (type == INT)
        return convert_to_int(str);
    if (type == UINT)
        return convert_to_uint(str);
    if (type == FLOAT)
        return convert_to_float(str);
    if (type == BOOL)
        return convert_to_bool(str);
    return (void *)strdup(str);
}
