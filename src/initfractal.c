


#include "fractol.h"



	// may need to seperate parts of this function out into multiple so can have 
	// mendel and julia and others...
int		ft_createwin(t_fract *mlx, t_ol *tab, int i) // don't really need i...
{
	char 	*str;

//	printf("creawin 1\n");

	tab->number = i;
	tab->mlx = mlx;
	tab->max_iter = 25;
	tab->scale = 0.005;
	tab->win_height = 800;
	tab->win_width = 880;
	tab->last_pix = tab->win_width * tab->win_height - 1;
	tab->win_origin = (tab->win_width) * (tab->win_height / 2)\
	+ tab->win_width / 2;
	
//	tab->og_st_x = -2.2;
//	tab->og_st_y = 2;


	tab->st_x = -2.2;
	tab->st_y = 2;
	tab->x_o = 0;
	tab->y_o = 0;
	tab->wid_scale = 4.4;
	tab->hei_scale = 4;
//	tab->scale = tab->start_x * 2 / tab->win_width;		// don't work ???
	tab->zoom = 1;
	tab->z_fact = 2;
	tab->disp_info = 0;

	// mouse stuff
	tab->m_pressed = 0;
	tab->m_x = 0;
	tab->m_y = 0;
	tab->m_st_x = 0;
	tab->m_st_y = 0;

	if (!(tab->win_ptr = mlx_new_window(\
		mlx->ptr, tab->win_width, tab->win_height, tab->name)))
		return (1);
//	free(str);			// necessary??? correct ??? see gnl...
	if (!(tab->img_ptr = mlx_new_image(\
		mlx->ptr, tab->win_width, tab->win_height)))
		return (2);
	if (!(tab->img_data = (int*)mlx_get_data_addr(tab->img_ptr, &mlx->bpp,
		&mlx->s_l, &mlx->endian)))
		return (3);
	return (0);
}

int		ft_initfractal(t_fract *mlx, t_ol *tab)
{
	int		i;
	
	i = 0;
//	printf("init test 1\n");
	

	if (!(mlx->ptr = mlx_init()))
		return (0);
	while (i < mlx->n_frols)
	{
//		tab[i]->type = files				// already done...
//		tab[i]->type = files->content_size;
		ft_createwin(mlx, &tab[i], i);
		++i;
	}
//	printf("init test 2\n");
	mlx->tab = tab;		// i think, do we need to store it here ??? might as well
//	mlx->max_iter = 50;
	return (1);
}


