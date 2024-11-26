#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define MAXM 10000
#define MAX_SEG_TREE_SIZE (1 << 15)

int		N;
int		a[MAXN];
int		ranks[MAXN];
int		compressed_values[MAXN];
int		len0_tree[MAX_SEG_TREE_SIZE];
int		len1_tree[MAX_SEG_TREE_SIZE];
int		temp_array[MAXN];
int		unique_values;

int	compare_ints(const void *a, const void *b)
{
	int	int_a;
	int	int_b;

	int_a = *(const int *)a;
	int_b = *(const int *)b;
	if (int_a < int_b)
		return (-1);
	else if (int_a > int_b)
		return (1);
	else
		return (0);
}

void	build_tree(int *tree, int node, int start, int end)
{
	int	mid;

	if (start == end)
	{
		tree[node] = 0;
	}
	else
	{
		mid = (start + end) / 2;
		build_tree(tree, 2 * node, start, mid);
		build_tree(tree, 2 * node + 1, mid + 1, end);
		tree[node] = 0;
	}
}

void	update(int *tree, int node, int start, int end, int idx, int val)
{
	int	mid;

	if (start == end)
	{
		if (tree[node] < val)
		{
			tree[node] = val;
		}
	}
	else
	{
		mid = (start + end) / 2;
		if (idx <= mid)
		{
			update(tree, 2 * node, start, mid, idx, val);
		}
		else
		{
			update(tree, 2 * node + 1, mid + 1, end, idx, val);
		}
		tree[node] = tree[2 * node] > tree[2 * node + 1] ? tree[2
			* node] : tree[2 * node + 1];
	}
}

int	query(int *tree, int node, int start, int end, int l, int r)
{
	int	mid;
	int	p1;
	int	p2;

	if (r < start || end < l)
	{
		return (0);
	}
	if (l <= start && end <= r)
	{
		return (tree[node]);
	}
	mid = (start + end) / 2;
	p1 = query(tree, 2 * node, start, mid, l, r);
	p2 = query(tree, 2 * node + 1, mid + 1, end, l, r);
	return (p1 > p2 ? p1 : p2);
}

void	coordinate_compress(void)
{
	int	left = 0, right;
	int	mid;

	for (int i = 0; i < N; i++)
	{
		temp_array[i] = a[i];
	}
	qsort(temp_array, N, sizeof(int), compare_ints);
	unique_values = 0;
	compressed_values[unique_values++] = temp_array[0];
	for (int i = 1; i < N; i++)
	{
		if (temp_array[i] != temp_array[i - 1])
		{
			compressed_values[unique_values++] = temp_array[i];
		}
	}
	for (int i = 0; i < N; i++)
	{
		left = 0, right = unique_values - 1;
		while (left <= right)
		{
			mid = (left + right) / 2;
			if (compressed_values[mid] == a[i])
			{
				ranks[i] = mid + 1;
				break ;
			}
			else if (compressed_values[mid] < a[i])
			{
				left = mid + 1;
			}
			else
			{
				right = mid - 1;
			}
		}
	}
}

int	max(int a, int b)
{
	return (a > b ? a : b);
}

int	main(void)
{
	int	M;
	int	answer;
	int	rank;
	int	len0;
	int	len1;
	int	max_len0_greater;

	if (scanf("%d", &N) != 1 || N <= 0 || N > MAXN)
	{
		fprintf(stderr, "Invalid input\n");
		return (1);
	}
	for (int i = 0; i < N; i++)
	{
		if (scanf("%d", &a[i]) != 1)
		{
			fprintf(stderr, "Invalid input\n");
			return (1);
		}
	}
	coordinate_compress();
	M = unique_values;
	build_tree(len0_tree, 1, 1, M);
	build_tree(len1_tree, 1, 1, M);
	answer = 0;
	for (int i = 0; i < N; i++)
	{
		rank = ranks[i];
		len0 = query(len0_tree, 1, 1, M, 1, rank) + 1;
		len1 = query(len1_tree, 1, 1, M, 1, rank) + 1;
		if (rank + 1 <= M)
		{
			max_len0_greater = query(len0_tree, 1, 1, M, rank + 1, M);
			len1 = max(len1, max_len0_greater + 1);
		}
		update(len0_tree, 1, 1, M, rank, len0);
		update(len1_tree, 1, 1, M, rank, len1);
		answer = max(answer, max(len0, len1));
	}
	printf("%d\n", answer);
	return (0);
}
