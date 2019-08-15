

#include "fractol.h"

int		ft_pan_right(t_ol *tab)
{
	tab->x_o += 5 * tab->scale;
	tab->st_x += 5 * tab->scale;
	return (ft_redraw(tab->mlx, tab->number));
}

int     ft_pan_left(t_ol *tab)
{
	tab->x_o -= 5 * tab->scale;
	tab->st_x -= 5 * tab->scale;
	return (ft_redraw(tab->mlx, tab->number));
}

int     ft_pan_up(t_ol *tab)
{
	tab->y_o += 5 * tab->scale;
	tab->st_y += 5 * tab->scale;
	return (ft_redraw(tab->mlx, tab->number));
}

int     ft_pan_down(t_ol *tab)
{
	tab->y_o -= 5 * tab->scale;
	tab->st_y -= 5 * tab->scale;
	return (ft_redraw(tab->mlx, tab->number));
}


