/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:25:45 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/22 00:35:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

char	get_map_size(t_main *main, int *fd, const char *file_name)
{
	char	*line;
	char	*line2;
	int		i;
	bool	error;
	char	*str;

	error = false;
	i = 1;
	line = get_next_line(*fd);
	str = ft_strtrim(line, " ");
	while (line && *str == '\n')
	{
		free (str);
		if (check_map_error(main, line, &error))
			return (free(line), EXIT_FAILURE);
		free(line);
		line = get_next_line(*fd);
		str = ft_strtrim(line, " ");
	}
	free(str);
	if (error)
		return (free(line), EXIT_FAILURE);
	while (line)
	{
		process_map_line(main, line, &i);
		free(line);
		line = get_next_line(*fd);
	}
	main->map->map_max_y = i;
	return ((close(*fd)), EXIT_SUCCESS);
}

int	fill_map_struct(t_main *main, int *fd, const char *file_name)
{
	char	*line;
	int		i;
	int		j;

	*fd = open(file_name, O_RDWR);
	if (*fd < 0 || init_map(main->map) == EXIT_FAILURE)
		return (close(*fd), EXIT_FAILURE);
	line = get_next_line(*fd);
	skip_identifiers(*fd, &line);
	i = 0;
	while (line && i < main->map->map_max_y)
	{
		if (!ft_find_in_str(line, "10NSWE\n "))
			break ;
		j = -1;
		while (line[++j] && line[j] != '\n')
			main->map->map[i + 1][j + 1] = line[j];
		free(line);
		line = get_next_line(*fd);
		i++;
	}
	if (line)
		free(line);
	return (close(*fd), EXIT_SUCCESS);
}
