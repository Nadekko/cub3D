/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:39:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:20:49 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// fog: cells never crossed by a ray stay hidden
static unsigned int	cell_color(t_data *data, double mx, double my)
{
	int		cell;
	double	across;

	if (mx < 0 || my < 0 || mx >= data->map->width || my >= data->map->height
		|| !data->map->seen[(int)my * data->map->width + (int)mx])
		return (MINI_FOG);
	cell = data->map->map_int[(int)my][(int)mx];
	if (cell == 1)
		return (MINI_WALL);
	if (cell == 4)
		return (MINI_DOOR_CLOSED);
	if (cell == 5)
		return (MINI_DOOR_MOVING);
	if (cell == 6)
	{
		across = my - (int)my;
		if (door_along_y(data, (int)mx, (int)my))
			across = mx - (int)mx;
		if (across < 1.0 / 3.0 || across > 2.0 / 3.0)
			return (MINI_DOOR_OPEN);
	}
	return (MINI_FLOOR);
}

// projects (vx, vy) (relative to the player) into camera space, like a sprite:
// visible if in front, inside the screen and closer than the wall of its column
static int	in_view(t_data *data, double vx, double vy)
{
	t_raycast	*r;
	double		inv;
	double		tx;
	double		ty;
	int			col;

	r = data->raycast;
	inv = 1.0 / (r->plane_x * r->dir_y - r->dir_x * r->plane_y);
	tx = inv * (r->dir_y * vx - r->dir_x * vy);
	ty = inv * (-r->plane_y * vx + r->plane_x * vy);
	if (ty <= 0.0)
		return (0);
	col = (int)(WIDTH / 2 * (1.0 + tx / ty));
	if (col < 0 || col >= WIDTH)
		return (0);
	return (ty < r->zbuf[col]);
}

// screen offset (in pixels, from the view center) -> world position
// rotate: the player direction points up
static void	world_pos(t_data *data, t_view *v, int xy[2], double w[2])
{
	double	fx;
	double	fy;

	fx = xy[0] / v->scale;
	fy = xy[1] / v->scale;
	if (!v->rotate)
	{
		w[0] = v->wx + fx;
		w[1] = v->wy + fy;
		return ;
	}
	w[0] = v->wx - fx * data->raycast->dir_y - fy * data->raycast->dir_x;
	w[1] = v->wy + fx * data->raycast->dir_x - fy * data->raycast->dir_y;
}

// color of one map pixel, shared by the minimap and the big map
unsigned int	map_pixel(t_data *data, t_view *v, int x, int y)
{
	int				xy[2];
	double			w[2];
	double			d[2];
	unsigned int	color;

	xy[0] = x;
	xy[1] = y;
	world_pos(data, v, xy, w);
	d[0] = w[0] - data->player->pos_x;
	d[1] = w[1] - data->player->pos_y;
	if ((d[0] * d[0] + d[1] * d[1]) * v->scale * v->scale
		<= MINI_PLAYER * MINI_PLAYER)
		return (MINI_PLAYER_COLOR);
	color = cell_color(data, w[0], w[1]);
	if (color != MINI_FOG && in_view(data, d[0], d[1]))
		color = mix(color, MINI_FOV_COLOR);
	return (color);
}

// 3/4 of a + 1/4 of b, per channel
unsigned int	mix(unsigned int a, unsigned int b)
{
	return (((a >> 2) & 0x3F3F3F) * 3 + ((b >> 2) & 0x3F3F3F));
}
