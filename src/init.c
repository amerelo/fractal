/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 21:11:19 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/29 04:18:50 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int				ft_quit(void)
{
	exit(0);
}

static void		init_frac(t_env *box)
{
	box->fra[0].name = "mandelbrot";
	box->fra[0].fractol = mandelbrot;
	box->fra[1].name = "julia";
	box->fra[1].fractol = julia;
	box->fra[2].name = "trimandel";
	box->fra[2].fractol = trimandel;
	box->fra[3].name = "ghost";
	box->fra[3].fractol = ghost;
	box->fra[4].name = "violetbrot";
	box->fra[4].fractol = violetbrot;
	box->fra[5].name = "burning_ship";
	box->fra[5].fractol = burning_ship;
	box->fra[6].name = "snake";
	box->fra[6].fractol = snake;
	box->fra[7].name = "tree";
	box->fra[7].fractol = tree;
}

void			init_thread(t_thread *t, t_env *box)
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

void			init_env(t_env *box)
{
	box->img_ptr = NULL;
	box->mlx_ptr = NULL;
	box->win_ptr = NULL;
	box->img = NULL;
	box->stop = 0;
	box->index = 0;
	box->img_bpp = 0;
	box->img_bpl = 0;
	box->endian = 0;
	box->c[0] = 0;
	box->c[1] = 0.0;
	box->c[2] = 0.0;
	box->m.inter_x = 0.0;
	box->m.inter_y = 0.0;
	box->m.interval_x = 0.0;
	box->m.interval_y = 0.0;
	box->m.mouse_x = 0.355;
	box->m.mouse_y = 0.288;
	box->m.zoom = 6.0;
	box->m.iter = 50;
	init_frac(box);
}
