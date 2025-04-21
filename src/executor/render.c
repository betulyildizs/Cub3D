#include "../../lib/cub3d.h"

void	move_forward(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y + (main->player_pos->diry * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y += main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x + (main->player_pos->dirx * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x += main->player_pos->dirx * speed;
}

void	move_backward(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y - (main->player_pos->diry * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y -= main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x - (main->player_pos->dirx * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x -= main->player_pos->dirx * speed;
}

void	move_right(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x - (main->player_pos->diry * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x -= main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y + (main->player_pos->dirx * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y += main->player_pos->dirx * speed;
}

void	move_left(t_main *main, const double delta_time)
{
	double			speed;
	int				new_y;
	int				new_x;

	speed = delta_time * MOVE_SPEED;
	new_y = (int)(main->player_pos->y);
	new_x = (int)(main->player_pos->x + (main->player_pos->diry * speed));
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->x += main->player_pos->diry * speed;
	new_y = (int)(main->player_pos->y - (main->player_pos->dirx * speed));
	new_x = (int)(main->player_pos->x);
	if (main->map->map[new_y][new_x] != '1')
		main->player_pos->y -= main->player_pos->dirx * speed;
}

int	render(void *param)
{
	t_main					*main;
	unsigned long long		current;
	double					delta_time;
	double					angle;

	main = param;
	current = get_timestamp();
	delta_time = (current - main->mlx.last_tick) / 1000.0;
	main->mlx.last_tick = current;
	angle = delta_time * 180 * ROTATION_SPEED * 3.14 / 180.0;
	if_condition(main, angle, delta_time);
	if (main->keys.esc_pressed)
	{
		free_all(main);
		mlx_destroy_window(main->mlx.mlx, main->mlx.win);
		exit(1);
	}
	display(main);
	return (1);
}
