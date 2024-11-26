#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long	mod_decimal(const char *A, unsigned long m)
{
	unsigned long	res;

	res = 0;
	for (int i = 0; A[i]; i++)
	{
		res = (res * 10 + (A[i] - '0')) % m;
	}
	return (res);
}

unsigned long	pow_mod_binary(const char *B, unsigned long A_mod,
		unsigned long m)
{
	unsigned long	res;

	res = 1;
	for (int i = 0; B[i]; i++)
	{
		res = (res * res) % m;
		if (B[i] == '1')
		{
			res = (res * A_mod) % m;
		}
	}
	return (res);
}

int	main(void)
{
	char			*A;
	char			*B;
	int				idx;
	int				c;
	unsigned long	A_mod4;
	unsigned long	A_mod25;
	unsigned long	pow_mod4;
	unsigned long	pow_mod25;
	unsigned long	pow_mod25_mod4;
	unsigned long	diff;
	unsigned long	x;

#define MAX_LEN 1000000
	A = (char *)malloc((MAX_LEN + 1) * sizeof(char));
	B = (char *)malloc((MAX_LEN + 1) * sizeof(char));
	if (A == NULL || B == NULL)
	{
		return (1);
	}
	idx = 0;
	while ((c = getchar()) != '\n' && c != EOF && idx < MAX_LEN)
	{
		A[idx++] = c;
	}
	A[idx] = '\0';
	idx = 0;
	while ((c = getchar()) != '\n' && c != EOF && idx < MAX_LEN)
	{
		B[idx++] = c;
	}
	B[idx] = '\0';
	A_mod4 = mod_decimal(A, 4);
	A_mod25 = mod_decimal(A, 25);
	pow_mod4 = pow_mod_binary(B, A_mod4, 4);
	pow_mod25 = pow_mod_binary(B, A_mod25, 25);
	pow_mod25_mod4 = pow_mod25 % 4;
	diff = (pow_mod4 + 4 - pow_mod25_mod4) % 4;
	x = (pow_mod25 + 25 * diff) % 100;
	if (x < 10)
	{
		printf("0%lu\n", x);
	}
	else
	{
		printf("%lu\n", x);
	}
	free(A);
	free(B);
	return (0);
}
