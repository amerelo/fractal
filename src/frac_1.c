/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frac_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/29 04:01:41 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/29 04:02:13 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	*julia(void *curent)
{
	t_thread	*t;
	long double	z[9];

	t = (t_thread*)curent;
	z[8] = WINX / (*t->box).m.zoom;
	z[0] = t->lim[0];
	while (z[0]++ < t->lim[1] && !(z[1] = 0))
		while (z[1]++ < WINX)
		{
			z[4] = (*t->box).m.mouse_x;
			z[3] = (*t->box).m.mouse_y;
			z[5] = (z[1] - HEIGHT) / z[8] + (*t->box).m.inter_x;
			z[6] = (z[0] - WIDTH) / z[8] + (*t->box).m.inter_y;
			z[7] = 0;
			while (z[6] * z[6] + z[5] * z[5] <= 4 && z[7]
			< (*t->box).m.iter && ++z[7])
			{
				z[2] = z[6] * z[6] - z[5] * z[5] + z[4];
				z[6] = 2 * z[5] * z[6] + z[3];
				z[5] = z[2];
			}
			julia_print(z, t);
		}
	return (NULL);
}

void	*snake(void *curent)
{
	t_thread	*t;
	long double	z[9];

	t = (t_thread*)curent;
	z[8] = WINX / (*t->box).m.zoom;
	z[0] = t->lim[0];
	while (z[0]++ < t->lim[1] && !(z[1] = 0))
		while (z[1]++ < WINX)
		{
			z[4] = (*t->box).m.mouse_x;
			z[3] = (*t->box).m.mouse_y;
			z[5] = (z[1] - HEIGHT) / z[8] + (*t->box).m.inter_x;
			z[6] = (z[0] - WIDTH) / z[8] + (*t->box).m.inter_y;
			z[7] = 0;
			while (z[6] * z[6] + z[5] * z[5] <= 4 && z[7]
			< (*t->box).m.iter && ++z[7])
			{
				z[2] = sin(z[5] * z[5]) - tan(z[6] * z[6]) + z[3];
				z[6] = 2 * cos(z[5] * z[6]) + z[3];
				z[5] = z[2];
			}
			julia_print(z, t);
		}
	return (NULL);
}

void	*violetbrot(void *curent)
{
	t_thread	*t;
	long double	z[9];

	t = (t_thread*)curent;
	z[8] = WINX / (*t->box).m.zoom;
	z[0] = t->lim[0];
	while (z[0]++ < t->lim[1] && !(z[1] = 0))
		while (z[1]++ < WINX)
		{
			z[4] = (*t->box).m.mouse_x;
			z[3] = (*t->box).m.mouse_y;
			z[5] = (z[1] - HEIGHT) / z[8] + (*t->box).m.inter_x;
			z[6] = (z[0] - WIDTH) / z[8] + (*t->box).m.inter_y;
			z[7] = 0.0;
			while (z[6] * z[6] + z[5] * z[5] <= 4 && z[7]
			< (*t->box).m.iter && ++z[7])
			{
				z[2] = 2 * z[6] + 1.5 * z[5] * z[5] - z[4];
				z[6] = 2 * z[5] * z[6] - tan(z[3]);
				z[5] = z[2];
			}
			julia_print(z, t);
		}
	return (NULL);
}

void	*tree(void *curent)
{
	t_thread	*t;
	long double	z[9];

	t = (t_thread*)curent;
	z[8] = WINX / (*t->box).m.zoom;
	z[0] = t->lim[0];
	while (z[0]++ < t->lim[1] && !(z[1] = 0))
		while (z[1]++ < WINX)
		{
			z[4] = (*t->box).m.mouse_x;
			z[3] = (*t->box).m.mouse_y;
			z[5] = (z[1] - HEIGHT) / z[8] + (*t->box).m.inter_x;
			z[6] = (z[0] - WIDTH) / z[8] + (*t->box).m.inter_y;
			z[7] = 0.0;
			while (z[6] * z[6] + z[5] * z[5] <= 4 && z[7]
			< (*t->box).m.iter && ++z[7])
			{
				z[2] = fabsl(z[6] * z[6]) - fabsl(z[5] * z[5]) + z[4];
				z[6] = sqrt(fabsl(2 * z[5] * z[6])) + z[3];
				z[5] = z[2];
			}
			julia_print(z, t);
		}
	return (NULL);
}

void	*ghost(void *curent)
{
	t_thread	*t;
	long double	z[9];

	t = (t_thread*)curent;
	z[8] = WINX / (*t->box).m.zoom;
	z[0] = t->lim[0];
	while (z[0]++ < t->lim[1] && !(z[1] = 0))
		while (z[1]++ < WINX)
		{
			z[4] = (*t->box).m.mouse_x;
			z[3] = (*t->box).m.mouse_y;
			z[5] = (z[1] - HEIGHT) / z[8] + (*t->box).m.inter_x;
			z[6] = (z[0] - WIDTH) / z[8] + (*t->box).m.inter_y;
			z[7] = 0.0;
			while (z[6] * z[6] + z[5] * z[5] <= 4 && z[7]
			< (*t->box).m.iter && ++z[7])
			{
				z[2] = (z[6] * z[6] * z[6]) - fabsl(z[5] * z[5]) + z[4];
				z[6] = fabsl(2 * z[5] * z[6]) - z[3];
				z[5] = z[2];
			}
			julia_print(z, t);
		}
	return (NULL);
}
