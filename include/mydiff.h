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
    int *data;
    int ind;
    int capacity;
} Int_Vector;

typedef struct
{
    Int_Vector back_vec;
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
    Edit_Node *data;
    int ind;
    int capacity;
} Edit_Vector;

typedef struct
{
    char **els_f1_vec; // Null-terminated string vectors
    char **els_f2_vec;

    Edit_Vector els_vec;
    int els_ind;
} Edit_List;

// Vector functions
void appendInt(Int_Vector *vec, int new_int);
void appendString(String_Vector *list, char *new_string);
void appendEditNode(Edit_Vector *vec, Edit_Node *new_node);

int getLines(FILE *to_read, String_Vector *ret_list);
int fewest_edits(FILE *str1, FILE *str2, Edit_List *edit_list);

#endif // MY_DIFF_H