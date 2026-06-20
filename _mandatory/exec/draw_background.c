/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 23:28:49 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 18:15:13 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

static void	draw_celing(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = rgb_to_int(data->texture_c->red,
			data->texture_c->green, data->texture_c->blue);
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT / 2)
		{
			put_pixel(data->mlx->img[5], x, y, color);
			y++;
		}
		x++;
	}
}

static void	draw_floor(t_data *data)
{
	int	x;
	int	y;
	int	color;

	x = 0;
	color = rgb_to_int(data->texture_f->red,
			data->texture_f->green, data->texture_f->blue);
	while (x < WIDTH)
	{
		y = HEIGHT / 2;
		while (y < HEIGHT)
		{
			put_pixel(data->mlx->img[5], x, y, color);
			y++;
		}
		x++;
	}
}

static void	fill_background(t_data *data)
{
	draw_celing(data);
	draw_floor(data);
}

int	load_background(t_data *data)
{
	if (!data->mlx->img[5])
	{
		data->mlx->img[5] = malloc(sizeof(t_img));
		if (!data->mlx->img[5])
			return (1);
	}
	if (!data->mlx->img[5]->img)
	{
		data->mlx->img[5]->img = mlx_new_image(data->mlx->mlx, WIDTH, HEIGHT);
		if (!data->mlx->img[5]->img)
			return (printf("Erreur : mlx_new_image a échoué !\n"), 1);
		data->mlx->img[5]->width = WIDTH;
		data->mlx->img[5]->height = HEIGHT;
		data->mlx->img[5]->addr = mlx_get_data_addr(
				data->mlx->img[5]->img,
				&data->mlx->img[5]->bpp,
				&data->mlx->img[5]->line_len,
				&data->mlx->img[5]->endian);
		if (!data->mlx->img[5]->addr)
			return (printf("Erreur : mlx_get_data_addr a échoué !\n"), 1);
	}
	fill_background(data);
	return (0);
}
