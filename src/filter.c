/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Data filtering functions.
*/

#include "dataframe.h"

bool filter_function(void *value)
{
    if (!value)
        return false;
    return *(int *)value > 30;
}

static int add_filtered_row(dataframe_t *new_df, dataframe_t *df,
    int i)
{
    void ***tmp = realloc(new_df->data,
        sizeof(void **) * (new_df->nb_rows + 1));

    if (!tmp)
        return 0;
    new_df->data = tmp;
    new_df->data[new_df->nb_rows] = malloc(sizeof(void *) * df->nb_columns);
    if (!new_df->data[new_df->nb_rows])
        return 0;
    copy_data(new_df, new_df->nb_rows, df, i);
    new_df->nb_rows++;
    return 1;
}

dataframe_t *df_filter(dataframe_t *df, const char *column,
    bool (*filter_function)(void *value))
{
    int column_index = 0;
    dataframe_t *new_df;

    if (!df || !column || !filter_function)
        return NULL;
    column_index = get_column_index(df, column);
    if (column_index == -1)
        return NULL;
    new_df = init_new_df(df, 0);
    if (!new_df)
        return NULL;
    for (int i = 0; i < df->nb_rows; i++)
        if (filter_function(df->data[i][column_index]) &&
            !(add_filtered_row(new_df, df, i))) {
            df_free(new_df);
            return NULL;
        }
    return new_df;
}
