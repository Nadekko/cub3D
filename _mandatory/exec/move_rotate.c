/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:33:26 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/23 06:03:22 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	rotate_player(t_data *data, double angle)
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

int	ft_rotate(t_data *data)
{
	if (data->move.l == 1)
		rotate_player(data, -ROT_SPEED);
	if (data->move.r == 1)
		rotate_player(data, ROT_SPEED);
	return (0);
}
