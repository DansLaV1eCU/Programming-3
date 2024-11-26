/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llupache <llupache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:49:28 by llupache          #+#    #+#             */
/*   Updated: 2024/11/22 20:50:51 by llupache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	initialise(t_fractal *fract)
{
	fract->min_re = -2.0;
	fract->max_re = 1.2;
	fract->min_img = -1;
	fract->max_img = fract->min_img + (fract->max_re - fract->min_re) * HEIGHT
		/ WIDTH;
	fract->max_img = 1;
	fract->max_norm = 2;
	fract->zoom = 1;
	fract->color = 0xFCBE11;
}

int	check_parameters(int argc, char **argv, t_fractal *fract)
{
	if (argc < 2 || (ft_strncmp(argv[1], "Julia", 6) != 0 && ft_strncmp(argv[1],
				"Mandelbrot", 11) != 0 && ft_strncmp(argv[1], "Burning_ship",
				13) != 0))
		return (0);
	if (ft_strncmp(argv[1], "Julia", 6) == 0)
	{
		if (argc == 3)
		{
			fract->x_c = string_to_double(argv[2]);
			fract->y_c = 0.0;
		}
		else if (argc == 4)
		{
			fract->x_c = string_to_double(argv[2]);
			fract->y_c = string_to_double(argv[3]);
		}
		else if (argc != 3 && argc != 4)
			return (0);
		fract->name = "Julia";
	}
	else if (ft_strncmp(argv[1], "Mandelbrot", 11) == 0)
		fract->name = "Mandelbrot";
	else if (ft_strncmp(argv[1], "Burning_ship", 13) == 0)
		fract->name = "Burning_ship";
	return (1);
}

void	put_pixel_to_image(t_fractal *fract, t_image *img, int color)
{
	int				pixel;

	pixel = fract->y * img->size_line + fract->x * 4;
	if (img->endian == 0)
	{
		img->addr[pixel + 3] = (color >> 24);
		img->addr[pixel + 2] = (color >> 16) & 0xFF;
		img->addr[pixel + 1] = (color >> 8) & 0xFF;
		img->addr[pixel + 0] = (color) & 0xFF;
	}
	else
	{
		img->addr[pixel + 0] = (color >> 24);
		img->addr[pixel + 1] = (color >> 16) & 0xFF;
		img->addr[pixel + 2] = (color >> 8) & 0xFF;
		img->addr[pixel + 3] = (color) & 0xFF;
	}
}

double	x_to_re(t_fractal *fract, int x)
{
	return (fract->min_re + (double)x * (fract->max_re - fract->min_re)
		/ (double)(WIDTH - 1));
}

double	y_to_img(t_fractal *fract, int y)
{
	return (fract->min_img + (double)y * (fract->max_img - fract->min_img)
		/ (double)(HEIGHT - 1));
}
