

#include "img.h"


// if ret img rather than put in it self then could make altdraw do same and
// easier to implement...

void	ft_draw(t_img *mlx)
{
	int		i;
	int		color;
	int		x;
	int		y;

	i = 0;
	while (i < mlx->last_b)
	{
//		n = 0xFFFFFF - (abs(rand()) % 16777216);// need better rand that isnt neg...

		color = rand() % 256 * 65536 + rand() % 256 * 256 + rand() % 256;
		y = 0;
		while (y < mlx->dim->b_hei)
		{
			x = 0;
			while (x < mlx->dim->b_wid)
			{
				mlx->img->img_data[mlx->tab[i] + y * mlx->img->x + x] = color;
//				printf("n: %d\n", n);
				++x;
			}
			++y;
		}
		++i;
	}
}
