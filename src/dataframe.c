/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Functions to work with
** the dataframe.
*/

#include "../include/dataframe.h"

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

void convert_data(dataframe_t *df)
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
