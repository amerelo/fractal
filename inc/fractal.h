/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:03:37 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/26 21:51:51 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <pthread.h>
#include <stdio.h> //
# define WINX 1500 // 2560
# define WINY 1200 // 1440
# define HEIGHT WINX / 2.0
# define WIDTH WINY / 2.0
# define TR 16

typedef struct			s_mandel
{
	long double				inter_x;
	long double				inter_y;
	long double				interval_x;
	long double				interval_y;
	long double				mouse_x;
	long double				mouse_y;
	long double				zoom;
	int						iter;
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

void					*mandelbrot(void *curent);
void					init_env(t_env *box);
void					init_thread(t_thread *t, t_env *box);
int						ft_quit(void);
int						mouse(int x, int y, t_env *box);
void					remake(t_env *box);
int						detect_click(int button, int x, int y, t_env *box);
int						detect(int keycode, t_env *box);


#endif
