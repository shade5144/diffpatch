#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "mydiff.h"

void appendString(String_Vector *list, char *new_string)
{
	if (list->ind + 1 > list->capacity)
	{
		list->data = (char **)realloc(list->data, sizeof(char *) * list->capacity * 2);

		list->capacity *= 2;
	}

	list->data[list->ind] = new_string;
	list->ind += 1;
}

int getLines(FILE *file, String_Vector *ret_list)
{
	char *line = NULL;
	char *buf;
	ssize_t num_read;
	size_t len;

	int ind = 0;

	while ((num_read = getline(&line, &len, file)) != -1)
	{
		buf = (char *)malloc(sizeof(char) * (num_read + 1));

		if (line[num_read - 1] == '\n')
		{
			line[num_read - 1] = '\0';
		}

		strcpy(buf, line);

		appendString(ret_list, buf);

		ind++;
	}

	return ind;
}

int fewest_edits(FILE *file1, FILE *file2, Edit_List *edit_list)
{
	int d = 0;

	String_Vector str_list1;
	String_Vector str_list2;

	str_list1.data = (char **)malloc(sizeof(char *) * 8);
	str_list1.capacity = 8;
	str_list1.ind = 0;

	str_list2.data = (char **)malloc(sizeof(char *) * 8);
	str_list2.capacity = 8;
	str_list2.ind = 0;

	int n = getLines(file1, &str_list1);
	int m = getLines(file2, &str_list2);

	int max = m + n;

	int *v = (int *)malloc(sizeof(int) * (2 * max + 1));

	Backtrack_Store backtrack;

	backtrack.back_arr = (int *)malloc(sizeof(int) * 128); // Consider using a vector
	backtrack.back_ind = -1;
	backtrack.back_d = -1;

	printf("File1 %d: \n", n);
	for (int i = 0; i < n; i++)
	{
		printf("%s\n", str_list1.data[i]);
	}

	printf("File2 %d: \n", m);
	for (int i = 0; i < m; i++)
	{
		printf("%s\n", str_list2.data[i]);
	}

	int mid = max / 2;

	if (m > n)
	{
		mid = (2 * max) - mid;
	}

	v[mid] = 0;

	for (int d = 0; d <= max; d++)
	{
		for (int k = -d; k <= d; k += 2)
		{
			if (k < -m || k > n)
			{
				backtrack.back_ind++;
				backtrack.back_arr[backtrack.back_ind] = -1;
				continue;
			}

			int x;

			if (k == -d || (k != d && v[k + mid - 1] < v[k + mid + 1]))
			{
				x = v[k + mid + 1];
			}
			else
			{
				x = v[k + mid - 1] + 1;
			}

			int y = x - k;

			if (y >= 0)
			{
				while (x < n && y < m && !strcmp(str_list1.data[x], str_list2.data[y]))
				{
					x++;
					y++;
				}
			}

			v[k + mid] = x;

			backtrack.back_ind++;
			backtrack.back_arr[backtrack.back_ind] = x;

			if (x >= n && y >= m)
			{
				int back_d = backtrack.back_d;

				int cur_k;
				int prev_k = x - y;

				int prev_x, prev_y;

				for (int a = back_d; a > -1; a--) // Iterate backwards for d
				{
					cur_k = x - y;

					int base = (a - 1) * (a) / 2 + (a == 1);

					for (int l = -a + 1; l <= a - 1; l += 2) // Revert the array to the previous state
					{
						int temp = backtrack.back_arr[base];

						if (temp >= 0)
						{
							v[mid + l] = temp;
						}

						base++;
					}

					if (a == 0)
					{
						v[mid] = backtrack.back_arr[0];
					}

					if (cur_k == -a || (cur_k != a && cur_k + 1 <= a && v[mid + cur_k - 1] < v[mid + cur_k + 1]))
					{
						prev_k = cur_k + 1;
					}
					else
					{
						if (cur_k - 1 >= -a)
						{
							prev_k = cur_k - 1;
						}
						else
						{
							prev_k = cur_k + 1;
						}
					}

					prev_x = v[mid + prev_k];
					prev_y = prev_x - prev_k;

					while (x > prev_x && y > prev_y)
					{
						// printf("%d %d -> %d %d\n", x - 1, y - 1, x, y);

						x--;
						y--;
					}

					// printf("%d %d -> %d %d\n", prev_x, prev_y, x, y);

					if (x - prev_x == 1)
					{
						edit_list->els_arr[edit_list->els_ind] = (Edit_Node){.ed_ind = x, .ed_type = 'd'};
						edit_list->els_arr[edit_list->els_ind++].ed_val = str_list1.data[x - 1];
					}
					else if (y - prev_y == 1)
					{
						edit_list->els_arr[edit_list->els_ind] = (Edit_Node){.ed_ind = x, .ed_type = 'i'};
						edit_list->els_arr[edit_list->els_ind++].ed_val = str_list2.data[y - 1];
					}

					x = prev_x;
					y = prev_y;
				}

				while (x > 0 && y > 0)
				{
					// printf("%d %d -> %d %d\n", x - 1, y - 1, x, y);

					x--;
					y--;
				}

				appendString(&str_list1, NULL);
				appendString(&str_list2, NULL);

				edit_list->els_f1_vec = str_list1.data;
				edit_list->els_f2_vec = str_list2.data;

				free(backtrack.back_arr);
				free(v);
				return d;
			}
		}

		backtrack.back_d++;
	}

	free(backtrack.back_arr);
	free(v);

	return d;
}
