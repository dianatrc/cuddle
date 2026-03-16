/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Functions to work with
** the dataframe and the CSV file.
*/

#include "dataframe.h"

dataframe_t *create_df(void)
{
    dataframe_t *df = malloc(sizeof(dataframe_t));

    if (!df)
        return NULL;
    df->nb_rows = 0;
    df->nb_columns = 0;
    df->column_names = NULL;
    df->column_types = NULL;
    df->data = NULL;
    return df;
}

static void convert_data(dataframe_t *df)
{
    char *tmp;

    for (int i = 0; i < df->nb_rows; i++) {
        for (int j = 0; j < df->nb_columns; j++) {
            tmp = df->data[i][j];
            df->data[i][j] = convert_to_type(tmp, df->column_types[j]);
            free(tmp);
        }
    }
}

dataframe_t *df_read_csv(const char *filename, const char *separator)
{
    FILE *fd = fopen(filename, "r");
    dataframe_t *df;

    if (!fd)
        return NULL;
    df = create_df();
    if (!df) {
        fclose(fd);
        return NULL;
    }
    get_column_names(df, fd, separator);
    read_lines(df, fd, separator);
    determine_columns_type(df);
    convert_data(df);
    fclose(fd);
    return df;
}

static void print_cell(FILE *fd, dataframe_t *df, int i, int j)
{
    if (df->data[i][j] == NULL)
        return;
    if (df->column_types[j] == STRING)
        fprintf(fd, "%s", (char *)df->data[i][j]);
    if (df->column_types[j] == FLOAT)
        fprintf(fd, "%f", *(float *)df->data[i][j]);
    if (df->column_types[j] == INT)
        fprintf(fd, "%d", *(int *)df->data[i][j]);
    if (df->column_types[j] == UINT)
        fprintf(fd, "%u", *(unsigned int *)df->data[i][j]);
    if (df->column_types[j] == BOOL && *(int *)df->data[i][j] == 1)
        fprintf(fd, "true");
    else if (df->column_types[j] == BOOL && *(int *)df->data[i][j] == 0)
        fprintf(fd, "false");
}

static void write_row(FILE *fd, dataframe_t *df, int i)
{
    for (int j = 0; j < df->nb_columns; j++) {
        print_cell(fd, df, i, j);
        if (j < df->nb_columns - 1)
            fprintf(fd, ",");
        else
            fprintf(fd, "\n");
    }
}

int df_write_csv(dataframe_t *df, const char *filename)
{
    FILE *fd = fopen(filename, "w");

    if (!fd || !df)
        return -1;
    for (int i = 0; i < df->nb_columns; i++)
        if (i < df->nb_columns - 1)
            fprintf(fd, "%s,", df->column_names[i]);
        else
            fprintf(fd, "%s\n", df->column_names[i]);
    for (int i = 0; i < df->nb_rows; i++)
        write_row(fd, df, i);
    fclose(fd);
    return 0;
}

void copy_data(dataframe_t *new_df, int i_new_df,
    dataframe_t *df, int i_old_df)
{
    int size;

    for (int j = 0; j < df->nb_columns; j++) {
        if (!df->data[i_old_df][j]) {
            new_df->data[i_new_df][j] = NULL;
            continue;
        }
        if (new_df->column_types[j] == STRING) {
            new_df->data[i_new_df][j] = strdup((char *)df->data[i_old_df][j]);
            continue;
        }
        if (new_df->column_types[j] == FLOAT)
            size = sizeof(float);
        else
            size = sizeof(int);
        new_df->data[i_new_df][j] = malloc(size);
        if (new_df->data[i_new_df][j])
            memcpy(new_df->data[i_new_df][j], df->data[i_old_df][j], size);
    }
}

dataframe_t *init_new_df(dataframe_t *df, int nb_rows)
{
    dataframe_t *new_df = create_df();

    if (!new_df)
        return NULL;
    new_df->nb_rows = nb_rows;
    new_df->nb_columns = df->nb_columns;
    new_df->column_names = malloc(sizeof(char *) * df->nb_columns);
    new_df->column_types = malloc(sizeof(column_type_t) * df->nb_columns);
    new_df->data = malloc(sizeof(void **) * nb_rows);
    for (int i = 0; i < df->nb_columns; i++) {
        new_df->column_names[i] = strdup(df->column_names[i]);
        new_df->column_types[i] = df->column_types[i];
    }
    return new_df;
}
