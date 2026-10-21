/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:39:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:20:49 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// x, y: pixel relative to the minimap center
static void	mini_pixel(t_data *data, t_view *v, int x, int y)
{
	t_img			*img;
	unsigned int	*px;
	int				d2;

	img = data->mlx->img[BACKGROUND];
	px = (unsigned int *)(img->addr + (MINI_POS + MINI_R + y) * img->line_len
			+ (MINI_POS + MINI_R + x) * (img->bpp / 8));
	d2 = x * x + y * y;
	if (d2 > (MINI_R - MINI_BORDER) * (MINI_R - MINI_BORDER))
		*px = MINI_BORDER_COLOR;
	else
		*px = mix(map_pixel(data, v, x, y), *px);
}

// drawn straight into the 3D image: mlx has no transparency,
// so a separate image could not be round
void	load_mini_map(t_data *data)
{
	t_view	v;
	int		x;
	int		y;

	if (data->mini.big)
		return ;
	v.wx = data->player->pos_x;
	v.wy = data->player->pos_y;
	v.scale = data->mini.scale;
	v.rotate = data->mini.rotate;
	y = -MINI_R;
	while (++y < MINI_R)
	{
		x = -MINI_R;
		while (++x < MINI_R)
		{
			if (x * x + y * y <= MINI_R * MINI_R)
				mini_pixel(data, &v, x, y);
		}
	}
}

// call after mlx_put_image_to_window (the text is drawn on the window)
void	draw_mini_north(t_data *data)
{
	int	nx;
	int	ny;

	if (data->mini.big)
		return ;
	nx = 0;
	ny = -(MINI_R - 12);
	if (data->mini.rotate)
	{
		nx = (int)(-data->raycast->dir_x * (MINI_R - 12));
		ny = (int)(data->raycast->dir_y * (MINI_R - 12));
	}
	mlx_string_put(data->mlx->mlx, data->mlx->win, MINI_POS + MINI_R + nx - 3,
		MINI_POS + MINI_R + ny + 4, 0xFFFFFF, "N");
}
