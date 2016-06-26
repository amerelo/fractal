/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:04:15 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/26 21:53:33 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

// void	put_pixel_to_img(int x , int y, t_env box)
// {
// 	int dis;
//
// 	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
// 	{
// 		dis = (x * 4) + (y * box.img_bpl);
// 		box.img[dis] = 0;
// 		box.img[dis + 1] = 0;
// 		box.img[dis + 2] = 0;
// 	}
// }

void	put_pixel_border(int x , int y, t_env box, long double n)
{
	int dis;

	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
	{
		dis = (x * 4) + (y * box.img_bpl);
		box.img[dis] = (int)(n / 2);
		box.img[dis + 1] = (int)(n / 1.5);
		box.img[dis + 2] = (int)(n / 1.5);
	}
}

// void	*make_mandel(void *curent) // julia
// {
// 	t_thread	*t;
// 	int row;
// 	int col;
// 	long double x_new;
// 	long double c_im;
// 	long double c_re;
// 	long double x;
// 	long double y;
// 	long double i;
// 	long double zoom;
//
// 	t = (t_thread*)curent;
// 	zoom = WINX / (*t->box).m.zoom;
// 	row = t->lim[0];
// 	// printf("%d %d\n",(*t->box).m.mouse_x, (*t->box).m.mouse_y);
// 	while (row++ < t->lim[1] && !(col = 0))
// 		while (col++ < WINX)
// 		{
// 			c_re = (*t->box).m.mouse_x;
// 			c_im = (*t->box).m.mouse_y;
// 			x = (col - HEIGHT) / zoom + (*t->box).m.inter_x;
// 			y = (row - WIDTH) / zoom + (*t->box).m.inter_y;
// 			i = 0.0;
// 			while (x * x + y * y <= 4 && i < (*t->box).m.iter && ++i)
// 			{
// 				x_new = x * x - y * y + c_re ;
// 				y = 2 * x * y + c_im;
// 				x = x_new;
// 			}
// 			if (i == (*t->box).m.iter)
// 				put_pixel_border(col, row, (*t->box),
// 				(int)(i * (long double)row * (long double)col) % 255);
// 			else
// 				put_pixel_border(col, row, (*t->box),i * 10);
// 		}
// 	return (NULL);
// }
//
// void	*make_mandel(void *curent) // 3
// {
// 	t_thread	*t;
// 	int row;
// 	int col;
// 	long double x_new;
// 	long double c_im;
// 	long double c_re;
// 	long double x;
// 	long double y;
// 	long double i;
// 	long double zoom;
//
// 	t = (t_thread*)curent;
// 	zoom = WINX / (*t->box).m.zoom;
// 	row = t->lim[0];
// 	while (row++ < t->lim[1] && !(col = 0))
// 		while (col++ < WINX &&
// 		((c_re = (col - HEIGHT) / zoom + (*t->box).m.inter_x) || 1) &&
// 		((c_im = (row - WIDTH) / zoom + (*t->box).m.inter_y) || 1))
// 		{
// 			x = 0;
// 			y = 0;
// 			i = 0.0;
// 			while (x * x + y * y <= 4 && i < (*t->box).m.iter && ++i)
// 			{
// 				x_new = y * y - x * x + c_re;
// 				y = 2 * x * y + c_im;
// 				x = x_new;
// 			}
// 			if (i == (*t->box).m.iter)
// 				put_pixel_border(col, row, (*t->box),
// 				(int)(i * (long double)row * (long double)col) % 255);
// 			else
// 				put_pixel_border(col, row, (*t->box),i * 10);
// 		}
// 	return (NULL);
// }

void	*mandelbrot(void *curent)
{
	t_thread	*t;
	long double z[9];

	t = (t_thread*)curent;
	z[8] = WINX / (*t->box).m.zoom;
	z[0] = t->lim[0];
	while (z[0]++ < t->lim[1] && !(z[1] = 0))
		while (z[1]++ < WINX)
		{
			z[6] = (z[1] - HEIGHT) / z[8] + (*t->box).m.inter_x;
			z[5] = (z[0] - WIDTH) / z[8] + (*t->box).m.inter_y;
			z[2] = 0;
			z[3] = 0;
			z[7] = 0.0;
			while (z[2] * z[2] + z[3] * z[3] <= 4 && z[7] < (*t->box).m.iter &&
			++(z[7]) && ((z[4] = z[2] * z[2] - z[3] * z[3] + z[6]) || 1)
			&& ((z[3] = 2 * z[2] * z[3] + z[5]) || 1))
				z[2] = z[4];
			if (z[7] == (*t->box).m.iter)
				put_pixel_border(z[1], z[0], (*t->box),
				(int)(z[7] * z[0] * z[1]) % 255);
			else
				put_pixel_border(z[1], z[0], (*t->box),z[7] * 10);
		}
	return (NULL);
}

int		main(void)
{
	t_env		box;
	pthread_t	p[TR];
	int			i = -1;
	int			j = -1;

	init_env(&box);
	if (!(box.mlx_ptr = mlx_init()) ||
	!(box.win_ptr = mlx_new_window(box.mlx_ptr, WINX, WINY, "fractal")) ||
	!(box.img_ptr = mlx_new_image(box.mlx_ptr, WINX, WINY)) ||
	!(box.img = mlx_get_data_addr(box.img_ptr, &box.img_bpp,
	&box.img_bpl, &box.endian)))
		return (0);
	init_thread(box.t, &box);
	while (++i < TR)
		pthread_create(&p[i], NULL, mandelbrot, &box.t[i]);
	while (++j < TR)
		pthread_join(p[j], NULL);
	// mlx_hook(box.win_ptr, 6, (1L << 6), mouse, &box);
	mlx_put_image_to_window(box.mlx_ptr, box.win_ptr, box.img_ptr, 0, 0);
	mlx_mouse_hook(box.win_ptr, detect_click, &box);
	mlx_hook(box.win_ptr, 2, (1L << 0), detect, &box);
	mlx_hook(box.win_ptr, 17, (1L << 17), ft_quit, &box);
	mlx_loop(box.mlx_ptr);
}
