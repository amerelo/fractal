/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 21:14:02 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/29 04:27:51 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	remake(t_env *box)
{
	pthread_t	p[TR];
	int			i;
	int			j;

	i = -1;
	j = -1;
	ft_bzero(box->img, (WINX * WINY * 4));
	while (++i < TR)
		pthread_create(&p[i], NULL, box->fra[box->index].fractol, &box->t[i]);
	while (++j < TR)
		pthread_join(p[j], NULL);
	mlx_put_image_to_window(box->mlx_ptr, box->win_ptr, box->img_ptr, 0, 0);
}

int		mouse(int x, int y, t_env *box)
{
	if (box->stop == 0)
	{
		box->m.mouse_x = 0.353 + ((x - HEIGHT) * 0.001);
		box->m.mouse_y = 0.288 + ((y - WIDTH) * 0.001);
		remake(box);
	}
	return (1);
}

int		detect_click(int button, int x, int y, t_env *box)
{
	if (button == 1 || button == 6 || button == 4)
	{
		box->m.interval_x = box->m.inter_x;
		box->m.interval_y = box->m.inter_y;
		box->m.inter_x = box->m.inter_x + (x - HEIGHT) / 20 * box->m.zoom / 100;
		box->m.inter_y = box->m.inter_y + (y - WIDTH) / 20 * box->m.zoom / 100;
		if (box->m.iter < 300)
			box->m.iter += 5;
		box->m.zoom *= 0.5;
		remake(box);
	}
	else if (button == 2 || button == 7 || button == 5)
	{
		box->m.zoom *= 2;
		if (box->m.iter > 25)
			box->m.iter -= 5;
		remake(box);
	}
	return (1);
}

void	detect_2(int keycode, t_env *box)
{
	if (keycode == 12 && (box->c[0] += 1))
		remake(box);
	if (keycode == 13 && (box->c[1] += 0.1))
		remake(box);
	if (keycode == 0 && (box->c[0] -= 1))
		remake(box);
	if (keycode == 1 && (box->c[1] -= 0.1))
		remake(box);
	if (keycode == 83 && (box->m.iter += 5))
		remake(box);
	if (keycode == 84 && (box->m.iter -= 5))
		remake(box);
	if (keycode == 27)
	{
		box->index -= (box->index < 1) ? -7 : 1;
		remake(box);
	}
	if (keycode == 24)
	{
		box->index += (box->index < 7) ? 1 : -7;
		remake(box);
	}
}

int		detect(int keycode, t_env *box)
{
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
	if (keycode == 49)
		box->stop = (box->stop == 1) ? 0 : 1;
	if (keycode == 82 && reset(box))
		remake(box);
	detect_2(keycode, box);
	if (keycode == 53)
		ft_quit();
	return (1);
}
