#ifndef MY_DIFF_H
#define MY_DIFF_H

typedef struct
{
    int *back_arr;
    int back_ind; // For indexing array
    int back_d;   // Stores actual current value of d
} Backtrack_Store;

int fewest_edits(char *str1, char *str2);

#endif // MY_DIFF_H