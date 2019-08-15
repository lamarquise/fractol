


#include "fractol.h"

t_compn		ft_sqr_comp(t_compn *n)
{
	t_compn	tmp;
	
	tmp.real = n->real * n->real - n->imagin * n->imagin;
	tmp.imagin = 2 * n->real * n->imagin;
	return (tmp);
}

int			ft_math_it(t_ol *tab, t_compn *coord)	// for each pixel...
{
	int		c;
	t_compn	z;
	t_compn	tmp;
	double	n;

//	printf("math it\n");
	c = 0;
	z.real = 0;		// necessary init ???
	z.imagin = 0;
	while (c < tab->max_iter)
	{
		tmp = ft_sqr_comp(&z);
		z.real = tmp.real + coord->real;
		z.imagin = tmp.imagin + coord->imagin;
//		n = z.real + z.imagin;		// cool but doesn't work...
		n = z.real * z.real + z.imagin * z.imagin;
//		if (z.real * z.real + z.imagin * z.imagin >= 4)
//		printf("n: %f\n", n);
		if (n >= 4)
			return (c);
		++c;
	}
	return (tab->max_iter);
}

void	ft_drawcoordsys(t_fract *mlx, int i)
{
	int		p;

	p = 0;
	while (p < mlx->tab[i].win_width)
	{
		mlx->tab[i].img_data[mlx->tab[i].win_width\
		* mlx->tab[i].win_height / 2 + p] = 0xffffff;
		++p;
	}
	p = 0;
	while (p < mlx->tab[i].win_height)
	{
		mlx->tab[i].img_data[mlx->tab[i].win_width / 2 + p\
		* mlx->tab[i].win_width] = 0xffffff;
		++p;
	}
}

void		ft_draw(t_fract *mlx, int i)
{
	int		p;
	int		c;
	t_compn	coord;
	
			// this needs to be improved...

//	mlx->tab[i].cent = mlx->tab[i].start_x / mlx->tab[i].zoom;
//	mlx->tab[i].y = mlx->tab[i].start_y / mlx->tab[i].zoom;
//	mlx->tab[i].scale = mlx->tab[i].scale / mlx->tab[i].zoom;

	p = 0;
	while (p < mlx->tab[i].last_pix)
	{
		coord.real = mlx->tab[i].st_x + (p % mlx->tab[i].win_width)\
		* mlx->tab[i].scale;
		coord.imagin = mlx->tab[i].st_y - (p / mlx->tab[i].win_width)\
		* mlx->tab[i].scale;
//		printf("co.real: %f, im: %f\n", coord.real, coord.imagin);
		c = ft_math_it(&mlx->tab[i], &coord);
//		printf("c = %d\n", c);
		if (c < mlx->tab[i].max_iter)
			mlx->tab[i].img_data[p] = 0xff0000 + c * 64;
		++p;
	}

//	mlx->tab[i].img_data[176000 + 680] = 0xffffff;

	ft_drawcoordsys(mlx, i);
}




