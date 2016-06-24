/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:03:37 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/24 18:07:57 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <pthread.h>
# define WINX 1800 // 2560
# define WINY 1200 // 1440
# define HEIGHT WINX / 2.0
# define WIDTH WINY / 2.0
# define TR 8

typedef struct			s_mandel
{
	double				inter_x;
	double				inter_y;
	double				interval_x;
	double				interval_y;
	double				zoom;
}						t_man;

typedef struct			s_thread
{
	int					nb;
	int					lim[2];
	struct s_env		*box;
}						t_thread;

typedef struct			s_env
{
	void				*img_ptr;
	void				*mlx_ptr;
	void				*win_ptr;
	char				*img;
	int					img_bpp;
	int					img_bpl;
	int					endian;
	t_man				m;
	t_thread			t[TR];
}						t_env;

void	*make_mandel(void *curent);

#endif
