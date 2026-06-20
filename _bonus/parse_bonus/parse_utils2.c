/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-cola <ede-cola@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 12:55:56 by ede-cola          #+#    #+#             */
/*   Updated: 2025/03/18 11:11:33 by ede-cola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub_bonus.h"

int	ft_check_data(t_data *data)
{
	return (data->map != NULL && data->texture_n != NULL
		&& data->texture_f != NULL && data->texture_c != NULL
		&& data->texture_s != NULL && data->texture_e != NULL
		&& data->texture_w != NULL);
}

int	ft_get_data(t_data *data, char **file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i])
	{
		j = 0;
		while (file[i] && file[i][j] && ft_is_whitespaces(file[i][j]))
			ft_skip_whitespaces(file, &i, &j);
		if (file[i])
		{
			if (ft_get_textures(file, data, i, j))
				return (0);
			ft_get_map(file, &i, j, data);
			if (file[i])
				i++;
		}
	}
	return (ft_check_data(data));
}

int	ft_check_one_extension(char *map)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (map[i])
	{
		if (map[i] == '.')
			flag++;
		i++;
	}
	if (flag != 1)
		return (0);
	return (1);
}

int	ft_check_map_extension(char *file)
{
	if (ft_strncmp(file + ft_strlen(file) - 4, ".cub", 4)
		|| !ft_check_one_extension(file))
		return (0);
	return (1);
}

int	ft_check_existance(char *texture)
{
	if (!texture)
		return (0);
	return (1);
}
