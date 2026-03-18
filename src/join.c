/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Bonus: join function
** and helpers.
*/

#include "dataframe.h"

static int values_equal(void *value1, void *value2, column_type_t type)
{
    if (!value1 || !value2)
        return 0;
    if (type == FLOAT)
        return (*(float *)value1 == *(float *)value2);
    if (type == STRING)
        return (strcmp((char *)value1, (char *)value2) == 0);
    return (*(int *)value1 == *(int *)value2);
}

static dataframe_t *df_empty_alloc(int nb_columns, char *separator)
{
    dataframe_t *df = create_df();

    if (!df)
        return NULL;
    df->nb_rows = 0;
    df->nb_columns = nb_columns;
    df->column_names = malloc(sizeof(char *) * nb_columns);
    df->column_types = malloc(sizeof(column_type_t) * nb_columns);
    if (!separator)
        df->separator = strdup(",");
    else
        df->separator = strdup(separator);
    df->data = NULL;
    return df;
}

static dataframe_t *cols_types_and_names(dataframe_t *df1, dataframe_t *df2,
    int col)
{
    int new_nb_columns = df1->nb_columns + df2->nb_columns - 1;
    dataframe_t *new_df = df_empty_alloc(new_nb_columns, df1->separator);
    int i;
    int j = 0;

    if (!new_df)
        return NULL;
    for (i = 0; i < df1->nb_columns; i++) {
        new_df->column_names[j] = strdup(df1->column_names[i]);
        new_df->column_types[j] = df1->column_types[i];
        j++;
    }
    for (i = 0; i < df2->nb_columns; i++) {
        if (i == col)
            continue;
        new_df->column_names[j] = strdup(df2->column_names[i]);
        new_df->column_types[j] = df2->column_types[i];
        j++;
    }
    return new_df;
}

static void add_row(dataframe_t *new_df, dataframe_t *df1, dataframe_t *df2,
    int indexes[4])
{
    int row = new_df->nb_rows;
    int k = 0;
    int i;

    new_df->data = realloc(new_df->data, sizeof(void **) * (row + 1));
    new_df->data[row] = malloc(sizeof(void *) * new_df->nb_columns);
    for (i = 0; i < df1->nb_columns; i++) {
        new_df->data[row][k] = copy_value(df1->data[indexes[0]][i],
            df1->column_types[i]);
        k++;
    }
    for (i = 0; i < df2->nb_columns; i++) {
        if (i == indexes[3])
            continue;
        new_df->data[row][k] = copy_value(df2->data[indexes[1]][i],
            df2->column_types[i]);
        k++;
    }
    new_df->nb_rows++;
}

static void perform_action(dataframe_t *new_df, dataframe_t *df1,
    dataframe_t *df2, int indexes[4])
{
    int r1 = indexes[0];
    int r2 = indexes[1];
    int col1 = indexes[2];
    int col2 = indexes[3];

    if (values_equal(df1->data[r1][col1],
            df2->data[r2][col2], df1->column_types[col1])) {
        add_row(new_df, df1, df2, indexes);
    }
}

dataframe_t *df_join(dataframe_t *df1, dataframe_t *df2, const char *column)
{
    dataframe_t *new_df;
    int indexes[4];
    int col1 = get_column_index(df1, column);
    int col2 = get_column_index(df2, column);

    if (!df1 || !df2 || !column || col1 == -1 || col2 == -1)
        return NULL;
    new_df = cols_types_and_names(df1, df2, col2);
    if (!new_df)
        return NULL;
    indexes[2] = col1;
    indexes[3] = col2;
    for (int i = 0; i < df1->nb_rows; i++)
        for (int j = 0; j < df2->nb_rows; j++) {
            indexes[0] = i;
            indexes[1] = j;
            perform_action(new_df, df1, df2, indexes);
        }
    return new_df;
}
