

#include "fractol.h"

int		ft_display_info(t_ol *tab)
{
	tab->disp_info = abs(tab->disp_info - 1);
	return (ft_redraw(tab->mlx, tab->number));	// necessary redraw???
}		// expensive for removing a simple string...


int		ft_more_precise(t_ol *tab)
{
	tab->max_iter += 25;
	return (ft_redraw(tab->mlx, tab->number));
}

int		ft_less_precise(t_ol *tab)
{
	if (tab->max_iter > 25)
		tab->max_iter -= 25;
	return (ft_redraw(tab->mlx, tab->number));
}
