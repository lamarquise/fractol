

	// would need to change the include to use with something else...

#include "img.h"

	// fairly certain this shit is useless or redundant or both
/*
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
*/

	// seems good but need to test

int		lin_interpol(int c1, int c2, double perc)	// standard perc, always left...
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


	// could put all the math in the ret, but more confusing so...

	return (red * 65536 + green * 256 + blue);
}

/*
int		bilin_interpol(t_mag *og, t_mag *new, int cord)
{
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
*/

	// seems good but need to test

int		bilin_interpol(t_mag *og, int pix_start, double perc_x, double perc_y)
{
	int		color;

	if ((pix_start + 1) % og->x == 1)	// case B or D
	{
		if ((pix_start + og->x * 2) / og->x > og->y)	// case D

			return (og->img_data[pix_start]);
		else			// case B
			return (lin_interpol(og->img_data[pix_start], og->img_data[pix_start + og->x], perc_y));
	}
	else if ((pix_start + og->x * 2) / og->x > og->y)	// case C
		return (lin_interpol(og->img_data[pix_start], og->img_data[pix_start + 1], perc_x));

	// case A
	return (lin_interpol(lin_interpol(og->img_data[pix_start], og->img_data[pix_start + 1], perc_x),\
			lin_interpol(og->img_data[pix_start + og->x], og->img_data[pix_start + og->x + 1], perc_x), perc_y));
}

// return an img ???
void	ft_altdraw(t_img *mlx)		// send new img dimentions ???
{
	int		i;
	t_mag	tmp;
//	t_car	*new;
	double	x;
	double	y;


			// acting v strange this interpol thing....

	printf("inter test: %d\n", lin_interpol(0x000000, 0x000000, 0.5));

	printf("alt test 1\n");

//	printf("imgx %d, y %d\n", mlx->img->x, mlx->img->y);

	// now have correct numbers thanks to double cast
	tmp.x = mlx->img->x * (1 + ((double)mlx->zoom - 1) / 10);
	tmp.y = mlx->img->y * (1 + ((double)mlx->zoom - 1) / 10);
	tmp.last_p = tmp.x * tmp.y;

//	printf("wid: %d, hei: %d\n", tmp.x, tmp.y);


	printf("alt test 2\n");

	if (!(tmp.img_ptr = mlx_new_image(mlx->ptr, tmp.x, tmp.y)))
		return ;
//	if (!(
	tmp.img_data = (int*)mlx_get_data_addr(tmp.img_ptr,\
		&mlx->bpp, &mlx->s_l, &mlx->endian); //))
//		return ;
	
	printf("alt test 3\n");
//	start_car(mlx->img, old);		// should init the tables that convert cartesian to
//	start_car(&tmp, new);			// torch pos for each img
	printf("alt test 4\n");
	i = 0;
	while (i < tmp.last_p)
	{

		// better, send old img, pos in img, ratios x and y, return color, top left pixel

		// x in new_img = i % tmp.x;
		// y in new_img = i / tmp.x;


//		x = i % tmp.x;
//		y = i / tmp.x;

		// mlx->img->x / tmp.x * x = new x in old 
		// mlx->img->y / tmp.y * y = new y in old

		x = mlx->img->x / tmp.x * (i % tmp.x);		// new x pos in old img
		y = mlx->img->y / tmp.y * (i / tmp.x);

		// floor(new x in old - 0.5) + floor(new y in old - 0.5) * mlx->img->x;	== top left pix in old
		// top left = (floor(x - 0.5) + floor(y - 0.5) * mlx->img->x);


		// percentage x = floor(new x in old - 0.5)	// wait is it ???
		// percentage y = floor(new y in old - 0.5)
		// perc_x = (x - 0.5) - floor(x - 0.5);
		// perc_y = (y - 0.5) - floor(y - 0.5);
		
//		perc_x = floor(mlx->img->x / tmp.x * (i % tmp.x) - 0.5);		
//		perc_y = floor(mlx->img->y / tmp.y * (i / tmp.x) - 0.5);


		//new one:
/*
		tmp.img_data[i] = bilin_interpol(mlx->img, floor(x - 0.5) +\
							floor(y - 0.5) * mlx->img->x,\
							(x - 0.5) - floor(x - 0.5), (y - 0.5) -\
							floor(y - 0.5));
*/

//		tmp.img_data[i] = bilin_interpol(mlx->img, &tmp, i);
		tmp.img_data[i] = 0xF11FFF;
//		printf("color: %d\n", tmp.img_data[i]);
		++i;
	}
	mlx_destroy_image(mlx->ptr, mlx->img->img_ptr);

	mlx->img = &tmp;
	
	mlx_clear_window(mlx->ptr, mlx->win_ptr);
	mlx_put_image_to_window(mlx->ptr, mlx->win_ptr,\
		mlx->img->img_ptr, 50, 50);

	printf("alt test 5\n");

	// seems like all that needs to be cleared gets cleard, have to test...


}

