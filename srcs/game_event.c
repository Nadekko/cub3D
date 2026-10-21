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

int	key_release(int keycode, t_data *data)
{
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 0;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 0;
	if (keycode == KEY_S)
		data->move.s = 0;
	if (keycode == KEY_D)
		data->move.d = 0;
	return (0);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == KEY_ESC)
	{
		data->exit = 1;
		ft_free_data(data);
	}
	if (keycode == KEY_Z || keycode == KEY_W)
		data->move.z = 1;
	if (keycode == KEY_Q || keycode == KEY_A)
		data->move.q = 1;
	if (keycode == KEY_S)
		data->move.s = 1;
	if (keycode == KEY_D)
		data->move.d = 1;
	if (keycode == KEY_TAB)
		data->hud.show = !data->hud.show;
	map_keys(keycode, data);
	return (0);
}

static int	ft_play(t_data *data)
{
	hud_update(data);
	animation_doors(data);
	ft_raycasting(data);
	load_mini_map(data);
	animation_paws(data);
	draw_player_to_image(data);
	draw_big_map(data);
	ft_move(data);
	hud_draw_box(data);
	mlx_put_image_to_window(data->mlx->mlx, data->mlx->win,
		data->mlx->img[BACKGROUND]->img, 0, 0);
	hud_draw_text(data);
	draw_mini_north(data);
	return (0);
}

// hides the mouse cursor, but mlx_mouse_hide leaks
void	ft_display_game(t_data *data)
{
	mlx_mouse_hide(data->mlx->mlx, data->mlx->win);
	init_ambiance(data);
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
