/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llupache <llupache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:49:34 by llupache          #+#    #+#             */
/*   Updated: 2024/11/22 21:22:05 by llupache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	julia_generate(t_fractal *fract, t_image *img)
{
	int		i;
	double	temp_x;
	double	temp_y;
	double	temp;

	temp_x = x_to_re(fract, fract->x);
	temp_y = y_to_img(fract, fract->y);
	i = 0;
	while (++i < MAX_ITERATIONS && norm(temp_x, temp_y) < 4)
	{
		temp = temp_x;
		temp_x = temp_x * temp_x - temp_y * temp_y + fract->x_c;
		temp_y = 2 * temp * temp_y + fract->y_c;
	}
	if (i == MAX_ITERATIONS)
	{
		put_pixel_to_image(fract, img, 0x000000);
	}
	else
		put_pixel_to_image(fract, img, fract->color * (i % 255));
}

void	mandelbrot_generate(t_fractal *fract, t_image *img)
{
	int		i;
	double	temp_x;
	double	temp_y;
	double	temp;

	temp_x = 0.0;
	temp_y = 0.0;
	fract->x_c = x_to_re(fract, fract->x);
	fract->y_c = y_to_img(fract, fract->y);
	i = 0;
	while (++i < MAX_ITERATIONS && norm(temp_x, temp_y) < 4)
	{
		temp = temp_x;
		temp_x = temp_x * temp_x - temp_y * temp_y + fract->x_c;
		temp_y = 2 * temp * temp_y + fract->y_c;
	}
	if (i == MAX_ITERATIONS)
	{
		put_pixel_to_image(fract, img, 0x000000);
	}
	else
		put_pixel_to_image(fract, img, fract->color * (i % 255));
}

void	burning_ship_generate(t_fractal *fract, t_image *img)
{
	int		i;
	double	temp_x;
	double	temp_y;
	double	temp;

	temp_x = 0.0;
	temp_y = 0.0;
	fract->x_c = x_to_re(fract, fract->x);
	fract->y_c = y_to_img(fract, fract->y);
	i = 0;
	while (++i < MAX_ITERATIONS && norm(temp_x, temp_y) < 10)
	{
		temp_x = fabs(temp_x);
		temp_y = fabs(temp_y);
		temp = temp_x;
		temp_x = temp_x * temp_x - temp_y * temp_y + fract->x_c;
		temp_y = fabs(2 * temp * temp_y) + fract->y_c;
	}
	if (i == MAX_ITERATIONS)
	{
		put_pixel_to_image(fract, img, 0x000000);
	}
	else
		put_pixel_to_image(fract, img, fract->color * (i % 255));
}

int	close_window(void *mlx, void *window)
{
	mlx_destroy_window(mlx, window);
	exit(0);
}

int	close_window2(t_fractal *fract)
{
	mlx_destroy_window(fract->mlx, fract->window);
	exit(0);
}
