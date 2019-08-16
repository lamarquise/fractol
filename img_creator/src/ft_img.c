

#include "img.h"

	// fills the table with the cord in window of all future points...

void	ft_clear(t_img *mlx)
{
	printf("quit test 1\n");
	if (mlx->img->img_ptr)// && mlx->img->img_data)
	{
		printf("quit test 1,5\n");
		mlx_destroy_image(mlx->ptr, mlx->img->img_ptr);		// segfaults???
	}
	if (mlx->win_ptr)
	{
		mlx_clear_window(mlx->ptr, mlx->win_ptr);
		mlx_destroy_window(mlx->ptr, mlx->win_ptr);
	}
	printf("quit test 2\n");
}

int		ft_quit(t_img *mlx)
{
	ft_clear(mlx);
	exit(0);
}

	// still somewhat usefull...

void	ft_filltab(t_img *mlx, t_cord *dim)
{
	int		x;
	int		y;

	y = 0;
	while (y < dim->y_b)
	{
		x = 0;
		while (x < dim->x_b)
		{		// has to be more efficient way to go through tab...
			mlx->tab[y * dim->x_b + x] = x * dim->b_wid + y * mlx->img->x * dim->b_hei;
			++x;
		}
		++y;
	}
}

int		ft_img(t_cord *dim)			// better a void???
{
	int		*tab;
	t_img	mlx;
	t_mag	img;
	t_car	*cord;

	if (!(tab = ft_memalloc(sizeof(int) * dim->x_b * dim->y_b)))
		return (usage_err("malloc failed\n"));
	img.x = dim->x_b * dim->b_wid;
	img.y = dim->y_b * dim->b_hei;
	img.last_p = img.x * img.y;

//	start_car(&img, cord);

	mlx.img = &img;
	if (ft_initimg(&mlx, dim) != -1)
		return (usage_err("init failed\n"));
	mlx.tab = tab;
	ft_filltab(&mlx, dim);
	mlx.last_b = dim->x_b * dim->y_b;
	mlx.dim = dim;
	ft_draw(&mlx);
	mlx_put_image_to_window(mlx.ptr, mlx.win_ptr, mlx.img->img_ptr, 50, 50);
	ft_hooks_loop(&mlx);
	mlx_loop(mlx.ptr);
	return (0);
}
