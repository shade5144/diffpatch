#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydiff.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("USAGE: ./executable <SOURCE_FILENAME> <DEST_FILENAME> <PATCH_FILE>\n");
        exit(0);
    }

    Edit_List ed_ls;

    ed_ls.els_vec.data = (Edit_Node *)malloc(sizeof(Edit_Node) * 16);
    ed_ls.els_vec.capacity = 16;
    ed_ls.els_vec.ind = 0;

    ed_ls.els_ind = 0;

    FILE *f1 = fopen(argv[1], "rb");
    FILE *f2 = fopen(argv[2], "rb");

    int ret = fewest_edits(f1, f2, &ed_ls);

    printf("Edits taken: %d\n", ret);

    // printf("Edits taken: %d\n", fewest_edits(f1, f2, &ed_ls));
    // printf("-----\n");

    fclose(f1);
    fclose(f2);

    int els_tracker = ed_ls.els_ind - 1;

    String_Vector ed_buf; // Probably turn this into a String_Vector

    ed_buf.data = (char **)malloc(sizeof(char *) * 16);
    ed_buf.capacity = 16;
    ed_buf.ind = 0;

    int ins_flag = 0;

    int del_flag = 0; // Add delete range
    int del_start = 0;
    int del_end = 0;

    int prev_ind_buf = -1;
    int ind_buf = -1;

    int iter = 0;

    FILE *patch_file = fopen(argv[3], "wb");

    // Handle inserts to the same index
    while (els_tracker > -1)
    {
        ind_buf = ed_ls.els_vec.data[els_tracker].ed_ind;

        if (ins_flag)
        {
            if ((ind_buf != prev_ind_buf && prev_ind_buf != -1) || ed_buf.ind >= 128) // Flush if 128 edits are considered
            {
                appendString(&ed_buf, NULL);

                fprintf(patch_file, "I%d\n", prev_ind_buf);

                iter = 0;

                while (ed_buf.data[iter] != NULL)
                {
                    fprintf(patch_file, ">%s\n", ed_buf.data[iter]);
                    // printf(">%s\n", ed_buf.data[iter]);

                    iter++;
                }

                ed_buf.ind = 0;
                ins_flag = 0;
            }
        }

        if (ed_ls.els_vec.data[els_tracker].ed_type == 'd')
        {
            if (del_flag)
            {
                del_end = ed_ls.els_vec.data[els_tracker].ed_ind;
            }
            else
            {
                del_end = -1;
                del_start = ed_ls.els_vec.data[els_tracker].ed_ind;
                del_flag = 1;
            }
        }
        else
        {
            appendString(&ed_buf, ed_ls.els_vec.data[els_tracker].ed_val);
            ins_flag = 1;

            if (del_flag)
            {
                int del_end_buf = del_end;

                if (del_end == -1)
                {
                    del_end_buf = del_start;
                }

                fprintf(patch_file, "D%d,%d\n", del_start, del_end_buf);
            }

            del_flag = 0;
        }

        prev_ind_buf = ind_buf;
        els_tracker--;
    }

    if (ed_buf.ind > 0)
    {
        appendString(&ed_buf, NULL);

        fprintf(patch_file, "I%d\n", prev_ind_buf);

        iter = 0;

        while (ed_buf.data[iter] != NULL)
        {
            fprintf(patch_file, ">%s\n", ed_buf.data[iter]);

            iter++;
        }
    }

    if (del_flag)
    {
        int del_end_buf = del_end;

        if (del_end == -1)
        {
            del_end_buf = del_start;
        }

        fprintf(patch_file, "D%d,%d\n", del_start, del_end_buf);
    }

    fclose(patch_file);

    for (int i = 0; ed_ls.els_f1_vec[i] != NULL; i++)
    {
        free(ed_ls.els_f1_vec[i]);
    }

    for (int i = 0; ed_ls.els_f2_vec[i] != NULL; i++)
    {
        free(ed_ls.els_f2_vec[i]);
    }

    free(ed_buf.data);
    free(ed_ls.els_f1_vec);
    free(ed_ls.els_f2_vec);
    free(ed_ls.els_vec.data);
}