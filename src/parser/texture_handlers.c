/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 19:26:48 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/21 15:12:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

static int	handle_texture(t_line_parse *p, char *prefix, int idx)
{
	char	*content;

	if (!ft_strncmp(p->line, prefix, 3) && !p->textures->textures[idx])
	{
		char	*str;

		str = ft_strdup(p->line + p->index + 3);
		p->textures->textures[idx] = 1;
		content = ft_strtrim(str, " \n");
		if (idx == 0)
			p->textures->no = content;
		else if (idx == 1)
			p->textures->so = content;
		else if (idx == 2)
			p->textures->we = content;
		else if (idx == 3)
			p->textures->ea = content;
		free(str);
		return (1);
	}
	return (0);
}

static int	handle_color(t_line_parse *p, char *prefix, int idx)
{
	if (!ft_strncmp(p->line, prefix, 2) && !p->textures->textures[idx]
		&& count_char(p->line, ',') == 2)
	{
		p->textures->textures[idx] = 1;
		if (idx == 4)
			p->textures->c = ft_split(p->line + p->index + 2, ',');
		else if (idx == 5)
			p->textures->f = ft_split(p->line + p->index + 2, ',');
		return (1);
	}
	return (0);
}

int	process_texture_lines(t_line_parse *p)
{
	if (handle_texture(p, "NO ", 0))
		return (1);
	if (handle_texture(p, "SO ", 1))
		return (1);
	if (handle_texture(p, "WE ", 2))
		return (1);
	if (handle_texture(p, "EA ", 3))
		return (1);
	if (handle_color(p, "C ", 4))
		return (1);
	if (handle_color(p, "F ", 5))
		return (1);
	return (0);
}
