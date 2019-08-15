

#include "img.h"




void	ft_draw(t_img *mlx)
{
	int		i;
	int		n;
	int		x;
	int		y;

	i = 0;
	while (i < mlx->last_p)
	{
//		n = 0xFFFFFF - (abs(rand()) % 16777216);// need better rand that isnt neg...

		n = rand() % 256 * 65536 + rand() % 256 * 256 + rand() % 256;
		y = 0;
		while (y < mlx->dim->hei)
		{
			x = 0;
			while (x < mlx->dim->wid)
			{
				mlx->img->img_data[mlx->tab[i] + y * mlx->img->x + x] = n;
//				printf("n: %d\n", n);
				++x;
			}
			++y;
		}
		++i;
	}
}
