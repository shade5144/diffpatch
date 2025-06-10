#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydiff.h"

// TODO:
// - Generate actionable patch script
// - Change static arrays to vectors

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("USAGE: ./executable <SOURCE_FILENAME> <DEST_FILENAME>\n");
        exit(0);
    }

    Edit_List ed_ls;

    ed_ls.els_vec.data = (Edit_Node *)malloc(sizeof(Edit_Node) * 16);
    ed_ls.els_vec.capacity = 16;
    ed_ls.els_vec.ind = 0;

    ed_ls.els_ind = 0;

    FILE *f1 = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "rb");

    printf("Edits taken: %d\n", fewest_edits(f1, f2, &ed_ls));
    printf("-----\n");

    int els_tracker = ed_ls.els_ind - 1;

    // for (int i = 0; i < ed_ls.els_ind; i++)
    // {
    //     printf("%d ", ed_ls.els_arr[i].ed_ind);
    // }

    // printf("\n");

    char *ed_buf[16];
    char ed_buf_ind = 0;

    int ins_flag = 0;
    int prev_ind_buf = -1;
    int ind_buf = -1;

    int iter = 0;

    // Handle inserts to the same index
    while (els_tracker > -1)
    {
        ind_buf = ed_ls.els_vec.data[els_tracker].ed_ind;

        if (ins_flag)
        {
            if (ind_buf != prev_ind_buf && prev_ind_buf != -1)
            {
                ed_buf[ed_buf_ind] = NULL;

                printf("I%d\n", prev_ind_buf);

                for (iter = 0; iter < ed_buf_ind; iter++)
                {
                    printf("> %s\n", ed_buf[iter]);

                    iter++;
                }

                ed_buf_ind = 0;
                ins_flag = 0;
            }
        }

        if (ed_ls.els_vec.data[els_tracker].ed_type == 'd')
        {
            printf("D%d\n", ed_ls.els_vec.data[els_tracker].ed_ind);
            printf("< %s\n", ed_ls.els_vec.data[els_tracker].ed_val);
        }
        else
        {
            // printf("-->%s\n", ed_ls.els_arr[els_tracker].ed_val);
            ed_buf[ed_buf_ind++] = ed_ls.els_vec.data[els_tracker].ed_val;
            ins_flag = 1;
            // printf("I%d%c\n", ed_ls.els_arr[els_tracker].ed_ind, ed_ls.els_arr[els_tracker].ed_val);
        }

        prev_ind_buf = ind_buf;
        els_tracker--;
    }

    if (ed_buf_ind > 0)
    {
        ed_buf[ed_buf_ind] = NULL;

        printf("I%d\n", prev_ind_buf);

        iter = 0;

        while (ed_buf[iter] != NULL)
        {
            printf("> %s\n", ed_buf[iter]);

            iter++;
        }
    }
}