/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:59 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:40 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	door_gestion(t_data *data)
{
	int	i;
	int	r_map_x;
	int	r_map_y;

	if (!data->doors)
		return ;
	i = 0;
	r_map_x = data->raycast->map_x;
	r_map_y = data->raycast->map_y;
	while (i < data->doors->nb)
	{
		if (data->doors[i].is_open == 1 && data->doors[i].anim_frame <= 4
			&& !data->doors[i].has_been_open
			&& data->map->map_int[r_map_y][r_map_x] == 5)
		{
			data->raycast->texture = DOOR + data->doors[i].anim_frame;
			break ;
		}
		else if (data->map->map_int[r_map_y][r_map_x] == 4
			&& (data->doors[i].is_open == 0
				|| data->doors[i].has_been_open))
			data->raycast->texture = DOOR;
		i++;
	}
}

static void	set_texture2(t_data *data)
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
}

static void	set_texture(t_data *data)
{
	if (data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 4
		|| data->map->map_int[data->raycast->map_y][data->raycast->map_x] == 5)
		door_gestion(data);
	else
		set_texture2(data);
	if (data->raycast->side == 0)
		data->raycast->wall_x = data->player->pos_y + data->raycast->wall_dist
			* data->raycast->ray_y;
	else
		data->raycast->wall_x = data->player->pos_x + data->raycast->wall_dist
			* data->raycast->ray_x;
	data->raycast->wall_x -= floor(data->raycast->wall_x);
}

void	put_shade(t_data *data, int i, int y)
{
	t_img			*dst;
	unsigned int	color;
	double			shade;

	color = get_pixel(data->mlx->img[data->raycast->texture],
			data->raycast->tex_x, data->raycast->tex_y);
	if (color == 0xFF000000)
		return ;
	shade = data->raycast->shade;
	color = rgb_to_int(((color >> 16) & 0xFF) * shade,
			((color >> 8) & 0xFF) * shade, (color & 0xFF) * shade);
	dst = data->mlx->img[BACKGROUND];
	*(unsigned int *)(dst->addr + y * dst->line_len
			+ i * (dst->bpp / 8)) = color;
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
		if (data->raycast->texture < DOOR || data->raycast->texture > DOOR + 4)
			put_shade(data, i, y);
		y++;
	}
}
