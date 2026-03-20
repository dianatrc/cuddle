/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Aggregation logic
*/

#include "dataframe.h"

void *agg_func(void **values, int nb_values)
{
    int *sum;

    if (!values || nb_values <= 0)
        return NULL;
    sum = malloc(sizeof(int));
    if (!sum)
        return NULL;
    *sum = 0;
    for (int i = 0; i < nb_values; i++) {
        if (values[i])
            *sum += *(int *)values[i];
    }
    return (void *)sum;
}

static int are_equals(void *value1, void *value2, column_type_t type)
{
    if (!value1 || !value2) {
        if (value1 == value2)
            return 1;
        return 0;
    }
    if (type == STRING) {
        if (strcmp((char *)value1, (char *)value2) == 0)
            return 1;
        return 0;
    }
    if (type == FLOAT) {
        if (*(float *)value1 == *(float *)value2)
            return 1;
        return 0;
    }
    if (*(int *)value1 == *(int *)value2)
        return 1;
    return 0;
}

static void allocate_names_and_types(dataframe_t *new_df, dataframe_t *df,
    int agg_count)
{
    new_df->nb_columns = agg_count + 1;
    new_df->column_names = calloc(new_df->nb_columns, sizeof(char *));
    new_df->column_types = malloc(sizeof(column_type_t) * new_df->nb_columns);
    if (df->separator)
        new_df->separator = strdup(df->separator);
    else
        new_df->separator = strdup(",");
}

static void init_columns(dataframe_t *new_df, dataframe_t *df,
    const char *group_column, const char **to_aggregate)
{
    int agg_count = 0;
    int df_index = get_column_index(df, group_column);
    int new_column_index = 1;

    for (int i = 0; to_aggregate[i]; i++)
        if (get_column_index(df, to_aggregate[i]) != -1)
            agg_count++;
    allocate_names_and_types(new_df, df, agg_count);
    new_df->column_names[0] = strdup(group_column);
    new_df->column_types[0] = df->column_types[df_index];
    for (int i = 0; to_aggregate[i]; i++) {
        df_index = get_column_index(df, to_aggregate[i]);
        if (df_index == -1)
            continue;
        new_df->column_names[new_column_index] = strdup(to_aggregate[i]);
        new_df->column_types[new_column_index] = df->column_types[df_index];
        new_column_index++;
    }
}

static void copy_group_value(dataframe_t *new_df, int new_df_row,
    dataframe_t *df, int df_indexes[2])
{
    int df_row = df_indexes[0];
    int df_column = df_indexes[1];
    column_type_t type = df->column_types[df_column];
    void *value = df->data[df_row][df_column];

    if (!value)
        return;
    if (type == STRING) {
        new_df->data[new_df_row][0] = strdup((char *)value);
        return;
    }
    if (type == FLOAT) {
        new_df->data[new_df_row][0] = malloc(sizeof(float));
        *(float *)new_df->data[new_df_row][0] = *(float *)value;
        return;
    }
    new_df->data[new_df_row][0] = malloc(sizeof(int));
    *(int *)new_df->data[new_df_row][0] = *(int *)value;
}

static int find_row_by_value(dataframe_t *df, int column_index,
    void *value)
{
    if (!df || !value)
        return -1;
    for (int i = 0; i < df->nb_rows; i++)
        if (are_equals(df->data[i][column_index], value,
                df->column_types[column_index]))
            return i;
    return -1;
}

static void build_groups(dataframe_t *new_df,
    dataframe_t *df, int group_index)
{
    int df_indexes[2];

    for (int i = 0; i < df->nb_rows; i++) {
        if (find_row_by_value(new_df, 0,
                df->data[i][group_index]) == -1) {
            new_df->data = realloc(new_df->data,
                sizeof(void **) * (new_df->nb_rows + 1));
            new_df->data[new_df->nb_rows] = calloc(new_df->nb_columns,
                sizeof(void *));
            df_indexes[0] = i;
            df_indexes[1] = group_index;
            copy_group_value(new_df, new_df->nb_rows, df, df_indexes);
            new_df->nb_rows++;
        }
    }
}

static int collect_values(dataframe_t *df, void **values,
    int *indexes, void *group_value)
{
    int n = 0;

    for (int i = 0; i < df->nb_rows; i++) {
        if (are_equals(df->data[i][indexes[0]], group_value,
                df->column_types[indexes[0]])) {
            values[n] = df->data[i][indexes[1]];
            n++;
        }
    }
    return n;
}

static void apply_agg(dataframe_t *new_df, dataframe_t *df,
    int *indexes, void *(*agg_func)(void **values, int nb_values))
{
    void **values = malloc(sizeof(void *) * df->nb_rows);
    int n = 0;
    int dest_column = indexes[2];

    if (!values)
        return;
    for (int i = 0; i < new_df->nb_rows; i++) {
        n = collect_values(df, values, indexes, new_df->data[i][0]);
        if (n > 0) {
            free(new_df->data[i][dest_column]);
            new_df->data[i][dest_column] = agg_func(values, n);
        }
    }
    free(values);
}

dataframe_t *df_groupby(dataframe_t *df, const char *aggregate_by,
    const char **to_aggregate, void *(*agg_func)(void **values, int nb_values))
{
    dataframe_t *new_df;
    int group_index;
    int indexes[3];

    if (!df || !aggregate_by || !to_aggregate || !agg_func)
        return NULL;
    group_index = get_column_index(df, aggregate_by);
    if (group_index == -1)
        return NULL;
    new_df = create_df();
    init_columns(new_df, df, aggregate_by, to_aggregate);
    build_groups(new_df, df, group_index);
    for (int i = 0; to_aggregate[i] != NULL; i++) {
        indexes[0] = group_index;
        indexes[1] = get_column_index(df, to_aggregate[i]);
        indexes[2] = get_column_index(new_df, to_aggregate[i]);
        if (indexes[1] != -1 && indexes[2] != -1)
            apply_agg(new_df, df, indexes, agg_func);
    }
    return new_df;
}
