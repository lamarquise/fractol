

	// would need to change the include to use with something else...

#include "img.h"

void	start_car(t_mag *img, t_car *cord)
{
	int		i;
	int		n;

	i = 0;
	n = img->x * img->y;
	if (!(cord = ft_memalloc(sizeof(t_car) * n)))
		return ;
	while (i < n)
	{
		cord[i].x = i % img->x;		// cartesian coords, the unit is Pixels?
		cord[i].y = i / img->x;
		++i;
	}
	img->tab = cord;
}


// do i put all the info in a new struct type or keep it in mlx, or leave in func???

int		lin_interpol(int c1, int c2, float perc)	// standard perc, always left...
{
	int		red;
	int		green;
	int		blue;		// no idea if this will work.....

//	printf("c1 red: %d\n", c1 % 256);
//	printf("c1: %d\n", c1);
/*
	red = (1 - perc) * ((c1 >> 16) & 0xFF) + perc * ((c2 >> 16) & 0xFF);
	green = (1 - perc) * ((c1 >> 8) & 0xFF) + perc * ((c2 >> 8) & 0xFF);
	return (red<<16 | green<<8 | blue);
*/

	red = (1 - perc) * c1 / 65536 + perc * c2 / 65536;
//	printf("perc: %f, c1: %d, c2: %d, red: %d\n", perc, c1 / 65536, c2 / 65536, red);	


	green = (1 - perc) * ((c1 / 256) % 256) + perc * ((c2 / 256) % 256);
	blue = (1 - perc) * (c1 % 256) + perc * (c2 % 256);

	return (red * 65536 + green * 256 + blue);
}

	// or do while for all pixels here ....
	// calls lin_inter 3 times... ca    lled for each point...
int		bilin_interpol(t_mag *og, t_mag *new, int cord)
{		// how to handle edge cases ????
	int		color;
	int		tmp;
	t_car	point;
	t_car	perc;
	int		bot;

	// get coord of new point in og:

	point.x = new->tab[cord].x / new->x * og->x;
	point.y = new->tab[cord].y / new->y * og->y;

	bot = (int)floor(point.x - 0.5);	// x cord of pix in og system

	// from coord get percentage between points
	perc.x = point.x - 0.5 - bot;					//use same perc for 2 pix under?
	perc.y = point.y - 0.5 - floor(point.y - 0.5);

	// interpolate * 3
	// no idea if these ternaires work...
	color = lin_interpol(og->img_data[bot],\
			og->img_data[(bot % og->x == 0) ? bot : bot + 1], perc.x);
	tmp = lin_interpol(og->img_data[(bot + og->x > og->x * og->y) ? bot : bot + og->x],\
			og->img_data[(bot + 1 + og->x > og->x * og->y) ? bot : bot + 1 + og->x], perc.x);
	color = lin_interpol(color, tmp, perc.y);
	return (color);
}


// return an img ???
void	ft_altdraw(t_img *mlx)		// send new img dimentions ???
{
	int		i;
	t_mag	tmp;
	t_car	*new;


			// acting v strange this interpol thing....

	printf("inter test: %d\n", lin_interpol(0x000000, 0x000000, 0.5));

	printf("alt test 1\n");

	tmp.x = mlx->img->x * ((mlx->zoom - 1) / 10);
	tmp.y = mlx->img->y * ((mlx->zoom - 1) / 10);
	printf("alt test 2\n");
	if (!(tmp.img_ptr = mlx_new_image(mlx->ptr, tmp.x, tmp.y)))
		return ;
	if (!(tmp.img_data = (int*)mlx_get_data_addr(tmp.img_ptr,\
		&mlx->bpp, &mlx->s_l, &mlx->endian)))
		return ;
	printf("alt test 3\n");
//	start_car(mlx->img, old);		// should init the tables that convert cartesian to
	start_car(&tmp, new);			// torchle pos for each img
	printf("alt test 4\n");
	i = 0;
	while (i < tmp.x * tmp.y)
	{
		tmp.img_data[i] = bilin_interpol(mlx->img, &tmp, i);
		++i;
	}
	mlx->img = &tmp;
	printf("alt test 5\n");
	// somehow clear old img and replace with new one...
}
