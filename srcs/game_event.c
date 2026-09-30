/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_event_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:33:13 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/27 18:38:02 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	ft_play(t_data *data)
{
	animation_doors(data);
	load_background(data);
	ft_raycasting(data);
	load_mini_map(data);
	draw_player_to_image(data);
	animation_paws(data);
	ft_move(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[BACKGROUND]->img, 0, 0);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[MINI_MAP]->img, 10, 10);
	return (0);
}

// cette fonction permet de cacher le curseur de la souris mais elle leak
void	ft_display_game(t_data *data)
{
	mlx_mouse_hide(data->mlx->mlx, data->mlx->win); // function form minilibx (can leak)
	data->exit = 1;
	mlx_hook(data->mlx->win, 17, 1L << 17, ft_free_data, data);
	mlx_hook(data->mlx->win, 2, 1L << 0, key_press, data);
	mlx_loop_hook(data->mlx->mlx, &ft_play, data);
	mlx_hook(data->mlx->win, 3, 1L << 1, key_release, data);
	mlx_hook(data->mlx->win, 6, 1L << 6, mouse_move, data);
	mlx_hook(data->mlx->win, 4, 1L << 2, mouse_press, data);
	mlx_mouse_move(data->mlx->mlx, data->mlx->win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(data->mlx->mlx);
}
