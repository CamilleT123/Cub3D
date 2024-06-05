#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub	cub;

	(void)ac;
	init_cub(av[1], &cub);
	ft_putar(cub.scene.map);
	printf("north: %s\n", cub.scene.north);
	printf("south: %s\n", cub.scene.south);
	printf("east: %s\n", cub.scene.east);
	printf("west: %s\n", cub.scene.west);
	printf("floor: %d\n", cub.scene.f_color);
	printf("ceiling: %d\n", cub.scene.c_color);
	return (0);
}
