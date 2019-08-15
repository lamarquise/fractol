

#include "fractol.h"

int		ft_mouse_press(int n, int x, int y, t_ol *tab)
{
	if (n == 4)
		return (ft_zoom_in(x, y, tab));		// in a return, yea i guess
	if (n == 5)
		return (ft_zoom_out(x, y, tab));
	if (n == 1)		// more securite stuff ??? i mean maybe later
	{
		tab->m_pressed = 1;
		tab->m_x = x;
		tab->m_y = y;
	}
	return (0);
}

int		ft_mouse_release(int n, int x, int y, t_ol *tab)
{
	if (n == 1)
		tab->m_pressed = 0;
	return (0);
}

	// can i make the calculations more efficient ???

int		ft_mouse_move(int x, int y, t_ol *tab)
{
	if (tab->m_pressed)
	{			// 2 so a bit more controled, better...
		tab->x_o -= (x - tab->m_x) * tab->scale / 2;
		tab->y_o += (y - tab->m_y) * tab->scale / 2;
		tab->st_x -= (x - tab->m_x) * tab->scale / 2;
		tab->st_y += (y - tab->m_y) * tab->scale / 2;
		return (ft_redraw(tab->mlx, tab->number));
	}
	return (0);
}


