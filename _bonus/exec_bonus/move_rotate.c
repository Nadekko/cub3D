/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 19:26:03 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/23 05:36:10 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

void	rotate_player(t_data *data, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = data->raycast->dir_x;
	old_plane_x = data->raycast->plane_x;
	data->raycast->dir_x = data->raycast->dir_x * cos(angle)
		- data->raycast->dir_y * sin(angle);
	data->raycast->dir_y = old_dir_x * sin(angle)
		+ data->raycast->dir_y * cos(angle);
	data->raycast->plane_x = data->raycast->plane_x * cos(angle)
		- data->raycast->plane_y * sin(angle);
	data->raycast->plane_y = old_plane_x * sin(angle)
		+ data->raycast->plane_y * cos(angle);
}

int	mouse_move(int x, int y, t_data *data)
{
	int		last_x;

	(void)y;
	last_x = WIDTH / 2;
	if (x > last_x)
		rotate_player(data, ROT_SPEED);
	else if (x < last_x)
		rotate_player(data, -ROT_SPEED);
	last_x = WIDTH / 2;
	mlx_mouse_move(data->mlx->mlx, data->mlx->win, WIDTH / 2, HEIGHT / 2);
	return (0);
}
