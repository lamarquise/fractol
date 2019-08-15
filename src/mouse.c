

#include "fractol.h"

int		ft_mouse_press(int n, int x, int y, t_ol *tab)
{
	if (n == 4)
		return (ft_zoom_in(x, y, tab));		// in a return, yea i guess
	if (n == 5)
		return (ft_zoom_out(x, y, tab));
	if (n == 1 && x >= 0 && x <= tab->win_width && y >= 0 && y <= tab->win_width)		// more securite stuff ??? i mean maybe later
	{
		printf("x:%d, y:%d", x, y);
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
	{			// need to match mouse move with img move...
		tab->x_o -= (x - tab->m_x) * tab->scale;
		tab->y_o += (y - tab->m_y) * tab->scale;
		tab->st_x -= (x - tab->m_x) * tab->scale;
		tab->st_y += (y - tab->m_y) * tab->scale;
		return (ft_redraw(tab->mlx, tab->number));
	}
	return (0);
}


