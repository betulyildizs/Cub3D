/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 16:07:08 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/22 01:07:16 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void clean_mlx(t_mlx *mlx)
{
    if (!mlx)
        return;
    if (mlx->image.img) 
        mlx_destroy_image(mlx->mlx, mlx->image.img);
    if (mlx->so_text.img)
        mlx_destroy_image(mlx->mlx, mlx->so_text.img);
    if (mlx->we_text.img)
        mlx_destroy_image(mlx->mlx, mlx->we_text.img);
    if (mlx->no_text.img)
        mlx_destroy_image(mlx->mlx, mlx->no_text.img);
    if (mlx->ea_text.img)
        mlx_destroy_image(mlx->mlx, mlx->ea_text.img);
}

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
		return;
	
	if (textures->no != NULL)
		free(textures->no);
	if (textures->so != NULL)
		free(textures->so);
	if (textures->we != NULL)
		free(textures->we);
	if (textures->ea != NULL)
		free(textures->ea);

	if (textures->c != NULL)
		free_texture_array(textures->c);
	if (textures->f != NULL)
		free_texture_array(textures->f);

	if (textures->keys != NULL)
		free(textures->keys);
	if (textures->textures != NULL)
		free(textures->textures);

	free(textures);
}

void free_all(t_main *main)
{
    if (!main)
        return;

    // Harita ve diğer verilerin serbest bırakılması
    if (main->map)
        free_map(main->map);
    
    if (main->textures)
        free_textures(main->textures);

    if (main->player_pos)
        free(main->player_pos);

    // mlx kaynaklarının temizlenmesi
    clean_mlx(&main->mlx);

    // mlx.mlx'yi temizlemeden önce free yapma
    if (main->mlx.mlx)
    {
        mlx_destroy_display(main->mlx.mlx);  // Önce display'i yok et
        free(main->mlx.mlx);  // Ardından bellek alanını serbest bırak
    }

    // Son olarak ana yapı bellekten kaldırılır
    free(main);
}
