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

static void	algo_dda(t_data *data)
{
	int	hit;
	int	map_y;

	hit = 0;
	while (!hit)
	{
		if (data->raycast->side_x < data->raycast->side_y)
		{
			data->raycast->side_x += data->raycast->delta_x;
			data->raycast->map_x += data->raycast->step_x;
			data->raycast->side = 0;
		}
		else
		{
			data->raycast->side_y += data->raycast->delta_y;
			data->raycast->map_y += data->raycast->step_y;
			data->raycast->side = 1;
		}
		map_y = data->raycast->map_y;
		if (data->map->map_int[map_y][data->raycast->map_x] == 1
			|| data->map->map_int[map_y][data->raycast->map_x] == 4
			|| data->map->map_int[map_y][data->raycast->map_x] == 5)
			hit = 1;
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
	data->raycast->line_height = (int)(HEIGHT / data->raycast->wall_dist);
	data->raycast->draw_start = -data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_start < 0)
		data->raycast->draw_start = 0;
	data->raycast->draw_end = data->raycast->line_height / 2 + HEIGHT / 2;
	if (data->raycast->draw_end >= HEIGHT)
		data->raycast->draw_end = HEIGHT;
}

void	draw_sprites(t_data *data, int i, int y)
{
	double			shade;
	unsigned int	color;
	double			r;
	double			g;
	double			b;

	shade = 1.0 / (1.0 + data->raycast->wall_dist * 0.2);
	color = get_pixel(*data->mlx->img[data->raycast->texture],
			data->raycast->tex_x, data->raycast->tex_y);
	if (color != 0xFF000000)
	{
		r = ((color >> 16) & 0xFF) * shade;
		g = ((color >> 8) & 0xFF) * shade;
		b = (color & 0xFF) * shade;
		color = rgb_to_int(r, g, b);
		put_pixel(data->mlx->img[BACKGROUND], i, y, color);
	}
}

void	draw_doors(t_data *data, int i)
{
	int		y;
	double	step;

	y = data->raycast->draw_start;
	data->raycast->tex_x = (int)(data->raycast->wall_x * (double)PIXEL);
	step = (double)PIXEL / data->raycast->line_height;
	data->raycast->tex_p = (data->raycast->draw_start - HEIGHT / 2
			+ data->raycast->line_height / 2) * step;
	if ((data->raycast->side == 0 && data->raycast->ray_x > 0)
		|| (data->raycast->side == 1 && data->raycast->ray_y < 0))
		data->raycast->tex_x = PIXEL - data->raycast->tex_x - 1;
	while (y < data->raycast->draw_end)
	{
		data->raycast->tex_y = (int)data->raycast->tex_p % PIXEL;
		data->raycast->tex_p += step;
		if (data->raycast->texture >= DOOR && data->raycast->texture <= DOOR
			+ 4)
			draw_sprites(data, i, y);
		y++;
	}
}

void	ft_raycasting(t_data *data)
{
	int	i;

	i = 0;
	while (i < WIDTH)
	{
		init_raycasting(data, i);
		algo_dda(data);
		compute_wall_dist(data);
		put_texture(data, i);
		draw_doors(data, i);
		i++;
	}
}
