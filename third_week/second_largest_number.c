#include <stdio.h>

int	horn()
{
	int		res;
	int		negative;
	char	chr;

	negative = 1;
	res = 0;
	chr = getchar();
	if (chr == '-')
	{
		negative = -1;
		chr = getchar();
	}
	while (chr != '\n' && chr != ' ')
	{
		res = res * 10 + (chr - 48);
		chr = getchar();
	}
	return (res * negative);
}

int	main(void)
{
	int	max;
	int	second_max;
	int	temp;

	max = horn();
	second_max = horn();
	if (second_max > max)
	{
		temp = max;
		max = second_max;
		second_max = temp;
	}
	while (1)
	{
		temp = horn();
		if (temp == -1)
			break ;
		if (temp >= max)
		{
			second_max = max;
			max = temp;
		}
		else if (temp > second_max)
			second_max = temp;
	}
	printf("%d", second_max);
	return (0);
}
