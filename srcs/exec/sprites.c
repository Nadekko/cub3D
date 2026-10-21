/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:48 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:21:52 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"
#include <X11/keysym.h>

int	animation_paws(t_data *data)
{
	long	now;

	if (!data->anim_running)
		return (0);
	now = get_time_ms();
	if (now - data->anim_last >= PAW_FRAME_MS)
	{
		data->anim_frame++;
		data->anim_last = now;
	}
	if (data->anim_frame > 9)
	{
		data->anim_running = 0;
		data->anim_frame = 0;
	}
	return (0);
}

// closest door in front of the player, 2 cells max
t_doors	*door_in_front(t_data *data)
{
	t_doors	*best;
	double	d[3];
	double	best_dist;
	int		i;

	best = NULL;
	best_dist = 4.0;
	i = -1;
	while (data->doors && ++i < data->doors->nb)
	{
		d[0] = data->doors[i].x + 0.5 - data->player->pos_x;
		d[1] = data->doors[i].y + 0.5 - data->player->pos_y;
		d[2] = d[0] * d[0] + d[1] * d[1];
		if (d[2] <= best_dist
			&& d[0] * data->raycast->dir_x + d[1] * data->raycast->dir_y > 0)
		{
			best_dist = d[2];
			best = &data->doors[i];
		}
	}
	return (best);
}

// click: opens a closed door, closes an open one
// (unless the player is inside it, otherwise they would get stuck)
int	is_near_player(t_data *data)
{
	t_doors	*door;

	door = door_in_front(data);
	if (!door)
		return (0);
	if (door->state == D_CLOSED)
		set_door_state(data, door, D_OPENING);
	else if (door->state == D_OPEN && !player_in_door(data, door))
		set_door_state(data, door, D_CLOSING);
	return (1);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		is_near_player(data);
		data->anim_frame = 1;
		data->anim_running = 1;
		data->anim_last = get_time_ms();
	}
	if (button == 4 || button == 5)
		map_zoom(data, button == 4);
	return (0);
}
