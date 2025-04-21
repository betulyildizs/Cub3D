#include "../../lib/cub3d.h"

void	draw_background(t_main *main)
{
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				x;
	int				y;
	int				pixel_index;

	floor_color = rgbtouint(main->textures->f);
	ceiling_color = rgbtouint(main->textures->c);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			pixel_index = (y * main->mlx.image.size_line + x
					* (main->mlx.image.bpp / 8)) / 4;
			if (y < HEIGHT / 2)
				((unsigned int *)main->mlx.image.addr)[pixel_index]
					= ceiling_color;
			else
				((unsigned int *)main->mlx.image.addr)[pixel_index]
					= floor_color;
		}
	}
}

void	init_ray(t_ray *ray, t_positon *player_pos, int x)
{
	ray->camera_x = 2 * x / (double)WIDTH - 1;
	ray->raydir_x = player_pos->dirx + player_pos->planex * ray->camera_x;
	ray->raydir_y = player_pos->diry + player_pos->planey * ray->camera_x;
	ray->map_x = (int)player_pos->x;
	ray->map_y = (int)player_pos->y;
	if (ray->raydir_x == 0)
		ray->deltadist_x = 1e30;
	else
		ray->deltadist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltadist_y = 1e30;
	else
		ray->deltadist_y = fabs(1 / ray->raydir_y);
	ray->hit = 0;
}

void	set_ray_step(t_ray *ray, t_positon *player_pos)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (player_pos->x - ray->map_x) * ray->deltadist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - player_pos->x) * ray->deltadist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (player_pos->y - ray->map_y) * ray->deltadist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - player_pos->y) * ray->deltadist_y;
	}
}

void	perform_dda(t_ray *ray, char **map)
{
	while (map[ray->map_y][ray->map_x] != '1')
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->deltadist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->deltadist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
	}
}
