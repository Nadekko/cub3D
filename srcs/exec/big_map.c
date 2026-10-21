/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:39:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:20:49 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// scale that fits the whole map on screen
static double	big_fit(t_data *data)
{
	double	sx;
	double	sy;

	sx = (WIDTH - 2 * BIG_MARGIN) / (double)data->map->width;
	sy = (HEIGHT - 2 * BIG_MARGIN) / (double)data->map->height;
	if (sx < sy)
		return (sx);
	return (sy);
}

// whole map centered, or centered on the player once zoomed in
static void	big_view(t_data *data, t_view *v)
{
	v->scale = big_fit(data) * data->mini.big_zoom;
	v->rotate = 0;
	v->wx = data->map->width / 2.0;
	v->wy = data->map->height / 2.0;
	if (data->mini.big_zoom > 1.0)
	{
		v->wx = data->player->pos_x;
		v->wy = data->player->pos_y;
	}
}

void	draw_big_map(t_data *data)
{
	t_view			v;
	t_img			*img;
	unsigned int	*px;
	int				x;
	int				y;

	if (!data->mini.big)
		return ;
	img = data->mlx->img[BACKGROUND];
	big_view(data, &v);
	y = BIG_MARGIN - 1;
	while (++y < HEIGHT - BIG_MARGIN)
	{
		x = BIG_MARGIN - 1;
		while (++x < WIDTH - BIG_MARGIN)
		{
			px = (unsigned int *)(img->addr + y * img->line_len
					+ x * (img->bpp / 8));
			*px = mix(map_pixel(data, &v, x - WIDTH / 2, y - HEIGHT / 2),
					*px);
		}
	}
}

void	map_keys(int keycode, t_data *data)
{
	if (keycode == KEY_M)
		data->mini.big = !data->mini.big;
	if (keycode == KEY_R)
		data->mini.rotate = !data->mini.rotate;
}

// mouse wheel: zooms the big map if it is open, else the minimap
void	map_zoom(t_data *data, int zoom_in)
{
	double	f;

	f = 1.0 / 1.2;
	if (zoom_in)
		f = 1.2;
	if (data->mini.big)
	{
		data->mini.big_zoom *= f;
		if (data->mini.big_zoom < 1.0)
			data->mini.big_zoom = 1.0;
		if (data->mini.big_zoom > BIG_ZOOM_MAX)
			data->mini.big_zoom = BIG_ZOOM_MAX;
		return ;
	}
	data->mini.scale *= f;
	if (data->mini.scale < MINI_SCALE_MIN)
		data->mini.scale = MINI_SCALE_MIN;
	if (data->mini.scale > MINI_SCALE_MAX)
		data->mini.scale = MINI_SCALE_MAX;
}
