/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:32 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	dda_step(t_raycast *r)
{
	if (r->side_x < r->side_y)
	{
		r->side_x += r->delta_x;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_y += r->delta_y;
		r->map_y += r->step_y;
		r->side = 1;
	}
}

// an animating (5) or open (6) door does not stop the ray:
// remember the first one crossed and keep going until a real wall
static void	algo_dda(t_data *data)
{
	t_raycast	*r;
	int			cell;
	int			max_iter;

	r = data->raycast;
	r->door_hit = 0;
	max_iter = 0;
	while (max_iter++ < 1000)
	{
		dda_step(r);
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= data->map->width
			|| r->map_y >= data->map->height)
			return ;
		data->map->seen[r->map_y * data->map->width + r->map_x] = 1;
		cell = data->map->map_int[r->map_y][r->map_x];
		if (cell == 1 || cell == 4)
			return ;
		if ((cell == 5 || cell == 6) && !r->door_hit)
		{
			r->door_hit = 1;
			r->door_map_x = r->map_x;
			r->door_map_y = r->map_y;
			r->door_side = r->side;
		}
	}
}

static void	compute_wall_dist(t_data *data)
{
	if (data->raycast->side == 0)
		data->raycast->wall_dist = (data->raycast->map_x - data->player->pos_x
				+ (1 - data->raycast->step_x) / 2) / data->raycast->ray_x;
	else
		data->raycast->wall_dist = (data->raycast->map_y - data->player->pos_y
				+ (1 - data->raycast->step_y) / 2) / data->raycast->ray_y;
	if (data->raycast->wall_dist < 0.01)
		data->raycast->wall_dist = 0.01;
	data->raycast->line_height = (int)(HEIGHT / data->raycast->wall_dist);
	column_light(data);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT;
	if (data->raycast->draw_end < data->raycast->draw_start)
		data->raycast->draw_end = data->raycast->draw_start;
}

// draws the door over the wall already drawn (skips transparent pixels)
static void	draw_door_layer(t_data *data, int i)
{
	t_raycast	*r;

	r = data->raycast;
	if (!r->door_hit)
		return ;
	r->map_x = r->door_map_x;
	r->map_y = r->door_map_y;
	r->side = r->door_side;
	compute_wall_dist(data);
	put_texture(data, i);
}

void	ft_raycasting(t_data *data)
{
	int	i;

	data->map->seen[(int)data->player->pos_y * data->map->width
		+ (int)data->player->pos_x] = 1;
	i = 0;
	while (i < WIDTH)
	{
		init_raycasting(data, i);
		algo_dda(data);
		compute_wall_dist(data);
		data->raycast->zbuf[i] = data->raycast->wall_dist;
		if (i == WIDTH / 2)
			data->hud.center_dist = data->raycast->wall_dist;
		put_texture(data, i);
		draw_background_column(data, i);
		draw_door_layer(data, i);
		i++;
	}
}
