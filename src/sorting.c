/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main and helper
** functions for sorting.
*/

#include "dataframe.h"

static int get_column_index(dataframe_t *df, const char *column)
{
    for (int i = 0; i < df->nb_columns; i++)
        if (strcmp(df->column_names[i], column) == 0)
            return i;
    return -1;
}

static void swap_rows(dataframe_t *df, int a, int b)
{
    void **tmp = df->data[a];

    df->data[a] = df->data[b];
    df->data[b] = tmp;
}

static void sort_rows(dataframe_t *df, int col, int i,
    bool (*sort_func)(void *, void *))
{
    for (int j = 0; j < df->nb_rows - i - 1; j++) {
        if (!df->data[j] || !df->data[j + 1] ||
            !df->data[j][col] || !df->data[j + 1][col])
            continue;
        if (sort_func(df->data[j][col], df->data[j + 1][col]))
            swap_rows(df, j, j + 1);
    }
}

bool compare_int(void *value1, void *value2)
{
    if (!value1 || !value2)
        return false;
    return (*(int *)value1 > *(int *)value2);
}

bool compare_float(void *value1, void *value2)
{
    if (!value1 || !value2)
        return false;
    return (*(float *)value1 > *(float *)value2);
}

bool compare_string(void *value1, void *value2)
{
    if (!value1 || !value2)
        return false;
    return (strcmp((char *)value1, (char *)value2) > 0);
}

dataframe_t *df_sort(dataframe_t *df, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    dataframe_t *new_df;
    int col;

    if (!df || !column || !sort_func || df->nb_rows < 1)
        return NULL;
    new_df = df_head(df, df->nb_rows);
    if (!new_df || !new_df->data)
        return NULL;
    if (df->nb_rows == 1)
        return new_df;
    col = get_column_index(df, column);
    if (col == -1)
        return NULL;
    for (int i = 0; i < new_df->nb_rows - 1; i++)
        sort_rows(new_df, col, i, sort_func);
    return new_df;
}
