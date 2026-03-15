/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Main entry point for the
** cuddle bootstrap.
*/

#include "dataframe.h"

static dataframe_t *create_df(void)
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

static dataframe_t *df_read_csv(const char *filename, const char *separator)
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

static void df_info(dataframe_t *df)
{
    char *types[] = {"bool", "int", "uint", "float", "string", "undefined"};

    printf("%d columns:\n", df->nb_columns);
    for (int i = 0; i < df->nb_columns; i++) {
        printf("- %s: %s\n", df->column_names[i], types[df->column_types[i]]);
    }
}

static dataframe_shape_t df_shape(dataframe_t *df)
{
    dataframe_shape_t shape = {df->nb_rows, df->nb_columns};

    return shape;
}

int main(int argc, char **argv)
{
    dataframe_t *df;
    dataframe_shape_t shape;

    if (argc < 2)
        return 84;
    df = df_read_csv(argv[1], ",");
    if (!df)
        return 84;
    df_info(df);
    shape = df_shape(df);
    printf("Shape: %d rows, %d columns\n", shape.nb_rows, shape.nb_columns);
    return 0;
}
