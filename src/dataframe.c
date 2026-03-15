/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Functions to work with
** the rows and columns from the file.
*/

#include "dataframe.h"

static int count_columns(char *line, const char *separator)
{
    int count = 0;
    char *copy = strdup(line);
    char *tmp = copy;
    char *token = strsep(&tmp, separator);

    while (token) {
        count++;
        token = strsep(&tmp, separator);
    }
    free(copy);
    return count;
}

void get_column_names(dataframe_t *df, FILE *fd, const char *separator)
{
    char line[1024];
    char *token;
    int i = 0;
    char *tmp = line;

    if (fgets(line, sizeof(line), fd)) {
        line[strcspn(line, "\n")] = '\0';
        df->nb_columns = count_columns(line, separator);
        df->column_names = malloc(sizeof(char *) * df->nb_columns);
        df->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
        token = strsep(&tmp, separator);
        while (token && i < df->nb_columns) {
            df->column_names[i] = strdup(token);
            i++;
            token = strsep(&tmp, separator);
        }
    }
}

static void process_row(dataframe_t *df, char *line, const char *separator)
{
    char *tmp = line;
    char *token = strsep(&tmp, separator);
    int current_column = 0;

    while (token && current_column < df->nb_columns) {
        df->data[df->nb_rows][current_column] = strdup(token);
        current_column++;
        token = strsep(&tmp, separator);
    }
}

void read_lines(dataframe_t *df, FILE *fd, const char *separator)
{
    char line[1024];

    while (fgets(line, sizeof(line), fd)) {
        line[strcspn(line, "\n")] = '\0';
        df->data = realloc(df->data, sizeof(void **) * (df->nb_rows + 1));
        df->data[df->nb_rows] = malloc(sizeof(void *) * df->nb_columns);
        process_row(df, line, separator);
        df->nb_rows++;
    }
}

static column_type_t mix_types(column_type_t type1, column_type_t type2)
{
    if (type1 == UNDEFINED)
        return type2;
    if (type2 == UNDEFINED)
        return type1;
    if (type1 == type2)
        return type1;
    if ((type1 == INT || type1 == UINT || type1 == FLOAT)
        && (type2 == INT || type2 == UINT || type2 == FLOAT))
        return FLOAT;
    return STRING;
}

static column_type_t get_column_type(dataframe_t *df, int col)
{
    column_type_t type = determine_str_type((char *)df->data[0][col]);
    column_type_t current_type;

    for (int row = 1; row < df->nb_rows; row++) {
        current_type = determine_str_type((char *)df->data[row][col]);
        type = mix_types(type, current_type);
    }
    return type;
}

void determine_columns_type(dataframe_t *df)
{
    for (int col = 0; col < df->nb_columns; col++) {
        df->column_types[col] = get_column_type(df, col);
    }
}
