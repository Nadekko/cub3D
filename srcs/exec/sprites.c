/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 14:41:48 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:21:52 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"
#include <X11/keysym.h>

int	animation_paws(t_data *data)
{
	long	now;

	if (!data->anim_running)
		return (0);
	now = get_time_ms();
	if (now - data->anim_last >= PAW_FRAME_MS)
	{
		data->anim_frame++;
		data->anim_last = now;
	}
	if (data->anim_frame > 9)
	{
		data->anim_running = 0;
		data->anim_frame = 0;
	}
	return (0);
}

void	ft_reset_doors(t_data *data, t_doors *door)
{
	int	x;
	int	y;

	x = door->x;
	y = door->y;
	door->is_open = 0;
	door->has_been_open = 0;
	door->anim_frame = 0;
	data->map->map_int[y][x] = 6;
}

int	animation_doors(t_data *data)
{
	int		i;
	long	now;

	if (!data->doors)
		return (0);
	now = get_time_ms();
	i = 0;
	while (i < data->doors->nb)
	{
		if (data->doors[i].is_open && !data->doors[i].has_been_open
			&& now - data->doors[i].last >= DOOR_FRAME_MS)
		{
			data->doors[i].anim_frame++;
			data->doors[i].last = now;
			if (data->doors[i].anim_frame > 4)
				ft_reset_doors(data, &data->doors[i]);
		}
		i++;
	}
	return (0);
}

int	is_near_player(t_data *data)
{
	int		i;
	t_doors	*door;
	float	dist_x;
	float	dist_y;

	if (!data->doors)
		return (0);
	i = -1;
	while (++i < data->doors->nb)
	{
		door = &data->doors[i];
		dist_x = door->x - data->player->pos_x;
		dist_y = door->y - data->player->pos_y;
		if (dist_x * dist_x + dist_y * dist_y <= 4.0 && !door->has_been_open
			&& dist_x * data->raycast->dir_x
			+ dist_y * data->raycast->dir_y > 0)
		{
			door->is_open = 1;
			door->anim_frame = 1;
			door->last = get_time_ms();
			data->map->map_int[(int)door->y][(int)door->x] = 5;
			return (1);
		}
	}
	return (0);
}

int	mouse_press(int button, int x, int y, t_data *data)
{
	(void)x;
	(void)y;
	if (button == 1)
	{
		is_near_player(data);
		data->anim_frame = 1;
		data->anim_running = 1;
		data->anim_last = get_time_ms();
	}
	return (0);
}

// int	animation_paws(t_data *data)
// {
// 	if (!data->anim_running)
// 		return (0);
// 	if (data->anim_frame > 9)
// 	{
// 		data->anim_running = 0;
// 		data->anim_frame = 0;
// 		return (0);
// 	}
// 	load_background(data);
// 	ft_raycasting(data);
// 	put_img_to_img(data, *data->mlx->img[PLAYER + data->anim_frame], 0, 0);
// 	data->anim_frame++;
// 	usleep(10000);
// 	return (0);
// }

// int	animation_doors(t_data *data)
// {
// 	int	i;

// 	if (!data->doors)
// 		return (0);
// 	i = 0;
// 	while (i < data->doors->nb)
// 	{
// 		if (data->doors[i].is_open && data->doors[i].anim_frame > 4
// 			&& !data->doors[i].has_been_open)
// 		{
// 			ft_reset_doors(data, &data->doors[i]);
// 			return (0);
// 		}
// 		else if (data->doors[i].is_open && data->doors[i].anim_frame <= 4
// 			&& !data->doors[i].has_been_open)
// 		{
// 			data->doors[i].anim_frame++;
// 			mlx_do_sync(data->mlx->mlx);
// 			usleep(10000);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
// int	is_near_player(t_data *data)
// {
// 	int		i;
// 	int		y;
// 	float	dist_x;
// 	float	dist_y;
// 	float	dist;

// 	if (!data->doors)
// 		return (0);
// 	i = 0;
// 	while (i < data->doors->nb)
// 	{
// 		dist_x = data->doors[i].x - data->player->pos_x;
// 		dist_y = data->doors[i].y - data->player->pos_y;
// 		dist = sqrt(dist_x * dist_x + dist_y * dist_y);
// 		y = data->doors[i].y;
// 		if (dist <= 2.0 && (dist_x * data->raycast->dir_x + dist_y
// 				* data->raycast->dir_y > 0) && !data->doors[i].has_been_open)
// 		{
// 			data->doors[i].is_open = 1;
// 			data->doors[i].anim_frame = 1;
// 			data->map->map_int[y][(int)data->doors[i].x] = 5;
// 			return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }
