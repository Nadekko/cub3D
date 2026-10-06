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

static int	mini_color(t_data *data, int map_x, int map_y)
{
	char	c;

	if (map_x < 0 || map_y < 0 || map_x >= data->map->width
		|| map_y >= data->map->height)
		return (0x000000);
	c = data->map->map_tab[map_y][map_x];
	if (c == '1')
		return (0xbb8fce);
	if (c == 'D')
		return (0xf6b5fd);
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0xabb2b9);
	return (0x000000);
}

static void	fill_mini_row(t_data *data, int *row, int y, double *off)
{
	int	x;
	int	map_x;
	int	map_y;

	map_y = (int)floor(off[1] + y / (double)MINI_SCALE);
	x = 0;
	while (x < MINISIZE)
	{
		map_x = (int)floor(off[0] + x / (double)MINI_SCALE);
		row[x] = mini_color(data, map_x, map_y);
		x++;
	}
}

static void	draw_mini_player(t_img *img)
{
	int	x;
	int	y;
	int	*row;

	y = MINISIZE / 2 - MINI_PLAYER / 2;
	while (y < MINISIZE / 2 + MINI_PLAYER / 2)
	{
		row = (int *)(img->addr + y * img->line_len);
		x = MINISIZE / 2 - MINI_PLAYER / 2;
		while (x < MINISIZE / 2 + MINI_PLAYER / 2)
		{
			row[x] = 0xFF0000;
			x++;
		}
		y++;
	}
}

void	load_mini_map(t_data *data)
{
	t_img	*img;
	double	off[2];
	int		y;

	img = data->mlx->img[MINI_MAP];
	off[0] = data->player->pos_x - (MINISIZE / 2.0) / MINI_SCALE;
	off[1] = data->player->pos_y - (MINISIZE / 2.0) / MINI_SCALE;
	y = 0;
	while (y < MINISIZE)
	{
		fill_mini_row(data, (int *)(img->addr + y * img->line_len), y, off);
		y++;
	}
	draw_mini_player(img);
}

// void	draw_on_mini_map(t_img *img, int x, int y, int color)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < TILE_SIZE)
// 	{
// 		j = 0;
// 		while (j < TILE_SIZE)
// 		{
// 			if ((x + i) >= 0 && (x + i) < MINISIZE && (y + j) >= 0 && (y
// 					+ j) < MINISIZE)
// 				put_pixel(img, x + i, y + j, color);
// 			j++;
// 		}
// 		i++;
// 	}
// }

// void	clear_mini_map(t_img *img)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < MINISIZE)
// 	{
// 		x = 0;
// 		while (x < MINISIZE)
// 		{
// 			put_pixel(img, x, y, 0x000000);
// 			x++;
// 		}
// 		y++;
// 	}
// }

// static void	ft_fill_mini(t_data *data, int x, int y)
// {
// 	int	map_x;
// 	int	map_y;
// 	int	offset[2];

// 	offset[0] = data->player->pos_x - ((MINISIZE / 2.0) / 30);
// 	offset[1] = data->player->pos_y - ((MINISIZE / 2.0) / 30);
// 	map_x = (int)(offset[0] + (x / (double)30));
// 	map_y = (int)(offset[1] + (y / (double)30));
// 	if (map_x >= 0 && map_x < data->map->width && map_y >= 0
// 		&& map_y < data->map->height)
// 	{
// 		if (data->map->map_tab[map_y][map_x] == '1')
// 			draw_on_mini_map(data->mlx->img[MINI_MAP], x, y, 0xbb8fce);
// 		else if (data->map->map_tab[map_y][map_x] == '0'
// 			|| ft_strchr("NSWE", data->map->map_tab[map_y][map_x]))
// 			draw_on_mini_map(data->mlx->img[MINI_MAP], x, y, 0xabb2b9);
// 		else if (data->map->map_tab[map_y][map_x] == 'D')
// 			draw_on_mini_map(data->mlx->img[MINI_MAP], x, y, 0xf6b5fd);
// 	}
// }

// void	fill_mini_map(t_data *data)
// {
// 	int		x;
// 	int		y;

// 	clear_mini_map(data->mlx->img[MINI_MAP]);
// 	y = -1;
// 	while (++y < MINISIZE)
// 	{
// 		x = -1;
// 		while (++x < MINISIZE)
// 			ft_fill_mini(data, x, y);
// 	}
// 	draw_on_mini_map(data->mlx->img[MINI_MAP], MINISIZE / 2, MINISIZE / 2,
// 		0xFF0000);
// }

// void	load_mini_map(t_data *data)
// {
// 	fill_mini_map(data);
// }
