/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:32 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

t_doors	*get_door(t_data *data, int x, int y)
{
	int	i;

	if (!data->doors)
		return (NULL);
	i = 0;
	while (i < data->doors->nb)
	{
		if ((int)data->doors[i].x == x && (int)data->doors[i].y == y)
			return (&data->doors[i]);
		i++;
	}
	return (NULL);
}

// closed -> DOOR, animating -> DOOR + 1..3, open -> DOOR + 4
void	set_door_texture(t_data *data)
{
	t_doors	*door;

	data->raycast->texture = DOOR;
	door = get_door(data, data->raycast->map_x, data->raycast->map_y);
	if (door)
		data->raycast->texture = DOOR + door->anim_frame;
}

// cell: 4 = closed, 5 = animating (blocks everything), 6 = open
void	set_door_state(t_data *data, t_doors *door, int state)
{
	int	cell;

	door->state = state;
	door->last = get_time_ms();
	cell = 5;
	if (state == D_OPENING)
		door->anim_frame = 1;
	else if (state == D_CLOSING)
		door->anim_frame = 3;
	else if (state == D_OPEN)
	{
		door->anim_frame = 4;
		cell = 6;
	}
	else
	{
		door->anim_frame = 0;
		cell = 4;
	}
	data->map->map_int[(int)door->y][(int)door->x] = cell;
}

static void	step_door(t_data *data, t_doors *door)
{
	door->last = get_time_ms();
	if (door->state == D_OPENING)
	{
		door->anim_frame++;
		if (door->anim_frame >= 4)
			set_door_state(data, door, D_OPEN);
	}
	else
	{
		door->anim_frame--;
		if (door->anim_frame <= 0)
			set_door_state(data, door, D_CLOSED);
	}
}

int	animation_doors(t_data *data)
{
	int		i;
	long	now;
	t_doors	*door;

	if (!data->doors)
		return (0);
	now = get_time_ms();
	i = 0;
	while (i < data->doors->nb)
	{
		door = &data->doors[i];
		if ((door->state == D_OPENING || door->state == D_CLOSING)
			&& now - door->last >= DOOR_FRAME_MS)
			step_door(data, door);
		i++;
	}
	return (0);
}
