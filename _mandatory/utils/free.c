/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 23:44:57 by ede-cola          #+#    #+#             */
/*   Updated: 2025/02/22 18:16:01 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub.h"

int	ft_free_int_tab(t_data *data)
{
	size_t	i;

	i = 0;
	while (i < ft_tab_len(data->map->map_tab))
	{
		free(data->map->map_int[i]);
		i++;
	}
	free(data->map->map_int);
	return (0);
}

void	ft_free_texture(t_data *data)
{
	free(data->texture_f);
	free(data->texture_c);
	free(data->texture_n);
	free(data->texture_s);
	free(data->texture_e);
	free(data->texture_w);
}

int	ft_free_data(t_data *data)
{
	if (data->map)
	{
		if (data->map->map_int)
			ft_free_int_tab(data);
		ft_free_tab(data->map->map_tab);
		free(data->map);
	}
	if (data->mlx)
	{
		if (data->mlx->mlx)
			ft_free_mlx(data->mlx);
		free(data->mlx);
	}
	if (data->player)
		free(data->player);
	if (data->raycast)
		free(data->raycast);
	ft_free_texture(data);
	return (0);
}

int	ft_free_exit(t_data *data)
{
	if (data->map)
	{
		if (data->map->map_int)
			ft_free_int_tab(data);
		ft_free_tab(data->map->map_tab);
		free(data->map);
	}
	if (data->mlx)
	{
		if (data->mlx->mlx)
		{
			ft_free_img(data->mlx, IMG_COUNT);
			if (data->mlx->win)
				mlx_destroy_window(data->mlx->mlx, data->mlx->win);
			mlx_destroy_display(data->mlx->mlx);
			free(data->mlx->mlx);
		}
		free(data->mlx);
	}
	if (data->player)
		free(data->player);
	if (data->raycast)
		free(data->raycast);
	ft_free_texture(data);
	exit(0);
}

int	ft_free_img(t_mlx *mlx, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (mlx->img[i])
		{
			mlx_destroy_image(mlx->mlx, mlx->img[i]->img);
			free(mlx->img[i]);
			mlx->img[i] = NULL;
		}
		i++;
	}
	return (0);
}
