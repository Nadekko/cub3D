/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:32:27 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/23 06:02:20 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	ft_play(t_data *data)
{
	load_background(data);
	ft_raycasting(data);
	draw_player_to_image(data);
	ft_rotate(data);
	ft_move(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[5]->img, 0, 0);
	return (0);
}

void	ft_display_game(t_data *data)
{
	mlx_hook(data->mlx->win, 17, 1L << 17, ft_free_exit, data);
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx->mlx, &ft_play, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_loop(data->mlx->mlx);
}
