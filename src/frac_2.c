/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 04:03:16 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/29 04:31:11 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*trimandel(void *curent)
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
			++(z[7]) && ((z[4] = z[3] * z[3] - z[2] * z[2] + z[6]) || 1)
			&& ((z[3] = 2 * z[2] * z[3] + z[5]) || 1))
				z[2] = z[4];
			if (z[7] == (*t->box).m.iter)
				put_pixel_to_img(z[1], z[0], (*t->box),
				(int)(z[7] * z[0] * z[1]) % 255);
			else
				put_pixel_to_img(z[1], z[0], (*t->box), z[7] * 10);
		}
	return (NULL);
}

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
				put_pixel_to_img(z[1], z[0], (*t->box),
				(int)(z[7] * z[0] * z[1]) % 255);
			else
				put_pixel_to_img(z[1], z[0], (*t->box), z[7] * 10);
		}
	return (NULL);
}

void	*burning_ship(void *curent)
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
			++(z[7]) && ((z[4] = fabsl(z[2] * z[2] - z[3] * z[3] + z[6])) || 1)
			&& ((z[3] = fabsl(2 * z[2] * z[3] + z[5])) || 1))
				z[2] = z[4];
			julia_print(z, t);
		}
	return (NULL);
}
