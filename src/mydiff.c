#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mydiff.h"

// TODO:
// - Edit Script
// - Generalize for multiple lines
// - Check bounds on backtracking conditions

int fewest_edits(char *str1, char *str2)
{
	int d = 0;

	int n = strlen(str1);
	int m = strlen(str2);

	int max = m + n;

	int *v = (int *)malloc(sizeof(int) * (max + 1));

	Backtrack_Store backtrack;

	backtrack.back_arr = (int *)malloc(sizeof(int) * 128); // Consider using a vector
	backtrack.back_ind = -1;
	backtrack.back_d = -1;

	int mid = max / 2;

	v[mid] = 0;

	// printf("%d\n", mid);

	for (int d = 0; d <= max; d++)
	{
		for (int k = -d; k <= d; k += 2)
		{
			if (k < -m || k > n)
			{
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

			// printf("%d %d %d\n", x, y, k);

			if (y >= 0)
			{
				while (x < n && y < m && str1[x] == str2[y])
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
				printf("--------\n");
				for (int j = 0; j <= max; j++)
				{
					printf("%d ", v[j]);
				}

				printf("\n");
				int back_d = backtrack.back_d;

				int cur_k;
				int prev_k = x - y;

				int prev_x, prev_y;

				for (int a = back_d; a > 0; a--) // Iterate backwards for d
				{
					cur_k = x - y;

					// printf("%d\n", cur_k);

					int base = (a - 1) * a / 2;

					// printf("%d\n", base);

					for (int l = -a + 1; l <= a - 1; l += 2) // Revert the array to the previous state
					{
						v[mid + l] = backtrack.back_arr[base];
						base++;
					}

					if (cur_k == -a || (cur_k != a && cur_k + 1 <= a && cur_k - 1 >= -a && v[mid + cur_k - 1] < v[mid + cur_k + 1]))
					{
						prev_k = cur_k + 1;
					}
					else
					{
						prev_k = cur_k - 1;
					}

					// printf("--->%d\n", prev_k);

					prev_x = v[mid + prev_k];
					prev_y = prev_x - prev_k;

					// printf("!!!!%d %d\n", prev_x, prev_y);
					// printf("!!!!%d %d\n", a, prev_k);
					// printf("!!!!%d %d %d %d\n", v[mid + cur_k - 1], v[mid + cur_k + 1], cur_k, a);

					while (x > prev_x && y > prev_y)
					{
						printf("%d %d -> %d %d\n", x - 1, y - 1, x, y);

						x--;
						y--;
					}

					if (1)
					{
						printf("%d %d -> %d %d\n", prev_x, prev_y, x, y);
					}

					x = prev_x;
					y = prev_y;

					// printf("%d ", back_d);

					// for (int j = 0; j <= max; j++)
					// {
					// 	printf("%d ", v[j]);
					// }

					// printf("\n");
				}

				printf("0 0 -> %d %d\n", x, y);

				// for (int back_d = 0; back_d <= backtrack.back_d; back_d++)
				// {
				// 	int i = back_d * (back_d + 1) / 2;

				// 	for (int x = i; x < i + back_d + 1; x++)
				// 	{
				// 		printf("%d ", backtrack.back_arr[x]);
				// 	}
				// 	printf("\n");
				// }

				free(backtrack.back_arr);
				free(v);
				return d;
			}
		}

		printf("%d ", d);

		for (int j = 0; j <= max; j++)
		{
			printf("%d ", v[j]);
		}

		printf("\n");

		backtrack.back_d++;
	}

	free(backtrack.back_arr);
	free(v);

	return d;
}

int main()
{
	// char *string1 = "ABCABBA";
	// char *string2 = "CBABAC";

	char *string1 = "abc";
	char *string2 = "a";

	printf("%d\n", fewest_edits(string1, string2));
}
