/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 17:37:34 by halozdem          #+#    #+#             */
/*   Updated: 2025/04/21 17:41:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib/cub3d.h"

void    display(t_main *main);

unsigned long long get_timestamp(void)
{
	struct timeval	time;
	
	if (gettimeofday(&time, NULL) == -1)
	return (0);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	key_press(int keycode, void *main)
{
	t_keys	*keys;

	keys = &((t_main *)main)->keys;
	if (keycode == KEY_W)
		keys->w_pressed = 1;
	else if (keycode == KEY_S)
		keys->s_pressed = 1;
	else if (keycode == KEY_A)
		keys->a_pressed = 1;
	else if (keycode == KEY_D)
		keys->d_pressed = 1;
	else if (keycode == KEY_LEFT)
		keys->left_pressed = 1;
	else if (keycode == KEY_RIGHT)
		keys->right_pressed = 1;
	else if (keycode == KEY_ESC)
		keys->esc_pressed = 1;
}

int	key_release(int keycode, void *main)
{
	t_keys	*keys;

	keys = &((t_main *)main)->keys;
	if (keycode == KEY_W)
		keys->w_pressed = 0;
	else if (keycode == KEY_S)
		keys->s_pressed = 0;
	else if (keycode == KEY_A)
		keys->a_pressed = 0;
	else if (keycode == KEY_D)
		keys->d_pressed = 0;
	else if (keycode == KEY_LEFT)
		keys->left_pressed = 0;
	else if (keycode == KEY_RIGHT)
		keys->right_pressed = 0;
	else if (keycode == KEY_ESC)
		keys->esc_pressed = 0;
}

int	rgbtouint(char **colors)
{
	return (ft_atoi(colors[0]) * 65536 + ft_atoi(colors[1]) * 256 + ft_atoi(colors[2]));
}

t_image	*get_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0 && ray->raydir_x > 0)
		return (&mlx->ea_text);
	else if (ray->side == 0 && ray->raydir_x < 0)
		return (&mlx->we_text);
	else if (ray->side == 1 && ray->raydir_y > 0)
		return (&mlx->no_text);
	else
		return (&mlx->so_text);
}
