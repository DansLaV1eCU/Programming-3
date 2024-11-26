/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llupache <llupache@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 18:23:53 by llupache          #+#    #+#             */
/*   Updated: 2024/11/22 21:26:21 by llupache         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

# include "../../../libft/libft.h"
# include "../../../minilibx-linux/mlx.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define HEIGHT 1080
# define WIDTH 1920
# define MAX_ITERATIONS 100

typedef struct t_fractal
{
	int		x;
	int		y;
	double	y_c;
	double	x_c;
	double	min_re;
	double	max_re;
	double	min_img;
	double	max_img;
	double	max_norm;
	void	*mlx;
	void	*window;
	double	zoom;
	char	*name;
	int		color;
}			t_fractal;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}			t_image;

void		generate_fract(t_fractal *fract);
void		julia_generate(t_fractal *fract, t_image *img);
void		burning_ship_generate(t_fractal *fract, t_image *img);
void		mandelbrot_generate(t_fractal *fract, t_image *img);
void		initialise(t_fractal *fract);
int			check_parameters(int argc, char **argv, t_fractal *fract);
void		put_pixel_to_image(t_fractal *fract, t_image *img, int color);
double		x_to_re(t_fractal *fract, int x);
double		y_to_img(t_fractal *fract, int y);
int			norm(double x, double y);
void		change_color(t_fractal *fract);
double		string_to_double(const char *str);
void		put_strings(t_fractal *fract);
int			close_window(void *mlx, void *window);
int			close_window2(t_fractal *fract);

#endif
