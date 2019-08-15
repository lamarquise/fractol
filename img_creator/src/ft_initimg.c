


#include "img.h"

int		ft_create_win(t_img *mlx)
{
	if (!(mlx->ptr = mlx_init()))
		return (usage_err("mlx_init\n"));
//	printf("x: %d y: %d\n", mlx->img->x, mlx->img->y);
	if (!(mlx->win_ptr = mlx_new_window(\
		mlx->ptr, mlx->win_width, mlx->win_width, "img")))
		return (usage_err("win_init\n"));
	if (!(mlx->img->img_ptr = mlx_new_image(mlx->ptr,\
		mlx->img->x, mlx->img->y)))
		return (usage_err("img_init\n"));
	if (!(mlx->img->img_data = (int*)mlx_get_data_addr(mlx->img->img_ptr,\
		&mlx->bpp, &mlx->s_l, &mlx->endian)))
		return (usage_err("data_init\n"));
	return (-1);
}

int		ft_initimg(t_img *mlx, t_cord *dim)
{
	int		n;
/*		// variable window size...
	if (dim->x >= dim->y)
		n = dim->x;
	else
		n = dim->y;
	if (dim->size * n + 20 >= MIN_WID && dim->size * n + 20 <= MAX_WID)
		mlx->win_width = dim->size * n + 20;
	else if (dim->size * n + 20 < MIN_WID)
		mlx->win_width = MIN_WID;
	else
		mlx->win_width = MAX_WID;
*/
	mlx->win_width = 700;
	mlx->zoom = 1;
	return (ft_create_win(mlx));
}
