/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:28:49 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/24 16:30:04 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	fill_column(t_data *data, int x, int start, int end)
{
	t_img	*img;
	int		color;

	img = data->mlx->img[BACKGROUND];
	while (start < end)
	{
		if (start < HEIGHT / 2)
			color = data->color_c;
		else
			color = data->color_f;
		*(int *)(img->addr + start * img->line_len
				+ x * (img->bpp / 8)) = color;
		start++;
	}
}

void	draw_background_column(t_data *data, int x)
{
	if (data->raycast->texture >= DOOR && data->raycast->texture <= DOOR + 4)
	{
		fill_column(data, x, 0, HEIGHT);
		return ;
	}
	fill_column(data, x, 0, data->raycast->draw_start);
	fill_column(data, x, data->raycast->draw_end, HEIGHT);
}


// static void	draw_celing(t_data *data)
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	x = 0;
// 	color = rgb_to_int(data->texture_c->red,
// 			data->texture_c->green, data->texture_c->blue);
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < HEIGHT / 2)
// 		{
// 			put_pixel(data->mlx->img[BACKGROUND], x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// static void	draw_floor(t_data *data)
// {
// 	int	x;
// 	int	y;
// 	int	color;

// 	x = 0;
// 	color = rgb_to_int(data->texture_f->red,
// 			data->texture_f->green, data->texture_f->blue);
// 	while (x < WIDTH)
// 	{
// 		y = HEIGHT / 2;
// 		while (y < HEIGHT)
// 		{
// 			put_pixel(data->mlx->img[BACKGROUND], x, y, color);
// 			y++;
// 		}
// 		x++;
// 	}
// }

// int	load_background(t_data *data)
// {
// 	ft_raycasting(data);
// 	draw_celing(data);
// 	draw_floor(data);
// 	return (0);
// }
