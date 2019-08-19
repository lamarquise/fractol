

#include "img.h"

int		ft_redraw(t_img *mlx)	// should work???
{
	if (mlx->zoom == 1)
	{
//		printf("redraw test 1\n");
		mlx_destroy_image(mlx->ptr, mlx->img->img_ptr);
		if (!(mlx->img->img_ptr = mlx_new_image(mlx->ptr,\
			mlx->img->x, mlx->img->y)))
			return (0);
		mlx->img->img_data = (int*)mlx_get_data_addr(mlx->img->img_ptr,\
							&mlx->bpp, &mlx->s_l, &mlx->endian);
		ft_draw(mlx);
//		printf("redraw test 2\n");
	
		mlx_clear_window(mlx->ptr, mlx->win_ptr);
//		mlx_put_image_to_window(mlx->ptr, mlx->win_ptr,\
			mlx->img->img_ptr, 50, 50);
	}
	else		// ft_zoom already called so no need to send new img dims
		ft_altdraw(mlx);
//	printf("redraw test 3\n");
//	mlx_clear_window(mlx->ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr,\
		mlx->img->img_ptr, 50, 50);
//	printf("redraw test 4\n");
	return (0);
}

void	ft_light_torch(t_key *torch)
{
	torch[0].keycode = 53;
	torch[0].f = &ft_quit;
	torch[1].keycode = 24;
	torch[1].f = ft_zoom_in;
	torch[2].keycode = 27;
	torch[2].f = ft_zoom_out;
	torch[3].keycode = 15;
	torch[3].f = ft_redraw;

/*
	torch[4].keycode = ;
	torch[4].f = ;

	torch[4].keycode = ;
	torch[4].f = ;
	torch[4].keycode = ;
	torch[4].f = ;
	torch[4].keycode = ;
	torch[4].f = ;
	torch[4].keycode = ;
	torch[4].f = ;
*/
	
}

int		ft_keyhooks(int keycode, t_img *mlx)
{
	static t_key	torch[20] = {{42, NULL}};
	int				i;

	i = 0;
	if (torch[0].keycode == 42)
		ft_light_torch(torch);
	while (i < 20)
	{
		if (keycode == torch[i].keycode)
			return (torch[i].f(mlx));
		++i;
	}
	return (0);
}

void	ft_hooks_loop(t_img *mlx)
{
	mlx_hook(mlx->win_ptr, 2, 0, &ft_keyhooks, mlx);
	mlx_hook(mlx->win_ptr, 17, 0, &ft_quit, mlx);
	
}
