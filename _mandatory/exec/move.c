/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 19:04:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 19:24:21 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 0;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 0;
	if (keycode == KEY_S)
		data->move.s = 0;
	if (keycode == KEY_D)
		data->move.d = 0;
	if (keycode == LEFT)
		data->move.l = 0;
	if (keycode == RIGHT)
		data->move.r = 0;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
		ft_free_exit(data);
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 1;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 1;
	if (keycode == KEY_S)
		data->move.s = 1;
	if (keycode == KEY_D)
		data->move.d = 1;
	if (keycode == LEFT)
		data->move.l = 1;
	if (keycode == RIGHT)
		data->move.r = 1;
	return (0);
}

static int	is_valid_move(double new_x, double new_y, t_data *data)
{
	int	map_x;
	int	map_y;

	if (new_x < 0 || new_x >= data->map->width || new_y < 0
		|| new_y >= data->map->height)
		return (0);
	map_x = (int)new_x;
	map_y = (int)new_y;
	if (data->map->map_int[map_y][map_x] == 1 ||
		data->map->map_int[(int)(new_y + 0.1)][map_x] == 1 ||
		data->map->map_int[map_y][(int)(new_x + 0.1)] == 1)
		return (0);
	return (1);
}

static void	get_new_position(t_data *data, double *new_x, double *new_y)
{
	*new_x = data->player->pos_x;
	*new_y = data->player->pos_y;
	if (data->move.z == 1)
	{
		*new_x += data->raycast->dir_x * MOVE_SPEED;
		*new_y += data->raycast->dir_y * MOVE_SPEED;
	}
	if (data->move.s == 1)
	{
		*new_x -= data->raycast->dir_x * MOVE_SPEED;
		*new_y -= data->raycast->dir_y * MOVE_SPEED;
	}
	if (data->move.q == 1)
	{
		*new_x -= data->raycast->plane_x * MOVE_SPEED;
		*new_y -= data->raycast->plane_y * MOVE_SPEED;
	}
	if (data->move.d == 1)
	{
		*new_x += data->raycast->plane_x * MOVE_SPEED;
		*new_y += data->raycast->plane_y * MOVE_SPEED;
	}
}

int	ft_move(t_data *data)
{
	double	new_x;
	double	new_y;

	get_new_position(data, &new_x, &new_y);
	if (is_valid_move(new_x, data->player->pos_y, data))
		data->player->pos_x = new_x;
	if (is_valid_move(data->player->pos_x, new_y, data))
		data->player->pos_y = new_y;
	return (0);
}
