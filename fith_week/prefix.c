#include <stdio.h>
#include <stdlib.h>

struct spojak
{
	long int value;
	int operator;
	int is_number;
	struct spojak *next;
	struct spojak *prev;
};

int end = 0;
int bad_end;

struct spojak *try_to_opperate(struct spojak *p)
{
	while (p->is_number && p->prev && p->prev->is_number)
	{
		p = p->prev->prev;
		if (p->operator == '-')
		{
			p->value = p->next->value - p->next->next->value;
			p->is_number = 1;
			p->next = NULL;
		}
		else if (p->operator == '+')
		{
			p->value = p->next->value + p->next->next->value;
			p->is_number = 1;
			p->next = NULL;
		}
		else if (p->operator == '*')
		{
			p->value = p->next->value * p->next->next->value;
			p->is_number = 1;
			p->next = NULL;
		}
		else if (p->operator == '/')
		{
			if (p->next->next->value == 0)
			{	
				printf("CHYBA");
				bad_end = 1;
				return p;
			}
			p->value = p->next->value / p->next->next->value;
			p->is_number = 1;
			p->next = NULL;
		}
	}
	return p;
}

long int	horn(char chr, int minus)
{
	long int	res;

	res = 0;
	if (minus == -1)
		chr = getchar();
	while (chr != '\n' && chr != ' ')
	{
		res = res * 10 + (chr - 48);
		chr = getchar();
	}
	if (chr == '\n')
		end = 1;
	return (res * minus);
}

int main(void)
{
	char letter;
	char temp_letter;
	struct spojak* p;
	struct spojak* new;

	p = malloc(sizeof(struct spojak));
	p->prev = NULL;
	while ((letter = (char)getchar()) && (letter != '\n'))
	{
		if (letter == ' ')
			continue;
		new = malloc(sizeof(struct spojak));
		new->next = NULL;
		new->prev = p;
		p->next = new;
		new->is_number = 0;
		if (letter == '-')
		{
			temp_letter = getchar();
			if (temp_letter >= 49 && temp_letter <= 57)
			{
				new -> value = horn(temp_letter, -1);
				new->is_number = 1;
			}
			else
				new -> operator = letter;
		}
		else if (letter == '+' || letter == '*' || letter == '/')
			new -> operator = letter;
		else if (letter >= 48 && letter <= 57)
		{
			new -> value = horn(letter, 1);
			new->is_number = 1;
		}
		p = new;
		p = try_to_opperate(p);
		if (bad_end == 1)
			return (0);
		if (end == 1)
			break;
	}
	printf("%ld", p->value);
	return (0);
}