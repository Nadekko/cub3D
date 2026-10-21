/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hud.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:38:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/28 15:26:32 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

// average fps, recomputed every 500 ms
void	hud_update(t_data *data)
{
	long	now;

	now = get_time_ms();
	if (data->hud.last_fps == 0)
		data->hud.last_fps = now;
	data->hud.frames++;
	if (now - data->hud.last_fps >= 500)
	{
		data->hud.fps = data->hud.frames * 1000 / (now - data->hud.last_fps);
		data->hud.frame_ms = (now - data->hud.last_fps)
			/ (double)data->hud.frames;
		data->hud.frames = 0;
		data->hud.last_fps = now;
	}
}

static void	hud_lines_player(t_data *data, char l[HUD_LINES][HUD_BUF])
{
	double	angle;

	ft_strlcat(l[0], "FPS: ", HUD_BUF);
	hud_cat_int(l[0], data->hud.fps);
	ft_strlcat(l[0], "  (", HUD_BUF);
	hud_cat_double(l[0], data->hud.frame_ms);
	ft_strlcat(l[0], " ms)", HUD_BUF);
	ft_strlcat(l[1], "Pos: ", HUD_BUF);
	hud_cat_double(l[1], data->player->pos_x);
	ft_strlcat(l[1], ", ", HUD_BUF);
	hud_cat_double(l[1], data->player->pos_y);
	ft_strlcat(l[1], "  case ", HUD_BUF);
	hud_cat_int(l[1], (int)data->player->pos_x);
	ft_strlcat(l[1], ",", HUD_BUF);
	hud_cat_int(l[1], (int)data->player->pos_y);
	angle = atan2(data->raycast->dir_y, data->raycast->dir_x) * 180.0 / M_PI;
	if (angle < 0)
		angle += 360.0;
	ft_strlcat(l[2], "Angle: ", HUD_BUF);
	hud_cat_double(l[2], angle);
	ft_strlcat(l[2], " deg", HUD_BUF);
}

static void	hud_lines_world(t_data *data, char l[HUD_LINES][HUD_BUF])
{
	t_doors	*door;

	ft_strlcat(l[3], "Mur (centre): ", HUD_BUF);
	hud_cat_double(l[3], data->hud.center_dist);
	ft_strlcat(l[4], "Porte: ", HUD_BUF);
	door = door_in_front(data);
	if (!door)
		ft_strlcat(l[4], "-", HUD_BUF);
	else if (door->state == D_CLOSED)
		ft_strlcat(l[4], "fermee", HUD_BUF);
	else if (door->state == D_OPENING)
		ft_strlcat(l[4], "ouverture", HUD_BUF);
	else if (door->state == D_OPEN)
		ft_strlcat(l[4], "ouverte", HUD_BUF);
	else
		ft_strlcat(l[4], "fermeture", HUD_BUF);
	ft_strlcat(l[5], "Carte: ", HUD_BUF);
	hud_cat_int(l[5], data->map->width);
	ft_strlcat(l[5], "x", HUD_BUF);
	hud_cat_int(l[5], data->map->height);
	ft_strlcat(l[6], "[M] carte [R] rot [TAB] hud", HUD_BUF);
}

// call before mlx_put_image_to_window
void	hud_draw_box(t_data *data)
{
	if (!data->hud.show)
		return ;
	hud_darken(data->mlx->img[BACKGROUND], WIDTH - HUD_W - 10, 10);
}

// call after mlx_put_image_to_window (the text is drawn on the window)
void	hud_draw_text(t_data *data)
{
	char	l[HUD_LINES][HUD_BUF];
	int		i;

	if (!data->hud.show)
		return ;
	ft_bzero(l, sizeof(l));
	hud_lines_player(data, l);
	hud_lines_world(data, l);
	i = 0;
	while (i < HUD_LINES)
	{
		mlx_string_put(data->mlx->mlx, data->mlx->win, WIDTH - HUD_W,
			25 + i * HUD_LINE_H, 0xFFFFFF, l[i]);
		i++;
	}
}
