

#ifndef IMG_H
# define IMG_H

	// ok so it's just always gonna be square cuz whatevs...

# define MIN_WID 400
# define MAX_WID 1200

# include <stdio.h>

# include "mlx.h"
# include "libft.h"

# include <math.h>

typedef struct	s_car
{			// may not need floats, cuz cartesian
	float	x;
	float	y;
}				t_car;

typedef struct	s_cord
{
	int		x_b;			// # of boxes wide
	int		y_b;
	int		b_wid;		// width of box
	int		b_hei;
	t_car	*tab;		// table of cartesian coords??
}				t_cord;

		// necessary ???

typedef struct	s_mag
{
	void	*img_ptr;
	int		*img_data;
	int		x;			// #pixels wide
	int		y;			// of img
	int		last;
	t_car	*tab;
	
}				t_mag;

typedef struct	s_img
{
	void	*ptr;
	void	*win_ptr;
	int		win_width;
	int		last_p;
	int		*tab;		//still somewhat usefull...
//	void	*img_ptr;
//	int		*img_data;
	int		bpp;
	int		s_l;
	int		endian;
	int		zoom;
	t_cord	*dim;
	t_mag	*img;
}				t_img;

typedef struct	s_key
{
	int		keycode;
	int     (*f)(t_img *mlx);
}				t_key;


int		usage_err(char *str);
int		ft_initimg(t_img *mlx, t_cord *dim);
int		ft_img(t_cord *dim);
void	ft_draw(t_img *mlx);
void	ft_hooks_loop(t_img *mlx);
int		ft_quit(t_img *mlx);
int		ft_zoom_in(t_img *mlx);
int		ft_zoom_out(t_img *mlx);
int		ft_redraw(t_img *mlx);
void	start_car(t_mag *img, t_car *cord);
void	ft_altdraw(t_img *mlx);

#endif
