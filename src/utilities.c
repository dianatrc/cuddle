/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main and helper
** utilities functions.
*/

#include "dataframe.h"

void *df_get_value(dataframe_t *df, int row, const char *column)
{
    int col;

    if (!df || row < 0 || row >= df->nb_rows || !column)
        return NULL;
    col = get_column_index(df, column);
    if (col == -1)
        return NULL;
    if (!df->data[row][col])
        return NULL;
    return df->data[row][col];
}

void **df_get_values(dataframe_t *df, const char *column)
{
    void **values = malloc(sizeof(void *) * (df->nb_rows + 1));
    int col;
    int i;

    if (!df || !column || !values)
        return NULL;
    col = get_column_index(df, column);
    if (col == -1) {
        free(values);
        return NULL;
    }
    for (i = 0; i < df->nb_rows; i++)
        values[i] = df->data[i][col];
    values[i] = NULL;
    return values;
}

static int value_exists(void **values, int count, void *val,
    column_type_t type)
{
    for (int i = 0; i < count; i++) {
        if (type == STRING && strcmp((char *)values[i], (char *)val) == 0)
            return 1;
        if (type != STRING && *(int *)values[i] == *(int *)val)
            return 1;
    }
    return 0;
}

void **df_get_unique_values(dataframe_t *df, const char *column)
{
    void **values = malloc(sizeof(void *) * (df->nb_rows + 1));
    int col;
    int count = 0;

    if (!df || df->nb_rows == 0 || !column || !values)
        return NULL;
    col = get_column_index(df, column);
    if (col == -1)
        return NULL;
    for (int i = 0; i < df->nb_rows; i++) {
        if (!df->data[i][col])
            continue;
        if (value_exists(values, count, df->data[i][col],
                df->column_types[col]) == 0) {
            values[count] = df->data[i][col];
            count++;
        }
    }
    values[count] = NULL;
    return values;
}

void df_free(dataframe_t *df)
{
    if (!df)
        return;
    for (int i = 0; i < df->nb_columns; i++)
        free(df->column_names[i]);
    free(df->column_names);
    free(df->column_types);
    for (int i = 0; df->data && i < df->nb_rows; i++) {
        for (int j = 0; df->data[i] && j < df->nb_columns; j++)
            free(df->data[i][j]);
        free(df->data[i]);
    }
    free(df->data);
    free(df);
}
