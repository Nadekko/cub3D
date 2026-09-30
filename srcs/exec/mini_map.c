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

void	draw_on_mini_map(t_img *img, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			if ((x + i) >= 0 && (x + i) < MINISIZE && (y + j) >= 0 && (y
					+ j) < MINISIZE)
				put_pixel(img, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

void	clear_mini_map(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < MINISIZE)
	{
		x = 0;
		while (x < MINISIZE)
		{
			put_pixel(img, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

static void	ft_fill_mini(t_data *data, int x, int y)
{
	int	map_x;
	int	map_y;
	int	offset[2];

	offset[0] = data->player->pos_x - ((MINISIZE / 2.0) / 30);
	offset[1] = data->player->pos_y - ((MINISIZE / 2.0) / 30);
	map_x = (int)(offset[0] + (x / (double)30));
	map_y = (int)(offset[1] + (y / (double)30));
	if (map_x >= 0 && map_x < data->map->width && map_y >= 0
		&& map_y < data->map->height)
	{
		if (data->map->map_tab[map_y][map_x] == '1')
			draw_on_mini_map(data->mlx->img[MINI_MAP], x, y, 0xbb8fce);
		else if (data->map->map_tab[map_y][map_x] == '0'
			|| ft_strchr("NSWE", data->map->map_tab[map_y][map_x]))
			draw_on_mini_map(data->mlx->img[MINI_MAP], x, y, 0xabb2b9);
		else if (data->map->map_tab[map_y][map_x] == 'D')
			draw_on_mini_map(data->mlx->img[MINI_MAP], x, y, 0xf6b5fd);
	}
}

void	fill_mini_map(t_data *data)
{
	int		x;
	int		y;

	clear_mini_map(data->mlx->img[MINI_MAP]);
	y = -1;
	while (++y < MINISIZE)
	{
		x = -1;
		while (++x < MINISIZE)
			ft_fill_mini(data, x, y);
	}
	draw_on_mini_map(data->mlx->img[MINI_MAP], MINISIZE / 2, MINISIZE / 2,
		0xFF0000);
}

void	load_mini_map(t_data *data)
{
	fill_mini_map(data);
}
