/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amerelo <amerelo@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/16 19:03:37 by amerelo           #+#    #+#             */
/*   Updated: 2016/06/16 19:38:24 by amerelo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H
# include "libft.h"
# include <mlx.h>
# include <math.h>
# define WINX 1800
# define WINY 1200


typedef struct			s_env
{
	void				*img_ptr;
	void				*mlx_ptr;
	void				*win_ptr;
	char				*img;
	int					img_bpp;
	int					img_bpl;
	int					endian;
}						t_env;

#endif
