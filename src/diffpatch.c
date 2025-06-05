#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydiff.h"

// TODO:
// - Edit Script
// - Generalize for multiple lines

int main()
{
    // char *string1 = "ABCABBA";
    // char *string2 = "CBABAC";

    char *string1 = "abcd";
    char *string2 = "ba";

    // char *string1 = "ab";
    // char *string2 = "abcd";

    // char *string2 = "abcd";
    // char *string1 = "";

    Edit_List ed_ls;
    ed_ls.els_ind = 0;

    printf("String1: %s\n", string1);
    printf("String2: %s\n", string2);

    printf("%d\n", fewest_edits(string1, string2, &ed_ls));

    int els_tracker = ed_ls.els_ind - 1;

    for (int i = 0; i < ed_ls.els_ind; i++)
    {
        printf("%d ", ed_ls.els_arr[i].ed_ind);
    }

    printf("\n");

    char ed_buf[16];
    char ed_buf_ind = 0;

    int ins_flag = 0;
    int prev_ind_buf = -1;
    int ind_buf = -1;

    // Handle inserts to the same index
    while (els_tracker > -1)
    {
        ind_buf = ed_ls.els_arr[els_tracker].ed_ind;

        if (ins_flag)
        {
            if (ind_buf != prev_ind_buf && prev_ind_buf != -1)
            {
                ed_buf[ed_buf_ind] = '\0';
                printf("I%d%s\n", prev_ind_buf, ed_buf);

                ed_buf_ind = 0;
                ins_flag = 0;
            }
        }

        if (ed_ls.els_arr[els_tracker].ed_type == 'd')
        {
            printf("D%d\n", ed_ls.els_arr[els_tracker].ed_ind);
        }
        else
        {
            ed_buf[ed_buf_ind++] = ed_ls.els_arr[els_tracker].ed_val;
            ins_flag = 1;
            // printf("I%d%c\n", ed_ls.els_arr[els_tracker].ed_ind, ed_ls.els_arr[els_tracker].ed_val);
        }

        prev_ind_buf = ind_buf;
        els_tracker--;
    }

    if (ed_buf_ind > 0)
    {
        printf("I%d%s\n", prev_ind_buf, ed_buf);
    }
}