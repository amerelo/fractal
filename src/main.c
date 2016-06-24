/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:04:15 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/24 18:14:59 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"
#include <stdio.h>

int		ft_quit(void)
{
	exit(0);
}

void	init_env(t_env *box)
{
	box->img_ptr = NULL;
	box->mlx_ptr = NULL;
	box->win_ptr = NULL;
	box->img = NULL;
	box->img_bpp = 0;
	box->img_bpl = 0;
	box->endian = 0;
	box->m.inter_x = 0.0;
	box->m.inter_y = 0.0;
	box->m.interval_x = 0.0;
	box->m.interval_y = 0.0;
	box->m.zoom = 6.0;
}

void	remake(t_env *box)
{
	pthread_t	p[TR];
	int		i = -1;
	int		j = -1;

	ft_bzero(box->img, (WINX * WINY * 4));
	// make_mandel(*box);
	while (++i < TR)
		pthread_create(&p[i], NULL, make_mandel, &box->t[i]);
	while (++j < TR)
		pthread_join(p[j], NULL);
	mlx_put_image_to_window(box->mlx_ptr, box->win_ptr, box->img_ptr, 0, 0);
}


int		detect_click(int button, int x, int y, t_env *box)
{
	(void)button;
	printf("%d %d\n", x, y);
	printf("%f %f\n", box->m.inter_x, box->m.inter_y);
	printf("%f %f\n", HEIGHT, WIDTH);
	box->m.interval_x = box->m.interval_x + (x - HEIGHT) / 20 * box->m.zoom / 100;
	box->m.interval_y = box->m.interval_y + (y - WIDTH) / 20 * box->m.zoom / 100;
	box->m.inter_x = box->m.interval_x;
	box->m.inter_y = box->m.interval_y;
	remake(box);
	return (1);
}

int		mouse(int x, int y, t_env *box)
{
	(void)x;
	(void)y;
	(void)box;
	return (1);
}

int		detect(int keycode, t_env *box)
{
	// printf("%d\n", keycode);
	if (keycode == 69 && (box->m.zoom *= 0.5))
		remake(box);
	if (keycode == 78 && (box->m.zoom *= 2))
		remake(box);
	if (keycode == 124 && (box->m.inter_x += box->m.zoom / 100))
		remake(box);
	if (keycode == 123 && (box->m.inter_x -= box->m.zoom / 100))
		remake(box);
	if (keycode == 126 && (box->m.inter_y -= box->m.zoom / 100))
		remake(box);
	if (keycode == 125 && (box->m.inter_y += box->m.zoom / 100))
		remake(box);
	if (keycode == 53)
		ft_quit();
	return (1);
}


void	put_pixel_to_img(int x , int y, t_env box)
{
	int dis;

	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
	{
		dis = (x * 4) + (y * box.img_bpl);
		box.img[dis] = 0;
		box.img[dis + 1] = 0;// v
		box.img[dis + 2] = 0;//random() % 255;
	}
}

void	put_pixel_border(int x , int y, t_env box, double n)
{
	int dis;

	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
	{
		dis = (x * 4) + (y * box.img_bpl);
		box.img[dis] = (int)(n / 2);
		box.img[dis + 1] = (int)(n / 1);// v
		box.img[dis + 2] = (int)(n / 1);
	}
}

void	*make_mandel(void *curent)
{
	t_thread	*t;
	int max = 250;
	int row;
	int col;
	double x_new;
	double c_im;
	double c_re;
	double x;
	double y;
	double i;
	double zoom;

	t = (t_thread*)curent;
	zoom = WINX / (*t->box).m.zoom;
	row = t->lim[0];
	while (row++ < t->lim[1] && !(col = 0))
		while (col++ < WINX &&
		((c_re = (col - HEIGHT) / zoom + (*t->box).m.inter_x) || 1) &&
		((c_im = (row - WIDTH) / zoom + (*t->box).m.inter_y) || 1))
		{
			x = 0;
			y = 0;
			i = 0.0;
			while (x * x + y * y <= 4 && i < max && ++i &&
			((x_new = x * x - y * y + c_re) || 1)
			&& ((y = 2 * x * y + c_im) || 1))
				x = x_new;
			if (i == max)
				put_pixel_border(col, row, (*t->box), (int)(i * (double)row * (double)col) % 255);
			else
				put_pixel_border(col, row, (*t->box),i * 10);
		}
	return (NULL);
}

void	init_thread(t_thread *t, t_env *box)
{
	int i;
	int y;

	i = 0;
	y = WINY / TR;
	while (i < TR)
	{
		t[i].nb = i;
		t[i].lim[0] = y * i;
		t[i].lim[1] = y * (i + 1);
		t[i].box = box;
		++i;
	}
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
		pthread_create(&p[i], NULL, make_mandel, &box.t[i]);
	while (++j < TR)
		pthread_join(p[j], NULL);
	mlx_put_image_to_window(box.mlx_ptr, box.win_ptr, box.img_ptr, 0, 0);
	// mlx_hook(box.win_ptr, 6, (1L << 6), mouse, &box);
	mlx_mouse_hook(box.win_ptr, detect_click, &box);
	mlx_hook(box.win_ptr, 2, (1L << 0), detect, &box);
	mlx_hook(box.win_ptr, 17, (1L << 17), ft_quit, &box);
	mlx_loop(box.mlx_ptr);
}
