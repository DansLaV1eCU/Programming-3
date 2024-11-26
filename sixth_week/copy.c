#include <stdio.h>
#include <stdlib.h>

int end = 0;

struct spojak
{
	long value;
	struct spojak *next;
};

long	horn()
{
	long		res;
	int		negative;
	char	chr;

	negative = 1;
	res = 0;
	chr = getchar();
	if (chr == -1)
	{
		end = 1;
		return (0);		
	}
	if (chr == '\n')
		end = 1;
	if (chr == '-')
	{
		negative = -1;
		chr = getchar();
	}
	while (chr != '\n' && chr != -1)
	{
		res = res * 10 + (chr - 48);
		chr = getchar();
	}
	
	return (res * negative);
}

void print_list(struct spojak *p)
{
	while (p)
	{
		printf("%ld\n", p->value);
		p = p->next;
	}
}

int main(void)
{
	struct spojak* p;
	struct spojak* first;
	struct spojak* second;
	struct spojak* new;
	long number;

	p = malloc(sizeof(struct spojak));
	number = horn();
	if (end)
		return (0);
	first = p;
	second = p;
	p->value = number;
	p->next = NULL;
	while (!end)
	{
		new = malloc(sizeof(struct spojak));
		number = horn();
		if (end)
			break;
		new->value = number;
		p->next = new;
		p = p->next;
	}
	print_list(first);
	print_list(second);
	free(first);
	return (0);
}