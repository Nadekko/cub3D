/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/23 06:05:08 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

void	draw_player_to_image(t_data *data)
{
	put_img_to_img(data, *data->mlx->img[PLAYER], 0, 0);
}

static void	set_texture(t_data *data)
{
	if (data->raycast->side == 0)
	{
		if (data->raycast->ray_x > 0)
			data->raycast->texture = NO_TEXTURE;
		else
			data->raycast->texture = SO_TEXTURE;
	}
	else
	{
		if (data->raycast->ray_y > 0)
			data->raycast->texture = EA_TEXTURE;
		else
			data->raycast->texture = WE_TEXTURE;
	}
	if (data->raycast->side == 0)
		data->raycast->wall_x = data->player->pos_y + data->raycast->wall_dist
			* data->raycast->ray_y;
	else
		data->raycast->wall_x = data->player->pos_x + data->raycast->wall_dist
			* data->raycast->ray_x;
	data->raycast->wall_x -= floor(data->raycast->wall_x);
}

static void	put_shade(t_data *data, int i, int y)
{
	double	shade;
	int		color;
	double	r;
	double	g;
	double	b;

	shade = 1.0 / (1.0 + data->raycast->wall_dist * 0.2);
	color = get_pixel(*data->mlx->img[data->raycast->texture],
			data->raycast->tex_x, data->raycast->tex_y);
	r = ((color >> 16) & 0xFF) * shade;
	g = ((color >> 8) & 0xFF) * shade;
	b = (color & 0xFF) * shade;
	color = rgb_to_int(r, g, b);
	put_pixel(data->mlx->img[BACKGROUND], i, y, color);
}

void	put_texture(t_data *data, int i)
{
	int		y;
	double	step;

	set_texture(data);
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
		put_shade(data, i, y);
		y++;
	}
}
