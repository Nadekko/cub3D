/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_collision.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:32 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// walls on the left and right: the door is crossed along the y axis
int	door_along_y(t_data *data, int cx, int cy)
{
	if (cx <= 0 || cx >= data->map->width - 1)
		return (0);
	return (data->map->map_int[cy][cx - 1] == 1
		&& data->map->map_int[cy][cx + 1] == 1);
}

// open door (6): the panels fill 0..1/3 and 2/3..1 of the cell,
// like in door4.xpm, only the middle gap is free
static int	panel_hit(t_data *data, double px, double py, int along_y)
{
	int		cx;
	int		cy;
	double	across;

	cx = (int)px;
	cy = (int)py;
	if (data->map->map_int[cy][cx] != 6
		|| door_along_y(data, cx, cy) != along_y)
		return (0);
	if (along_y)
		across = px - cx;
	else
		across = py - cy;
	return (across < 1.0 / 3.0 || across > 2.0 / 3.0);
}

// the center must be in the gap; in front of the door we also test the point
// PLAYER_MARGIN away along the passage axis (no sticking to the panels)
int	door_blocks(t_data *data, double x, double y)
{
	return (panel_hit(data, x, y, 0) || panel_hit(data, x, y, 1)
		|| panel_hit(data, x, y - PLAYER_MARGIN, 1)
		|| panel_hit(data, x, y + PLAYER_MARGIN, 1)
		|| panel_hit(data, x - PLAYER_MARGIN, y, 0)
		|| panel_hit(data, x + PLAYER_MARGIN, y, 0));
}

int	player_in_door(t_data *data, t_doors *door)
{
	double	px;
	double	py;

	px = data->player->pos_x;
	py = data->player->pos_y;
	return (px + PLAYER_MARGIN > door->x && px - PLAYER_MARGIN < door->x + 1
		&& py + PLAYER_MARGIN > door->y && py - PLAYER_MARGIN < door->y + 1);
}
