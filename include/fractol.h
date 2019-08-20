/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erlazo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 16:31:12 by erlazo            #+#    #+#             */
/*   Updated: 2019/08/20 21:49:22 by erlazo           ###   ########.fr       */
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



// img stuff for interpolation

typedef struct	s_mag
{
	void	*img_ptr;
	int		*img_data;
	int		x;			// # of pixels wid of img
	int		y;
	int		last_p;
}				t_mag;




// regular fractal stuff

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
	struct s_fract	*mlx;

//	void			*all_ptr;
	char			*name;
	int				type;
	int				number;
	void			*win_ptr;
	void			*img_ptr;
	int				*img_data;
	int				win_width;
	int				win_height;
	int				last_pix;
	int				win_origin;
	double			z_fact;		//zoom factor
	int				z_iter;		// # of times interpolate between final imgs when zoom (-1), basically its a factor for between regular zooms
//	double			og_st_x;//og left cord
//	double			og_st_y;
	double			st_x; // current left cord
	double			st_y;
	double			x_o;// cord of mid wind, origin
	double			y_o;
	double			wid_scale;	//size of syst
	double			hei_scale;
	double			scale;	// pixel to syst
	int				zoom;
	int				max_iter;
	int				disp_info;

	// stuff for interpol
	double			old_st_x;
	double			old_st_y;
	double			old_wid_scale;
	double			old_hei_scale;
	double			old_scale;

	// mouse stuff:
	int				m_pressed;	// is or not
	int				m_x;		// new mouse coord
	int				m_y;
	int				m_st_x;		// prev mouse coord
	int				m_st_y;		// useful ?????

//	t_compn			*o;	// coord of mid of wind
}				t_ol;

typedef struct	s_fract
{
	void	*ptr;
	t_ol	*tab;	// linked list instead???
	int		n_frols;
	int		bpp;
	int		s_l;
	int		endian;
}				t_fract;

typedef struct	s_key
{
	int		keycode;
	int		(*f)(t_ol *tab);
}				t_key;

void	ft_fractal(t_list *files);
int		ft_initfractal(t_fract *mlx, t_ol *tab);
int		ft_redraw(t_fract *mlx, int i);
void	ft_hooks_loop(t_fract *mlx, int i);
void	ft_draw(t_fract *mlx, int i);
int		ft_quitfract(t_ol *tab);
int		ft_quitone(t_ol *tab);

int		ft_zoom_in(int x, int y, t_ol *tab);
int		ft_zoom_out(int x, int y, t_ol *tab);
int		ft_resetfract(t_ol *tab);
int		ft_display_info(t_ol *tab);
int		ft_more_precise(t_ol *tab);
int		ft_less_precise(t_ol *tab);

int		ft_pan_right(t_ol *tab);
int		ft_pan_left(t_ol *tab);
int		ft_pan_up(t_ol *tab);
int		ft_pan_down(t_ol *tab);
int		ft_mouse_press(int n, int x, int y, t_ol *tab);
int		ft_mouse_release(int n, int x, int y, t_ol *tab);
int		ft_mouse_move(int x, int y, t_ol *tab);

// interpolation
void	ft_resize(t_ol *tab);
int		ft_simple_zoom(t_ol *tab);	// tmp ???

#endif
