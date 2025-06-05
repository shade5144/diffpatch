#ifndef MY_DIFF_H
#define MY_DIFF_H

typedef struct
{
    int *back_arr;
    int back_ind; // For indexing array
    int back_d;   // Stores actual current value of d
} Backtrack_Store;

typedef struct
{
    short ed_ind;
    char ed_type;
    char ed_val;
} Edit_Node;

typedef struct
{
    Edit_Node els_arr[16];
    int els_ind;
} Edit_List;

int fewest_edits(char *str1, char *str2, Edit_List *edit_list);

#endif // MY_DIFF_H