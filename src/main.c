/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main entry point for the
** cuddle project.
*/

#include "dataframe.h"

static void test_get_values(dataframe_t *df, void **values)
{
    for (int i = 0; i < df->nb_rows; i++) {
        if (values[i])
            printf("Value: %d\n", *(int *)values[i]);
        else
            printf("Value: empty\n");
    }
}

static void test_functions(dataframe_t *df)
{
    dataframe_t *filtered = df_filter(df, "age", filter_function);
    dataframe_t *sorted = df_sort(df, "age", compare_int);
    dataframe_t *transformed = df_apply(df, "age", multiply);
    void **values = df_get_values(df, "age");

    df_write_csv(filtered, "filtered.out");
    df_write_csv(sorted, "sorted.out");
    df_write_csv(transformed, "transformed.out");
    test_get_values(df, values);
    df_free(filtered);
    df_free(sorted);
    df_free(transformed);
    free(values);
}

int main(int argc, char **argv)
{
    dataframe_t *df;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s filename.csv\n", argv[0]);
        return 84;
    }
    df = df_read_csv(argv[1], ",");
    if (!df)
        return 84;
    df_info(df);
    test_functions(df);
    df_free(df);
    return 0;
}
