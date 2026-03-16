/*
** EPITECH PROJECT, 2026
** Cuddle
** File description:
** Main entry point for the
** cuddle project.
*/

#include "dataframe.h"

int main(void)
{
    dataframe_t *df = df_read_csv("utils/data.csv", ",");
    dataframe_t *filtered;
    const char *to_agg[] = {"age", NULL};
    dataframe_t *grouped;

    if (!df)
        return 84;
    filtered = df_filter(df, "age", filter_function);
    if (df_write_csv(filtered, "filtered.csv") == -1)
        return 84;
    grouped = df_groupby(df, "city", to_agg, agg_sum_int);
    if (df_write_csv(grouped, "grouped.csv") == -1)
        return 84;
    free_df(grouped);
    free_df(df);
    free_df(filtered);
    return 0;
}
