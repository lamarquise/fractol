/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:31:12 by erlazo            #+#    #+#             */
/*   Updated: 2019/07/04 19:09:14 by erlazo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>


# include "mlx.h"
# include "libft.h"
# include <math.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct	s_compn
{
	double	real;
	double	imagin;
}				t_compn;

typedef struct	s_frol_type
{
	int		type;
	int		equ;	// ???????
}				t_frol_type;

typedef	struct	s_ol
{
	char		*name;
	int			type;
	void		*win_ptr;
	void		*img_ptr;
	int			*img_data;
	int			win_width;
	int			win_height;
	int			last_pix;
	int			syst_origin;
	double		start_x;
	double		start_y;	//these depend on scale ???? i think so...
	double		scale;
	int			zoom_scale_thing;
}				t_ol;

typedef struct	s_fract
{
	void	*ptr;
	t_ol	*tab;	// make this a table but later maybe a ll 
	int		n_frols;
//	int		win_width;
//	int		win_height;
//	int		last_pix;
//	void	*img_ptr;
//	int		*img_data;
	int		bpp;
	int		s_l;
	int		endian;
//	int		syst_origin;



	int		max_iter;



}				t_fract;

typedef struct	s_key
{
	int		keycode;
	int		(*f)(t_fract *mlx);
}				t_key;

void	ft_fractal(t_list *files);
int		ft_initfractal(t_fract *mlx, t_ol *tab, t_list *files);
int		ft_redraw(t_fract *mlx, int i);
void	ft_hooks_loop(t_fract *mlx, int i);
void	ft_draw(t_fract *mlx, int i);
int		ft_quitfract(t_fract *mlx);


#endif
