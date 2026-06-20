/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:10:19 by andjenna          #+#    #+#             */
/*   Updated: 2025/02/22 18:21:50 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

static void	ft_dir_ns(t_data *data, char c)
{
	if (c == 'N')
	{
		data->raycast->dir_x = 0;
		data->raycast->dir_y = -1;
		data->raycast->plane_x = 0.66;
		data->raycast->plane_y = 0;
	}
	else if (c == 'S')
	{
		data->raycast->dir_x = 0;
		data->raycast->dir_y = 1;
		data->raycast->plane_x = -0.66;
		data->raycast->plane_y = 0;
	}
}

static void	ft_dir_ew(t_data *data, char c)
{
	if (c == 'E')
	{
		data->raycast->dir_x = 1;
		data->raycast->dir_y = 0;
		data->raycast->plane_x = 0;
		data->raycast->plane_y = 0.66;
	}
	else if (c == 'W')
	{
		data->raycast->dir_x = -1;
		data->raycast->dir_y = 0;
		data->raycast->plane_x = 0;
		data->raycast->plane_y = -0.66;
	}
}

static void	ft_set_player_dir(t_data *data, char c)
{
	ft_dir_ns(data, c);
	ft_dir_ew(data, c);
}

int	ft_get_player_dir(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (ft_strchr("NSWE", data->map->map_tab[i][j]))
			{
				ft_set_player_dir(data, data->map->map_tab[i][j]);
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

// 0.5 est ajouté pour placer le joueur au centre de la case
int	ft_get_player_pos(t_data *data)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		j = 0;
		while (j < ft_strlen(data->map->map_tab[i]))
		{
			if (data->map->map_int[i][j] == 3)
			{
				data->player->pos_y = (double)i + 0.5;
				data->player->pos_x = (double)j + 0.5;
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}
