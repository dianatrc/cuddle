/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main and helper
** functions for sorting.
*/

#include "dataframe.h"

bool compare_int(void *value1, void *value2)
{
    if (!value1 && !value2)
        return false;
    if (!value1)
        return false;
    if (!value2)
        return true;
    return (*(int *)value1 < *(int *)value2);
}

bool compare_float(void *value1, void *value2)
{
    if (!value1 && !value2)
        return false;
    if (!value1)
        return false;
    if (!value2)
        return true;
    return (*(float *)value1 < *(float *)value2);
}

bool compare_string(void *value1, void *value2)
{
    if (!value1 && !value2)
        return false;
    if (!value1)
        return false;
    if (!value2)
        return true;
    return (strcmp((char *)value1, (char *)value2) < 0);
}

static void swap_rows(void ***data, int i, int j)
{
    void **tmp = data[i];

    data[i] = data[j];
    data[j] = tmp;
}

static int partition(dataframe_t *df, int bounds[2], int col,
    bool (*sort_func)(void *value1, void *value2))
{
    void *pivot_val = df->data[bounds[1]][col];
    int i = bounds[0] - 1;

    for (int j = bounds[0]; j < bounds[1]; j++) {
        if (sort_func(df->data[j][col], pivot_val)) {
            i++;
            swap_rows(df->data, i, j);
        }
    }
    swap_rows(df->data, i + 1, bounds[1]);
    return (i + 1);
}

static void quicksort(dataframe_t *df, int bounds[2], int col,
    bool (*sort_func)(void *value1, void *value2))
{
    int pivot;
    int left[2];
    int right[2];

    if (bounds[0] < bounds[1]) {
        pivot = partition(df, bounds, col, sort_func);
        left[0] = bounds[0];
        left[1] = pivot - 1;
        right[0] = pivot + 1;
        right[1] = bounds[1];
        quicksort(df, left, col, sort_func);
        quicksort(df, right, col, sort_func);
    }
}

dataframe_t *df_sort(dataframe_t *df, const char *column,
    bool (*sort_func)(void *value1, void *value2))
{
    dataframe_t *new_df;
    int col;
    int bounds[2];

    if (!df || !column || !sort_func || df->nb_rows < 1)
        return NULL;
    new_df = df_head(df, df->nb_rows);
    if (!new_df || !new_df->data)
        return NULL;
    if (new_df->nb_rows == 1)
        return new_df;
    col = get_column_index(new_df, column);
    if (col == -1)
        return NULL;
    bounds[0] = 0;
    bounds[1] = new_df->nb_rows - 1;
    quicksort(new_df, bounds, col, sort_func);
    return new_df;
}
