/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llupache <llupache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:01:30 by llupache          #+#    #+#             */
/*   Updated: 2024/11/22 20:55:24 by llupache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract_ol.h"

void	generate_fract(t_fractal *fract)
{
	t_image	img;

	img.img = mlx_new_image(fract->mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
			&img.endian);
	fract->y = 0;
	while (fract->y < HEIGHT)
	{
		fract->x = 0;
		while (fract->x < WIDTH)
		{
			if (ft_strncmp(fract->name, "Julia", 6) == 0)
				julia_generate(fract, &img);
			else if (ft_strncmp(fract->name, "Mandelbrot", 11) == 0)
				mandelbrot_generate(fract, &img);
			else if (ft_strncmp(fract->name, "Burning_ship", 6) == 0)
				burning_ship_generate(fract, &img);
			fract->x++;
		}
		fract->y++;
	}
	mlx_put_image_to_window(fract->mlx, fract->window, img.img, 0, 0);
	put_strings(fract);
}

int	zoom(int button, int x, int y, t_fractal *fract)
{
	if (x > WIDTH)
		return (0);
	if (y > HEIGHT)
		return (0);
	if (button == 4)
		fract->zoom = 1.2;
	else if (button == 5)
		fract->zoom = 0.8;
	else
		return (0);
	fract->min_re += (x_to_re(fract, x) - fract->min_re) * (1 - 1
			/ fract->zoom);
	fract->min_img += (y_to_img(fract, y) - fract->min_img) * (1 - 1
			/ fract->zoom);
	fract->max_re -= (fract->max_re - x_to_re(fract, x)) * (1 - 1
			/ fract->zoom);
	fract->max_img -= (fract->max_img - y_to_img(fract, y)) * (1 - 1
			/ fract->zoom);
	generate_fract(fract);
	return (0);
}

void	wasd_move(int keycode, t_fractal *fract)
{
	if (keycode == 115)
	{
		fract->min_img += (fract->max_img - fract->min_img) * 0.1;
		fract->max_img += (fract->max_img - fract->min_img) * 0.1;
	}
	else if (keycode == 119)
	{
		fract->min_img -= (fract->max_img - fract->min_img) * 0.1;
		fract->max_img -= (fract->max_img - fract->min_img) * 0.1;
	}
	else if (keycode == 100)
	{
		fract->min_re += (fract->max_re - fract->min_re) * 0.1;
		fract->max_re += (fract->max_re - fract->min_re) * 0.1;
	}
	else if (keycode == 97)
	{
		fract->min_re -= (fract->max_re - fract->min_re) * 0.1;
		fract->max_re -= (fract->max_re - fract->min_re) * 0.1;
	}
	generate_fract(fract);
}

int	key_pressed(int keycode, t_fractal *fract)
{
	if (keycode == 65307)
	{
		mlx_destroy_window(fract->mlx, fract->window);
		exit(0);
	}
	if (keycode == 114)
	{
		initialise(fract);
		generate_fract(fract);
	}
	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
		wasd_move(keycode, fract);
	if (keycode == 99)
		change_color(fract);
	return (0);
}

int	main(int argc, char **argv)
{
	void		*mlx;
	void		*mlx_win;
	t_fractal	fract;

	if (!check_parameters(argc, argv, &fract))
	{
		write(1, "Available fractals:\n-Julia Re Img\n", 35);
		return (write(1, "-Mandelbrot\n-Burning_ship\n", 27));
	}
	mlx = mlx_init();
	if (!mlx)
		return (0);
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, argv[1]);
	if (!mlx_win)
		close_window(mlx, mlx_win);
	fract.mlx = mlx;
	fract.window = mlx_win;
	initialise(&fract);
	generate_fract(&fract);
	mlx_mouse_hook(fract.window, zoom, &fract);
	mlx_key_hook(fract.window, key_pressed, &fract);
	mlx_hook(fract.window, 17, 1, close_window2, &fract);
	mlx_loop(mlx);
	return (0);
}
