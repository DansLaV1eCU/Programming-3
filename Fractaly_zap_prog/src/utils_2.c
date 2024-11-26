/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llupache <llupache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:49:32 by llupache          #+#    #+#             */
/*   Updated: 2024/11/22 20:50:23 by llupache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	change_color(t_fractal *fract)
{
	if (fract->color == 0xFCBE11)
		fract->color = 0x5C0EB0;
	else if (fract->color == 0x5C0EB0)
		fract->color = 0x002A8C;
	else if (fract->color == 0x002A8C)
		fract->color = 0xFCBE11;
	generate_fract(fract);
}

int	norm(double x, double y)
{
	return (x * x + y * y);
}

double	str_to_double_2(const char *str, int i, double result)
{
	double	fraction;
	double	divider;

	fraction = 0.0;
	divider = 1.0;
	while (ft_isdigit((unsigned char)str[i]))
	{
		fraction = fraction * 10.0 + (str[i] - '0');
		divider *= 10.0;
		i++;
	}
	result += fraction / divider;
	return (result);
}

double	string_to_double(const char *str)
{
	double	result;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
	result = 0.0;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (ft_isdigit(str[i]))
		result = result * 10.0 + (str[i++] - '0');
	if (str[i] == '.')
		result = str_to_double_2(str, ++i, result);
	return (sign * result);
}

void	put_strings(t_fractal *fract)
{
	mlx_string_put(fract->mlx, fract->window, 30, 30, 0xFFFFFF, "MWU- zoom in");
	mlx_string_put(fract->mlx, fract->window, 30, 45, 0xFFFFFF,
		"MWD- zoom out");
	mlx_string_put(fract->mlx, fract->window, 30, 60, 0xFFFFFF, "WASD - move");
	mlx_string_put(fract->mlx, fract->window, 30, 75, 0xFFFFFF,
		"R- regenerate");
	mlx_string_put(fract->mlx, fract->window, 30, 90, 0xFFFFFF,
		"C- change color");
	mlx_string_put(fract->mlx, fract->window, 30, 105, 0xFFFFFF, "Esc - quit");
}
