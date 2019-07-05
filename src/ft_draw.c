


#include "fractol.h"

t_compn		ft_sqr_comp(t_compn *n)
{
	t_compn	tmp;
	
	tmp.real = n->real * n->real - n->imagin * n->imagin;
	tmp.imagin = 2 * n->real * n->imagin;
	return (tmp);
}


int			ft_math_it(t_fract * mlx, t_compn *coord)	// for each pixel...
{
	int		i;
	t_compn	z;
	t_compn	tmp;
	double	n;

//	printf("math it\n");

	i = 0;
	z.real = 0;
	z.imagin = 0;
	while (i < mlx->max_iter)
	{
		tmp = ft_sqr_comp(&z);
		z.real = tmp.real + coord->real;
		z.imagin = tmp.imagin + coord->imagin;

	
//		printf("co.real: %f, im: %f\n", coord->real, coord->imagin);
//		tmp.real = z.real * z.real + coord->real;
//		tmp.imagin = z.imagin * z.imagin + coord->imagin;
//		z = tmp;
//		printf("z.r: %f, z.i: %f\n", z.real, z.imagin);
//		free(tmp);		// right way to do this ???
		n = z.real * z.real + z.imagin * z.imagin;
//		if (z.real * z.real + z.imagin * z.imagin >= 4)
//		printf("n: %f\n", n);
		if (n >= 4)
			return (i);
		++i;
	}
	return (mlx->max_iter);
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

/*
t_frol_type	*ft_init_frols(t_fract *mlx)	// ????
{
	int		
}

*/

void		ft_draw(t_fract *mlx, int i)
{
	int		p;
	int		c;
	t_compn	coord;

/*	mlx->tab[i].img_data[mlx->tab[i].syst_origin] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin + 1] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin - 1] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin + mlx->tab[i].win_width] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin - mlx->tab[i].win_width] = 0xffffff;	
*/
	p = 0;
	while (p < mlx->tab[i].last_pix)
	{
		coord.real = mlx->tab[i].start_x + (p % mlx->tab[i].win_width)\
		* mlx->tab[i].scale;
		coord.imagin = mlx->tab[i].start_y - (p / mlx->tab[i].win_width)\
		* mlx->tab[i].scale;
//		printf("co.real: %f, im: %f\n", coord.real, coord.imagin);
		c = ft_math_it(mlx, &coord);
//		printf("c = %d\n", c);
		if (c < mlx->max_iter)
			mlx->tab[i].img_data[p] = 0xff0000 + c * 64;
		++p;
//		p += 10;
	}

	mlx->tab[i].img_data[176000 + 680] = 0xffffff;
	
//	printf("ite

	ft_drawcoordsys(mlx, i);	
/*	
	mlx->tab[i].img_data[mlx->tab[i].syst_origin] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin + 1] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin - 1] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin + mlx->tab[i].win_width] = 0xffffff;
	mlx->tab[i].img_data[mlx->tab[i].syst_origin - mlx->tab[i].win_width] = 0xffffff;
*/
}




