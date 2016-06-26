/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 21:14:02 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/26 21:51:39 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		ft_quit(void)
{
	exit(0);
}

void	remake(t_env *box)
{
	pthread_t	p[TR];
	int		i = -1;
	int		j = -1;

	ft_bzero(box->img, (WINX * WINY * 4));
	while (++i < TR)
		pthread_create(&p[i], NULL, mandelbrot, &box->t[i]);
	while (++j < TR)
		pthread_join(p[j], NULL);
	mlx_put_image_to_window(box->mlx_ptr, box->win_ptr, box->img_ptr, 0, 0);
}

int		mouse(int x, int y, t_env *box)
{
	// printf("%d %d\n",x , y);
	box->m.mouse_x = 0.353 + ((x - HEIGHT) * 0.0001);
	box->m.mouse_y = 0.288 + ((y - WIDTH) * 0.0001);
	remake(box);
	return (1);
}

int		detect_click(int button, int x, int y, t_env *box)
{
	// printf("%d\n", button);
	// printf("%Lf %Lf\n", box->m.inter_x, box->m.inter_y);
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
