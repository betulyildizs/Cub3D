/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:07:08 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/21 15:32:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void	free_copy_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map || !map->copy_map)
		return ;
	while (map->copy_map[i])
	{
		free(map->copy_map[i]);
		i++;
	}
	free(map->copy_map);
	map->copy_map = NULL;
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	if (map->map)
	{
		while (map->map[i])
		{
			free(map->map[i]);
			i++;
		}
		free(map->map);
		map->map = NULL;
	}
	free(map);
}

static void	free_texture_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_textures(t_textures *textures)
{
	if (!textures)
		return ;
	if (textures->no)
		free(textures->no);
	if (textures->so)
		free(textures->so);
	if (textures->we)
		free(textures->we);
	if (textures->ea)
		free(textures->ea);
	free_texture_array(textures->c);
	free_texture_array(textures->f);
	if (textures->keys)
		free(textures->keys);
	if (textures->textures)
		free(textures->textures);
	free(textures);
}

void	free_all(t_main *main)
{
	if (!main)
		return ;
	if (main->textures)
		free_textures(main->textures);
	if (main->map)
		free_map(main->map);
	if (main->player_pos)
		free(main->player_pos);
	free(main);
}
