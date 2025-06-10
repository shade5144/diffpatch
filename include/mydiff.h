#ifndef MY_DIFF_H
#define MY_DIFF_H

typedef struct
{
    char **data;
    int ind;
    int capacity;
} String_Vector;

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
    char *ed_val;
} Edit_Node;

typedef struct
{
    char **els_f1_vec; // Null-terminated string vectors
    char **els_f2_vec;

    Edit_Node els_arr[16];
    int els_ind;
} Edit_List;

void appendString(String_Vector *list, char *new_string);
int getLines(FILE *to_read, String_Vector *ret_list);
int fewest_edits(FILE *str1, FILE *str2, Edit_List *edit_list);

#endif // MY_DIFF_H