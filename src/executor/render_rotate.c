#include "../../lib/cub3d.h"

void    if_condition(t_main *main, const double angle, const double delta_time)
{
	if (main == NULL)
		return ;
    if (main->keys.w_pressed)
		move_forward(main, delta_time);
	if (main->keys.s_pressed)
		move_backward(main, delta_time);
	if (main->keys.a_pressed)
		move_left(main, delta_time);
	if (main->keys.d_pressed)
		move_right(main, delta_time);
	if (main->keys.left_pressed)
		rotate_left(main, angle);
	if (main->keys.right_pressed)
		rotate_right(main, angle);
}

void	rotate_right(t_main *main, const double angle)
{
	double	olddirx;
	double	oldplanex;

	olddirx = main->player_pos->dirx;
	oldplanex = main->player_pos->planex;
	main->player_pos->dirx = olddirx * cos(angle) \
		- main->player_pos->diry * sin(angle);
	main->player_pos->diry = olddirx * sin(angle) \
		+ main->player_pos->diry * cos(angle);
	main->player_pos->planex = oldplanex * cos(angle) \
		- main->player_pos->planey * sin(angle);
	main->player_pos->planey = oldplanex * sin(angle) \
		+ main->player_pos->planey * cos(angle);
}

void	rotate_left(t_main *main, const double angle)
{
	double	olddirx;
	double	oldplanex;

	olddirx = main->player_pos->dirx;
	oldplanex = main->player_pos->planex;
	main->player_pos->dirx = olddirx * cos(-angle) \
		- main->player_pos->diry * sin(-angle);
	main->player_pos->diry = olddirx * sin(-angle) \
		+ main->player_pos->diry * cos(-angle);
	main->player_pos->planex = oldplanex * cos(-angle) \
		- main->player_pos->planey * sin(-angle);
	main->player_pos->planey = oldplanex * sin(-angle) \
		+ main->player_pos->planey * cos(-angle);
}
