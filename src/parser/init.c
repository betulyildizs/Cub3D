/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:09 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/22 01:13:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

t_textures	*init_textures_struct(void)
{
	t_textures	*textures;
	int			i;

	textures = (t_textures *)malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	textures->no = NULL;
	textures->so = NULL;
	textures->we = NULL;
	textures->ea = NULL;
	textures->c = NULL;
	textures->f = NULL;
	textures->textures = malloc(sizeof(int) * 6);
	if (!textures->textures)
	{
		free(textures);
		return (NULL);
	}
	i = -1;
	while (++i < 6)
		textures->textures[i] = 0;
	textures->keys = ft_strdup("NSWEACF");
	if (!textures->keys)
		return (free(textures->textures), free(textures), NULL);
	return (textures);
}

t_map	*init_map_struct(void)
{
	t_map	*map;

	map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!map)
		return (NULL);
	map->map_max_x = 0;
	map->map_max_y = 0;
	map->map = NULL;
	return (map);
}

void	init_keys(t_keys *keys)
{
	if (keys == NULL)
		return ;
	keys->w_pressed = 0;
	keys->s_pressed = 0;
	keys->a_pressed = 0;
	keys->d_pressed = 0;
	keys->left_pressed = 0;
	keys->right_pressed = 0;
	keys->esc_pressed = 0;
}

t_main	*init_all(char *map_name)
{
	t_main	*main;

	main = malloc(sizeof(t_main));
	if (!main)
		return (NULL);
	main->player_pos = (t_positon *)malloc(sizeof(t_positon));
	if (!main->player_pos)
		return (free(main), NULL);
	main->player_pos->x = -1;
	main->player_pos->y = -1;
	main->player_pos->count = 0;
	init_keys(&main->keys);
	main->textures = init_textures_struct();
	if (!main->textures)
		return (free(main->player_pos), free(main), NULL);
	main->map = init_map_struct();
	if (!main->map)
	{
		free(main->textures->textures);
		free(main->textures->keys);
		free(main->textures);
		free(main->player_pos);
		free(main);
		return (NULL);
	}

	return (main);
}
