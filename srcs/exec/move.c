/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:04:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/27 18:12:55 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static int	is_blocked(t_data *data, double x, double y)
{
	int	cell;

	if (x < 0 || y < 0 || x >= data->map->width || y >= data->map->height)
		return (1);
	cell = data->map->map_int[(int)y][(int)x];
	return (cell == 1 || cell == 4 || cell == 5);
}

// checks the 4 corners of a hitbox around the player
static int	is_valid_move(double x, double y, t_data *data)
{
	return (!is_blocked(data, x - PLAYER_MARGIN, y - PLAYER_MARGIN)
		&& !is_blocked(data, x + PLAYER_MARGIN, y - PLAYER_MARGIN)
		&& !is_blocked(data, x - PLAYER_MARGIN, y + PLAYER_MARGIN)
		&& !is_blocked(data, x + PLAYER_MARGIN, y + PLAYER_MARGIN)
		&& !door_blocks(data, x, y));
}

static void	get_new_position(t_data *data, double *new_x, double *new_y,
	double speed)
{
	*new_x = data->player->pos_x;
	*new_y = data->player->pos_y;
	if (data->move.z == 1)
	{
		*new_x += data->raycast->dir_x * speed;
		*new_y += data->raycast->dir_y * speed;
	}
	if (data->move.s == 1)
	{
		*new_x -= data->raycast->dir_x * speed;
		*new_y -= data->raycast->dir_y * speed;
	}
	if (data->move.q == 1)
	{
		*new_x -= data->raycast->plane_x * speed;
		*new_y -= data->raycast->plane_y * speed;
	}
	if (data->move.d == 1)
	{
		*new_x += data->raycast->plane_x * speed;
		*new_y += data->raycast->plane_y * speed;
	}
}

// FPS-independent speed: distance = MOVE_SPEED * elapsed time
int	ft_move(t_data *data)
{
	double	new_x;
	double	new_y;
	long	now;
	double	dt;

	now = get_time_ms();
	if (data->move.last == 0)
		data->move.last = now;
	dt = (now - data->move.last) / 1000.0;
	data->move.last = now;
	if (dt > 0.05)
		dt = 0.05;
	get_new_position(data, &new_x, &new_y, MOVE_SPEED * dt);
	if (is_valid_move(new_x, data->player->pos_y, data))
		data->player->pos_x = new_x;
	if (is_valid_move(data->player->pos_x, new_y, data))
		data->player->pos_y = new_y;
	return (0);
}
