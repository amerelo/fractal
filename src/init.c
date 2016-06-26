/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/26 21:11:19 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/26 21:47:32 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

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
	box->m.mouse_x = 0.355;
	box->m.mouse_y = 0.288;
	box->m.zoom = 6.0;
	box->m.iter = 100;
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
