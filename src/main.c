/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:04:15 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/29 04:16:52 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		mlx_all(t_env box)
{
	pthread_t	p[TR];
	int			i;
	int			j;

	i = -1;
	j = -1;
	if (!(box.mlx_ptr = mlx_init()) ||
	!(box.win_ptr = mlx_new_window(box.mlx_ptr, WINX, WINY, "fractal")) ||
	!(box.img_ptr = mlx_new_image(box.mlx_ptr, WINX, WINY)) ||
	!(box.img = mlx_get_data_addr(box.img_ptr, &box.img_bpp,
	&box.img_bpl, &box.endian)))
		return (0);
	init_thread(box.t, &box);
	while (++i < TR)
		pthread_create(&p[i], NULL, box.fra[box.index].fractol, &box.t[i]);
	while (++j < TR)
		pthread_join(p[j], NULL);
	mlx_hook(box.win_ptr, 6, (1L << 6), mouse, &box);
	mlx_put_image_to_window(box.mlx_ptr, box.win_ptr, box.img_ptr, 0, 0);
	mlx_mouse_hook(box.win_ptr, detect_click, &box);
	mlx_hook(box.win_ptr, 2, (1L << 0), detect, &box);
	mlx_hook(box.win_ptr, 17, (1L << 17), ft_quit, &box);
	mlx_loop(box.mlx_ptr);
	return (1);
}

int		find_frac(char *str, t_env *box)
{
	box->index = -1;
	while (++box->index < NF)
	{
		if (ft_strequ(str, box->fra[box->index].name))
			return (box->index);
	}
	return (-1);
}

int		main(int ac, char **av)
{
	t_env	box;

	init_env(&box);
	if (ac != 2 || find_frac(av[1], &box) < 0)
	{
		ft_putstr_fd("mandelbrot\njulia\ntrimandel\nsnake\ntree\n", 2);
		ft_putstr_fd("ghost\nburning_ship\nvioletbrot\n", 2);
		return (0);
	}
	mlx_all(box);
}
