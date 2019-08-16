


#include "img.h"

int		usage_err(char *str)
{
	ft_putstr(str);
	return (0);
}

int		main(int ac, char **av)
{
	t_cord	dim;

//	printf("%d\n", rand());


	if (ac != 5 && ac != 3 && ac != 1)
		return (usage_err("Usage: <x> <y> <point width> <point height>\n"));
	else if (ac == 1)
	{
		dim.x_b = 40;
		dim.y_b = 40;
		dim.b_wid = 3;
		dim.b_hei = 3;
		ft_img(&dim);
	}
	else if (ac == 5)
	{
		dim.x_b = ft_atoi(av[1]);
		dim.y_b = ft_atoi(av[2]);
		dim.b_wid = ft_atoi(av[3]);
		dim.b_hei = ft_atoi(av[4]);
		ft_img(&dim);
	}
	else if (ac == 3)
	{
		dim.x_b = ft_atoi(av[1]);
		dim.y_b = ft_atoi(av[2]);
		dim.b_wid = 3;
		dim.b_hei = 3;
		ft_img(&dim);
	}
	return (0);
}
