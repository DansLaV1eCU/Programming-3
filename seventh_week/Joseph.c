#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int	main(void)
{
	char			line[256];
	char			*endptr;
	char			*ptr;
	long			N;
	unsigned long	n;
	unsigned long	p;
	unsigned long	L;
	unsigned long	J;

	if (!fgets(line, sizeof(line), stdin))
	{
		printf("ERROR\n");
		return (0);
	}
	line[strcspn(line, "\n")] = '\0';
	errno = 0;
	ptr = line;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (*ptr == '\0')
	{
		printf("ERROR\n");
		return (0);
	}
	N = strtol(ptr, &endptr, 10);
	if (errno != 0 || *endptr != '\0' || ptr == endptr)
	{
		printf("ERROR\n");
		return (0);
	}
	if (N <= 0)
	{
		printf("ERROR\n");
		return (0);
	}
	n = (unsigned long)N;
	p = 1UL << (sizeof(unsigned long) * 8 - 1);
	while (p > n)
		p >>= 1;
	L = n - p;
	J = 2 * L + 1;
	printf("%lu\n", J);
	return (0);
}
