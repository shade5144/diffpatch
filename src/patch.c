#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "mydiff.h"

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        printf("USAGE: ./executable <TO_PATCH> <PATCH_FILE> <OUTPUT_FILE>\n");
        exit(0);
    }

    FILE *src = fopen(argv[1], "rb");
    FILE *patch_file = fopen(argv[2], "rb");
    FILE *dest = fopen(argv[3], "wb");

    int line_start = 0;
    int line_end = 0; // Maybe use for ranged delete?

    char *line = NULL;
    ssize_t num_read;
    size_t len;

    size_t src_len;

    int ind = 0;
    char *patch_line = NULL;

    char control_char; // I(Insert),D(Delete),>(Insertion indicator)

    int del_flag = 0;

    while ((num_read = getline(&patch_line, &len, patch_file)) != -1)
    {

        sscanf(patch_line, "%c", &control_char);

        switch (control_char)
        {
        case 'I':
        {
            sscanf(patch_line, "I%d\n", &line_start);

            while (ind != line_start)
            {
                ssize_t read_bytes = getline(&line, &src_len, src);

                fprintf(dest, "%s", line);

                ind++;
            }

            break;
        }
        case 'D':
        {
            sscanf(patch_line, "D%d,%d\n", &line_start, &line_end);

            while (ind != line_start - 1)
            {
                ssize_t read_bytes = getline(&line, &src_len, src);

                fprintf(dest, "%s", line);
                ind++;
            }

            while (ind != line_end)
            {
                ssize_t read_bytes = getline(&line, &src_len, src);

                ind++;
            }

            break;
        }
        case '>':
        {
            fprintf(dest, "%s", patch_line + 1);
            break;
        }
        default:
        {
            line_start = -1;
            line_end = -1;
            break;
        }
        }
    }

    while ((num_read = getline(&line, &len, src)) != -1)
    {
        fprintf(dest, "%s", line);
    }

    free(patch_line);
    free(line);

    fclose(src);
    fclose(patch_file);
    fclose(dest);
}