#include "../../lib/cub3d.h"

static void	calculate_wall_properties(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpwall_dist = (ray->sidedist_x - ray->deltadist_x);
	else
		ray->perpwall_dist = (ray->sidedist_y - ray->deltadist_y);
	ray->line_height = (int)(HEIGHT / ray->perpwall_dist);
	ray->draw_start = -ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
}

static void	draw_textured_wall(t_main *main, t_ray *ray)
{
	t_image	*texture;
	int		tex_pixel;
	int		img_pixel;

	texture = get_texture(&main->mlx, ray);
	ray->wall_x = main->player_pos->y + ray->perpwall_dist * ray->raydir_y;
	if (ray->side == 1)
		ray->wall_x = main->player_pos->x + ray->perpwall_dist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->texture_x = (int)(ray->wall_x * (double)(texture->width));
	if ((ray->side == 1 && ray->raydir_y < 0) || (ray->side == 0
			&& ray->raydir_x > 0))
		ray->texture_x = texture->width - ray->texture_x - 1;
	ray->textstep = (double)texture->height / ray->line_height;
	ray->textpos = (ray->draw_start - HEIGHT / 2 + ray->line_height / 2)
		* ray->textstep;
	while (ray->draw_start < ray->draw_end)
	{
		tex_pixel = ((((int)ray->textpos & (texture->height - 1))
				* texture->size_line) + ray->texture_x * (texture->bpp / 8)) / 4;
		img_pixel = (ray->draw_start * main->mlx.image.size_line + ray->x
				* (main->mlx.image.bpp / 8)) / 4;
		((unsigned int *)main->mlx.image.addr)[img_pixel]
			= ((unsigned int *)texture->addr)[tex_pixel];
		ray->textpos += ray->textstep;
		ray->draw_start++;
	}
}

void	display(t_main *main)
{
	t_ray	*ray;

	ray = &main->ray;
	draw_background(main);
	ray->x = -1;
	while (++ray->x < WIDTH)
	{
		init_ray(ray, main->player_pos, ray->x);
		set_ray_step(ray, main->player_pos);
		perform_dda(ray, main->map->map);
		calculate_wall_properties(ray);
		draw_textured_wall(main, ray);
	}
	mlx_put_image_to_window(main->mlx.mlx, main->mlx.win,
		main->mlx.image.img, 0, 0);
}