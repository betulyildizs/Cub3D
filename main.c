/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 17:42:14 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/21 19:11:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib/cub3d.h"

static int	handle_textures(t_main *main, char *path)
{
	int	fd;

	if (!main->textures)
		return (1);
	fd = fill_textures_struct(main->textures, path);
	if (fd == -1)
	{
		printf("Error: Invalid map.\n");
		free_all(main);
		return (1);
	}
	if (check_image(main->textures) || check_color(main->textures)
		|| is_any_texture_file_empty(main->textures))
	{
		free_all(main);
		return (1);
	}
	return (fd);
}

static int	handle_map(t_main *main, int *fd, char *path)
{
	if (get_map_size(main, fd, path))
	{
		free_all(main);
		printf("Error: Invalid map.\n");
		return (1);
	}
	if (fill_map_struct(main, fd, path))
	{
		free_all(main);
		return (1);
	}
	flood_fill(main);
	flood_fill_2(main);
	if (!get_player_pos(main))
	{
		printf("Error: Invalid map.\n");
		free_all(main);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_main	*main;
	int		fd;

	if (argc != 2)
		return (0);
	main = init_all(argv[1]);
	fd = handle_textures(main, argv[1]);
	if (fd == 1)
		return (0);
	if (handle_map(main, &fd, argv[1]))
		return (0);
	main->mlx.last_tick = 0;
	if (!init_mlx(main, &main->mlx))// bunun içinde freele ve derle
	{
		free_all(main);
		return (0);
	} 
	free_all(main);
	return (0);
}
