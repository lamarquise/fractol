


#include "fractol.h"

int		ft_createwin(t_fract *mlx, t_ol *tab, int i)
{
	char 	*str;

//	printf("creawin 1\n");

//	str = ft_strjoin("factol", ft_itoa(i));
	tab->start_x = -2.2;
	tab->start_y = 2;
	tab->scale = 0.005;
	tab->win_height = 800;
	tab->win_width = 880;
	tab->last_pix = tab->win_width * tab->win_height - 1;
	tab->syst_origin = (tab->win_width) * (tab->win_height / 2)\
	+ tab->win_width / 2;
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

int		ft_initfractal(t_fract *mlx, t_ol *tab, t_list *files)
{
	int		i;
	
	i = 0;
//	if (!(tab = (t_ol*)ft_memalloc(sizeof(t_ol) * mlx->n_frols)))
//		return (0);
	
//	printf("init test 1\n");
	

	if (!(mlx->ptr = mlx_init()))
		return (0);
//	while (i < mlx->n_frols)
//	{
//		tab[i]->type = files
//		tab[i]->type = files->content_size;
//		tab[i]->win_height = 500;
//		tab[i]->win_width = 700;
//		tab[i]->last_pix = tab[i]->win_width * tab[i]->win_height - 1;
//		tab[i]->syst_origin = (tab[i]->win_width) * (tab[i]->win_height / 2)\
//		+ tab[i]->win_width / 2;
		ft_createwin(mlx, &tab[i], i);
//		++i;
//	}
//	printf("init test 2\n");
	mlx->tab = tab;		// i think, do we need to store it here ??? might as well
	mlx->max_iter = 50;
	return (1);
}


