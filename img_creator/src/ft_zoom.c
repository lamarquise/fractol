

#include "img.h"

int		ft_zoom_in(t_img *mlx)
{
	++mlx->zoom;
	printf("zoom test in\n");
	return (ft_redraw(mlx));
}

int		ft_zoom_out(t_img *mlx)
{
	printf("zoom test out\n");
	if (mlx->zoom > 1)
		++mlx->zoom;
//	printf("zoom: %f\n", mlx->zoom);
	return (ft_redraw(mlx));
}
