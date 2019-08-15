



#include "fractol.h"

	// new zoom is a facor of 2 every time...


int		ft_resetfract(t_ol *tab)	// could call this in init to save space
{									// wait no cuz return...
	tab->st_x = -2.2;
	tab->st_y = 2;
	tab->scale = 0.005;
	tab->x_o = 0;
	tab->y_o = 0;
	tab->wid_scale = 4.4;
	tab->hei_scale = 4;
	tab->zoom = 1;
	return (ft_redraw(tab->mlx, tab->number));
}

int		ft_zoom_out(int x, int y, t_ol *tab)
{
	if (tab->zoom == 1)
		return (ft_resetfract(tab));
	else if (tab->zoom > 1)
	{
		--tab->zoom;

		tab->x_o = (tab->st_x + x * tab->scale) * (1 - tab->z_fact) +\
					(tab->x_o * tab->z_fact);
		tab->y_o = (tab->st_y - y * tab->scale) * (1 - tab->z_fact) +\
					(tab->y_o * tab->z_fact);


		tab->wid_scale *= tab->z_fact;
		tab->hei_scale *= tab->z_fact;

//		printf("out origin: x = %f, y = %f\n", tab->x_o, tab->y_o);

		tab->scale *= tab->z_fact;

		tab->st_x = tab->x_o - tab->wid_scale / 2;
		tab->st_y = tab->y_o + tab->hei_scale / 2;
		
//		printf("out new st: x %f, y %f\n", tab->st_x, tab->st_y);

		return (ft_redraw(tab->mlx, tab->number));
	}
	return (0);
}

int		ft_zoom_in(int x, int y, t_ol *tab)
{
	int		i;

	i = 0;
		++tab->zoom;

//	while (i < 5)
//	{
		
		tab->x_o = ((tab->z_fact - 1) * (tab->st_x + x *\
					tab->scale) + tab->x_o) / tab->z_fact;
		tab->y_o = ((tab->z_fact - 1) * (tab->st_y - y *\
					tab->scale) + tab->y_o) / tab->z_fact;

		tab->scale /= tab->z_fact;

		tab->wid_scale /= tab->z_fact;	// adjust to new win wid scale
		tab->hei_scale /= tab->z_fact;

//		printf("in origin: x = %f, y = %f\n", tab->x_o, tab->y_o);
			//divide again because need 1/4 only works if fact is 2 ???
		tab->st_x = tab->x_o - tab->wid_scale / 2;
		tab->st_y = tab->y_o + tab->hei_scale / 2;		// this sets new top left coord
	
//		printf("in new st: x %f, y %f\n", tab->st_x, tab->st_y);
		ft_redraw(tab->mlx, tab->number);
//		++i;
//	}
	return (ft_redraw(tab->mlx, tab->number));
}







