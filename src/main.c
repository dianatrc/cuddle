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
    dataframe_t *new_df;

    if (!df)
        return 84;
    df_info(df);
    new_df = df_to_type(df, "score", BOOL);
    if (new_df == NULL)
        printf("error convert\n");
    else
        df_info(new_df);
    if (df_write_csv(new_df, "to_type.csv") == -1)
        return 84;
    df_free(new_df);
    df_free(df);
    return 0;
}
