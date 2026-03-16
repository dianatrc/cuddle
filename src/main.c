/*
** EPITECH PROJECT, 2026
** Cuddle - Bootstrap
** File description:
** Main entry point for the
** cuddle bootstrap.
*/

#include "../include/dataframe.h"

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
    df_describe(df);
    return 0;
}
