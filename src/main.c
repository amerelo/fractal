/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:04:15 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/16 19:40:03 by amerelo          ###   ########.fr       */
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
}

int		main(void)
{
	t_env box;

	init_env(&box);
	if (!(box.mlx_ptr = mlx_init()) ||
	!(box.win_ptr = mlx_new_window(box.mlx_ptr, WINX, WINY, "fractal")) ||
	!(box.img_ptr = mlx_new_image(box.mlx_ptr, WINX, WINY)) ||
	!(box.img = mlx_get_data_addr(box.img_ptr, &box.img_bpp,
	&box.img_bpl, &box.endian)))
		return (0);

	mlx_hook(box.win_ptr, 17, (1L << 17), ft_quit, &box);
	mlx_hook(box.win_ptr, 2, (1L << 0), detect, &box);
	mlx_loop(box.mlx_ptr);
}
