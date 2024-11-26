#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

int	compare_desc(const void *a, const void *b)
{
	int	int_a;
	int	int_b;

	int_a = *(const int *)a;
	int_b = *(const int *)b;
	return (int_b - int_a);
}

int	main(void)
{
	int		*list;
	int		capacity;
	int		size;
	char	line[256];
	int		n;
	int		*new_list;
	int		found;

	list = malloc(INITIAL_CAPACITY * sizeof(int));
	if (!list)
	{
		return (1);
	}
	capacity = INITIAL_CAPACITY;
	size = 0;
	while (fgets(line, sizeof(line), stdin))
	{
		int op, num;
		n = sscanf(line, "%d %d", &op, &num);
		if (op == 6)
		{
			break ;
		}
		else if (op == 1 && n == 2)
		{
			if (size >= capacity)
			{
				capacity *= 2;
				new_list = realloc(list, capacity * sizeof(int));
				if (!new_list)
				{
					fprintf(stderr, "Memory allocation failed\n");
					free(list);
					return (1);
				}
				list = new_list;
			}
			list[size++] = num;
		}
		else if (op == 2 && n == 2)
		{
			found = 0;
			for (int i = 0; i < size; i++)
			{
				if (list[i] == num)
				{
					for (int j = i; j < size - 1; j++)
					{
						list[j] = list[j + 1];
					}
					size--;
					found = 1;
					break ;
				}
			}
		}
		else if (op == 4)
		{
			qsort(list, size, sizeof(int), compare_desc);
		}
		else if (op == 5)
		{
			for (int i = 0; i < size; i++)
			{
				printf("%d\n", list[i]);
			}
		}
	}
	free(list);
	return (0);
}
