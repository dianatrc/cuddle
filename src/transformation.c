/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main and helper functions
** for the transformation.
*/

#include "dataframe.h"

void *multiply(void *value)
{
    int *new_value = malloc(sizeof(int));

    if (!new_value)
        return NULL;
    *new_value = *(int *)value * 2;
    return new_value;
}

dataframe_t *df_apply(dataframe_t *df, const char *column,
    void *(*apply_func)(void *value))
{
    dataframe_t *new_df;
    int col;
    void *tmp;

    if (!df || !column || !apply_func || df->nb_rows == 0)
        return NULL;
    col = get_column_index(df, column);
    if (col == -1)
        return NULL;
    new_df = df_head(df, df->nb_rows);
    if (!new_df)
        return NULL;
    for (int i = 0; i < new_df->nb_rows; i++) {
        if (!new_df->data[i][col])
            continue;
        tmp = new_df->data[i][col];
        new_df->data[i][col] = apply_func(tmp);
        free(tmp);
    }
    return new_df;
}
