/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/28 20:26:16 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/29 04:12:21 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	julia_print(long double *z, t_thread *t)
{
	if (z[7] == (*t->box).m.iter)
		put_pixel_border(z[1], z[0], (*t->box),
		wtf(0, 0, 1));
	else
		put_pixel_border(z[1], z[0], (*t->box),
	wtf(z[7] + t->box->c[0], fmod(t->box->c[1], 1), z[7] / (*t->box).m.iter));
}

int		wtf(double h, double s, double v)
{
	double	c;
	double	x;
	double	m;
	int		t;

	c = v * s;
	m = v - c;
	h = fmod(h, 360);
	t = ((t_)(m * M) << 16) + ((t_)(m * M) << 8) + m * M;
	if (h >= 0 && h < 60 && ((x = c * (1 - fabs(fmod(h / 60, 2) - 1))) || 1))
		t = (((t_)((c + m) * M) << G) + ((t_)((x + m) * M) << 8) + m * M);
	else if (h < 120 && ((x = c * (1 - fabs(fmod(h / 60, 2) - 1))) || 1))
		t = (((t_)((x + m) * M) << G) + ((t_)((c + m) * M) << 8) + m * M);
	else if (h < 180 && ((x = c * (1 - fabs(fmod(h / 60, 2) - 1))) || 1))
		t = (((t_)(m * M) << G) + ((t_)((c + m) * M) << 8) + (t_)((x + m) * M));
	else if (h < 240 && ((x = c * (1 - fabs(fmod(h / 60, 2) - 1))) || 1))
		t = (((t_)(m * M) << G) + ((t_)((x + m) * M) << 8) + (t_)((c + m) * M));
	else if (h < 300 && ((x = c * (1 - fabs(fmod(h / 60, 2) - 1))) || 1))
		t = (((t_)((x + m) * M) << G) + ((t_)(m * M) << 8) + (t_)((c + m) * M));
	else if (h < 360 && ((x = c * (1 - fabs(fmod(h / 60, 2) - 1))) || 1))
		t = (((t_)((c + m) * M) << G) + ((t_)(m * M) << 8) + (t_)((x + m) * M));
	return (t);
}

void	put_pixel_to_img(int x, int y, t_env box, int n)
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

void	put_pixel_border(int x, int y, t_env box, int n)
{
	int dis;

	if (x >= 0 && x < WINX && y >= 0 && y < WINY)
	{
		dis = (x * 4) + (y * box.img_bpl);
		box.img[dis] = (n) & 0xFF;
		box.img[dis + 1] = (n >> 8) & 0xFF;
		box.img[dis + 2] = (n >> 16) & 0xFF;
	}
}

int		reset(t_env *box)
{
	box->stop = 0;
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
	return (1);
}
