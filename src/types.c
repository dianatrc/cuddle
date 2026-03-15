/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Includes functions to determine
** the type of a column.
*/

#include "../include/dataframe.h"

static int is_bool(char *str)
{
    if (strcmp(str, "true") == 0 || strcmp(str, "false") == 0)
        return 1;
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

static int is_string(char *str)
{
    if (!is_uint(str) && !is_float(str) && !is_int(str) && !is_bool(str))
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
    if (is_int(str))
        return INT;
    if (is_uint(str))
        return UINT;
    if (is_string(str))
        return STRING;
    return UNDEFINED;
}

static void *convert_to_int(char *str)
{
    int *value = malloc(sizeof(int));

    *value = atoi(str);
    return (void *)value;
}

static void *convert_to_float(char *str)
{
    float *value = malloc(sizeof(float));

    *value = atof(str);
    return (void *)value;
}

static void *convert_to_bool(char *str)
{
    int *value = malloc(sizeof(int));

    if (strcmp(str, "true") == 0)
        *value = 1;
    else
        *value = 0;
    return (void *)value;
}

void *convert_to_type(char *str, column_type_t type)
{
    if (type == INT || type == UINT)
        return convert_to_int(str);
    if (type == FLOAT)
        return convert_to_float(str);
    if (type == BOOL)
        return convert_to_bool(str);
    return (void *)strdup(str);
}
