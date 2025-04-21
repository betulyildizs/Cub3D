/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 16:50:21 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/22 00:44:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

static char	check_xpm_extension(char *path)
{
	int	len;

	len = ft_strlen(path);
	if (len < 4)
		return (EXIT_FAILURE);
	if (path[len - 1] != 'm' || path[len - 2] != 'p'
		|| path[len - 3] != 'x' || path[len - 4] != '.')
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	check_image(t_textures *textures)
{
	if (!textures->no || !textures->so || !textures->we
		|| !textures->ea || !textures->c || !textures->f)
	{
		printf("Error: Invalid map.\n");
		return (EXIT_FAILURE);
	}
	if (check_xpm_extension(textures->no) == EXIT_FAILURE
		|| check_xpm_extension(textures->so) == EXIT_FAILURE
		|| check_xpm_extension(textures->we) == EXIT_FAILURE
		|| check_xpm_extension(textures->ea) == EXIT_FAILURE)
	{
		printf("Error: Invalid xpm file.\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static char	check_texture_file(char *filename)
{
	int		fd;
	char	buffer[1];
	ssize_t	bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Couldn't open texture file");
		return (EXIT_FAILURE);
	}
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read <= 0)
	{
		printf("Error: Empty texture file: \"%s\"\n", filename);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

char	is_any_texture_file_empty(t_textures *tex)
{
	if (check_texture_file(tex->no) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_texture_file(tex->so) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_texture_file(tex->we) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (check_texture_file(tex->ea) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

char	check_color_value(char *color_str)
{
	int		temp_d;
	char	*temp_s;

	temp_d = ft_atoi(color_str);
	temp_s = ft_itoa(temp_d);
	if (ft_strncmp(color_str, temp_s, ft_strlen(temp_s))
		|| (temp_d < 0 || temp_d >= 255))
	{
		free(temp_s);
		return (EXIT_FAILURE);
	}
	free(temp_s);
	temp_s = NULL;
	return (EXIT_SUCCESS);
}
