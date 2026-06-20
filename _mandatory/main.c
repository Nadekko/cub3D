/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: andjenna <andjenna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 21:41:31 by andjenna          #+#    #+#             */
/*   Updated: 2025/03/14 17:52:11 by andjenna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

static int	ft_init_matrix(t_data *data)
{
	data->map->width = ft_strlen(data->map->map_tab[0]);
	data->map->height = ft_tab_len(data->map->map_tab);
	data->map->map_int = ft_convert_map(data->map->map_tab);
	if (mlx_window_init(data))
		return (ft_free_data(data),
			ft_putendl_fd("Error initalizing window failed", 2), 1);
	ft_clean_init_player(data);
	ft_clean_init_raycast(data);
	ft_clean_init_move(data);
	if (ft_get_player_pos(data))
		return (ft_free_data(data), ft_putendl_fd("Error no player position",
				2), 1);
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
			ft_putendl_fd("Error invalid textures / image files", 2),
			1);
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

// int	ft_init_game(t_data *data, char *map_file)
// {
// 	char	**file;
// 	size_t	i;
// 	size_t	j;

// 	file = ft_read_map(map_file);
// 	if (!file)
// 		return (ft_putendl_fd("Error can't read map", 2), 1);
// 	i = 0;
// 	ft_clean_init_data(data);
// 		if (ft_get_data(data, file))
// 		{
// 			printf("texture N = %s\n", data->texture_n);
// 			printf("texture S = %s\n", data->texture_s);
// 			printf("texture W = %s\n", data->texture_w);
// 			printf("texture E = %s\n", data->texture_e);
// 			printf("texture F = %d, %d, %d\n", data->texture_f->red,
// 				data->texture_f->green, data->texture_f->blue);
// 			printf("texture C = %d, %d, %d\n", data->texture_c->red,
// 				data->texture_c->green, data->texture_c->blue);
// 			while (data->map->map_tab[i])
// 			{
// 				printf("%s", data->map->map_tab[i]);
// 				i++;
// 			}
// 			if (mlx_start(data))
// 				return (ft_free_data(data), ft_free_tab(file),
// 					ft_putendl_fd("Error initalizing mlx failed", 2), 1);
// 			if (ft_check_textures(data) || ft_check_rgb(data))
// 				return (ft_free_data(data), ft_free_tab(file),
// 					ft_putendl_fd("Error invalid textures / image files", 2),
// 					1);
// 			else if (ft_check_map_closed(data->map->map_tab)
// 				|| ft_check_player(data->map->map_tab))
// 				return (ft_free_data(data), ft_free_tab(file),
// 					ft_putendl_fd("Error invalid map file", 2), 1);
// 		}
// 		else
// 			return (ft_free_data(data), ft_free_tab(file),
// 				ft_putendl_fd("Error invalid file", 2), 1);
// 		ft_free_tab(file);
// 		data->map->width = ft_strlen(data->map->map_tab[0]);
// 		data->map->height = ft_tab_len(data->map->map_tab);
// 		data->map->map_int = ft_convert_map(data->map->map_tab);
// 		if (mlx_window_init(data))
// 			return (ft_free_data(data),
// 				ft_putendl_fd("Error initalizing window failed", 2), 1);
// 		i = 0;
// 		printf("\n");
// 		while (i < ft_tab_len(data->map->map_tab))
// 		{
// 			printf("{");
// 			j = 0;
// 			while (j < ft_strlen(data->map->map_tab[i]) - 1)
// 			{
// 				printf("%d", data->map->map_int[i][j]);
// 				if (j != ft_strlen(data->map->map_tab[i]) - 2)
// 					printf(",");
// 				j++;
// 			}
// 			printf("}\n");
// 			i++;
// 		}
// 		ft_clean_init_player(data);
// 		ft_clean_init_raycast(data);
// 		ft_clean_init_move(data);
// 		if (!ft_get_player_pos(data))
// 			printf("player pos x = %f, player pos y = %f\n",
//				data->player->pos_x,
// 				data->player->pos_y);
// 		ft_display_game(data);
// 		ft_free_data(data);
// 		return (0);
// }
