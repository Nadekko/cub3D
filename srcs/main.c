/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:41:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/27 18:37:40 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	ft_init_matrix(t_data *data)
{
	data->map->width = ft_longest_line(data->map->map_tab);
	data->map->height = ft_tab_len(data->map->map_tab);
	data->map->map_int = ft_convert_map(data->map->map_tab);
	if (mlx_window_init(data))
		return (ft_free_data(data),
			ft_putendl_fd("Error initalizing window failed", 2), 1);
	ft_clean_init_player(data);
	ft_clean_init_raycast(data);
	ft_clean_init_move(data);
	if (ft_get_player_pos(data) || ft_clean_init_elements(data))
		return (ft_free_data(data),
			ft_putendl_fd("Error no player or error initializing elements",
				2), 1);
	data->color_c = rgb_to_int(data->texture_c->red, data->texture_c->green,
			data->texture_c->blue);
	data->color_f = rgb_to_int(data->texture_f->red, data->texture_f->green,
			data->texture_f->blue);
	ft_display_game(data);
	ft_free_data(data);
	return (0);
}

static int	ft_data_start(t_data *data, char **file)
{
	if (mlx_start(data))
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error initalizing mlx failed", 2), 1);
	if (ft_check_textures(data) || ft_check_rgb(data))
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error invalid textures / image files", 2), 1);
	else if (ft_check_map_closed(data->map->map_tab)
		|| ft_check_player(data->map->map_tab))
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error invalid map file", 2), 1);
	return (0);
}

static int	ft_init_game(t_data *data, char *map_file)
{
	char	**file;

	file = ft_read_map(map_file);
	if (!file)
		return (ft_putendl_fd("Error can't read map", 2), 1);
	ft_clean_init_data(data);
	if (ft_get_data(data, file))
	{
		if (ft_data_start(data, file))
			return (1);
	}
	else
		return (ft_free_data(data), ft_free_tab(file),
			ft_putendl_fd("Error invalid file", 2), 1);
	ft_free_tab(file);
	if (ft_init_matrix(data))
		return (1);
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (!env || !*env)
		return (ft_putendl_fd("Error env is needed to launch cub3d", 2), 1);
	else if (ac != 2)
		return (ft_putendl_fd("Error wrong arguments count", 2), 1);
	else if (!ft_check_map_extension(av[1]))
		return (ft_putendl_fd("Error invalid map extension", 2), 1);
	else
	{
		if (ft_init_game(&data, av[1]))
			return (1);
	}
	return (0);
}
